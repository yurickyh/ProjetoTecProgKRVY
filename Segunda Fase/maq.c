#include <stdio.h>
#include <stdlib.h>
#include "maq.h"
//#include "arena.h"

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
  "ATR"//,
  //"MOVE",
  //"RECO",
  //"DEPO",
  //"ATAQ"
};

char *TYP[] = {
  "NUM",
  "ACAO",
  "VAR",
  "CEL"
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
  return m;
}

void destroi_maquina(/*Maquina *m, */Maquina** maq) {
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
  int i;
  for (i = 0; i < n; i++) {
 OpCode   opc = prg[ip].instr;
 OPERANDO arg = prg[ip].op;
 
 D(printf("%3d: %-4.4s {%-4.4s, %3d}\n     ", ip, CODES[opc], TYP[arg.t], arg.val));

 switch (opc) {
   OPERANDO tmp;
   OPERANDO tmp2;
 case PUSH:
   printf("Tipo: %s  ", TYP[arg.t]);
   printf("Val: %d  ", arg.val);
   printf("Ter: %d  ", arg.Controlador.CEL.cristal);
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
   tmp = desempilha(pil);
   tmp2.t = NUM;
   tmp2.val = tmp.val + desempilha(pil).val;
   empilha(pil, tmp2);
   break;
 case SUB:
   tmp = desempilha(pil);
   tmp2.t = NUM;
   tmp2.val = desempilha(pil).val-tmp.val;
   empilha(pil, tmp2);
   break;
 case MUL:
   tmp = desempilha(pil);
   tmp2.t = NUM;
   tmp2.val = tmp.val*desempilha(pil).val;
   empilha(pil, tmp2);
   break;
 case DIV:
   tmp = desempilha(pil);
   tmp2.t = NUM;
   tmp2.val = desempilha(pil).val/tmp.val;
   empilha(pil, tmp2);
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
   if (desempilha(pil).val == desempilha(pil).val){
     tmp.t = NUM;
     tmp.val = 1;  
     empilha(pil, tmp);
   }
   else{
     tmp.t = NUM;
     tmp.val = 0;
     empilha(pil, tmp);
   }
   break;
 case GT:
   if (desempilha(pil).val < desempilha(pil).val){
     tmp.t = NUM;
     tmp.val = 1;
     empilha(pil, tmp);
   }
   else{
     tmp.t = NUM;
     tmp.val = 0;
     empilha(pil, tmp);
   }
   break;
 case GE:
   if (desempilha(pil).val <= desempilha(pil).val){
     tmp.t = NUM;
     tmp.val = 1;
     empilha(pil, tmp);
   }
   else{
     tmp.t = NUM;
     tmp.val = 0;
     empilha(pil, tmp);
   }
   break;
 case LT:
   if (desempilha(pil).val > desempilha(pil).val){
     tmp.t = NUM;
     tmp.val = 1;
     empilha(pil, tmp);
   }
   else{
     tmp.t = NUM;
     tmp.val = 0;
     empilha(pil, tmp);
   }
   break;
 case LE:
   if (desempilha(pil).val >= desempilha(pil).val){
     tmp.t = NUM;
     tmp.val = 1;
     empilha(pil, tmp);
   }
   else{
     tmp.t = NUM;
     tmp.val = 0;
     empilha(pil, tmp);
   }
   break;
 case NE:
   if (desempilha(pil).val != desempilha(pil).val){
     tmp.t = NUM;
     tmp.val = 1;
     empilha(pil, tmp);
   }
   else{
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
   printf("%d\n", desempilha(pil).val);
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
   //verificar se o tipo eh celula
   if(TYP[tmp.t] == "CEL"){
    switch(arg.val){    
    //quando faz tmp.t = 0, eh pra fazer referencia a NUM  
      case 0:
        //empilha o numero referido a enum do terreno
        tmp.t = 4;
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
   } 
   else{
    Erro("Operando nao eh do tipo CEL");
   }
   break;
 //case ATR:
  // tmp = desempilha(pil);
   /*Celula é um operando??? Como??
   switch(arg.val){
   case 0:
     empilha(pil, tmp.terrain);
     break;
   case 1:
     empilha(pil, tmp.cristais);
     break;
   case 2:
     empilha(pil, tmp.ocup);
     break;
   case 3:
     empilha(pil, tmp.base);
     break;
   }*/
 //  break;
 //case MOVE:
   //Sistema(arg.val);
   //break;
 //case RECO:
   //Sistema(arg.val);
   //break;
 //case DEPO:
   //Sistema(arg.val);
   //break;
 //case ATAQ:
   //Sistema(arg.val);
   //break;
 }
 D(imprime(pil,5));
 D(puts("\n"));

 ip++;
  }
}
