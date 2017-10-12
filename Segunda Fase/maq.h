#include "pilha.h"

#define MAXMEM 100

typedef struct {
  Pilha pil;
  Pilha exec;
  OPERANDO Mem[MAXMEM];
  INSTR *prog;
  int ip;
  int rbp;
  int position[2];
  int cristal;
} Maquina;

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(/*Maquina *m, */Maquina** maq);

void exec_maquina(Maquina *m, int n);
