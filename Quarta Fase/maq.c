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
  "ATR",
  "ENTRY",
  "LEAVE",
  "MOVE",
  "ATAQ",
  "DEPO",
  "RECO"
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
  m->pil.topo = 0;
  m->ib = 0;
  m->cristal = 0;
  m->vida = 3;
  m->index = 0;
  m->count = 0;
  return m;
}

void destroi_maquina(Maquina** m) {
  free(*m);
  *m = NULL;
}

int new_frame(Maquina *m, int n) {
  int ibc = m->ib;
  if (ibc < MAXFRM-1) {
	m->bp[++m->ib] = n+ibc;
	return m->ib;
  }
  return -1;
}

int del_frame(Maquina *m) {
  if (m->ib > 0) return --m->ib;
  return -1;
}

/* Alguns macros para facilitar a leitura do código */
#define ip (m->ip)
#define pil (&m->pil)
#define exec (&m->exec)
#define prg (m->prog)

void exec_maquina(Maquina *m, int n, FILE *display) {
  char *TYP[] = {
	"NUM",
	"ACAO",
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

	D(printf("%3d: %-5.5s %d\n", ip, CODES[opc], arg.val));

	switch (opc) {
	  OPERANDO tmp;
	  OPERANDO op1;
	  OPERANDO op2;
	  OPERANDO res;
	  
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

	  if (op1.t == NUM && op2.t == NUM) {
		res.t = NUM;
		res.val = op1.val+op2.val;
		empilha(pil, res);
	  }
	  else{
		Erro("Os tipos não são NUM.\n");
	  }
	  break;
	case SUB:
	  op1 = desempilha(pil);
	  op2 = desempilha(pil);

	  if (op1.t == NUM && op2.t == NUM) {
		res.t = NUM;
		res.val = op2.val-op1.val;
		empilha(pil, res);
	  }
	  else{
		Erro("Os tipos não são NUM.\n");
	  }

	  break;
	case MUL:
	  op1 = desempilha(pil);
	  op2 = desempilha(pil);

	  if (op1.t == NUM && op2.t == NUM) {
		res.t = NUM;
		res.val = op1.val*op2.val;
		empilha(pil, res);
	  }
	  else{
		Erro("Os tipos não são NUM.\n");
	  }
	  break;
	case DIV:
	  op1 = desempilha(pil);
	  op2 = desempilha(pil);

	  if (op1.t == NUM && op2.t == NUM) {
		res.t = NUM;
		res.val = op2.val/op1.val;
		empilha(pil, res);
	  }
	  else{
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
	  tmp.val = ip;
	  tmp.t = NUM;
	  empilha(exec, tmp);
	  ip = arg.val;
	  continue;
	case RET:
	  ip = desempilha(exec).val;
	  break;

	case EQ:
	  if (desempilha(pil).val == desempilha(pil).val){
		tmp.t = NUM;
		tmp.val = 1;
		empilha(pil, tmp);}
	  else{
		tmp.t = NUM;
		tmp.val = 0;
		empilha(pil, tmp);}
	  break;

	case GT:
	  if (desempilha(pil).val < desempilha(pil).val){
		tmp.t = NUM;
		tmp.val = 1;
		empilha(pil, tmp);}
	  else{
		tmp.t = NUM;
		tmp.val = 0;
		empilha(pil, tmp);}
	  break;

	case GE:
	  if (desempilha(pil).val <= desempilha(pil).val){
		tmp.t = NUM;
		tmp.val = 1;
		empilha(pil, tmp);}
	  else{
		tmp.t = NUM;
		tmp.val = 0;
		empilha(pil, tmp);}
	  break;

	case LT:
	  if (desempilha(pil).val > desempilha(pil).val){
		tmp.t = NUM;
		tmp.val = 1;
		empilha(pil, tmp);}
	  else{
		tmp.t = NUM;
		tmp.val = 0;
		empilha(pil, tmp);}
	  break;

	case LE:
	  if (desempilha(pil).val >= desempilha(pil).val){
		tmp.t = NUM;
		tmp.val = 1;
		empilha(pil, tmp);}
	  else{
		tmp.t = NUM;
		tmp.val = 0;
		empilha(pil, tmp);}
	  break;

	case NE:
	  if (desempilha(pil).val != desempilha(pil).val){
		tmp.t = NUM;
		tmp.val = 1;
		empilha(pil, tmp);}
	  else{
		tmp.t = NUM;
		tmp.val = 0;
		empilha(pil, tmp);}
	  break;

	case STO:
	  m->Mem[arg.val+m->bp[m->ib]] = desempilha(pil);
	  break;
	  
	case RCL:
	  empilha(pil,m->Mem[arg.val+m->bp[m->ib]]);
	  break;
	  
	case END:
	  pil->topo = 0;
	  return;
	  
	case PRN:	  
	  printf("%d\n", desempilha(pil).val);
	  break;
	  
	case ENTRY:
	  new_frame(m, arg.val);
	  break;
	  
	case LEAVE:
	  del_frame(m);
	  break;	

	case ATAQ:
	  Sistema(m, 'A', arg.val, display);
	  break;

	case DEPO:
	  Sistema(m, 'D', arg.val, display);
	  break;

	case RECO:
	  Sistema(m, 'R', arg.val, display);
	  break;

	case MOVE:
	  Sistema(m, 'M', arg.val, display);
	  break;

	case ATR://Arrumar ATR!!!
	  empilha(pil, (OPERANDO) {NUM, arg.val});
	  printf("ATR: ");

	}
	D(imprime(pil,5));
	D(puts("\n"));

	ip++;
  }
}
