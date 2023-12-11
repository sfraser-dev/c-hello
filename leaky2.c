#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// using malloc'd memory after being freed 
int main(int argc, const char *argv[]) {
    char *s = malloc(100);
    free(s);
    strcpy(s, "Hello world!");
    printf("string is: %s\n", s);
    return 0;
}