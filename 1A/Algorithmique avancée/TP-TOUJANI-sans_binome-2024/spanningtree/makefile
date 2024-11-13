CC=gcc
CFLAGS=-Wall -lm
LDFLAGS=
EXEC=testprim
SRC= $(wildcard *.c) ../graph/graph.c ../heap/heap.c ../queue/queue.c ../stack/stack.c ../list/list.c
OBJ= $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.../queue/queue.o: ../queue/queue.h
../stack/stack.o: ../stack/stack.h
../list/list.o: ../list/list.h
../graph/graph.o: ../graph/graph.h
../heap/heap.o: ../heap/heap.h
prim.o: prim.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ)
	rm -f *~
	rm -f $(EXEC)
	rm -f *.svg




