#include "concat.h"
#include <malloc.h>
#include <string.h>

char* concat (int count, const char **strings) {
    size_t result_size = 0;
    size_t result_allocated = 128;
    char *result = malloc(result_allocated);

    for (int i = 0; i < count; i++) {
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
