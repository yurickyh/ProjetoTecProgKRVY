#include <stdio.h>
#include "arena.h"
#include <string.h>

INSTR programa[] = {
   
    //FATORIAL. Para numeros muito grandes é preciso aumentar o valor da variavel INSTRNUMBER ou aumentar o numero do argumento passado na funcao Atualiza():
    //Descomentar para o teste 6.
    /*{PUSH, {NUM,  6}}, //0
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
     
    //Descomentar para o teste 7
    /*{MOVE, {ACAO, 315}},
    {MOVE, {ACAO, 270}},
    {MOVE, {ACAO,  45}}*/

    //Descomentar para o teste 8
    /*{RECO, {ACAO, 315}},
    {MOVE, {ACAO, 270}},
    {RECO, {ACAO, 270}}*/

    //Descomentar para o teste 9
    /*{RECO, {ACAO, 315}},
    {MOVE, {ACAO, 270}},
    {DEPO, {ACAO,  45}}*/

    //Descomentar para o teste 10
    /*{MOVE, {ACAO, 315}},
    {MOVE, {ACAO, 270}},
    {ATAQ, {ACAO, 270}}*/

};

int main(int ac, char **av) {

  //Teste 1: teste da matriz da arena. Mudar os valores de i(linha) e j(coluna) pela coordenada da celula desejada:  
  /*int i = 2;
  int j = 7;
  char *TER[] = {
  "road",
  "mountain",
  "river"
  };
  CriaArena();
  Celula c[4][8] = {
    {{road, 0, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 0, 0, 0}, {river, 3, 0, 0}, {mountain, 4, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}, 
    {{river, 4, 0, 0}, {river, 3, 0, 0}, {mountain, 2, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 1, 0, 0}, {river, 0, 0, 0}, {river, 1, 0, 0}},
    {{river, 2, 0, 0}, {river, 2, 0, 0}, {river, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {mountain, 2, 0, 0}, {mountain, 3, 0, 0}},
    {{river, 2, 0, 0}, {river, 1, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}
  };
  memcpy(a->matriz, c, sizeof(a->matriz));
  printf("Tipo do terreno: %-8.8s  ", TER[a->matriz[i][j].terrain]);
  printf("Cristais: %2d   ", a->matriz[i][j].cristal);
  if(a->matriz[i][j].ocup == 0){
    printf("Célula desocupada.\n");
  }
  else{
    printf("Célula ocupada.\n");
  }*/


  //Teste 2: insercao e remocao de exercitos. São inseridos 3 exércitos, mudar o valor de i para escolher qual dos 3 exércitos remover:
  /*CriaArena();
  Celula c[4][8] = {
    {{road, 0, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 0, 0, 0}, {river, 3, 0, 0}, {mountain, 4, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}, 
    {{river, 4, 0, 0}, {river, 3, 0, 0}, {mountain, 2, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 1, 0, 0}, {river, 0, 0, 0}, {river, 1, 0, 0}},
    {{river, 2, 0, 0}, {river, 2, 0, 0}, {river, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {mountain, 2, 0, 0}, {mountain, 3, 0, 0}},
    {{river, 2, 0, 0}, {river, 1, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}
  };  
  memcpy(a->matriz, c, sizeof(a->matriz));
  a->exerc[a->exercTopo++] = InsereExercito(0, 0, programa);
  a->exerc[a->exercTopo++] = InsereExercito(2, 0, programa);
  a->exerc[a->exercTopo++] = InsereExercito(1, 5, programa);  
  printf("Cor do exército: %2d  Posição da base: [%1d][%1d]\n", a->exerc[0]->base->colour, a->robos[ROBOSONEXERC*(a->exerc[0]->base->colour-1)]->position[0], a->robos[ROBOSONEXERC*(a->exerc[0]->base->colour-1)]->position[1]);
  printf("Cor do exército: %2d  Posição da base: [%1d][%1d]\n", a->exerc[1]->base->colour, a->robos[ROBOSONEXERC*(a->exerc[1]->base->colour-1)]->position[0], a->robos[ROBOSONEXERC*(a->exerc[1]->base->colour-1)]->position[1]);
  printf("Cor do exército: %2d  Posição da base: [%1d][%1d]\n", a->exerc[2]->base->colour, a->robos[ROBOSONEXERC*(a->exerc[2]->base->colour-1)]->position[0], a->robos[ROBOSONEXERC*(a->exerc[2]->base->colour-1)]->position[1]);
  printf("Cor da base na coordenada[0][0]: %2d\n", a->matriz[0][0].baseColour);
  printf("Cor da base na coordenada[2][0]: %2d\n", a->matriz[2][0].baseColour);
  printf("Cor da base na coordenada[1][5]: %2d\n", a->matriz[1][5].baseColour);
  int i = 1;
  RemoveExercito(a->exerc[i-1], &a->exerc[i-1]);
  if(!a->exerc[i-1]){//O ponteiro apontando para NULL indica que o exército foi removido.
    printf("Exército %2d foi removido.\n", i);
  }
  printf("Cor da base na coordenada[0][0]: %2d\n", a->matriz[0][0].baseColour);
  printf("Cor da base na coordenada[2][0]: %2d\n", a->matriz[2][0].baseColour);
  printf("Cor da base na coordenada[1][5]: %2d\n", a->matriz[1][5].baseColour);
  //Se a cor da base for 0, quer dizer que não há uma base ali.*/


  //Teste 3: teste da declaracao do vencedor pelo escalonador se houver apenas um exercito restante na arena. São inseridos 2 exercitos, mudar o valor de i para escolher qual exercito remover:
  /*CriaArena();
  Celula c[4][8] = {
    {{road, 0, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 0, 0, 0}, {river, 3, 0, 0}, {mountain, 4, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}, 
    {{river, 4, 0, 0}, {river, 3, 0, 0}, {mountain, 2, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 1, 0, 0}, {river, 0, 0, 0}, {river, 1, 0, 0}},
    {{river, 2, 0, 0}, {river, 2, 0, 0}, {river, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {mountain, 2, 0, 0}, {mountain, 3, 0, 0}},
    {{river, 2, 0, 0}, {river, 1, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}
  };  
  memcpy(a->matriz, c, sizeof(a->matriz)); 
  a->exerc[a->exercTopo++] = InsereExercito(0, 0, programa);
  a->exerc[a->exercTopo++] = InsereExercito(2, 0, programa); 
  int i = 1;
  RemoveExercito(a->exerc[i-1], &a->exerc[i-1]);
  Atualiza(1);*/


  //Teste 4: teste de remocao do exercito pelo escalonador quando a sua base fica sem vida. São inseridos 2 exercitos, mudar o valor de i para escolher qual exercito remover:
  /*CriaArena();
  Celula c[4][8] = {
    {{road, 0, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 0, 0, 0}, {river, 3, 0, 0}, {mountain, 4, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}, 
    {{river, 4, 0, 0}, {river, 3, 0, 0}, {mountain, 2, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 1, 0, 0}, {river, 0, 0, 0}, {river, 1, 0, 0}},
    {{river, 2, 0, 0}, {river, 2, 0, 0}, {river, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {mountain, 2, 0, 0}, {mountain, 3, 0, 0}},
    {{river, 2, 0, 0}, {river, 1, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}
  };  
  memcpy(a->matriz, c, sizeof(a->matriz));
  a->exerc[a->exercTopo++] = InsereExercito(0, 0, programa);
  a->exerc[a->exercTopo++] = InsereExercito(2, 0, programa);
  int i = 2;
  a->exerc[i-1]->base->vida = 0;
  Atualiza(2);*/


  //Teste 5: teste de remocao do robo pelo escalonador quando este fica sem vida. MUdar o valor de i para escolher qual robo sera removido, lembrando
  /*CriaArena();
  Celula c[4][8] = {
    {{road, 0, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 0, 0, 0}, {river, 3, 0, 0}, {mountain, 4, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}, 
    {{river, 4, 0, 0}, {river, 3, 0, 0}, {mountain, 2, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 1, 0, 0}, {river, 0, 0, 0}, {river, 1, 0, 0}},
    {{river, 2, 0, 0}, {river, 2, 0, 0}, {river, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {mountain, 2, 0, 0}, {mountain, 3, 0, 0}},
    {{river, 2, 0, 0}, {river, 1, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}
  };  
  memcpy(a->matriz, c, sizeof(a->matriz));
  a->exerc[a->exercTopo++] = InsereExercito(0, 0, programa);
  a->exerc[a->exercTopo++] = InsereExercito(2, 0, programa);
  int i = 3;
  a->robos[i-1]->vida = 0;
  Atualiza(1);
  if(!a->robos[i-1]){//O ponteiro apontando para NULL indica que o robô foi removido.
    printf("Robô %3d foi destruído.\n", i);
  }*/


  //Teste 6: criacao de 2 exercitos e cada robo executa um fatorial. Descomentar o fatorial no vetor de instruções em cima e comentar as outras instruções:
  /*CriaArena();
  Celula c[4][8] = {
    {{road, 0, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 0, 0, 0}, {river, 3, 0, 0}, {mountain, 4, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}, 
    {{river, 4, 0, 0}, {river, 3, 0, 0}, {mountain, 2, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 1, 0, 0}, {river, 0, 0, 0}, {river, 1, 0, 0}},
    {{river, 2, 0, 0}, {river, 2, 0, 0}, {river, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {mountain, 2, 0, 0}, {mountain, 3, 0, 0}},
    {{river, 2, 0, 0}, {river, 1, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}
  };  
  memcpy(a->matriz, c, sizeof(a->matriz)); 
  a->exerc[a->exercTopo++] = InsereExercito(0, 0, programa);
  a->exerc[a->exercTopo++] = InsereExercito(2, 0, programa); 
  Atualiza(4);*/

  //Teste 7: chamadas do sistema = MOVE. Como todos os robos comecam no mesmo lugar e irao tentar se mover para os mesmos lugares, haverá conflitos:
  //Descomentar no vetor de instruções a parte referente ao teste 7 e comentar as outras instruções.
  /*CriaArena();  
  Celula c[4][8] = {
    {{road, 0, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 0, 0, 0}, {river, 3, 0, 0}, {mountain, 4, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}, 
    {{river, 4, 0, 0}, {river, 3, 0, 0}, {mountain, 2, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 1, 0, 0}, {river, 0, 0, 0}, {river, 1, 0, 0}},
    {{river, 2, 0, 0}, {river, 2, 0, 0}, {river, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {mountain, 2, 0, 0}, {mountain, 3, 0, 0}},
    {{river, 2, 0, 0}, {river, 1, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}
  };  
  memcpy(a->matriz, c, sizeof(a->matriz));
  a->exerc[a->exercTopo++] = InsereExercito(0, 0, programa);
  a->exerc[a->exercTopo++] = InsereExercito(2, 3, programa);
  Atualiza(1);*/


  //Teste 8: chamadas do sistema = RECOLHER. Descomentar no vetor de instruções a parte referente ao teste 8 e comentar as outras instruções.
  /*CriaArena();  
  Celula c[4][8] = {
    {{road, 0, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 0, 0, 0}, {river, 3, 0, 0}, {mountain, 4, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}, 
    {{river, 4, 0, 0}, {river, 3, 0, 0}, {mountain, 2, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 1, 0, 0}, {river, 0, 0, 0}, {river, 1, 0, 0}},
    {{river, 2, 0, 0}, {river, 2, 0, 0}, {river, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {mountain, 2, 0, 0}, {mountain, 3, 0, 0}},
    {{river, 2, 0, 0}, {river, 1, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}
  };  
  memcpy(a->matriz, c, sizeof(a->matriz));
  a->exerc[a->exercTopo++] = InsereExercito(0, 0, programa);
  a->exerc[a->exercTopo++] = InsereExercito(1, 4, programa);
  Atualiza(1);*/


  //Teste 9: chamadas do sistema = DEPOSITAR. Descomentar no vetor de instruções a parte referente ao teste 9 e comentar as outras instruções.
  /*CriaArena();  
  Celula c[4][8] = {
    {{road, 0, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 0, 0, 0}, {river, 3, 0, 0}, {mountain, 4, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}, 
    {{river, 4, 0, 0}, {river, 3, 0, 0}, {mountain, 2, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 1, 0, 0}, {river, 0, 0, 0}, {river, 1, 0, 0}},
    {{river, 2, 0, 0}, {river, 2, 0, 0}, {river, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {mountain, 2, 0, 0}, {mountain, 3, 0, 0}},
    {{river, 2, 0, 0}, {river, 1, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}
  };  
  memcpy(a->matriz, c, sizeof(a->matriz));
  a->exerc[a->exercTopo++] = InsereExercito(0, 0, programa);
  a->exerc[a->exercTopo++] = InsereExercito(1, 4, programa);
  Atualiza(1);*/


  //Teste 10: chamadas do sistema = ATACAR. Descomentar no vetor de instruções a parte referente ao teste 10 e comentar as outras instruções.
  /*CriaArena();  
  Celula c[4][8] = {
    {{road, 0, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 0, 0, 0}, {river, 3, 0, 0}, {mountain, 4, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}, 
    {{river, 4, 0, 0}, {river, 3, 0, 0}, {mountain, 2, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 1, 0, 0}, {river, 0, 0, 0}, {river, 1, 0, 0}},
    {{river, 2, 0, 0}, {river, 2, 0, 0}, {river, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {mountain, 2, 0, 0}, {mountain, 3, 0, 0}},
    {{river, 2, 0, 0}, {river, 1, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}
  };  
  memcpy(a->matriz, c, sizeof(a->matriz));
  a->exerc[a->exercTopo++] = InsereExercito(0, 0, programa);
  a->exerc[a->exercTopo++] = InsereExercito(1, 4, programa);
  Atualiza(1);*/  

  return 0;
}
