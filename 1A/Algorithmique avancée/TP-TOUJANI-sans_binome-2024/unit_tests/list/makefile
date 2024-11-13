CC=gcc
CFLAGS=-W -Wall -g
LDFLAGS=
EXEC=unittest
SRC= unit_test_list.c ../../list/list.c
OBJ= $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): ../../list/list.h
../../list.o: ../../list/list.h

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

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





