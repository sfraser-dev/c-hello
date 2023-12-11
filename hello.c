#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // typedef of unnamed enum will have only a bool_t type
    typedef enum { FALSE, TRUE } bool_t;
    bool_t falsey = FALSE;
    !(FALSE) ? printf("falsey = %d\n", falsey) : 1 ;
 
    // enum simple
    enum vals { start = 10, next1, next2, end };
    enum vals ebegin = start;
    printf("start = %d\n", ebegin);
    enum vals en1 = next1;
    printf("next1 = %d\n", en1);
    enum vals en2 = next2;
    printf("next2 = %d\n", en2);
    enum vals eend = end;
    printf("next3 = %d\n", eend);

    // text-length plus one for implicitly added nul character '\0'
    char name_array_fixed[6] = "Harry";
    short size = (strlen(name_array_fixed) + 1) * sizeof(char);
    char *name_ptr_copy = malloc(size);
    strcpy(name_ptr_copy, name_array_fixed);
    printf("there are %lu letters in %s\n", strlen(name_array_fixed), name_array_fixed);
    printf("copying %s\n", name_ptr_copy);
    // clean up malloc'd memory
    free(name_ptr_copy);
    name_ptr_copy = NULL;

    // string of unkown length, count until '\0'
    char *name_ptr_unknown_length = "Poindexter";
    short len = 0;
    while (TRUE) {
        char c = *(name_ptr_unknown_length + len);
        if (c == '\0') {
            break;
        }
        len++;
    }
    printf("there are %d letters in %s\n", len, name_ptr_unknown_length);

    return 0;
}
