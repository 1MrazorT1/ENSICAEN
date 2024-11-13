CC=gcc
CFLAGS=-Wall -lm
LDFLAGS=
EXEC=testtopo
SRC= $(wildcard *.c) ../graph/graph.c ../queue/queue.c ../stack/stack.c ../list/list.c
OBJ= $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.../queue/queue.o: ../queue/queue.h
../stack/stack.o: ../stack/stack.h
../list/list.o: ../list/list.h
../graph/graph.o: ../graph/graph.h
topo.o: topo.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ)
	rm -f *~
	rm -f $(EXEC)
	rm -f *.svg



