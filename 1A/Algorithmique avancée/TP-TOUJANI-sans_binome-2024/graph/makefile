CC=gcc
CFLAGS=-Wall -lm
LDFLAGS=
EXEC=testgraph
SRC= $(wildcard *.c) ../queue/queue.c ../stack/stack.c ../list/list.c
OBJ= $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

../queue/queue.o: ../queue/queue.h
../stack/stack.o: ../stack/stack.h
../list/list.o: ../list/list.h
graph.o: graph.h


%.o: %.c
	$(CC) -o $@ -c $<


clean:
	rm -f $(OBJ)
	rm -f *~
	rm -f $(EXEC)
	rm -f *.svg

