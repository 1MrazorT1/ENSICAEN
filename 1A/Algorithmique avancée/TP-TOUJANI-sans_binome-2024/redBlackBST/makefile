CC=gcc
CFLAGS=-Wall
LDFLAGS=
EXEC=testrbbst
SRC= $(wildcard *.c) ../utils/utils.c ../bst/bst.c ../rBST/rbst.c
OBJ= $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(EXEC).o: redBlackBST.h ../rBST/rbst.h ../bst/bst.h ../utils/utils.h

../utils/utils.o: ../utils/utils.h
../bst/bst.o: ../bst/bst.h
../rBST/rbst.o: ../rBST/rbst.h
redBlackBST.o: redBlackBST.h

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



