#include <pcre.h>
#include <stdio.h>
#include <string.h>

/* https://lloydrochester.com/post/c/regex_pcre/ */
/* apt-get install libpcre3 libpcre3-dev */
/* gcc pcre-regex.c -lpcre -o a.out */

int main(int argc, char *argv[]) {
    /* for pcre_compile */
    pcre *re;
    const char *error;
    int erroffset;

    /* for pcre_exec */
    int rc;  // count
    int ovector[30];

    /* to get substrings from regex */
    int rc2 = -100;
    const char *substring;

    /* we'll start after the first quote and chop off the end quote */
    const char *regex = "^([A-Z][a-z]+) ([A-Z][a-z]+)$";
    const char *subject = "Lloyd Rochester";
    // const char *subject = "John McCarthy";
    re = pcre_compile(regex, 0, &error, &erroffset, NULL);

    rc = pcre_exec(re, NULL, subject, strlen(subject), 0, 0, ovector, 30);

    if (rc == PCRE_ERROR_NOMATCH) {
        fprintf(stderr, "no match\n");
    } else if (rc < -1) {
        fprintf(stderr, "error %d from regex\n", rc);
    } else {
        /* loop through matches and return them */
        for (int i = 0; i < rc; i++) {
            rc2 = pcre_get_substring(subject, ovector, rc, i, &substring);
            printf("%d: %s\n", i, substring);
            pcre_free_substring(substring);
        }
    }
    pcre_free(re);

    printf("\nrc=%d, rc2=%d\n", rc, rc2);

    return rc;
}