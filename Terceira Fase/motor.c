#include <stdio.h>
#include "arena.h"
#include <string.h>

FILE *display;
INSTR programa[] = {
    /*FATORIAL:
    {PUSH, {NUM,  6}}, //0
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
};

int main(int ac, char **av) {

    CriaArena();
    display = popen("java Map > map.txt", "r");
    pclose(display);
    char s[1024];
    char * pch;
    int i=0, j=0, count=0;
    display = fopen("map.txt", "r");
    fgets(s, 1024, display);
    pch = strtok(s, " ");
    while(pch!=NULL)
    {
        if(count==0)
        {
            a->matriz[i][j].terrain = pch;]
            count++;
        }
        else if(count==1)
        {
            a->matriz[i][j].cristal = (int)pch;
            count++;        
        }
        else if(count==2)
        {
            a->matriz[i][j].ocup = (int)pch;
            count++;        
        }
        else if(count==3)
        {
            a->matriz[i][j].baseCoulour = (int)pch;
            count = 0;
            if(j+1==MAXMATRIZC)
            {
                i++;
                j=0;
            }
            else
            {
                j++;            
            }        
        }
        if(i==MAXMATRIZL)
        {
            break;        
        }
        pch = strtok(NULL, " ");
    }
    fclose(display);
    printf("Teste %2d\n", a->matriz[2][2].cristal);
    
    /*int lin = 0, col = 0, color = 0;
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
    Celula c[MAXMATRIZL][MAXMATRIZC] = {
        {{road, 0, 0, 1}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 0, 0, 0}, {river, 3, 0, 0}, {mountain, 4, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}}, 
        {{river, 4, 0, 0}, {river, 3, 0, 0}, {mountain, 2, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 1, 0, 0}, {river, 0, 0, 0}, {river, 1, 0, 0}},
        {{river, 2, 0, 0}, {river, 2, 0, 0}, {river, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {mountain, 2, 0, 0}, {mountain, 3, 0, 0}},
        {{river, 2, 0, 0}, {river, 1, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 0}, {road, 2, 0, 2}}
    };
    memcpy(a->matriz, c, sizeof(a->matriz));
    display = popen("./apres", "w"); //criacao do pipe para apres
    if (display == NULL) { //verificar se o display eh nulo
        fprintf(stderr,"Não encontrei o programa de exibição\n");
        return 1;
    }  
    for (lin = 0; lin < MAXMATRIZL; lin++){
        for (col = 0; col < MAXMATRIZC; col++){
            if(a->matriz[lin][col].baseColour == 1){
                printf("\nEntrou aqui");
                fprintf(display, "base base1r.png %d %d %d\n", a->matriz[lin][col].baseColour, lin, col); //criar a base vermelha            
            }
            else if(a->matriz[lin][col].baseColour == 2){
                fprintf(display, "base base2r.png %d %d %d\n", a->matriz[lin][col].baseColour, lin, col); //criar a base azul
            }
            else {
                fprintf(display, "cel %d %d %s %s\n", lin, col, Color[a->matriz[lin][col].terrain]);
                fprintf(display, "cristal %d %d %d\n", lin, col, a->matriz[lin][col].cristal);
            }     
            fflush(display);   
        }
    }
    pclose(display);*/

    return 0;
}
