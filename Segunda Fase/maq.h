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
    int vida;//se há ataque, faz sentido o rebo ter uma barra de vida
    int index;//index no vetor de endereços da arena
} Maquina;

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina** maq);

void exec_maquina(Maquina *m, int n);
