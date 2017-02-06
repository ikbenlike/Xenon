#!/bin/sh

ccompiler="/usr/bin/gcc"
cargs="--std=c99 -g -Wall"

cd CXenon/src
bash -c "$ccompiler $cargs parser.c parse-test.c preprocessor.c repl.c mpc/mpc.c -o parse-test.out"
bash -c "$ccompiler $cargs walker.c parser.c preprocessor.c vm.c types.c repl.c mpc/mpc.c -o walk-test.out"
bash -c "$ccompiler $cargs vm.c types.c test.c -o test.out"
