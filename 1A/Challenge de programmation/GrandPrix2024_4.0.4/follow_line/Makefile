.PHONY: all clean install

CC = gcc
CFLAGS =  -Wall -Wextra -ansi -pedantic
LINK.o = $(LINK.cc)

EXE = main

all: $(EXE)

$(EXE): main.o follow_line.o
	$(CXX) $(CFLAGS) -o $@ $^

.o: .c .h

main.o: main.c

clean:
	rm -f $(EXE) *.o
