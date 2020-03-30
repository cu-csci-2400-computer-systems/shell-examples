CEXE=$(wildcard *.c)
EXE=$(patsubst %.c,%.exe,$(CEXE))

LIBS=-lpthread

all: $(EXE)

%.exe : %.c
	$(CC) -o $@ $< ./csapp.c $(LIBS)

csapp.exe: csapp.c
	@echo "We don't need to compile csapp.c"

clean:
	-rm *.exe *.o
