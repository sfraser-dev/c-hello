# choose which flags to use with Google's Sanitizer
SANITIZEFLAGS := -fsanitize=address -fno-omit-frame-pointer
# SANITIZEFLAGS := -fsanitize=memory -fsanitize-memory-track-origins -fno-omit-frame-pointer
# SANITIZEFLAGS := -fsanitize=undefined
# SANITIZEFLAGS :=

CC := clang
CFLAGS := -g -Wall $(SANITIZEFLAGS)
LDFLAGS := $(SANITIZEFLAGS)
INCLUDEDIRS := -I.
RM := rm -f

default: all

all: hello.exe leak-free.exe leaky1.exe leaky2.exe \
	leaky3.exe pcre1-regex.exe pcre2-regex.exe

hello.exe: hello.o
	$(CC) -lpcre -lpcre2-8 $(LDFLAGS) $< -o $@
hello.o: hello.c
	$(CC) $< $(CFLAGS) -c $(INCLUDEDIRS) -o $@

leak-free.exe: leak-free.c
	$(CC) $< $(CFLAGS) $(INCLUDEDIRS) -o $@
leaky1.exe: leaky1.c
	$(CC) $< $(CFLAGS) $(INCLUDEDIRS) -o $@
leaky2.exe: leaky2.c
	$(CC) $< $(CFLAGS) $(INCLUDEDIRS) -o $@
leaky3.exe: leaky3.c
	$(CC) $< $(CFLAGS) $(INCLUDEDIRS) -o $@

pcre1-regex.exe: pcre1-regex.o
	$(CC) -lpcre $(LDFLAGS) $< -o $@
pcre1-regex.o: pcre1-regex.c
	$(CC) $< $(CFLAGS) -c $(INCLUDEDIRS) -o $@
pcre2-regex.exe: pcre2-regex.o
	$(CC) -lpcre2-8 $(LDFLAGS) $< -o $@
pcre2-regex.o: pcre2-regex.c
	$(CC) $< $(CFLAGS) -c $(INCLUDEDIRS) -o $@

.PHONY: clean
clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe) $(wildcard *.out)

