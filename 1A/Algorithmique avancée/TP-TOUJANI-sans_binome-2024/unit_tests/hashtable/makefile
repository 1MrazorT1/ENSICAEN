CC=gcc
CFLAGS=-W -Wall -g
LDFLAGS=
EXEC=unittest

TEST= ./valgrind_tests.c unit_test_hashtableCreate.c unit_test_hashtableDestroy.c unit_test_hashtableDoubleSize.c unit_test_hashtableGetValue.c unit_test_hashtableHasKey.c unit_test_hashtableInsert.c unit_test_hashtableInsertWithoutResizing.c unit_test_hashtableRemove.c
OBJ= unit_test.o ../../list/list.o ../../hashtable/hashtable.o

all: $(EXEC)

unit_test.o: $(TEST)
../../list/list.o: ../../list/list.h
../../hashtable/hashtable.o: ../../hashtable/hashtable.h

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





