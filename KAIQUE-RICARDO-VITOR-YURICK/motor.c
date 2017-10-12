#include <stdio.h>
#include "maq.h"

INSTR programa[] = {

    /*//SIMPLES SOMA
    {PUSH, 3},
    {PUSH, 6},
    {CALL, 5},
    {PRN,  0},
    {END,  0},
    {ADD,  0},
    {RET,  0} */

    //FATORIAL:     
    {PUSH, 6},  // 0
    {CALL, 6},  // 1
    {RCE,  1},  // 2
    {MUL,  0},  // 3
    {PRN,  0},  // 4 
    {END,  0},  // 5    
    {ALC,  1},  // 6
    {DUP,  0},  // 7
    {STL,  1},  // 8 n
    {PUSH, 1},  // 9
    {EQ,   0},  // 10 n == 1 ?
    {JIF, 15},  // 11
    {PUSH, 1},  // 12
    {FRE,  1},  // 13
    {RET,  0},  // 14
    {RCE,  1},  // 15 n
    {PUSH, 1},  // 16
    {SUB,  0},  // 17 n-1
    {CALL, 6},  // 18 fat(n-1)
    {RCE,  1},  // 19 n
    {MUL,  0},  // 20 n * fat(n-1)
    {FRE,  1},  // 21
    {RET,  0}   // 22
};

int main(int ac, char **av) {
  Maquina *maq = cria_maquina(programa);
  exec_maquina(maq, 1000);
  destroi_maquina(maq);
  return 0;
}
