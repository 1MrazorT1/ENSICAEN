CC=gcc
CFLAGS=-W -Wall
LDFLAGS=
EXEC=testUtils
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(EXEC).o: utils.h
utils.o: utils.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o
	rm -f *~
	rm -f $(EXEC)

