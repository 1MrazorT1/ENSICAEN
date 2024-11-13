CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -g
LDFLAGS=-lm
EXEC=testList
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

testList: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

testList.o: list.h
list.o: list.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o
	rm -f *~
	rm -f testList

