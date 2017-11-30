#include "pilha.h"

#define MAXMEM 100
#define MAXFRM 30

typedef struct {
    Pilha pil;
    Pilha exec;
    OPERANDO Mem[MAXMEM];
    INSTR *prog;
    int ip;
    int bp[MAXFRM];
    int ib;
    int position[2];
    int cristal;
    int vida; //se há ataque, faz sentido o rebo ter uma barra de vida
    int index; //index no vetor de endereços da arena
    int count;
} Maquina;

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina** maq);

void exec_maquina(Maquina *m, int n, FILE *display);

int new_frame(Maquina *m, int pos);

int del_frame(Maquina *m);