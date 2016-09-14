/*
*    CXenon VM v0.0.5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "vm.h"



typedef struct {
    char name[8];
    int nargs;
} VM_INSTRUCTION;



static VM_INSTRUCTION vm_instructions[] = {
    { "noop",     0 },    // 0
    { "isub",     0 },    // 1
    { "imul",     0 },    // 2
    { "idiv",     0 },    // 3
    { "ilt",      0 },    // 4
    { "ieq",      0 },    // 6
    { "br",       1 },    // 7
    { "brt",      1 },    // 8
    { "brf",      1 },    // 9
    { "iconst",   1 },    // 10
    { "iload",    1 },    // 11
    { "igload",   1 },    // 12
    { "istore",   1 },    // 13
    { "igstore",  1 },    // 14
    { "iprint",   0 },    // 15
    { "iprintln", 0 },    // 16
    { "pop",      0 },    // 17
    { "call",     3 },    // 18
    { "ret",      0 },    // 19
    { "fadd",     0 },    // 20
    { "fsub",     0 },    // 21
    { "fmul",     0 },    // 22
    { "fdiv",     0 },    // 23
    { "fconst",   1 },    // 24
    { "flt",      0 },    // 25
    { "feq",      0 },    // 26
    { "fmt",      0 },    // 27
    { "fneq",     0 },    // 28
    { "imt",      0 },    // 29
    { "ineq",     0 },    // 30
    { "bconst",   1 },    // 31
    { "beq",      0 },    // 32
    { "bneq",     1 },    // 33
    { "btrue",    0 },    // 34
    { "bfalse",   0 },    // 35
    { "fprint",   0 },    // 36
    { "fprintln", 0 },    // 37
    { "bprint",   0 },    // 38
    { "bprintln", 0 },    // 39
    { "sconst",   1 },    // 40
    { "sprint",   0 },    // 41
    { "sprintln", 0 },    // 42
    { "seq",      0 },    // 43
    { "sneq",     0 },    // 44
    { "slt",      0 },    // 45
    { "smt",      0 },    // 46
    { "sgload",   1 },    // 47
    { "sgstore",  1 },    // 48
    { "sload",    1 },    // 49
    { "sstore",   1 },    // 50
    { "bgload",   1 },    // 51
    { "bgstore",  1 },    // 52
    { "bload",    1 },    // 53
    { "bstore",   1 },    // 54
    { "fgload",   1 },    // 55
    { "fgstore",  1 },    // 56
    { "fload",    1 },    // 57
    { "fstore",   1 },    // 58
    { "cconst",   1 },    // 59
    { "cprint",   0 },    // 60
    { "cprintln", 0 },    // 61
    { "ceq",      0 },    // 62
    { "cneq",     0 },    // 63
    { "cgload",   1 },    // 64
    { "cgstore",  1 },    // 65
    { "cload",    1 },    // 66
    { "cstore",   1 },    // 67
    { "halt",     0 }     // 68
};



static void vm_context_init(Context *ctx, int ip, int nlocals);



int vm_init(VM *vm, struct stack_base *code, int code_size, int nglobals){
    vm->code = code;
    vm->code_size = code_size;
    vm->globals = calloc(nglobals, sizeof(struct stack_base));
    vm->nglobals = nglobals;
    return 0;
}

int vm_free(VM *vm){
    free(vm->globals);
    free(vm);
    return 0;
}

VM *vm_create(struct stack_base *code, int code_size, int nglobals){
    VM *vm = calloc(1, sizeof(VM));
    vm_init(vm, code, code_size, nglobals);
    return vm;
}

int vm_print_instr(struct stack_base *code, int ip){
    int opcode = code[ip].data.anint;
    VM_INSTRUCTION *inst = &vm_instructions[opcode];
    switch (inst->nargs) {
        case 0:
            printf("%04d:  %-20s", ip, inst->name);
            break;
        case 1:
            printf("%04d:  %-10s%-10d", ip, inst->name, code[ip + 1].data.anint);
            break;
        case 2:
            printf("%04d:  %-10s%d,%10d", ip, inst->name, code[ip + 1].data.anint, code[ip + 2].data.anint);
            break;
        case 3:
            printf("%04d:  %-10s%d,%d,%-6d", ip, inst->name, code[ip + 1].data.anint, code[ip + 2].data.anint, code[ip + 3].data.anint);
            break;
    }
    return 0;
}

int vm_print_stack(struct stack_base *stack, int count){
    printf("stack=[");
    for (int i = 0; i <= count; i++) {
        printf(" %d", stack[i].data.anint);
    }
    printf(" ]\n");
    return 0;
}

int vm_exec(VM *vm, int startip, bool trace){

    int ip; // instructionpointer
    int fp; // framepointer
    int sp; // stackpointer
    int callsp;
    int offset = 0;
    int v;
    int addr;
    int nargs;
    int rvalue;
    int a, b;
    float fv;
    float fa, fb;
    bool bv;
    bool ba, bb;
    char* sv;
    char sa[1000];
    char sb[1000];
    char cv, ca, cb;

    int size = sizeof(vm->code); // declares size of code

    ip = startip;
    sp = -1;
    callsp = -1;
    int opcode = vm->code[ip].data.anint; // fetch

    while(1){

        if(trace){
            vm_print_instr(vm->code, ip); // prints trace
        }

        ip++;
        switch(opcode){
            case ICONST:
                vm->stack[++sp].data.anint = vm->code[ip++].data.anint;
                break;
            case ISUB:
                b = vm->stack[sp--].data.anint;
                a = vm->stack[sp--].data.anint;
                vm->stack[++sp].data.anint = a - b;
                break;
            case IADD:
                b = vm->stack[sp--].data.anint;
                a = vm->stack[sp--].data.anint;
                vm->stack[++sp].data.anint = a + b;
                break;
            case IMUL:
                b = vm->stack[sp--].data.anint;
                a = vm->stack[sp--].data.anint;
                vm->stack[++sp].data.anint = a * b;
                break;
            case IDIV:
                b = vm->stack[sp--].data.anint;
                a = vm->stack[sp--].data.anint;
                vm->stack[++sp].data.anint = a/b;
                break;
            case ILT:
                b = vm->stack[sp--].data.anint;
                a = vm->stack[sp--].data.anint;
                if(a > b){
                    vm->stack[++sp].data.abool = true;
                    break;
                }
                else {
                    vm->stack[++sp].data.abool = false;
                    break;
                }
            case IMT:
                b = vm->stack[sp--].data.anint;
                a = vm->stack[sp--].data.anint;
                if(a < b){
                    vm->stack[++sp].data.abool = true;
                    break;
                }
                else {
                    vm->stack[++sp].data.abool = false;
                    break;
                }
            case IEQ:
                b = vm->stack[sp--].data.anint;
                a = vm->stack[sp--].data.anint;
                if(a == b){
                    vm->stack[++sp].data.abool = true;
                    break;
                }
                else {
                    vm->stack[++sp].data.abool = false;
                    break;
                }
            case INEQ:
                b = vm->stack[sp--].data.anint;
                a = vm->stack[sp--].data.anint;
                if(a != b){
                    vm->stack[++sp].data.abool = true;
                    break;
                }
                else {
                    vm->stack[++sp].data.abool = false;
                    break;
                }
            case FCONST:
                fv = vm->code[ip].data.afloat;
                ip++;
                sp++;
                vm->stack[sp].data.afloat = fv;
                break;
            case FSUB:
                fb = vm->stack[sp--].data.afloat;
                fa = vm->stack[sp--].data.afloat;
                vm->stack[++sp].data.afloat = fa + fb;
                break;
            case FADD:
                fb = vm->stack[sp--].data.afloat;
                fa = vm->stack[sp--].data.afloat;
                vm->stack[++sp].data.afloat = fa + fb;
                break;
            case FMUL:
                fb = vm->stack[sp--].data.afloat;
                fa = vm->stack[sp--].data.afloat;
                vm->stack[++sp].data.afloat = fa * fb;
                break;
            case FDIV:
                fb = vm->stack[sp--].data.afloat;
                fa = vm->stack[sp--].data.afloat;
                vm->stack[++sp].data.afloat = fa/fb;
                break;
            case FEQ:
                fb = vm->stack[sp--].data.afloat;
                fa = vm->stack[sp--].data.afloat;
                if(fa == fb){
                    vm->stack[++sp].data.abool = true;
                    break;
                }
                else {
                    vm->stack[++sp].data.abool = false;
                    break;
                }
            case FLT:
                fb = vm->stack[sp--].data.afloat;
                fa = vm->stack[sp--].data.afloat;
                if(fa > fb){
                    vm->stack[++sp].data.abool = true;
                    break;
                }
                else {
                    vm->stack[++sp].data.abool = false;
                    break;
                }
            case FMT:
                fb = vm->stack[sp--].data.afloat;
                fa = vm->stack[sp--].data.afloat;
                if(fa < fb){
                    vm->stack[++sp].data.abool = true;
                    break;
                }
                else {
                    vm->stack[++sp].data.abool = false;
                    break;
                }
            case FNEQ:
                fb = vm->stack[sp--].data.afloat;
                fa = vm->stack[sp--].data.afloat;
                if(fa != fb){
                    vm->stack[++sp].data.abool = true;
                    break;
                }
                else {
                    vm->stack[++sp].data.abool = false;
                    break;
                }
            case BCONST:
                bv = vm->code[ip].data.anint;
                ip++;
                sp++;
                if(bv == BTRUE){
                    vm->stack[sp].data.abool = true;
                    break;
                }
                else if(bv == BFALSE){
                    vm->stack[sp].data.abool = false;
                    break;
                }
            case BNEQ:
                bb = vm->stack[sp--].data.abool;
                ba = vm->stack[sp--].data.abool;
                if(ba == bb){
                    vm->stack[++sp].data.abool = true;
                    break;
                }
                else {
                    vm->stack[++sp].data.abool = false;
                    break;
                }
            case BEQ:
                bb = vm->stack[sp--].data.abool;
                ba = vm->stack[sp--].data.abool;
                if(ba != bb){
                    vm->stack[++sp].data.abool = true;
                    break;
                }
                else {
                    vm->stack[++sp].data.abool = false;
                    break;
                }
            case SCONST:
                sv = vm->code[ip].data.astring;
                ip++;
                sp++;
                vm->stack[sp].data.astring = sv;
                break;
            case SEQ:
                strcpy(sb, vm->stack[sp--].data.astring);
                strcpy(sa, vm->stack[sp--].data.astring);
                if(strcmp(sa, sb) == 0){
                    vm->stack[++sp].data.abool = true;
                    strcpy(sa, "\0");
                    strcpy(sb, "\0");
                    break;
                }
                else {
                    vm->stack[++sp].data.abool = false;
                    strcpy(sa, "\0");
                    strcpy(sb, "\0");
                    break;
                }
            case SNEQ:
                strcpy(sb, vm->stack[sp--].data.astring);
                strcpy(sa, vm->stack[sp--].data.astring);
                if(strcmp(sa, sb) != 0){
                    vm->stack[++sp].data.abool = true;
                    strcpy(sa, "\0");
                    strcpy(sb, "\0");
                    break;
                }
                else {
                    vm->stack[++sp].data.abool = false;
                    strcpy(sa, "\0");
                    strcpy(sb, "\0");
                    break;
                }
            case SLT:
                strcpy(sb, vm->stack[sp--].data.astring);
                strcpy(sa, vm->stack[sp--].data.astring);
                if(strlen(sa) > strlen(sb)){
                    vm->stack[++sp].data.abool = true;
                    strcpy(sa, "\0");
                    strcpy(sb, "\0");
                    break;
                }
                else {
                    vm->stack[++sp].data.abool = false;
                    strcpy(sa, "\0");
                    strcpy(sb, "\0");
                    break;
                }
            case SMT:
                strcpy(sb, vm->stack[sp--].data.astring);
                strcpy(sa, vm->stack[sp--].data.astring);
                if(strlen(sa) < strlen(sb)){
                    vm->stack[++sp].data.abool = true;
                    strcpy(sa, "\0");
                    strcpy(sb, "\0");
                    break;
                }
                else {
                    vm->stack[++sp].data.abool = false;
                    strcpy(sa, "\0");
                    strcpy(sb, "\0");
                    break;
                }
            case CCONST:
                cv = vm->code[ip].data.achar;
                ip++;
                sp++;
                vm->stack[sp].data.achar = cv;
                break;
            case CEQ:
                cb = vm->stack[sp--].data.achar;
                ca = vm->stack[sp--].data.achar;
                if(ca == cb){
                    vm->stack[++sp].data.abool = true;
                }
                else {
                    vm->stack[++sp].data.abool = false;
                }
                break;
            case CNEQ:
                cb = vm->stack[sp--].data.achar;
                ca = vm->stack[sp--].data.achar;
                if(ca != cb){
                    vm->stack[++sp].data.abool = true;
                }
                else {
                    vm->stack[++sp].data.abool = false;
                }
                break;
            case IPRINT:
                v = vm->stack[sp].data.anint;
                sp--;
                printf("%i", v);
                break;
            case FPRINT:
                fv = vm->stack[sp].data.afloat;
                sp--;
                printf("%f", fv);
                break;
            case IPRINTLN:
                v = vm->stack[sp].data.anint;
                sp--;
                printf("%i\n", v);
                break;
            case FPRINTLN:
                fv = vm->stack[sp].data.afloat;
                sp--;
                printf("%f\n", fv);
                break;
            case BPRINT:
                bv = vm->stack[sp].data.anint;
                sp--;
                printf("%s", bv ? "true" : "false");
                break;
            case BPRINTLN:
                bv = vm->stack[sp].data.abool;
                sp--;
                printf("%s\n", bv ? "true" : "false");
                break;
            case SPRINT:
                sv = vm->stack[sp].data.astring;
                sp--;
                printf("%s", sv);
                break;
            case SPRINTLN:
                sv = vm->stack[sp].data.astring;
                sp--;
                printf("%s\n", sv);
                break;
            case CPRINT:
                cv = vm->stack[sp].data.achar;
                sp--;
                printf("%c", cv);
                break;
            case CPRINTLN:
                cv = vm->stack[sp].data.achar;
                sp--;
                printf("%c\n", cv);
                break;
            case IGLOAD:
                addr = vm->code[ip++].data.anint;
                vm->stack[++sp].data.anint = vm->globals[addr].data.anint;
                break;
            case IGSTORE:
                addr = vm->code[ip++].data.anint;
                vm->globals[addr].data.anint = vm->stack[sp--].data.anint;
                break;
            case ILOAD:
                offset = vm->code[ip++].data.anint;
                vm->stack[++sp].data.anint = vm->call_stack[callsp].locals[offset].data.anint;
                break;
            case ISTORE:
                offset = vm->code[ip++].data.anint;
                vm->call_stack[callsp].locals[offset].data.anint = vm->stack[sp--].data.anint;
                break;
            case SGLOAD:
                addr = vm->code[ip++].data.anint;
                vm->stack[++sp].data.astring = vm->globals[addr].data.astring;
                break;
            case SGSTORE:
                addr = vm->code[ip++].data.anint;
                vm->globals[addr].data.astring = vm->stack[sp--].data.astring;
                break;
            case SLOAD:
                offset = vm->code[ip++].data.anint;
                vm->stack[++sp].data.astring = vm->call_stack[callsp].locals[offset].data.astring;
                break;
            case SSTORE:
                offset = vm->code[ip++].data.anint;
                vm->call_stack[callsp].locals[offset].data.astring = vm->stack[sp--].data.astring;
                break;
            case BGLOAD:
                addr = vm->code[ip++].data.anint;
                vm->stack[++sp].data.abool = vm->globals[addr].data.abool;
                break;
            case BGSTORE:
                addr = vm->code[ip++].data.anint;
                vm->globals[addr].data.abool = vm->stack[sp--].data.abool;
                break;
            case BLOAD:
                offset = vm->code[ip++].data.anint;
                vm->stack[++sp].data.abool = vm->call_stack[callsp].locals[offset].data.abool;
                break;
            case BSTORE:
                offset = vm->code[ip++].data.anint;
                vm->call_stack[callsp].locals[offset].data.abool = vm->stack[sp--].data.abool;
                break;
            case FGLOAD:
                addr = vm->code[ip++].data.anint;
                vm->stack[++sp].data.afloat = vm->globals[addr].data.afloat;
                break;
            case FGSTORE:
                addr = vm->code[ip++].data.anint;
                vm->globals[addr].data.afloat = vm->stack[sp--].data.afloat;
                break;
            case FLOAD:
                offset = vm->code[ip++].data.anint;
                vm->stack[++sp].data.afloat = vm->call_stack[callsp].locals[offset].data.afloat;
                break;
            case FSTORE:
                offset = vm->code[ip++].data.anint;
                vm->call_stack[callsp].locals[offset].data.afloat = vm->stack[sp--].data.afloat;
                break;
            case CGLOAD:
                addr = vm->code[ip++].data.anint;
                vm->stack[++sp].data.achar = vm->globals[addr].data.achar;
                break;
            case CGSTORE:
                addr = vm->code[ip++].data.anint;
                vm->globals[addr].data.achar = vm->stack[sp--].data.achar;
                break;
            case CLOAD:
                offset = vm->code[ip++].data.anint;
                vm->stack[++sp].data.achar = vm->call_stack[callsp].locals[offset].data.achar;
                break;
            case CSTORE:
                offset = vm->code[ip++].data.anint;
                vm->call_stack[callsp].locals[offset].data.achar = vm->stack[sp--].data.achar;
                break;
            case CALL:
                addr = vm->code[ip++].data.anint;
                int nargs = vm->code[ip++].data.anint;
                int nlocals = vm->code[ip++].data.anint;
                ++callsp;
                vm_context_init(&vm->call_stack[callsp], ip, nargs+nlocals);
                for (int i=0; i<nargs; i++) {
                    vm->call_stack[callsp].locals[i].data.anint = vm->stack[sp-i].data.anint;
                }
                sp -= nargs;
                ip = addr;
                break;
            case RET:
                ip = vm->call_stack[callsp].returnip;
                callsp--;
                break;
            case BR:
                ip = vm->code[ip++].data.anint;
                break;
            case BRT:
                addr = vm->code[ip++].data.anint;
                if (vm->stack[sp--].data.abool == true) {
                    ip = addr;
                }
                break;
            case BRF:
                addr = vm->code[ip++].data.anint;
                if (vm->stack[sp--].data.abool == false){
                    ip = addr;
                }
                break;
            case POP:
                --sp;
                break;
            case HALT:
                return 0;
                break;
            default:
                printf("invalid opcode: %d at ip=%d\n", opcode, (ip - 1));
                exit(1);
        }
        if (trace){
            vm_print_stack(vm->stack, sp);
        }
        opcode = vm->code[ip].data.anint;
    }
}

static void vm_context_init(Context *ctx, int ip, int nlocals) {
    if ( nlocals>DEFAULT_NUM_LOCALS ) {
        fprintf(stderr, "too many locals requested: %d\n", nlocals);
    }
    ctx->returnip = ip;
}

int vm_print_data(struct stack_base *globals, int count){
    printf("Data memory:\n");
    for (int i = 0; i < count; i++) {
        printf("%04d: %d\n", i, globals[i].data.anint);
    }
    return 0;
}
