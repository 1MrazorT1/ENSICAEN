#!/bin/bash
gcc -o ../../list/list.o -c ../../list/list.c -W -Wall -g 2> out.txt
gcc -o $1.o -c $1.c -W -Wall -g 2>> out.txt
gcc -o $1 $1.o ../../list/list.o -W -Wall -g 2>> out.txt
valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --log-file="log-$1.out" --error-exitcode=3 ./$1 $2 $3 $4 > output.txt
valgrind_result=$?
rm -f $1
rm -f $1.o
rm -f out.txt
echo $valgrind_result > score-$1.out

