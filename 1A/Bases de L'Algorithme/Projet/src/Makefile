CC=gcc
CFLAGS=-Wall -g
LIBS=-L~/Documents/projet_algorithme/PROJET_FONDEMENTS/MODULE_IMAGE/
OBJ=test_KDtree.o
OUTPUT=test_KDtree

../bin/$(OUTPUT): $(OBJ) table.o image.o KDTree.o
	$(CC) $^  -o $@ -lm 

clean:
	rm -f $(OUTPUT) $(OBJ) *.o

image.o: image.c 
	$(CC) -I../include $< -o $@ -c

table.o: table.c 
	$(CC) -I../include $(CFLAGS)  $< -o $@ -c

KDTree.o: KDTree.c
	$(CC) -I../include $(CFLAGS) $< -o $@ -c

test_KDtree.o: test_KDtree.c 
	$(CC) -I../include $(CFLAGS) $< -o $@ -c
