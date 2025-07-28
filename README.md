# C code review

- `make clean`
- `make all`

## Memory checking: Google Sanitizer

Can Make with sanitizer on for Google's memory checking. If compiled with
this Google library, memory checking will be performed automatically when
the program executes.

```make
SANITIZEFLAGS := -fsanitize=address -fno-omit-frame-pointer
CFLAGS := -g -Wall $(SANITIZEFLAGS)
LDFLAGS := $(SANITIZEFLAGS)
```

## Memory checking: Valgrind

Valgrind checking can be done via:

```bash
perl valgrind.pl program-to-check.exe
```

Valgrind will **not work** if programs under scruitiny were built with Google's
sanitizer on.

## Regular Expressions

Implements regex in C using Philip Hazel's PCRE (Perl Compatible Regular Expressions) library (<https://www.pcre.org/>).

On Debian / Ubuntu, install PCRE1 (libpcre3-dev (yes, 3!) and PCRE2 (libpcre2-dev)) via:

- PCRE1: `sudo apt install libpcre3 libpcre3-dev pcregrep`
- PCRE2: `sudo apt install libpcre2 pcre2-utils`

## Cmake

- `cd build`
- `cmake ..`
- `make clean`
- `make all`
