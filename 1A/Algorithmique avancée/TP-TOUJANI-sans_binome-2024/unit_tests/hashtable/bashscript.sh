#!/bin/bash
gcc -o ../../list/list.o -c ../../list/list.c -W -Wall -g 2> out.txt
gcc -o ../../hashtable/hashtable.o -c ../../hashtable/hashtable.c -W -Wall -g 2> out.txt
gcc -o vg_exec.o -c vg_exec.c -W -Wall -g 2>> out.txt
gcc -o vg_exec vg_exec.o ../../hashtable/hashtable.o ../../list/list.o -W -Wall -g 2>> out.txt
valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --log-file="log-$1.out" --error-exitcode=3 ./vg_exec $1 $2 $3 $4 > output.txt
valgrind_result=$?
rm -f vg_exec
rm -f vg_exec.o
rm -f out.txt
echo $valgrind_result > score-$1.out

