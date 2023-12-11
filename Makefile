CC := clang
SANITIZEFLAGS := -fsanitize=address
CFLAGS := -g -Wall $(SANITIZEFLAGS)
LDFLAGS := $(SANITIZEFLAGS)
INCLUDEDIRS := -I.
RM := rm -f

default: all

all: hello.exe leak-free.exe leaky.exe

hello.exe: hello.o
	$(CC) $(LDFLAGS) $< -o $@

hello.o: hello.c
	$(CC) $< $(CFLAGS) -c $(INCLUDEDIRS) -o $@

leak-free.exe: leak-free.c
	$(CC) $< $(CFLAGS) $(INCLUDEDIRS) -o $@

leaky.exe: leaky.c
	$(CC) $< $(CFLAGS) $(INCLUDEDIRS) -o $@

.PHONY: clean
clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)

