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
  ATR//,
  //MOVE,
  //RECO,
  //DEPO,
  //ATAQ
} OpCode;

/* Tipos dos operandos */
/* no momento, são todos inteiros */
typedef enum {
  NUM,
  ACAO,
  VAR
} Tipo;

//Operando
typedef struct {
   Tipo t;
   int val;
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
