/*
    CXenon VM v0.0.5
*/

#ifndef VM_H_
#define MAIN_H_



#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_STACK_SIZE      1000
#define DEFAULT_CALL_STACK_SIZE 100
#define DEFAULT_NUM_LOCALS      10



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
    HALT =       69          // exit program
} VM_CODE;



typedef struct{
    int addr;
    int nargs;
    int nlocals;
    int xret_t;
    int xfunc_t;
    char *name;
} xabstract_func_t;



struct stack_base{
    int type;
    struct {
        char* astring;
        char achar;
        int anint;
        float afloat;
        bool abool;
        xabstract_func_t func;
    } data;
};



typedef struct {
    int returnip;
    struct stack_base locals[DEFAULT_NUM_LOCALS];
} Context;



typedef struct {
    struct stack_base *code;
    int code_size;

    struct stack_base *globals;
    int nglobals;

    struct stack_base stack[DEFAULT_STACK_SIZE];
    Context call_stack[DEFAULT_CALL_STACK_SIZE];
} VM;


void vm_context_init(Context *ctx, int ip, int nlocals);
VM *vm_create(struct stack_base *code, int code_size, int nglobals);
int vm_free(VM *vm);
int vm_init(VM *vm, struct stack_base *code, int code_size, int nglobals);
int vm_exec(VM *vm, int startip, bool trace);
int vm_print_instr(struct stack_base *code, int ip);
int vm_print_stack(struct stack_base *stack, int count);
int vm_print_data(struct stack_base *globals, int count);




#ifdef __cplusplus
}
#endif

#endif
