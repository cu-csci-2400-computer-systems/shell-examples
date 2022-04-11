CEXE=$(wildcard *.c)
EXE=$(patsubst %.c,%.exe,$(CEXE)) hello-asm64.exe

CFLAGS=-g -O0

LIBS=-lpthread

all: $(EXE)

%.exe : %.c csapp.o
	$(CC) $(CFLAGS) -o $@ $< ./csapp.o $(LIBS)

csapp.o: csapp.c
	$(CC) $(CFLAGS) -c ./csapp.c

#
# This is linux specific because of syscall interface
#
hello-asm64.exe: hello-asm64.sa
	cpp hello-asm64.sa > hello-asm64.s
	as -o hello-asm64.o hello-asm64.s
	cc -o hello-asm64.exe hello-asm64.o  # use 'cc' rather than a naked 'ld' to work on MacOS
	rm -f hello-asm64.s

csapp.exe: csapp.c
	@echo "We don't need to compile csapp.c"

clean:
	-rm *.exe *.o
	-rm -rf *.exe.dSYM   # for macos
	-rm hello-asm64.s
