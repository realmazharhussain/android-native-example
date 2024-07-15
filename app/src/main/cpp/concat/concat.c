#include <jni.h>
#include <malloc.h>
#include <string.h>

typedef struct StrArray_ {
    jsize size;
    const char **data;
} StrArray;

void StrArray_destroy(StrArray *str_array) {
    str_array->size = 0;
    free(str_array->data);
}

StrArray StrArray_from_collection(JNIEnv *env, jobject this, jobject collection) {
    StrArray result = {0, NULL};

    jclass collection_class = (*env)->GetObjectClass(env, collection);

    jmethodID collection_size_method = (*env)->GetMethodID(env, collection_class, "size", "()I");
    jmethodID collection_iterator_method = (*env)->GetMethodID(env, collection_class, "iterator", "()Ljava/util/Iterator;");

    result.size = (*env)->CallIntMethod(env, collection, collection_size_method);
    jobject collection_iterator = (*env)->CallObjectMethod(env, collection, collection_iterator_method);

    jclass iterator_class = (*env)->GetObjectClass(env, collection_iterator);
    jmethodID iterator_next_method = (*env)->GetMethodID(env, iterator_class, "next", "()Ljava/lang/Object;");
    jmethodID iterator_has_next_method = (*env)->GetMethodID(env, iterator_class, "hasNext", "()Z");

    result.data = malloc(result.size);

    jobject element;
    for (jsize i = 0; i < result.size; i++) {
        element = (*env)->CallObjectMethod(env, collection_iterator, iterator_next_method);
        result.data[i] = (*env)->GetStringUTFChars(env, element, NULL);
    }
    return result;
}

char* concat (size_t count, const char **strings) {
    size_t result_size = 0;
    size_t result_allocated = 128;
    char *result = malloc(result_allocated);

    for (jsize i = 0; i < count; i++) {
        size_t str_length = strlen(strings[i]);

        // resize the string if needed
        if (str_length >= result_allocated - result_size) {
            char *old_data = (char *) result;
            result = malloc(result_allocated + 128);
            result_allocated += 128;
            strncpy(result, old_data, result_size);
            free(old_data);
        }

        strncpy(&result[result_size], strings[i], str_length);
        result_size += str_length;
    }

    result[result_size] = '\0';

    return result;
}

JNIEXPORT jstring JNICALL
Java_com_example_nativeapplication_Concat_concat(JNIEnv *env, jobject this, jobject args) {
    StrArray str_array = StrArray_from_collection(env, this, args);
    char *result_str = concat(str_array.size, str_array.data);
    jstring result = (*env)->NewStringUTF(env, result_str);

    free(result_str);
    StrArray_destroy(&str_array);
    return result;
}
