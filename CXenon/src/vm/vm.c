#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "vm.h"
#include "vm_utils.h"



/*
    int xenon_vm_exec(xenon_stack_t code, xenon_stack_t stack, int startip);

    This function runs the VM using the provided `stack` and `code`,
    where `code` contains the data and where `stack` is empty.

    The `startip` parameter sets where in the `code` the VM should start 
    executing. 
*/


int xenon_vm_exec(xenon_stack_t code, xenon_stack_t stack, int startip) {
    int jmp_addr;   // the address to jump to for function execution
    int ret_addr;   // the address to return to after function execution
    int ip;     // instruction pointer
    int sp;     // stack pointer

    ip = startip;
    sp = 0;
    int opcode = code.stack[ip].opcode; // get the first opcode

    while(1){
        ip++;
        switch(opcode){
            case PUSH:
                stack.stack[++sp] = code.stack[ip++];
                break;

            case IADD: {
                int b = stack.stack[sp--].integer;
                int a = stack.stack[sp--].integer;
                stack.stack[++sp].integer = a + b;
            }
                break;
            case ISUB: {
                int b = stack.stack[sp--].integer;
                int a = stack.stack[sp--].integer;
                stack.stack[++sp].integer = a - b;
            }
                break;
            case IMUL: {
                int b = stack.stack[sp--].integer;
                int a = stack.stack[sp--].integer;
                stack.stack[++sp].integer = a * b;
            }
                break;
            case IDIV: {
                int b = stack.stack[sp--].integer;
                int a = stack.stack[sp--].integer;
                stack.stack[++sp].integer = a / b;
            }
                break;
            case IMOD: {
                int b = stack.stack[sp--].integer;
                int a = stack.stack[sp--].integer;
                stack.stack[++sp].integer = a % b;
            }
                break;

            case FADD: {
                float b = stack.stack[sp--].floating;
                float a = stack.stack[sp--].floating;
                stack.stack[++sp].integer = a + b;
            }
                break;
            case FSUB: {
                float b = stack.stack[sp--].floating;
                float a = stack.stack[sp--].floating;
                stack.stack[++sp].floating = a - b;
            }
                break;
            case FMUL: {
                float b = stack.stack[sp--].floating;
                float a = stack.stack[sp--].floating;
                stack.stack[++sp].floating = a * b;
            }
                break;
            case FDIV: {
                float b = stack.stack[sp--].floating;
                float a = stack.stack[sp--].floating;
                stack.stack[++sp].floating = a / b;
            }
                break;
            case FMOD: {
                float b = stack.stack[sp--].floating;
                float a = stack.stack[sp--].floating;
                stack.stack[++sp].floating = fmodf(a, b);
            }
                break;

            case SADD: {
                xenon_string_t b = stack.stack[sp--].string;
                xenon_string_t a = stack.stack[sp--].string;
                xenon_string_t x;
                //printf("%d\n", b.len);
                //printf("%d\n", a.len);
                x.len = a.len + b.len + 1;
                //printf("%d\n", x.len);
                x.contents = calloc(1, x.len * sizeof(char));
                if(x.contents == NULL){
                    puts("rip");
                }
                strncpy(x.contents, a.contents, a.len);
                //printf(x.contents);
                //printf("%s\n", x.contents);
                strncat(x.contents + a.len, b.contents, b.len);
                stack.stack[++sp].string = x;
            }
                break;

            case IPRINT:
                printf("%d", stack.stack[sp--].integer);
                break;
            case IPRINTLN:
                printf("%d\n", stack.stack[sp--].integer);
                break;
            case FPRINT:
                printf("%f", stack.stack[sp--].floating);
                break;
            case FPRINTLN:
                printf("%f\n", stack.stack[sp--].floating);
                break;
            case SPRINT:
                xenon_print_xstring(stack.stack[sp--].string);
                break;
            case SPRINTLN:
                xenon_print_xstring(stack.stack[sp--].string);
                putchar('\n');
                break;

            case HALT:
                return 0;
                break;
        }
        opcode = code.stack[ip].opcode;
    }

    return 0;
}


/*
    int xenon_vm_wrapper(xenon_vm *vm);

    This function takes a pointer to a `xenon_vm` struct and 
    runs the `xenon_vm_exec` function with the data provided by 
    the struct.

    Return type:
    non-zero at errors; otherwise zero is returned. 
*/

int xenon_vm_wrapper(xenon_vm_t *vm){
    return xenon_vm_exec(vm->code, vm->stack, vm->startip);
}
