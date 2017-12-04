#include <stdio.h>
#include <string.h>
#include "compila.tab.h"
#include "maq.h"
INSTR p1[2000];

int compilador(FILE *, INSTR *);

int main(int ac, char **argv/*[]*/) {  
  int i = 1;
  /*while(i < ac){
    FILE *p;
    int res;    
    p = fopen(argv[i++],"r");
    res = compilador(p, p1[i-2]);
    if (res) return 1;  
    Maquina *maq = cria_maquina(p1[i-2]);
    exec_maquina(maq, 1000);
    destroi_maquina(maq);
    pclose(p);
  }*/
   /* FILE *p, *p2;
    int res, res2;    
    p = fopen(argv[1],"r");
    p2 = fopen(argv[2],"r");
    res = compilador(p, p1);
    res2 = compilador(p2, p1);
    if (res || res2) return 1;  
    Maquina *maq = cria_maquina(p1);
    Maquina *maq2 = cria_maquina(p1);
    exec_maquina(maq, 1000);
    exec_maquina(maq2, 1000);
    destroi_maquina(maq);
    destroi_maquina(maq2);
    pclose(p);
    pclose(p2);*/
  
  //Teste Funcionando
  FILE* files[4];
  int res;
  files[0] = fopen(argv[1], "r");
  res = compilador(files[0], p1);
  if(res) return 1;
  Maquina *maq = cria_maquina(p1);
  exec_maquina(maq, 1000);
  fclose(files[0]);
  memset(p1, 0, 2000*(sizeof p1[0]));
  files[1] = fopen(argv[2], "r");
  res = compilador(files[1], p1);
  if(res) return 1;
  Maquina *maq2 = cria_maquina(p1);
  exec_maquina(maq2, 1000);
  fclose(files[1]);
  memset(p1, 0, 2000*(sizeof p1[0]));
  destroi_maquina(maq);
  destroi_maquina(maq2);
  return 0;
}
