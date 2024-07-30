#include <jni.h>
#include <malloc.h>
#include <concat.h>

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

JNIEXPORT jstring JNICALL
Java_com_example_nativeapplication_Concat_concat(JNIEnv *env, jobject this, jobject args) {
    StrArray str_array = StrArray_from_collection(env, this, args);
    char *result_str = concat(str_array.size, str_array.data);
    jstring result = (*env)->NewStringUTF(env, result_str);

    free(result_str);
    StrArray_destroy(&str_array);
    return result;
}
