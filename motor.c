#include <stdio.h>
#include "arena.h"
#include <string.h>

INSTR programa[] = {

    /*//SIMPLES SOMA
    {PUSH, 3},
    {PUSH, 6},
    {CALL, 5},
    {PRN,  0},
    {END,  0},
    {ADD,  0},
    {RET,  0} */

    /*FATORIAL ORIGINAL:
    {PUSH, 6},  // 0
    {CALL, 4},  // 1
    {PRN,  0},  // 2
    {END,  0},  // 3
    {ALC,  1},  // 4
    {DUP,  0},  // 5
    {STL,  1},  // 6 n
    {PUSH, 1},  // 7
    {EQ,   0},  // 8 n == 1 ?
    {JIF, 13},  // 9
    {PUSH, 1},  // 10
    {FRE,  1},  // 11
    {RET,  0},  // 12
    {RCE,  1},  // 13 n
    {PUSH, 1},  // 14
    {SUB,  0},  // 15 n-1
    {CALL, 4},  // 16 fat(n-1)
    {RCE,  1},  // 17 n
    {MUL,  0},  // 18 n * fat(n-1)
    {FRE,  1},  // 19
    {RET,  0}   // 20*/

    //FATORIAL SEGUNDA FASE:
    /*{PUSH, {NUM,  5}}, //0
    {CALL, {NUM,  4}}, //1
    {PRN,  {NUM,  0}}, //2
    {END,  {NUM,  0}}, //3
    {ALC,  {NUM,  1}}, //4
    {DUP,  {NUM,  0}}, //5
    {STL,  {NUM,  1}}, //6
    {PUSH, {NUM,  1}}, //7 
    {EQ,   {NUM,  0}}, //8
    {JIF,  {NUM, 13}}, //9
    {PUSH, {NUM,  1}}, //10
    {FRE,  {NUM,  1}}, //11
    {RET,  {NUM,  0}}, //12
    {RCE,  {NUM,  1}}, //13
    {PUSH, {NUM,  1}}, //14
    {SUB,  {NUM,  0}}, //15
    {CALL, {NUM,  4}}, //16
    {RCE,  {NUM,  1}}, //17
    {MUL,  {NUM,  0}}, //18
    {FRE,  {NUM,  1}}, //19
    {RET,  {NUM,  0}}  //20*/

    {PUSH, {TER, 1,{road, 2, 10, 6}}},
    {ATR, {NUM, 0}},
    {PRN, {NUM, 0}},
    {END,  {NUM,  0}}
};

int main(int ac, char **av) {
  //Arena *a = CriaArena();

  /*Celula c[4][8] = {
    {{road, 0, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 0, 0, 0}, {river, 3, 0, 0}, {mountain, 4, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}, 
    {{river, 4, 0, 0}, {river, 3, 0, 0}, {mountain, 2, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 1, 0, 0}, {river, 0, 0, 0}, {river, 1, 0, 0}},
    {{river, 2, 0, 0}, {river, 2, 0, 0}, {river, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {mountain, 2, 0, 0}, {mountain, 3, 0, 0}},
    {{river, 2, 0, 0}, {river, 1, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}
};
  memcpy(a->matriz, c, sizeof(a->matriz));
  a->exerc[a->exercTopo++] = InsereExercito(a, 0, 0);
  a->exerc[a->exercTopo++] = InsereExercito(a, 3, 7);
  a->exerc[a->exercTopo++] = InsereExercito(a, 2, 5);
  RemoveExercito(a, a->exerc[1], &a->exerc[1]);
  RemoveExercito(a, a->exerc[0], &a->exerc[0]);  
  Atualiza(2, a);*/
  
  Maquina *maq = cria_maquina(programa);
  exec_maquina(maq, 1000);
  //destroi_maquina(&maq);
  return 0;
}
