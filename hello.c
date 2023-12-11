#include <pcre.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // typedef of unnamed enum will have only a bool_t type
    typedef enum { FALSE, TRUE } bool_t;
    bool_t falsey = FALSE;
    !(FALSE) ? printf("falsey = %d\n", falsey) : 1;

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
    int size = (strlen(name_array_fixed) + 1) * sizeof(char);
    char *name_ptr_copy = malloc(size);
    strcpy(name_ptr_copy, name_array_fixed);
    printf("there are %lu letters in %s\n", strlen(name_array_fixed), name_array_fixed);
    printf("copying %s\n", name_ptr_copy);
    // clean up malloc'd memory
    free(name_ptr_copy);
    name_ptr_copy = NULL;

    // string of unkown length, count until '\0'
    char *name_ptr_unknown_length = "Poindexter";
    int len = 0;
    while (TRUE) {
        char c = *(name_ptr_unknown_length + len);
        if (c == '\0') {
            break;
        }
        len++;
    }
    printf("there are %d letters in %s\n", len, name_ptr_unknown_length);

    // user string input using fgets() then capturing items from this string using sscanf()
    char str_in1[30];
    int cap_num, ret_val;
    char cap_str[30];
    printf("enter your name and age: "); /* best to not use scanf, leaves '\n' in buffer */
    // right to left, read from stdin to str_in1
    fgets(str_in1, sizeof((str_in1)), stdin);
    // left to right, str_in1 is captured / formatted (%x) into f_num
    ret_val = sscanf(str_in1, "%s      %d", cap_str, &cap_num);
    if (ret_val > 0) {
        printf("sscanf formatted %d items.\nyour name is %s and you are %d\n", ret_val, cap_str, cap_num);
    } else if (ret_val == 0) {
        printf("sscanf didn't format any items\n");
    } else {
        printf("sscanf error\n");
    }
    char str_in2[30];
    printf("now enter just your name: ");
    fgets(str_in2, sizeof(str_in2), stdin);
    printf("your name is %s", str_in2);
    printf("\n");

    // regex via pcre.h and -lpcre (version 1 of pcre)
    /* for pcre_compile */
    pcre *re;
    const char *error;
    int erroffset;
    /* for pcre_exec */
    int rc; // count
    int ovector[30];
    /* to get substrings from regex */
    int rc2 = -100;
    const char *substring;
    // we'll start after the first quote and chop off the end quote
    const char *regex = "^([A-Z][a-z]+) ([A-Z][a-z]+)$";
    const char *subject = "Lloyd Rochester";
    /* compile */
    re = pcre_compile(regex, 0, &error, &erroffset, NULL);
    /* execute */
    rc = pcre_exec(re, NULL, subject, strlen(subject), 0, 0, ovector, 30);
    if (rc == PCRE_ERROR_NOMATCH) {
        fprintf(stderr, "no match\n");
    } else if (rc < -1) {
        fprintf(stderr, "error %d from regex\n", rc);
    } else {
        // loop through matches and return them
        for (int i = 0; i < rc; i++) {
            rc2 = pcre_get_substring(subject, ovector, rc, i, &substring);
            printf("%d: %s\n", i, substring);
            pcre_free_substring(substring);
        }
    }
    /* free the regex */
    pcre_free(re);

    return rc2;
}
