#include <stdio.h>
#include <stdlib.h>
#include "arena.h"

Arena *a;

static void Erro(char *msg) {
    fprintf(stderr,"%s\n", msg);
}

static void Fatal(char *msg, int cod) {
    Erro(msg);
    exit(cod);
}

void CriaArena(){
    a = malloc(sizeof(Arena));
    if(!a) Fatal("Memória insuficiente", 4);
    a->robosTopo = 0;
    a->exercTopo = 0;
}

void Atualiza(int rodadas){
    int i;
    for(i=0;i<rodadas;i++){
        int u;
        int count = 0;
        int aux;
        for(u=1;u<MAXEXERC+1;u++){//Checar se há apenas uma base ativa, isto é, checar se alguem ganhou
            if(a->baseCount[u] != 0){
                count++;
                if(count>1){
                    break;
                }
                aux = u;
            }
        }
        if(count==1){
            printf("Fim de jogo! Exército %2d ganhou\n", aux);
            exit(0);
        }
        int j;
        for(j=0;j<MAXMAQ;j++){
            if(a->robos[j]!=NULL && a->robos[j]->vida <= 0){//Checar se o robo ficou sem vida
                destroi_maquina(&a->robos[j]);
            }
            if(a->robos[j]!=NULL){
                exec_maquina(a->robos[j], INSTRNUMBER);
            }
            int y;
            for(y=0;y<MAXEXERC;y++){
                if(a->exerc[y]!=NULL){
                    if(a->exerc[y]->base->vida <= 0){//Checar se alguma base ficou sem vida
                        RemoveExercito(a->exerc[y], &a->exerc[y]);
                    }
                }
            }
        }
    }
}

Exercito *InsereExercito(int x, int y, INSTR *p, FILE *display){ //x e y = coordenadas da base desse novo exercito
    Exercito *e = (Exercito*)malloc(sizeof(Exercito));
    if(!e) Fatal("Memória insuficiente",4);
    int i;
    e->base = createBase();
    a->matriz[x][y].baseColour = e->base->colour;
    a->matriz[x][y].cristal = 0;
    a->matriz[x][y].ocup = MAXMAQ+1;
    for(i=0;i<ROBOSONEXERC;i++){
        Maquina *maq = cria_maquina(p);
        //Robos spawnam em cima da propria base
        maq->position[0] = x;
        maq->position[1] = y;
        maq->index = a->robosTopo;
        a->robos[a->robosTopo++] = maq;
        if(a->matriz[x][y].baseColour == 1){
            /*
                CRIAR AS POSIÇÕES AQUI E COLOCAR COMO ARGUMENTO NO FPRINTF


            */
            fprintf(display, "rob GILEAD_A.png"); 
            fprintf(display, "%d %d %d %d %d", a->robosTopo, , , , ); 

        }
        if(a->matriz[x][y].baseColour == 2){
            fprintf(display, "rob GILEAD_A.png"); 
            fprintf(display, "%d %d %d %d %d", a->robosTopo, , , , ); 
        }
        e->robots[i] = maq;
    }    
    return e;
}

Base *createBase(){//Escolher e criar uma base que ainda nao esta sendo usada
    int i;
    for(i=1;i<MAXEXERC+1; i++){
        if(a->baseCount[i]==0){
            a->baseCount[i] = 1;
            Base *b = (Base*)malloc(sizeof(Base));
            if(!b) Fatal("Memória insuficiente", 4);
            b->vida = BASELIFE;
            b->colour = i;
            return b;
        }
    }
    return 0;
}

void destroiBase(Base** b){
    free(*b);
    *b = NULL;
}

void RemoveExercito(Exercito *e, Exercito** ex){
    int i = e->base->colour;
    int j;
    for(j=(5*(i-1));j<(i*5);j++){
        destroi_maquina(&a->robos[j]);
    }
    a->baseCount[i] = 0;
    acertaMatriz();
    destroiBase(&e->base);
    free(*ex);
    *ex = NULL;
}

void acertaMatriz(){
    int i;
    for(i=0;i<MAXMATRIZL;i++){
        int j;
        for(j=0;j<MAXMATRIZC;j++){
            if(a->matriz[i][j].baseColour != 0){
                if(a->baseCount[a->matriz[i][j].baseColour] == 0){
                    a->matriz[i][j].baseColour = 0;
                    a->matriz[i][j].ocup = 0;
                    return;
                }
            }
        }
    }
}

void Sistema(Maquina *m, char code, int op){
    //op = angulo da direcao
    switch (code) {
        Coord tmp;
        Coord tmp2;
        case 'M':
            tmp = getNeighbour(m->position[0], m->position[1], op);
            if(tmp.x == MAXMATRIZL || tmp.y == MAXMATRIZC){
                printf("Tentativa de movimento para célula inválida.\n");
                return;
            }
            if(a->matriz[tmp.x][tmp.y].ocup != 0){
                printf("Tentativa de movimento para célula ocupada.\n");
                return;
            }
            tmp2.x = m->position[0];
            tmp2.y = m->position[1];
            m->position[0] = tmp.x;
            m->position[1] = tmp.y;
            if(a->matriz[tmp2.x][tmp2.y].ocup != MAXMAQ+1){
                a->matriz[tmp2.x][tmp2.y].ocup = 0;
            }
            a->matriz[tmp.x][tmp.y].ocup = m->index+1;
            printf("Andou para [%1d][%1d].\n", tmp.x, tmp.y);
            break;
        case 'D':
            tmp = getNeighbour(m->position[0], m->position[1], op);
            if(tmp.x == MAXMATRIZL || tmp.y == MAXMATRIZC){
                printf("Tentativa de depósito em célula inválida.\n");
                return;
            }
            if(a->matriz[tmp.x][tmp.y].ocup != MAXMAQ+1 && a->matriz[tmp.x][tmp.y].ocup != 0){
                printf("Tentativa de depósito em célula ocupada por outro robô.\n");
                return;
            }
            if(a->matriz[tmp.x][tmp.y].ocup == MAXMAQ+1){
                a->exerc[a->baseCount[a->matriz[tmp.x][tmp.y].baseColour]-1]->base->vida -= m->cristal;
                m->cristal = 0;  
                printf("Depositou na base %2d.\n", a->matriz[tmp.x][tmp.y].baseColour);
                return;     
            }
            if(a->matriz[tmp.x][tmp.y].ocup == 0){
                a->matriz[tmp.x][tmp.y].cristal += m->cristal;
                m->cristal = 0;
                printf("Depositou na célula [%1d][%1d].\n", tmp.x, tmp.y);
                return;
            }
            break;
        case 'R':
            tmp = getNeighbour(m->position[0], m->position[1], op);
            if(tmp.x == MAXMATRIZL || tmp.y == MAXMATRIZC){
                printf("Tentativa de recolher cristal em célula inválida.\n");
                return;
            }
            if(a->matriz[tmp.x][tmp.y].ocup != 0){
                printf("Tentativa de recolher cristal em célula ocupada.\n");
                return;
            }
            if(a->matriz[tmp.x][tmp.y].cristal == 0){
                printf("Não há cristais para recolher nesta célula.\n");
                return;
            }
            m->cristal = m->cristal + a->matriz[tmp.x][tmp.y].cristal;
            a->matriz[tmp.x][tmp.y].cristal = 0;
            printf("Recolheu da célula [%1d][%1d].\n", tmp.x, tmp.y);
            break;
        case 'A':
            tmp = getNeighbour(m->position[0], m->position[1], op);
            if(a->matriz[tmp.x][tmp.y].ocup == 0){
                printf("Tentativa de ataque em célula desocupada.\n");
                return;
            }
            if(a->matriz[tmp.x][tmp.y].ocup == MAXMAQ+1){
                printf("Tentativa de ataque em uma base. Não é possível atacar uma base diretamente.\n");
                return;
            }
            a->robos[a->matriz[tmp.x][tmp.y].ocup-1]->vida = a->robos[a->matriz[tmp.x][tmp.y].ocup-1]->vida - 1;
            printf("Efetuou o ataque na célula [%1d][%1d] atingindo o robô %3d.\n", tmp.x, tmp.y, a->matriz[tmp.x][tmp.y].ocup-1);
            break;
    }
}

Coord getNeighbour(int l, int c, int angle){
    Coord cord;
    switch (angle){
        case 0:
            if(c+1 == MAXMATRIZC) {
                cord.x = MAXMATRIZL;
                cord.y = MAXMATRIZC;
            } else {
                cord.x = l;
                cord.y = c+1;                
            }
            break;
        case 45:
            if(l==0 || (l%2!=0 && c+1==MAXMATRIZC)) {
                cord.x = MAXMATRIZL;
                cord.y = MAXMATRIZC;
            } else {
                if(l%2==0)
                {
                    cord.x = l-1;
                    cord.y = c;
                }
                else
                {
                    cord.x = l-1;
                    cord.y = c+1;
                }                
            }
            break;
        case 135:
            if(l == 0 || (c==0 && l%2==0)){
                cord.x = MAXMATRIZL;
                cord.y = MAXMATRIZC;
            } else {
                if(l%2==0) {
                    cord.x = l-1;
                    cord.y = c-1;
                } else{
                    cord.x = l-1;
                    cord.y = c;
                }
            }
            break;
        case 180:
            if(c == 0) {
                cord.x = MAXMATRIZL;
                cord.y = MAXMATRIZC;
            } else {
                cord.x = l;
                cord.y = c-1;
            }
            break;
        case 225:
            if(l+1==MAXMATRIZL || (l%2==0 && c==0)) {
                cord.x = MAXMATRIZL;
                cord.y = MAXMATRIZC;
            } else {
                if(l%2==0)
                {
                    cord.x = l+1;
                    cord.y = c-1;
                }
                else
                {
                    cord.x = l+1;
                    cord.y = c;
                }
            }
            break;
        case 315:
            if(l+1 == MAXMATRIZL || (c+1==MAXMATRIZC && l%2!=0)) {
                cord.x = MAXMATRIZL;
                cord.y = MAXMATRIZC;
            } else {
                if(c%2!=0){
                    cord.x = l+1;
                    cord.y = c+1;
                }
                else{
                    cord.x = l+1;
                    cord.y = c;
                }
            }
            break;
    }
    return cord;
}

Coord avaliableNeighbour(int l, int c)
{
    Coord co[] = {getNeighbour(l, c, 0), getNeighbour(l, c, 45), getNeighbour(l, c, 135), getNeighbour(l, c, 180), getNeighbour(l, c, 225), getNeighbour(l, c, 315)};
    int i;
    for(i=0; i<6; i++)
    {
        if(co[i].x!=MAXMATRIZL && co[i].y!=MASMATRIZC)
        {
            if(a->matriz[co[i].x][co[i].y].ocup==0)
            {
                return co[i];            
            }        
        }
    }
    co[0].x = MAXMATRIZL;
    co[0].y = MAXMATRIZC;
    return co[0];
}
