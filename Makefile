CC := clang
CFLAGS := -g -Wall 
LDFLAGS :=
INCLUDEDIRS := -I.
RM := rm -f

default: all

all: hello.exe 

hello.exe: hello.o
	$(CC) $(LDFLAGS) $< -o $@

hello.o: hello.c
	$(CC) $(CFLAGS) -c $< $(INCLUDEDIRS)

.PHONY: clean
clean:
	$(RM) $(wildcard *.o) $(wildcard *.exe)

