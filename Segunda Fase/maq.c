#include <stdio.h>
#include <stdlib.h>
#include "maq.h"

//#define DEBUG

#ifdef DEBUG
#  define D(X) X
char *CODES[] = {
    "PUSH",
    "POP",
    "DUP",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "JMP",
    "JIT",
    "JIF",
    "CALL",
    "RET",
    "EQ",
    "GT",
    "GE",
    "LT",
    "LE",
    "NE",
    "STO",
    "RCL",
    "END",
    "PRN",
    "STL",
    "RCE",
    "ALC",
    "FRE",
    "ATR",
    "MOVE",
    "RECO",
    "DEPO",
    "ATAQ"
};

#else
#  define D(X)
#endif

static void Erro(char *msg) {
    fprintf(stderr, "%s\n", msg);
}

static void Fatal(char *msg, int cod) {
    Erro(msg);
    exit(cod);
}

Maquina *cria_maquina(INSTR *p) {
    Maquina *m = (Maquina*)malloc(sizeof(Maquina));
    if (!m) Fatal("Memória insuficiente",4);
    m->ip = 0;
    m->prog = p;
    m->rbp = 0;
    m->cristal = 0;
    m->vida = 3;
    m->index = 0;
    return m;
}

void destroi_maquina(Maquina** maq) {
    free(*maq);
    *maq = NULL;
}

/* Alguns macros para facilitar a leitura do código */
#define ip (m->ip)
#define rbp (m->rbp)
#define pil (&m->pil)
#define exec (&m->exec)
#define prg (m->prog)

void exec_maquina(Maquina *m, int n) {
    char *TYP[] = {
        "NUM",
        "ACAO",
        "VAR",
        "CEL",
        "TER"
    };
    char *TERR[] = {
        "road",
        "mountain",
        "river"
    };
    int i;
    for (i = 0; i < n; i++) {
        OpCode   opc = prg[ip].instr;
        OPERANDO arg = prg[ip].op;

        D(printf("%3d: %-4.4s {%-4.4s, %3d}\n     ", ip, CODES[opc], TYP[arg.t], arg.val));

        switch (opc) {
            OPERANDO tmp;
            OPERANDO tmp2;
            OPERANDO op1;
            OPERANDO op2;
            case PUSH:
                empilha(pil, arg);
                break;
            case POP:
                desempilha(pil);
                break;
            case DUP:
                tmp = desempilha(pil);
                empilha(pil, tmp);
                empilha(pil, tmp);
                break;
            case ADD:
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                if(op1.t == NUM && op2.t == NUM) {
                    tmp.t = NUM;
                    tmp.val = op1.val + op2.val;
                    empilha(pil, tmp);
                } else {
                    Erro("Os tipos não são NUM.\n");
                }
                break;
            case SUB:
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                if(op1.t == NUM && op2.t == NUM) {
                    tmp.t = NUM;
                    tmp.val = op2.val-op1.val;
                    empilha(pil, tmp);
                } else {
                    Erro("Os tipos não são NUM.\n");
                }   
                break;
            case MUL:
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                if(op1.t == NUM && op2.t == NUM) {
                    tmp.t = NUM;
                    tmp.val = op1.val*op2.val;
                    empilha(pil, tmp);
                } else {
                    Erro("Os tipos não são NUM.\n");
                }
                break;
            case DIV:
                op1 = desempilha(pil);
                op2 = desempilha(pil);
                if(op1.t == NUM && op2.t == NUM) {
                    tmp.t = NUM;
                    tmp.val = op2.val/op1.val;
                    empilha(pil, tmp);
                } else {
                    Erro("Os tipos não são NUM.\n");
                }
                break;
            case JMP:
                ip = arg.val;
                continue;
            case JIT:
                if (desempilha(pil).val != 0) {
                    ip = arg.val;
                    continue;
                }
                break;
            case JIF:
                if (desempilha(pil).val == 0) {
                    ip = arg.val;
                    continue;
                }
                break;
            case CALL:
                tmp.val = rbp;
                empilha(exec, tmp);
                tmp.val = ip;
                empilha(exec, tmp);
                ip = arg.val;
                continue;
            case RET:
                ip = desempilha(exec).val; 
                rbp = desempilha(exec).val;  
                break;
            case EQ:
                if (desempilha(pil).val == desempilha(pil).val) {
                    tmp.t = NUM;
                    tmp.val = 1;  
                    empilha(pil, tmp);
                } else {
                    tmp.t = NUM;
                    tmp.val = 0;
                    empilha(pil, tmp);
                }
                break;
            case GT:
                if (desempilha(pil).val < desempilha(pil).val) {
                    tmp.t = NUM;
                    tmp.val = 1;
                    empilha(pil, tmp);
                } else {
                    tmp.t = NUM;
                    tmp.val = 0;
                    empilha(pil, tmp);
                }
                break;
            case GE:
                if (desempilha(pil).val <= desempilha(pil).val) {
                    tmp.t = NUM;
                    tmp.val = 1;
                    empilha(pil, tmp);
                } else {
                    tmp.t = NUM;
                    tmp.val = 0;
                    empilha(pil, tmp);
                }
                break;
            case LT:
                if (desempilha(pil).val > desempilha(pil).val) {
                    tmp.t = NUM;
                    tmp.val = 1;
                    empilha(pil, tmp);
                } else {
                    tmp.t = NUM;
                    tmp.val = 0;
                    empilha(pil, tmp);
                }
                break;
            case LE:
                if (desempilha(pil).val >= desempilha(pil).val {
                    tmp.t = NUM;
                    tmp.val = 1;
                    empilha(pil, tmp);
                } else {
                    tmp.t = NUM;
                    tmp.val = 0;
                    empilha(pil, tmp);
                }
                break;
            case NE:
                if (desempilha(pil).val != desempilha(pil).val) {
                    tmp.t = NUM;
                    tmp.val = 1;
                    empilha(pil, tmp);
                } else {
                    tmp.t = NUM;
                    tmp.val = 0;
                    empilha(pil, tmp);
                }
                break;
            case STO:
                m->Mem[arg.val] = desempilha(pil);
                break;
            case RCL:
                empilha(pil, m->Mem[arg.val]);
                break;
            case END:
                return;
            case PRN:
                tmp = desempilha(pil);
                if(tmp.t == CEL) {
                //A ordem da impressao e de acordo com os atributos da CEL:
                //terrain, cristal, ocup, baseColour
                    printf("%s %s %i %i %i\n", TYP[tmp.t],TERR[tmp.Controlador.CEL.terrain], tmp.Controlador.CEL.cristal, 
                    tmp.Controlador.CEL.ocup, tmp.Controlador.CEL.baseColour);
                } else if(tmp.t == TER) {
                    printf("%s %s\n", TYP[tmp.t], TERR[tmp.val]);
                } else {
                    printf("%s %i\n", TYP[tmp.t], tmp.val);
                }
                break;
            case STL:
                exec->val[arg.val+rbp] = desempilha(pil);
                break;
            case RCE:
                empilha(pil, exec->val[arg.val+rbp]);
                break;
            case ALC:
                rbp = exec->topo - 1;
                exec->topo = exec->topo + arg.val;
                break;
            case FRE:
                exec->topo = exec->topo - arg.val;
                break;
            case ATR:
                tmp = desempilha(pil);
                //Verificar se o tipo  celula
                if(tmp.t == CEL) {
                    switch(arg.val) {
                        //Quando tmp.t = 0, e pra fazer referencia a um NUM  
                    case 0:
                        //Empilha o numero referido a enum do terreno
                        tmp.t = TER;
                        tmp.val = tmp.Controlador.CEL.terrain;      
                        empilha(pil, tmp);
                        break;
                    case 1:
                        tmp.t = 0;
                        tmp.val = tmp.Controlador.CEL.cristal;
                        empilha(pil, tmp);
                        break;
                    case 2:
                        tmp.t = 0;
                        tmp.val = tmp.Controlador.CEL.ocup;
                        empilha(pil, tmp);
                        break;
                    case 3:
                        tmp.t = 0;
                        tmp.val = tmp.Controlador.CEL.baseColour;
                        empilha(pil, tmp);
                        break;
                    }
                } else {
                    Erro("Operando nao eh do tipo CEL");
                }
                break;
            case MOVE:
                Sistema(m, 'M', arg.val);
                break;
            case RECO:
                Sistema(m, 'R', arg.val);
                break;
            case DEPO:
                Sistema(m, 'D', arg.val);
                break;
            case ATAQ:
                Sistema(m, 'A', arg.val);
                break;
        }
        D(imprime(pil,5));
        D(puts("\n"));
        ip++;
    }
}