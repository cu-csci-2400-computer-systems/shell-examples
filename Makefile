CEXE=$(wildcard *.c)
EXE=$(patsubst %.c,%.exe,$(CEXE))

LIBS=-lpthread

all: $(EXE)

%.exe : %.c
	$(CC) -o $@ $< ./csapp.c $(LIBS)

hello-asm64.exe: hello-asm64.sa
	as -o hello-asm64.o hello-asm64.sa
	ld -o hello-asm64.exe hello-asm64.o

csapp.exe: csapp.c
	@echo "We don't need to compile csapp.c"

clean:
	-rm *.exe *.o
