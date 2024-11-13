CC=gcc
CFLAGS=-W -Wall -g
LDFLAGS=
EXEC=unittest
TEST= ./valgrind_tests.c ./unit_test_createHeap.c ./unit_test_getElement.c ./unit_test_insertHeap.c ./unit_test_modifyPriorityHeap.c ./unit_test_removeElement.c ./unit_test_largeHeap.c

OBJ= ./unit_test.o ../../heap/heap.o
all: $(EXEC)

unit_test.o: $(TEST)
../../heap/heap.o: ../../heap/heap.h

$(EXEC): $(OBJ) $(TEST)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ)
	rm -f *~
	rm -f $(EXEC)
	rm -f log-*
	rm -f score-*
	rm -f out.txt
	rm -f output.txt
	rm -f score.log





