/*
    CXenon VM v0.0.5
*/



#ifndef __VM_H_
    #define __VM_H_
#endif



#define DEFAULT_STACK_SIZE      1000
#define DEFAULT_CALL_STACK_SIZE 100
#define DEFAULT_NUM_LOCALS      10



typedef enum {
    IADD =       1,          // integer add
    ISUB =       2,          // integer substract
    IMUL =       3,          // integer multiply
    IDIV =       4,          // integer divide
    ILT =        5,          // integer less than
    IEQ =        6,          // integer equals
    BR =         7,          // branch
    BRT =        8,          // branch if true
    BRF =        9,          // branch if false
    ICONST =     10,         // integer constant
    ILOAD =      11,         // load from data memory
    IGLOAD =     12,         // global load from data memory
    ISTORE =     13,         // store in data memory
    IGSTORE =    14,         // global store in data memory
    IPRINT =     15,         // print
    IPRINTLN =   16,         // print with trailing newline
    POP =        17,         // pop from stack
    CALL =       18,         // call function
    RET =        19,         // return
    FADD =       20,         // float add
    FSUB =       21,         // float substract
    FMUL =       22,         // float multiply
    FDIV =       23,         // float divide
    FCONST =     24,         // float constant
    FLT =        25,         // float less than
    FEQ =        26,         // float equeals
    FMT =        27,         // float more than
    FNEQ =       28,         // float not equeals
    IMT =        29,         // integer more than
    INEQ =       30,         // integer not equeals
    BCONST =     31,         // boolean constant
    BEQ =        32,         // boolean equeals
    BNEQ =       33,         // boolean not equeals
    FPRINT =     36,         // float print
    FPRINTLN =   37,         // float print with trailing newline
    BPRINT =     38,         // boolean print
    BPRINTLN =   39,         // boolean print with trailing newline
    SCONST =     40,         // string constant
    SPRINT =     41,         // string print
    SPRINTLN =   42,         // string print with trailing newline
    SEQ =        43,         // string equeals
    SNEQ =       44,         // string not equeals
    SLT =        45,         // string less than
    SMT =        46,         // string more than
    SGLOAD =     47,         // string global load
    SGSTORE =    48,         // string global store
    SLOAD =      49,         // string load
    SSTORE =     50,         // string store
    BGLOAD =     51,         // boolean global load
    BGSTORE =    52,         // boolean global store
    BLOAD =      53,         // boolean load
    BSTORE =     54,         // boolean store
    FGLOAD =     55,         // float global load
    FGSTORE =    56,         // float global store
    FLOAD =      57,         // float load
    FSTORE =     58,         // float store
    CCONST =     59,         // char constant
    CPRINT =     60,         // char print
    CPRINTLN =   61,         // char print with trailing newline
    CEQ =        62,         // char equals
    CNEQ =       63,         // char not equals
    CGLOAD =     64,         // char global load
    CGSTORE =    65,         // char global store
    CLOAD =      66,         // char load
    CSTORE =     67,         // char store
    INPUT =      68,         // get input
    GLOAD =      69,
    GSTORE =     70,
    LOAD =       71,
    STORE =      72,
    CONST =      73,
    HALT =       74          // exit program
} VM_CODE;



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
    { "gload",    1 },
    { "gstore",   1 },
    { "load",     1 },
    { "store",    1 },
    { "const",    1 },
    { "halt",     0 }     // 68
};



typedef enum {
    x_integer,
    x_floating,
    x_character,
    x_string,
    x_boolean,
    x_opcode,
    x_function,
    x_void
} x_type;

typedef enum {
    x_native_t,
    x_foreign_t
} x_func_t;



typedef struct{
    int addr;
    int nargs;
    int nlocals;
    int xret_t;
    int xfunc_t;
    char *name;
} xabstract_func_t;



typedef struct{
    int type;
    struct {
        char* astring;
        char achar;
        long int anint;
        float afloat;
        bool abool;
        xabstract_func_t func;
    } data;
} xenon_stack_item;



typedef struct {
    char *name;
    int state;
    xenon_stack_item data;
} x_var_t;



typedef struct {
    int returnip;
    xenon_stack_item locals[DEFAULT_NUM_LOCALS];
} Context;



typedef struct {
    xenon_stack_item *code;
    int code_size;

    xenon_stack_item *globals;
    int nglobals;

    xenon_stack_item stack[DEFAULT_STACK_SIZE];
    Context call_stack[DEFAULT_CALL_STACK_SIZE];
} VM;


void vm_context_init(Context *ctx, int ip, int nlocals);
VM *vm_create(xenon_stack_item *code, int code_size, int nglobals);
int vm_free(VM *vm);
int vm_init(VM *vm, xenon_stack_item *code, int code_size, int nglobals);
int vm_exec(VM *vm, int startip, bool trace);
int vm_print_instr(xenon_stack_item *code, int ip);
int vm_print_stack(xenon_stack_item *stack, int count);
int vm_print_data(xenon_stack_item *globals, int count);
