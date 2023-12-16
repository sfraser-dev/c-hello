// gcc -Wall pcre2-regex.c -o pcre2-regex.exe -lpcre2-8 -lpcre2-16 -lpcre2-32
#include <endian.h>
#include <stdint.h>
#include <sys/types.h>
#define PCRE2_CODE_UNIT_WIDTH 8
// #define PCRE2_CODE_UNIT_WIDTH 16
// #define PCRE2_CODE_UNIT_WIDTH 32

#include <stdio.h>
#include <string.h>

#include "pcre2.h"

/* $> sudo apt-get -y install pcre2-utils */
/* sudo apt-get -y install libpcre2-dev */
/* These install pcre2 */

char **my_compile_and_match(const char *, const char *, u_int32_t *, int *);
void my_regex_free_substrings(char **rows_of_substrings, int amount_of_matches);
void my_regex_print_results(char **rows_of_substrings, const int amount_of_matches);

int main(int argc, char *argv[]) {
    const char *pattern = "^([A-Z][a-z]+) ([A-Z][a-z]+)$";
    const char *subject = "Lloyd Rochester";

    uint32_t options = 0;
    pcre2_match_data *match_data;
    uint32_t ovecsize = 128;
    char **rows_of_substrings = NULL;
    int amount_of_matches = -1;

    rows_of_substrings = my_compile_and_match(pattern, subject, &options, &amount_of_matches);

    printf("\namount of matches = %d\n", amount_of_matches);
    my_regex_print_results(rows_of_substrings, amount_of_matches);
    my_regex_free_substrings(rows_of_substrings, amount_of_matches);

    return 0;
}

char **my_compile_and_match(const char *pattern, const char *subject, uint32_t *options, int *amount_of_matches) {
    /* for pcre2_compile */
    pcre2_code *re;
    PCRE2_SIZE erroffset;
    int errcode;
    PCRE2_UCHAR8 buffer[128];

    /* for pcre2_match */
    PCRE2_SIZE *ovector;

    pcre2_match_data *match_data;
    uint32_t ovecsize = 128;

    size_t pattern_size = strlen(pattern);
    size_t subject_size = strlen(subject);

    char **rows_of_substrings = NULL;

    re = pcre2_compile(pattern, pattern_size, *options, &errcode, &erroffset, NULL);
    if (re == NULL) {
        pcre2_get_error_message(errcode, buffer, 120);
        fprintf(stderr, "%d\t%s\n", errcode, buffer);
        exit(1);
    }

    match_data = pcre2_match_data_create(ovecsize, NULL);
    *amount_of_matches = pcre2_match(re, subject, subject_size, 0, *options, match_data, NULL);

    if (*amount_of_matches == 0) {
        fprintf(stderr, "offset vector too small: %d", *amount_of_matches);
    } else if (*amount_of_matches > 0) {
        ovector = pcre2_get_ovector_pointer(match_data);
        PCRE2_SIZE i;
        rows_of_substrings = malloc((*amount_of_matches) * sizeof(char *));
        for (i = 0; i < *amount_of_matches; i++) {
            PCRE2_SPTR start = subject + ovector[2 * i];
            PCRE2_SIZE slen = ovector[2 * i + 1] - ovector[2 * i];
            // .* means the formatted length is passed as an addition argumnet (slen)
            printf("%2d: %.*s\n", i, (int)slen, (char *)start);
            unsigned long my_slen = slen;
            char *my_start = (char *)start;
            printf("%lu\n", my_slen);
            printf("%s\n", my_start);
            rows_of_substrings[i] = malloc(128 * sizeof(char));
            strncpy(rows_of_substrings[i], (char*)start, 128);

        }
    } else if (*amount_of_matches < 0) {
        printf("No match\n");
    }

    pcre2_match_data_free(match_data);
    pcre2_code_free(re);

    return rows_of_substrings;
}

void my_regex_free_substrings(char **rows_of_substrings, int amount_of_matches) {
    for (int i = 0; i < amount_of_matches; ++i) {
        free(rows_of_substrings[i]);
        rows_of_substrings[i] = NULL;
    }
    free(rows_of_substrings);
    rows_of_substrings = NULL;
}

void my_regex_print_results(char **rows_of_substrings, const int amount_of_matches) {
    if (rows_of_substrings == NULL) {
        fprintf(stderr, "rows_of_substrings = NULL\n");
    } else {
        if (amount_of_matches <= 0) {
            fprintf(stderr, "amount_of_matches <= 0\n");
        } else {
            for (int i = 0; i < amount_of_matches; ++i) {
                printf("%d: %s\n", i, rows_of_substrings[i]);
            }
        }
    }
}