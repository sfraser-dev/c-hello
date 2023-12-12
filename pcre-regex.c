#include <complex.h>
#include <pcre.h>
#include <stdio.h>
#include <string.h>

/* https://lloydrochester.com/post/c/regex_pcre/ */
/* apt-get install libpcre3 libpcre3-dev */
/* gcc pcre-regex.c -lpcre -o a.out */

char **run_regex(const char *, const char *, int *);

int main(int argc, char *argv[]) {
    /* we'll start after the first quote and chop off the end quote */
    const char *regex = "^([A-Z][a-z]+) ([A-Z][a-z]+)$";
    // const char *subject = "Lloyd Rochester";
    const char *subject = "John McCarthy";
    char **rows_of_substrings = NULL;
    int amount_of_matches = -1;

    rows_of_substrings = run_regex(regex, subject, &amount_of_matches);

    if (rows_of_substrings == NULL) {
        fprintf(stderr, "rows_of_substrings = NULL\n");
    } else {
        if (amount_of_matches <= 0) {
            fprintf(stderr, "amount_of_matches <= 0\n");
        } else {
            for (int i = 0; i < amount_of_matches; ++i) {
                printf("%d: %s\n", i, rows_of_substrings[i]);
                free(rows_of_substrings[i]);
                rows_of_substrings[i] = NULL;
            }
            free(rows_of_substrings);
            rows_of_substrings = NULL;
        }
    }

    return 0;
}

char **run_regex(const char *regex, const char *subject, int *amount_of_matches) {
    /* for pcre_compile */
    pcre *re;
    const char *error;
    int erroffset;

    /* for pcre_exec */
    int ovector[30];

    /* to get substrings from regex */
    const char *substring;

    char **rows_of_substrings = NULL;

    // const char *subject = "John McCarthy";
    re = pcre_compile(regex, 0, &error, &erroffset, NULL);

    *amount_of_matches = pcre_exec(re, NULL, subject, strlen(subject), 0, 0, ovector, 30);

    if (*amount_of_matches == PCRE_ERROR_NOMATCH) {
        fprintf(stderr, "no match\n");
    } else if (*amount_of_matches < -1) {
        fprintf(stderr, "error %d from regex\n", *amount_of_matches);
    } else {
        rows_of_substrings = malloc((*amount_of_matches) * sizeof(char *));
        /* loop through matches and return them */
        for (int i = 0; i < *amount_of_matches; ++i) {
            pcre_get_substring(subject, ovector, *amount_of_matches, i, &substring);
            rows_of_substrings[i] = malloc(30 * sizeof(char));
            strncpy(rows_of_substrings[i], substring, 30);
            pcre_free_substring(substring);
        }
    }
    pcre_free(re);

    return rows_of_substrings;
}