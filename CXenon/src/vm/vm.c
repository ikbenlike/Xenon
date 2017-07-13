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
    `cstack` is the callstack, which contains the return addresses of the
    functions the VM is executing.

    The `startip` parameter sets where in the `code` the VM should start 
    executing. 
*/


int xenon_vm_exec(xenon_stack_t code, xenon_stack_t stack, int startip, xenon_context_t *cstack){
    int jmp_addr;   // the address to jump to for function execution
    int ret_addr;   // the address to return to after function execution
    int ip;         // instruction pointer
    int sp;         // stack pointer
    int csp;        // callstack pointer

    ip = startip;
    sp = 0;
    csp = 0;
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
            case IEQ: {
                int b = stack.stack[sp--].integer;
                int a = stack.stack[sp--].integer;
                stack.stack[++sp].boolean = a == b;
            }
                break;
            case INEQ: {
                int b = stack.stack[sp--].integer;
                int a = stack.stack[sp--].integer;
                stack.stack[++sp].boolean = a != b;
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

            case BADD: {
                    bool b = stack.stack[sp--].boolean;
                    bool a = stack.stack[sp--].boolean;
                    stack.stack[sp++].integer = a + b;
                }
                    break;
            case BSUB: {
                    bool b = stack.stack[sp--].boolean;
                    bool a = stack.stack[sp--].boolean;
                    stack.stack[sp++].integer = a - b;
                }
                    break;
            case BMUL: {
                    bool b = stack.stack[sp--].boolean;
                    bool a = stack.stack[sp--].boolean;
                    stack.stack[sp++].integer = a * b;
                }
                    break;
            case BDIV: {
                    bool b = stack.stack[sp--].boolean;
                    bool a = stack.stack[sp--].boolean;
                    stack.stack[sp++].integer = a / b;
                }
                    break;
            case BEQ: {
                    bool b = stack.stack[sp--].boolean;
                    bool a = stack.stack[sp--].boolean;
                    stack.stack[sp++].boolean = a == b;
                }
                    break;
            case BNEQ: {
                    bool b = stack.stack[sp--].boolean;
                    bool a = stack.stack[sp--].boolean;
                    stack.stack[sp++].boolean = a != b;
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
            case BPRINT: {
                    bool a = stack.stack[sp--].boolean;
                    printf(a ? "true" : "false");
                }
                    break;
            case BPRINTLN: {
                    bool a = stack.stack[sp--].boolean;
                    puts(a ? "true" : "false");
                }


            case CALL: {
                int addr = code.stack[ip].func.addr;
                cstack[csp].ret = ip;
                cstack[csp].locals = calloc(code.stack[ip].func.nlocals + code.stack[ip].func.nargs, sizeof(xenon_stack_item_t));
                for(int i = 0; i < code.stack[ip].func.nargs; i++){
                    cstack[csp].locals[i] = stack.stack[sp-i];
                }
                sp -= code.stack[ip].func.nargs;
                ip = addr;
            }
                break;
            case RET:
                ip = cstack[csp].ret + 1;
                csp--;
                break;

            case JMP:
                ip = code.stack[ip++].integer;
                break;
            case BRT:
                if(stack.stack[sp--].boolean == true){
                    ip = code.stack[ip++].integer;
                }
                break;
            case BRF:
                if(stack.stack[sp--].boolean == false){
                    ip = code.stack[ip++].integer;
                }
                break;

            case HALT:
                return 0;
                break;

            default:
                fprintf(stderr, "Xenon: invalid opcode %d\n", opcode);
                return opcode;
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

int xenon_vm_exec_wrapper(xenon_vm_t *vm){
    return xenon_vm_exec(vm->code, vm->stack, vm->startip, vm->ctx);
}
