#!/bin/sh

ccompiler="/usr/bin/gcc"
cargs="--std=c99 -g"

cd CXenon/src
bash -c "$ccompiler $cargs parser.c parse-test.c preprocessor.c mpc/mpc.c -o parse-test.out"
bash -c "$ccompiler $cargs walker.c parser.c preprocessor.c mpc/mpc.c -o walk-test.out"
bash -c "$ccompiler $cargs vm.c types.c test.c"
