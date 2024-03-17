#!/bin/bash

echo "compiling $1"
rm -f lex.yy.c
rm -f $1.tab.c
rm -f $1
bison -d $1.y
lex $1.l
g++ IdList.cpp lex.yy.c  $1.tab.c -std=c++11 -o $1
