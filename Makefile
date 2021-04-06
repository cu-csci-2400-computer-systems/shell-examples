CEXE=$(wildcard *.c)
EXE=$(patsubst %.c,%.exe,$(CEXE)) hello-asm64.exe

CFLAGS=-g -O0

LIBS=-lpthread

all: $(EXE)

%.exe : %.c
	$(CC) $(CFLAGS) -o $@ $< ./csapp.c $(LIBS)

hello-asm64.exe: hello-asm64.sa
	as -o hello-asm64.o hello-asm64.sa
	ld -o hello-asm64.exe hello-asm64.o

csapp.exe: csapp.c
	@echo "We don't need to compile csapp.c"

clean:
	-rm *.exe *.o
