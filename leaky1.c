#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// no call to free malloc'd memory
int main(int argc, const char *argv[]) {
    char *s = malloc(100);
    strcpy(s, "Hello world!");
    printf("string is: %s\n", s);
    return 0;
}