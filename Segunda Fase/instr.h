/* Códigos das instruções */
typedef enum {
    PUSH,
    POP,
    DUP,
    ADD,
    SUB,
    MUL,
    DIV,
    JMP,
    JIT,
    JIF,
    CALL,
    RET,
    EQ,
    GT,
    GE,
    LT,
    LE,
    NE,
    STO,
    RCL,
    END,
    PRN,
    STL,
    RCE,
    ALC,
    FRE,
    ATR,
    MOVE,
    RECO,
    DEPO,
    ATAQ
} OpCode;

typedef enum{
    NUM,
    ACAO,
    VAR,
    CEL,
    TER
}Tipo;

typedef struct {  
    Tipo t;
    int val;
    union{
        struct {
            int terrain;
            int cristal;
            int ocup;
            int baseColour;
            //Base base;
        } CEL;
    } Controlador;
    /*union {
    int n;
    int ac;
    int v;
    } val;*/ 
} OPERANDO;

/* Instrução */
typedef struct {
    OpCode instr;
    OPERANDO op;
} INSTR;