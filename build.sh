#!/bin/sh

ccompiler="/usr/bin/gcc"
cargs="--std=c99 -g -Wall"

cd CXenon/src
bash -c "$ccompiler $cargs repl/repl.c walker/walker.c parser/parser.c parse-test.c preprocessor/preprocessor.c vm/vm.c vm/vm_utils.c mpc/mpc.c -o ../../builds/parse-test.out"
bash -c "$ccompiler $cargs repl/repl.c walker/walker.c walker_test.c parser/parser.c preprocessor/preprocessor.c vm/vm.c vm/vm_utils.c mpc/mpc.c -o ../../builds/walk-test.out"
bash -c "$ccompiler $cargs vm/vm.c hashmap/hashmap.c hashmap/hashmap_test.c -o ../../builds/hashmap_test.out"
bash -c "$ccompiler $cargs vm/vm.c vm/vm_utils.c test.c -o ../../builds/test.out"
