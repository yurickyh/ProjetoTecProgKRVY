#include <stdio.h>
#include "arena.h"
#include <string.h>
#define linhas 4
#define colunas 8

FILE *display;
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

    //Descomentar para o teste 11
    /*{PUSH, {CEL, 1,{river, 2, 10, 6}}},
    {ATR, {NUM, 0}},
    {PRN, {NUM, 0}},
    {END,  {NUM,  0}}*/
};

int main(int ac, char **av) {

    int lin = 0, col = 0, color = 0;
    char *TER[] = {
        "road",
        "mountain",
        "river"
    };
    char *Color[] = {
        "169 169 169",//cinza = river
        "139 69 19",//marrom = mountain
        "30 144 255"//azul = river
    };
    CriaArena();
    Celula c[linhas][colunas] = {
        {{road, 0, 0, 1}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 0, 0, 0}, {river, 3, 0, 0}, {mountain, 4, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}, 
        {{river, 4, 0, 0}, {river, 3, 0, 0}, {mountain, 2, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 1, 0, 0}, {river, 0, 0, 0}, {river, 1, 0, 0}},
        {{river, 2, 0, 0}, {river, 2, 0, 0}, {river, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {mountain, 2, 0, 0}, {mountain, 3, 0, 0}},
        {{river, 2, 0, 0}, {river, 1, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 2}}
    };
    memcpy(a->matriz, c, sizeof(a->matriz));
    display = popen("./apres", "w"); //criacao do pipe para apres
    if (display == NULL) {//verificar se o display eh nulo
        fprintf(stderr,"Não encontrei o programa de exibição\n");
        return 1;
    }  
    for (lin = 0; lin < linhas; lin++){
        for (col = 0; col < colunas; col++){
            if(a->matriz[lin][col].baseColour == 1){
                printf("\nEntrou aqui");
                fprintf(display, "base base1.png %d %d %d\n", a->matriz[lin][col].baseColour, lin, col);//criar a base vermelha            
            }
            else if(a->matriz[lin][col].baseColour == 2){
                fprintf(display, "base base2.png %d %d %d\n", a->matriz[lin][col].baseColour, lin, col);//criar a base azul
            }
            else {
                fprintf(display, "cel %d %d %s\n", lin, col, Color[a->matriz[lin][col].terrain]);    
            }     
            fflush(display);   
        }
    }
    pclose(display);

    return 0;
}
