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
    ATR,
    MOVE,
    RECO,
    DEPO,
    ATAQ,
    ENTRY,
    LEAVE
} OpCode;

typedef enum{
    NUM,
    ACAO,
    CEL,
    TER
} Tipo;

typedef struct {
    Tipo t;
    int val;
    union{
        struct {
            int terrain;
            int cristal;
            int ocup;
            int baseColour;
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
