#!/bin/sh

ccompiler="/usr/bin/gcc"
cargs="--std=c99 -g -Wall"

cd CXenon/src
bash -c "$ccompiler $cargs parser.c parse-test.c preprocessor.c vm/vm.c repl.c mpc/mpc.c -o ../../builds/parse-test.out"
bash -c "$ccompiler $cargs walker.c parser.c preprocessor.c vm/vm.c vm/vm_utils.c repl.c mpc/mpc.c -o ../../builds/walk-test.out"
bash -c "$ccompiler $cargs vm/vm.c hashtable/hashmap.c hashtable/hashtable_test.c -o ../../builds/hashmap_test.out"
bash -c "$ccompiler $cargs vm/vm.c vm/vm_utils.c test.c -o ../../builds/test.out"
