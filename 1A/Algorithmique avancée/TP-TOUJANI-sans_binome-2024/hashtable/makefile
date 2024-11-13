CC=gcc
CFLAGS=-Wall
LDFLAGS=
EXEC=testHashtable
SRC= $(wildcard *.c) ../list/list.c
OBJ= $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(EXEC).o: hashtable.h ../list/list.h
../list/list.o : ../list/list.h
hashtable.o: hashtable.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ)
	rm -f *~
	rm -f $(EXEC)




