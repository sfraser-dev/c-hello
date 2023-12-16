CC := clang
SANITIZEFLAGS := -fsanitize=address
# SANITIZEFLAGS :=
CFLAGS := -g -Wall $(SANITIZEFLAGS)
LDFLAGS := $(SANITIZEFLAGS)
INCLUDEDIRS := -I.
RM := rm -f

default: all

all: a.out leak-free.exe leaky1.exe leaky2.exe \
	leaky3.exe pcre-regex.exe pcre2-regex.exe

a.out: hello.o
	$(CC) -lpcre $(LDFLAGS) $< -o $@
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

pcre-regex.exe: pcre-regex.o
	$(CC) -lpcre $(LDFLAGS) $< -o $@
pcre-regex.o: pcre-regex.c
	$(CC) $< $(CFLAGS) -c $(INCLUDEDIRS) -o $@
pcre2-regex.exe: pcre2-regex.o
	$(CC) -lpcre2-8 $(LDFLAGS) $< -o $@
pcre2-regex.o: pcre2-regex.c
	$(CC) $< $(CFLAGS) -c $(INCLUDEDIRS) -o $@

.PHONY: clean
clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe) $(wildcard *.out)

