#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // text-length plus one for implicitly added nul character '\0'
    char name_array_fixed[6] = "Harry";
    char *name_ptr_copy = malloc((strlen(name_array_fixed) + 1) * sizeof(char));
    strcpy(name_ptr_copy, name_array_fixed);
    printf("there are %llu letters in %s\n", strlen(name_array_fixed), name_array_fixed);
    printf("copying %s\n", name_ptr_copy);

    free(name_ptr_copy);
    name_ptr_copy = NULL;

    // string of unkown length
    char *name_ptr_unknown_length = "Poindexter";
    short len = 0;
    while (1) {
        char c = *(name_ptr_unknown_length + len);
        if (c == '\0') {
            break;
        }
        len++;
    }
    printf("there are %d characters in %s\n", len, name_ptr_unknown_length);
    free(name_ptr_unknown_length);
    name_ptr_unknown_length = NULL;

    return 0;
}
