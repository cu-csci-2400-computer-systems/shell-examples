CEXE=$(wildcard *.c)
EXE=$(patsubst %.c,%.exe,$(CEXE))

LIBS=-lpthread

all: $(EXE)

%.exe : %.c
	$(CC) -o $@ $< ./csapp.c $(LIBS)

clean:
	-rm *.exe *.o
