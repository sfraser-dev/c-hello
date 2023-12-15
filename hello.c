#include <pcre.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **my_regex_run(const char *regex, const char *subject, int *amount_of_matches);
void my_regex_print_results(const char **rows_of_substrings, const int amount_of_matches);
void my_regex_free_substrings(char **rows_of_substrings, int amount_of_matches);
void simple_addition(int a, int b);
void simple_subtraction(int a, int b);
void simple_multiplication(int a, int b);
void simple_division(int a, int b);
int recursion_sum(int n);

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

    // getting user input via fgets() and then capturing and checking it with sscanf()
    char str_in1[30], str_in2[30], str_in3[30];
    int cap_num, ret_val;
    printf("enter your age: "); /* best to not use scanf, leaves '\n' in buffer */
    // right to left, read from stdin to str_in1
    fgets(str_in1, sizeof((str_in1)), stdin);
    // left to right, str_in1 is captured / formatted (%x) into f_num
    ret_val = sscanf(str_in1, "%d", &cap_num);
    if (ret_val > 0) {
        printf("sscanf formatted %d items.\nyour age is %d\n", ret_val, cap_num);
    } else if (ret_val == 0) {
        printf("sscanf didn't format any items\n");
    } else {
        printf("sscanf error\n");
    }
    printf("now enter your name: ");
    fgets(str_in2, sizeof(str_in2), stdin);
    ret_val = sscanf(str_in2, "%s", str_in2);
    if (ret_val > 0) {
        printf("sscanf formatted %d items.\nyour name is %s\n", ret_val, str_in2);
    } else if (ret_val == 0) {
        printf("sscanf didn't format any items\n");
    } else {
        printf("sscanf error\n");
    }
    printf("\n");

    // regex: C regex using the pcre library
    const char *regex = "^([A-Z][a-z]+) ([A-Z][a-z]+)$";
    const char *subject = "Lloyd Rochester";
    // const char *subject = "John McCarthy";
    char **rows_of_substrings = NULL;
    int amount_of_matches = -1;
    printf("regex in C...\n");
    rows_of_substrings = my_regex_run(regex, subject, &amount_of_matches);
    my_regex_print_results((const char **)rows_of_substrings, amount_of_matches);
    my_regex_free_substrings(rows_of_substrings, amount_of_matches);

    // regex: getting user input from fgets() and checking / matching it with regex
    printf("enter the following: FIRSTNAME SURNAME AGE: ");
    fgets(str_in3, sizeof(str_in3), stdin);
    printf("str_in3 = %s", str_in3);
    // word boundary '\b' is zero width so cannot represent a whitespace
    const char *regex2 = "^(\\w+)\\b\\s+\\b(\\w+)\\b\\s+\\b(\\d+)$";
    char **rows_of_substrings2 = NULL;
    int amount_of_matches2 = -1;
    rows_of_substrings2 = my_regex_run(regex2, (const char *)str_in3, &amount_of_matches2);
    my_regex_print_results((const char **)rows_of_substrings2, amount_of_matches2);
    my_regex_free_substrings(rows_of_substrings2, amount_of_matches2);
    printf("\n");

    // character ASCII values
    printf("ASCII 'A' = %d\n", 'A');
    printf("ASCII 'a' = %d\n", 'a');
    printf("ASCII 'Z' = %d\n", 'Z');
    printf("ASCII 'z' = %d\n", 'z');
    printf("ASCII '0' = %d\n", '0');
    printf("ASCII '9' = %d\n", '9');

    // bitwise operations
    short _2 = 2;              // 010
    short _3 = 3;              // 011
    short _xor = _2 ^ _3;      // 001
    short _3left1 = _3 << 1;   // 110
    short _2right1 = _2 >> 1;  // 001
    short _3complement = ~_3;  // 100
    printf("xor (2^3) = %hi\n", _xor);
    printf("3 << 1 = %hi\n", _3left1);
    printf("2 >> 1 = %hi\n", _2right1);
    printf("~3 (complement is -(N+1)) = %hi\n", _3complement);
    printf("\n");

    // function pointers
    // function pointers point to code, not data (points to start of executable code)
    // unlike normal pointers, we don't allocate / deallocate memory for function pointers
    // like normal pointers, can have an array of function pointers (like a switch statement)
    void (*fun_ptr)(int, int);  // declare funtion pointer
    fun_ptr = &simple_addition;
    (*fun_ptr)(10, 5);
    fun_ptr = &simple_subtraction;
    (*fun_ptr)(10, 5);
    fun_ptr = &simple_multiplication;
    (*fun_ptr)(10, 5);
    fun_ptr = simple_division;  // nb: name of function also holds its address
    fun_ptr(10, 5);             // nb: don't need to explicitly dereference a function pointer
    printf("\n");

    // declare and define an array of function pointers
    void (*fun_ptr_array[4])(int, int) = {simple_addition, simple_subtraction, simple_multiplication, simple_division};

    // array of function pointers is like a switch statement
    fun_ptr_array[0](10, 5);
    fun_ptr_array[1](10, 5);
    fun_ptr_array[2](10, 5);
    fun_ptr_array[3](10, 5);
    printf("\n");

    // function poiters cleaner code with typedefs
    typedef void (*fun_ptr_type)(int, int);  // typedef name will be fun_ptr_type
    fun_ptr_type fp = simple_multiplication;
    fp(10, 5);
    printf("\n");

    // very naughty: goto a label
    goto my_label;
    printf("goto: this won't be printed\n");
my_label:
    printf("goto: this will be printed\n");
    printf("\n");

    // calculate sum via recursion
    printf("recursion sum = %d\n", recursion_sum(3));

    return 0;
}

int recursion_sum(int n) {
    if (n == 0) {
        return 0;
    }
    return n + recursion_sum(n - 1);
}

void simple_addition(int a, int b) { printf("%d+%d=%d\n", a, b, a + b); }

void simple_subtraction(int a, int b) { printf("%d-%d=%d\n", a, b, a - b); }

void simple_multiplication(int a, int b) { printf("%d*%d=%d\n", a, b, a * b); }

void simple_division(int a, int b) { printf("%d/%d=%.1f\n", a, b, ((float)a) / b); }

void my_regex_free_substrings(char **rows_of_substrings, int amount_of_matches) {
    for (int i = 0; i < amount_of_matches; ++i) {
        free(rows_of_substrings[i]);
        rows_of_substrings[i] = NULL;
    }
    free(rows_of_substrings);
    rows_of_substrings = NULL;
}

void my_regex_print_results(const char **rows_of_substrings, const int amount_of_matches) {
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

char **my_regex_run(const char *regex, const char *subject, int *amount_of_matches) {
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