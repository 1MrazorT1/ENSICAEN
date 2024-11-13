CC=gcc
CFLAGS=-W -Wall
LDFLAGS=
EXEC=testqueue
SRC= $(wildcard *.c) ../list/list.c
OBJ= $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(EXEC).o: queue.h
queue.o: queue.h
../list/list.o: ../list/list.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o
	rm -f *~
	rm -f $(EXEC)

