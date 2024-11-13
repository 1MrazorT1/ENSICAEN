CC=gcc
CFLAGS=-W -Wall
LDFLAGS=
EXEC=teststack
SRC= $(wildcard *.c) ../list/list.c
OBJ= $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(EXEC).o: stack.h
stack.o: stack.h
../list/list.o: ../list/list.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o
	rm -f *~
	rm -f $(EXEC)

