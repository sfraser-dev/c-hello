# C code review

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

Implements regex in C using Philip Hazel's PCRE (Perl Compatible Regular Expressions) library.
