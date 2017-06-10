#
#    CXenon VM v0.0.5
#

import copy

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#ifndef __VM_H_
    #include "vm.h"
#endif
#ifndef __VM_UTILS_H_
    #include "vm_utils.h"
#endif

#
#    CXenon VM v0.0.5
#



#ifndef __VM_H_
    #define __VM_H_
#endif



DEFAULT_STACK_SIZE      =1000
DEFAULT_CALL_STACK_SIZE = 100
DEFAULT_NUM_LOCALS      = 10




IADD =       1          # integer add
ISUB =       2          # integer substract
IMUL =       3          # integer multiply
IDIV =       4          # integer divide
ILT =        5          # integer less than
IEQ =        6          # integer equals
BR =         7          # branch
BRT =        8          # branch if true
BRF =        9          # branch if false
ICONST =     10         # integer constant
ILOAD =      11         # load from data memory
IGLOAD =     12         # global load from data memory
ISTORE =     13         # store in data memory
IGSTORE =    14         # global store in data memory
IPRINT =     15         # print
IPRINTLN =   16         # print with trailing newline
POP =        17         # pop from stack
CALL =       18         # call function
RET =        19         # return
FADD =       20         # float add
FSUB =       21         # float substract
FMUL =       22         # float multiply
FDIV =       23         # float divide
FCONST =     24         # float constant
FLT =        25         # float less than
FEQ =        26         # float equeals
FMT =        27         # float more than
FNEQ =       28         # float not equeals
IMT =        29         # integer more than
INEQ =       30         # integer not equeals
BCONST =     31         # boolean constant
BEQ =        32         # boolean equeals
BNEQ =       33         # boolean not equeals
FPRINT =     36         # float print
FPRINTLN =   37         # float print with trailing newline
BPRINT =     38         # boolean print
BPRINTLN =   39         # boolean print with trailing newline
SCONST =     40         # string constant
SPRINT =     41         # string print
SPRINTLN =   42         # string print with trailing newline
SEQ =        43         # string equeals
SNEQ =       44         # string not equeals
SLT =        45         # string less than
SMT =        46         # string more than
SGLOAD =     47         # string global load
SGSTORE =    48         # string global store
SLOAD =      49         # string load
SSTORE =     50         # string store
BGLOAD =     51         # boolean global load
BGSTORE =    52         # boolean global store
BLOAD =      53         # boolean load
BSTORE =     54         # boolean store
FGLOAD =     55         # float global load
FGSTORE =    56         # float global store
FLOAD =      57         # float load
FSTORE =     58         # float store
CCONST =     59         # char constant
CPRINT =     60         # char print
CPRINTLN =   61         # char print with trailing newline
CEQ =        62         # char equals
CNEQ =       63         # char not equals
CGLOAD =     64         # char global load
CGSTORE =    65         # char global store
CLOAD =      66         # char load
CSTORE =     67         # char store
INPUT =      68         # get input
GLOAD =      69
GSTORE =     70
LOAD =       71
STORE =      72
CONST =      73
HALT =       74          # exit program




#typedef struct {
#    char name[8]
#    int nargs
#} VM_INSTRUCTION







#typedef enum {
#    x_integer,
#    x_floating,
#    x_character,
#    x_string,
#    x_boolean,
#    x_opcode,
#    x_function,
#    x_void
#} x_type

#typedef enum {
#    x_native_t,
#    x_foreign_t
#} x_func_t

x_integer = 0
x_floating = 1
x_character = 2
x_string = 3
x_boolean = 4
x_opcode = 5
x_function = 6
x_void = 7

x_native_t = 0
x_foreign_t = 1



class XAbstractFunc:
    addr = None
    nargs = None
    nlocals = None
    xret_t = None
    xfunc_t = None
    name = None

class XenonStackItem:
    type = None
    class Data:
        astring = None
        achar = None
        anint = None
        afloat = None
        abool = None
        func = None

class XenonStackVector:
    size = None
    cursor = None
    vector = None

class XenonVariable:
    name = None
    state = None
    data = None

class Context:
    returnip  = None
    locals = [XenonStackItem() for i in range(DEFAULT_NUM_LOCALS)]

class VirtualMachine:
    code = None
    code_size = None

    globals = None
    nglobals = None

    stack = None
    call_stack = [Context() for i in range(DEFAULT_CALL_STACK_SIZE)]



def vm_init(vm: VirtualMachine, code: XenonStackVector, nglobals: int) -> int:
    #vm.code.vector = calloc(1, sizeof(xenon_stack_item) * code.size)
    #memcpy(vm.code.vector, code.vector, code.size * sizeof(xenon_stack_item))
    #vm.code.size = code.size
    #vm.code.cursor = 0
    #vm.code_size = code.size
    vm.code = copy.deepcopy(code)
    vm.globals.vector = calloc(1, sizeof(xenon_stack_item) * nglobals)
    vm.globals.size = nglobals
    vm.globals.cursor = 0
    vm.nglobals = nglobals
    vm.stack.vector = calloc(1, sizeof(xenon_stack_vector) * 1000)
    vm.stack.size = 1000
    vm.stack.cursor = 0
    return 0

def vm_free(vm: VirtualMachine) -> int:
    vm = None
    del vm
    return 0

def vm_create(code: XenonStackVector, nglobals: int) -> VirtualMachine:
    vm = VirtualMachine()
    vm_init(vm, code, nglobals)
    return vm



def vm_exec(vm: VirtualMachine, startip: int, trace: bool) -> int:

    ip = None # instructionpointer
    #int fp # framepointer
    sp = None # stackpointer
    callsp = None
    offset = 0
    v = None
    addr = None
    #int nargs
    #int rvalue
    a = None
    b = None
    fv = None
    fa = None
    fb = None
    bv = None
    ba = None
    bb = None
    sv = None
    sa = None
    sb = None
    cv = None
    ca = None
    cb = None
    si = None

    #int size = sizeof(vm.code)
    ip = startip
    sp = -1
    callsp = -1
    opcode = vm.code.vector[ip].data.anint

    while True:

        ip += 1
        if opcode == CONST:
            sp += 1
            vm.stack.vector[sp] = vm.code.vector[ip]
            ip += 1
            break
        elif opcode == ICONST:
            sp += 1
            vm.stack.vector[sp].data.anint = vm.code.vector[ip].data.anint
            ip += 1
            break
        elif opcode == ISUB:
            sp -= 1
            b = vm.stack.vector[sp].data.anint
            a = vm.stack.vector[sp].data.anint
            #sp -= 1
            vm.stack.vector[sp].data.anint = a - b
            #sp  += 1
            break
        elif opcode == IADD:
            b = vm.stack.vector[sp].data.anint
            sp -= 1
            a = vm.stack.vector[sp].data.anint
            #sp -= 1
            #sp += 1
            vm.stack.vector[sp].data.anint = a + b
            break
        elif opcode == IMUL:
            b = vm.stack.vector[sp].data.anint
            sp -= 1
            a = vm.stack.vector[sp].data.anint
            #sp -= 1
            #sp += 1
            vm.stack.vector[sp].data.anint = a * b
            break
        elif opcode == IDIV:
            b = vm.stack.vector[sp].data.anint
            sp -= 1
            a = vm.stack.vector[sp].data.anint
            #sp -= 1
            #sp += 1
            vm.stack.vector[sp].data.anint = a/b
            break
        elif opcode == ILT:
            b = vm.stack.vector[sp].data.anint
            sp -= 1
            a = vm.stack.vector[sp].data.anint
            sp -= 1
            if a > b:
                sp += 1
                vm.stack.vector[sp].data.abool = true
                break
            else:
                sp += 1
                vm.stack.vector[sp].data.abool = false
                break
        elif opcode == IMT:
            sp -= 1
            b = vm.stack.vector[sp].data.anint
            sp -= 1
            a = vm.stack.vector[sp].data.anint
            if a < b:
                sp += 1
                vm.stack.vector[sp].data.abool = true
                break
            else:
                sp += 1
                vm.stack.vector[sp].data.abool = false
                break
        elif opcode == IEQ:
            b = vm.stack.vector[sp].data.anint
            sp -= 1
            a = vm.stack.vector[sp].data.anint
            sp -= 1
            if a == b:
                sp += 1
                vm.stack.vector[sp].data.abool = true
                break
            else:
                sp += 1
                vm.stack.vector[sp].data.abool = false
                break
        elif opcode == INEQ:
            b = vm.stack.vector[sp].data.anint
            sp -= 1
            a = vm.stack.vector[sp].data.anint
            sp -= 1
            if a != b:
                sp += 1
                vm.stack.vector[sp].data.abool = true
                break
            else:
                sp += 1
                vm.stack.vector[sp].data.abool = false
                break
        elif opcode == FCONST:
            fv = vm.code.vector[ip].data.afloat
            ip += 1
            sp += 1
            vm.stack.vector[sp].data.afloat = fv
            break
        elif opcode == FSUB:
            fb = vm.stack.vector[sp].data.afloat
            sp -= 1
            fa = vm.stack.vector[sp].data.afloat
            #sp -= 1
            #sp += 1
            vm.stack.vector[sp].data.afloat = fa + fb
            break
        elif opcode == FADD:
            fb = vm.stack.vector[sp].data.afloat
            sp -= 1
            fa = vm.stack.vector[sp].data.afloat
            #sp -= 1
            #sp += 1
            vm.stack.vector[sp].data.afloat = fa + fb
            break
        elif opcode == FMUL:
            fb = vm.stack.vector[sp].data.afloat
            sp -= 1 
            fa = vm.stack.vector[sp].data.afloat
            #sp -= 1
            #sp += 1
            vm.stack.vector[sp].data.afloat = fa * fb
            break
        elif opcode == FDIV:
            fb = vm.stack.vector[sp].data.afloat
            sp -= 1
            fa = vm.stack.vector[sp].data.afloat
            #sp -= 1
            #sp += 1
            vm.stack.vector[sp].data.afloat = fa/fb
            break
        elif opcode == FEQ:
            fb = vm.stack.vector[sp].data.afloat
            sp -= 1
            fa = vm.stack.vector[sp].data.afloat
            sp -= 1
            if fa == fb:
                sp += 1
                vm.stack.vector[sp].data.abool = true
                break
            else:
                sp += 1
                vm.stack.vector[sp].data.abool = false
                break
        elif opcode == FLT:
            fb = vm.stack.vector[sp].data.afloat
            sp -= 1
            fa = vm.stack.vector[sp].data.afloat
            sp -= 1
            if fa > fb:
                sp += 1
                vm.stack.vector[sp].data.abool = true
                break
            else:
                sp += 1
                vm.stack.vector[sp].data.abool = false
                break
        elif opcode == FMT:
            fb = vm.stack.vector[sp].data.afloat
            sp -= 1
            fa = vm.stack.vector[sp].data.afloat
            sp -= 1
            if fa < fb:
                sp += 1
                vm.stack.vector[sp].data.abool = true
                break
            else:
                sp += 1
                vm.stack.vector[sp].data.abool = false
                break
        elif opcode == FNEQ:
            fb = vm.stack.vector[sp].data.afloat
            sp -= 1
            fa = vm.stack.vector[sp].data.afloat
            sp -= 1
            if fa != fb:
                sp += 1
                vm.stack.vector[sp].data.abool = true
                break
            else:
                sp += 1
                vm.stack.vector[sp].data.abool = false
                break
        elif opcode == BCONST:
            sp += 1
            vm.stack.vector[sp].data.abool = vm.code.vector[ip].data.abool
            ip += 1
            break
        elif opcode == BNEQ:
            bb = vm.stack.vector[sp].data.abool
            sp -= 1
            ba = vm.stack.vector[sp].data.abool
            sp -= 1
            if ba == bb:
                sp += 1
                vm.stack.vector[sp].data.abool = true
                break
            else:
                sp += 1
                vm.stack.vector[sp].data.abool = false
                break
        elif opcode == BEQ:
            bb = vm.stack.vector[sp].data.abool
            sp -= 1
            ba = vm.stack.vector[sp].data.abool
            sp -= 1
            if ba != bb:
                sp += 1
                vm.stack.vector[sp].data.abool = true
                break
            else:
                sp += 1
                vm.stack.vector[sp].data.abool = false
                break
        elif opcode == SCONST:
            sv = vm.code.vector[ip].data.astring
            ip += 1
            sp += 1
            vm.stack.vector[sp].data.astring = sv
            break
        elif opcode == SEQ:
            strcpy(sb, vm.stack.vector[sp].data.astring)
            sp -= 1
            strcpy(sa, vm.stack.vector[sp].data.astring)
            sp -= 1
            if strcmp(sa, sb) == 0:
                sp += 1
                vm.stack.vector[sp].data.abool = true
                strcpy(sa, "\0")
                strcpy(sb, "\0")
                break
            else:
                sp += 1
                vm.stack.vector[sp].data.abool = false
                strcpy(sa, "\0")
                strcpy(sb, "\0")
                break
        elif opcode == SNEQ:
            strcpy(sb, vm.stack.vector[sp].data.astring)
            sp -= 1
            strcpy(sa, vm.stack.vector[sp].data.astring)
            sp -= 1
            if strcmp(sa, sb) != 0:
                sp += 1
                vm.stack.vector[sp].data.abool = true
                strcpy(sa, "\0")
                strcpy(sb, "\0")
                break
            else:
                sp += 1
                vm.stack.vector[sp].data.abool = false
                strcpy(sa, "\0")
                strcpy(sb, "\0")
                break
        elif opcode == SLT:
            strcpy(sb, vm.stack.vector[sp].data.astring)
            sp -= 1
            strcpy(sa, vm.stack.vector[sp].data.astring)
            sp -= 1
            if strlen(sa) > strlen(sb):
                sp += 1
                vm.stack.vector[sp].data.abool = true
                strcpy(sa, "\0")
                strcpy(sb, "\0")
                break
            else:
                sp += 1
                vm.stack.vector[sp].data.abool = false
                strcpy(sa, "\0")
                strcpy(sb, "\0")
                break
        elif opcode == SMT:
            strcpy(sb, vm.stack.vector[sp].data.astring)
            sp -= 1
            strcpy(sa, vm.stack.vector[sp].data.astring)
            sp -= 1
            if strlen(sa) < strlen(sb):
                sp += 1
                vm.stack.vector[sp].data.abool = true
                strcpy(sa, "\0")
                strcpy(sb, "\0")
                break
            else:
                sp += 1
                vm.stack.vector[sp].data.abool = false
                strcpy(sa, "\0")
                strcpy(sb, "\0")
                break
        elif opcode == CCONST:
            cv = vm.code.vector[ip].data.achar
            ip += 1
            sp += 1
            vm.stack.vector[sp].data.achar = cv
            break
        elif opcode == CEQ:
            cb = vm.stack.vector[sp].data.achar
            sp -= 1
            ca = vm.stack.vector[sp].data.achar
            sp -= 1
            if ca == cb:
                sp += 1
                vm.stack.vector[sp].data.abool = true
            else:
                sp += 1
                vm.stack.vector[sp].data.abool = false
            break
        elif opcode == CNEQ:
            cb = vm.stack.vector[sp].data.achar
            sp -= 1
            ca = vm.stack.vector[sp].data.achar
            sp -= 1
            if ca != cb:
                sp += 1
                vm.stack.vector[sp].data.abool = true
            else:
                sp += 1
                vm.stack.vector[sp].data.abool = false
            break
        elif opcode == IPRINT:
            v = vm.stack.vector[sp].data.anint
            sp -= 1
            print(v, end="")
            break
        elif opcode == FPRINT:
            fv = vm.stack.vector[sp].data.afloat
            sp -= 1
            print(fv, end="")
            break
        elif opcode == IPRINTLN:
            v = vm.stack.vector[sp].data.anint
            sp -= 1
            print("%i\n", v)
            break
        elif opcode == FPRINTLN:
            fv = vm.stack.vector[sp].data.afloat
            sp -= 1
            print("%f\n", fv)
            break
        elif opcode == BPRINT:
            bv = vm.stack.vector[sp].data.anint
            sp -= 1
            print(bv, end="")
            break
        elif opcode == BPRINTLN:
            bv = vm.stack.vector[sp].data.abool
            sp -= 1
            print(bv)
            break
        elif opcode == SPRINT:
            sv = vm.stack.vector[sp].data.astring
            sp -= 1
            print("%s", sv)
            break
        elif opcode == SPRINTLN:
            sv = vm.stack.vector[sp].data.astring
            sp -= 1
            print("%s\n", sv)
            break
        elif opcode == CPRINT:
            cv = vm.stack.vector[sp].data.achar
            sp -= 1
            print("%c", cv)
            break
        elif opcode == CPRINTLN:
            cv = vm.stack.vector[sp].data.achar
            sp -= 1
            print("%c\n", cv)
            break
        elif opcode == INPUT:
            sp += 1
            a = 0
            b = 100
            si = malloc(sizeof(char) * b)
            fflush(stdin)
            while True:
                si[a] = getchar()
                if a >= b:
                    b += 25
                    si = realloc(si, sizeof(char) * b)
                if si[a] == '\n':
                    si[a] = '\0'
                    break
                a += 1
            vm.stack.vector[sp].data.astring = si
            break
        elif opcode == IGLOAD:
            addr = vm.code.vector[ip].data.anint
            ip += 1
            sp += 1
            vm.stack.vector[sp].data.anint = vm.globals.vector[addr].data.anint
            break
        elif opcode == IGSTORE:
            addr = vm.code.vector[ip].data.anint
            ip += 1
            vm.globals.vector[addr].data.anint = vm.stack.vector[sp].data.anint
            sp -= 1
            break
        elif opcode == ILOAD:
            offset = vm.code.vector[ip].data.anint
            ip += 1
            sp += 1
            vm.stack.vector[sp].data.anint = vm.call_stack[callsp].locals[offset].data.anint
            break
        elif opcode == ISTORE:
            offset = vm.code.vector[ip].data.anint
            ip += 1
            vm.call_stack[callsp].locals[offset].data.anint = vm.stack.vector[sp].data.anint
            sp -= 1
            break
        elif opcode == SGLOAD:
            addr = vm.code.vector[ip].data.anint
            ip += 1
            sp += 1
            vm.stack.vector[sp].data.astring = vm.globals.vector[addr].data.astring
            break
        elif opcode == SGSTORE:
            addr = vm.code.vector[ip].data.anint
            ip += 1
            vm.globals.vector[addr].data.astring = vm.stack.vector[sp].data.astring
            sp -= 1
            break
        elif opcode == SLOAD:
            offset = vm.code.vector[ip].data.anint
            ip += 1
            sp += 1
            vm.stack.vector[sp].data.astring = vm.call_stack[callsp].locals[offset].data.astring
            break
        elif opcode == SSTORE:
            offset = vm.code.vector[ip].data.anint
            ip += 1
            vm.call_stack[callsp].locals[offset].data.astring = vm.stack.vector[sp].data.astring
            sp -= 1
            break
        elif opcode == BGLOAD:
            addr = vm.code.vector[ip].data.anint
            ip += 1
            sp += 1
            vm.stack.vector[sp].data.abool = vm.globals.vector[addr].data.abool
            break
        elif opcode == BGSTORE:
            addr = vm.code.vector[ip].data.anint
            ip += 1
            vm.globals.vector[addr].data.abool = vm.stack.vector[sp].data.abool
            sp -= 1
            break
        elif opcode == BLOAD:
            offset = vm.code.vector[ip].data.anint
            ip += 1
            sp += 1
            vm.stack.vector[sp].data.abool = vm.call_stack[callsp].locals[offset].data.abool
            break
        elif opcode == BSTORE:
            offset = vm.code.vector[ip].data.anint
            ip += 1
            vm.call_stack[callsp].locals[offset].data.abool = vm.stack.vector[sp].data.abool
            sp -= 1
            break
        elif opcode == FGLOAD:
            addr = vm.code.vector[ip].data.anint
            ip += 1
            sp += 1
            vm.stack.vector[sp].data.afloat = vm.globals.vector[addr].data.afloat
            break
        elif opcode == FGSTORE:
            addr = vm.code.vector[ip].data.anint
            ip += 1
            vm.globals.vector[addr].data.afloat = vm.stack.vector[sp].data.afloat
            sp -= 1
            break
        elif opcode == FLOAD:
            offset = vm.code.vector[ip].data.anint
            ip += 1
            sp += 1
            vm.stack.vector[sp].data.afloat = vm.call_stack[callsp].locals[offset].data.afloat
            break
        elif opcode == FSTORE:
            offset = vm.code.vector[ip].data.anint
            ip += 1
            vm.call_stack[callsp].locals[offset].data.afloat = vm.stack.vector[sp].data.afloat
            sp -= 1
            break
        elif opcode == CGLOAD:
            addr = vm.code.vector[ip].data.anint
            ip += 1
            sp += 1
            vm.stack.vector[sp].data.achar = vm.globals.vector[addr].data.achar
            break
        elif opcode == CGSTORE:
            addr = vm.code.vector[ip].data.anint
            ip += 1
            vm.globals.vector[addr].data.achar = vm.stack.vector[sp].data.achar
            sp -= 1
            break
        elif opcode == CLOAD:
            offset = vm.code.vector[ip].data.anint
            ip += 1
            sp += 1
            vm.stack.vector[sp].data.achar = vm.call_stack[callsp].locals[offset].data.achar
            break
        elif opcode == CSTORE:
            offset = vm.code.vector[ip].data.anint
            ip += 1
            vm.call_stack[callsp].locals[offset].data.achar = vm.stack.vector[sp].data.achar
            sp -= 1
            break
        elif opcode == GLOAD:
            addr = vm.code.vector[ip].data.anint
            ip += 1
            sp += 1
            vm.stack.vector[sp] = vm.globals.vector[addr]
            break
        elif opcode == GSTORE:
            addr = vm.code.vector[ip].data.anint
            ip += 1
            vm.globals.vector[addr] = vm.stack.vector[sp]
            sp -= 1
            break
        elif opcode == LOAD:
            offset = vm.code.vector[ip].data.anint
            ip += 1
            sp += 1
            vm.stack.vector[sp] = vm.call_stack[callsp].locals[offset]
            break
        elif opcode == STORE:
            offset = vm.code.vector[ip].data.anint
            ip += 1
            vm.call_stack[callsp].locals[offset] = vm.stack.vector[sp]
            sp -= 1
            break
        elif opcode == CALL:
            if vm.code.vector[ip].data.func.xfunc_t == x_native_t:
                addr = vm.code.vector[ip].data.func.addr
                nargs = vm.code.vector[ip].data.func.nargs
                nlocals = vm.code.vector[ip].data.func.nlocals
                ip += 1
                callsp += 1
                vm_context_init(vm.call_stack[callsp], ip, nargs+nlocals)
                i = 0
                while i<nargs:
                    vm.call_stack[callsp].locals[i].data = vm.stack.vector[sp-i].data
                    i += 1
                sp -= nargs
                ip = addr
            elif vm.code.vector[ip].data.func.xfunc_t == x_foreign_t:
                print("Feature not implemented yet, vm.c#617")
                print("A fatal error occured")
                exit(1)
            break
        elif opcode == RET:
            ip = vm.call_stack[callsp].returnip
            callsp -= 1
            break
        elif opcode == BR:
            ip = vm.code.vector[ip].data.anint
            ip += 1
            break
        elif opcode == BRT:
            addr = vm.code.vector[ip].data.anint
            ip += 1
            if vm.stack.vector[sp].data.abool == true:
                sp -= 1
                ip = addr
            break
        elif opcode == BRF:
            addr = vm.code.vector[ip].data.anint
            ip += 1
            if vm.stack.vector[sp].data.abool == false:
                sp -= 1
                ip = addr
            break
        elif opcode == POP:
            sp -= 1
            break
        elif opcode == HALT:
            return 0
            break
        else:
            print("invalid opcode:" + str(opcode)+ " at ip=", str(ip - 1))
            return 1
        opcode = vm.code.vector[ip].data.anint



def vm_context_init(ctx: Context, ip: int, nlocals: int):
    if nlocals>DEFAULT_NUM_LOCALS:
        fprint(stderr, "too many locals requested: %d\n", nlocals)
    ctx.returnip = ip

def vm_print_data(globals: XenonStackVector, count: int) -> int:
    print("Data memory:")
    i = 0
    while i < count:
        print(str(i) + str(globals.vector[i].data.anint))
        i += 1
    return 0

