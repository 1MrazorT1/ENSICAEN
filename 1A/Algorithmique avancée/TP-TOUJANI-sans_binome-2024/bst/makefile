CC=gcc
CFLAGS=-Wall
LDFLAGS=
EXEC=testbst
SRC= $(wildcard *.c) ../utils/utils.c
OBJ= $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(EXEC).o: bst.h ../utils/utils.h
../utils/utils.o: ../utils/utils.h
bst.o: bst.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

graph:
	gnuplot graph.gnuplot



.PHONY: clean

clean:
	rm -f $(OBJ)
	rm -f *~
	rm -f $(EXEC)
	rm -f *.png
	rm -f data.gnuplot





