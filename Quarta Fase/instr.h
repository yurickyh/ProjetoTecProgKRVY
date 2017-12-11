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
  ENTRY,
  LEAVE,
  MOVE,
  ATAQ,
  DEPO,
  RECO
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
} OPERANDO;

/* Instrução */
typedef struct {
    OpCode instr;
    OPERANDO op;
} INSTR;
