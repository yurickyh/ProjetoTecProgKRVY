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
    a->robosTopo = 1;
    a->exercTopo = 0;
}

void Atualiza(int rodadas, FILE *display){
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
            if(a->robos[j+1]!=NULL && a->robos[j+1]->vida <= 0){//Checar se o robo ficou sem vida
                //remover os robos na interface               
                fprintf(display, "clean %d %d\n", a->robos[j+1]->position[0], a->robos[j+1]->position[1]);
                fflush(display);
                destroi_maquina(&a->robos[j+1]);
            }
            if(a->robos[j+1]!=NULL){
                if(a->robos[j+1]->count!=0){//Se estiver com algum valor no contador, o robo não pode jogar essa rodada.
                    printf("Robo %2d perde essa rodada.\n", a->robos[j+1]->index-1);
                    a->robos[j+1]->count--;
                }
                else{
                    exec_maquina(a->robos[j+1], INSTRNUMBER, display);
                }
            }
            int y;
            for(y=0;y<MAXEXERC;y++){
                if(a->exerc[y]!=NULL){
                    if(a->exerc[y]->base->vida <= 0){//Checar se alguma base ficou sem vida
                        RemoveExercito(a->exerc[y], &a->exerc[y], display);
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
    e->base->position[0] = x;
    e->base->position[1] = y;
    if(a->matriz[x][y].baseColour == 1){
        fprintf(display, "base base1r.png %d %d %d\n", a->matriz[x][y].baseColour, x, y); //criar a base vermelha        
    }
    if(a->matriz[x][y].baseColour == 2){
        fprintf(display, "base base2r.png %d %d %d\n", a->matriz[x][y].baseColour, x, y); //criar a base azul
    }
    fflush(display);  
    for(i=0;i<ROBOSONEXERC;i++){
        Maquina *maq = cria_maquina(p);
        Coord aux = avaliableNeighbour(x, y);
        if(aux.x!=MAXMATRIZL && aux.y!=MAXMATRIZC){
            maq->position[0] = aux.x;
            maq->position[1] = aux.y;
            maq->index = a->robosTopo;
            a->robos[a->robosTopo++] = maq;
            a->matriz[aux.x][aux.y].ocup = maq->index; 
        }
        if(a->matriz[x][y].baseColour == 1){ 
            fprintf(display, "rob robo1.png %d %d %d\n", maq->index-1, maq->position[0], maq->position[1]);            
            fflush(display); 
        }
        if(a->matriz[x][y].baseColour == 2){
            fprintf(display, "rob robo2.png %d %d %d\n", maq->index-1, maq->position[0], maq->position[1]);
            fflush(display); 
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

void RemoveExercito(Exercito *e, Exercito** ex, FILE *display){
    int i = e->base->colour;      
    int j;
    a->matriz[e->base->position[0]][e->base->position[1]].ocup = 0;
    for(j=(ROBOSONEXERC*(i-1));j<(i*ROBOSONEXERC);j++){
        //parte para remover os robos do mapa
        fprintf(display, "clean %d %d\n", a->robos[j+1]->position[0], a->robos[j+1]->position[1]);
        fflush(display);
        destroi_maquina(&a->robos[j+1]);
    }
    a->baseCount[i] = 0;
    acertaMatriz();
    fprintf(display, "clean %d %d\n", e->base->position[0], e->base->position[1]);
    fflush(display);
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

char *TER[] = {
        "road",
        "mountain",
        "river"
    };

void Sistema(Maquina *m, char code, int op, FILE *display){
    //Agora recebendo display para escrever a cada chamada de sistema
    //op = angulo da direcao
    switch (code) {
        Coord tmp;
        Coord tmp2;
        case 'M':
            tmp = getNeighbour(m->position[0], m->position[1], op);
            printf("MAQ index: %d\n", m->index);
            if(tmp.x == MAXMATRIZL || tmp.y == MAXMATRIZC){
                printf("Tentativa de movimento para célula inválida. %d\n", m->index);
                break;
            }
            if(a->matriz[tmp.x][tmp.y].ocup != 0){
                printf("Tentativa de movimento para célula ocupada. %d\n", m->index);
                break;
            }
            fprintf(display, "%d %d %d %d %d %d\n", m->index-1, m->position[0], m->position[1], tmp.x, tmp.y, m->vida);
            fflush(display);
            fprintf(display, "cristal %d %d %d\n", m->position[0], m->position[1], a->matriz[m->position[0]][m->position[1]].cristal);
            fflush(display);
            printf("Andou de [%1d][%1d] para [%1d][%1d].\n", m->position[0], m->position[1], tmp.x, tmp.y);
            tmp2.x = m->position[0];
            tmp2.y = m->position[1];
            m->position[0] = tmp.x;
            m->position[1] = tmp.y;
            //Checar para qual tipo de terreno o robo está se movendo e alterar o valor do seu contador de acordo.
            char currentTerr[10];            
            char mount[10];
            char riv[10];
            strcpy(currentTerr, TER[a->matriz[tmp.x][tmp.y].terrain]);
            strcpy(riv, "river");
            strcpy(mount, "mountain");
            //Se for um tipo montanha, o robo perderá 1 rodada.
            if(strcmp(currentTerr, mount) == 0){
                m->count = 1;
            }
            //Se for um tipo rio, o robo perderá 2 rodadas.
            if(strcmp(currentTerr, riv) == 0){
                m->count = 2;
            }            
            if(a->matriz[tmp2.x][tmp2.y].ocup != MAXMAQ+1){
                a->matriz[tmp2.x][tmp2.y].ocup = 0;
            }
            a->matriz[tmp.x][tmp.y].ocup = m->index;            
            break;
        case 'D':
            tmp = getNeighbour(m->position[0], m->position[1], op);
            if(tmp.x == MAXMATRIZL || tmp.y == MAXMATRIZC){
                printf("Tentativa de deposito em celula invalida.\n");
                break;
            }
            if(a->matriz[tmp.x][tmp.y].ocup != MAXMAQ+1 && a->matriz[tmp.x][tmp.y].ocup != 0){
                printf("Tentativa de deposito em celula ocupada por outro robo.\n");
                break;
            }
            if(m->cristal == 0){
                printf("O robo %d nao tem cristais\n", m->index);
                break;
            }
            if(a->matriz[tmp.x][tmp.y].ocup == MAXMAQ+1){
                a->exerc[a->baseCount[a->matriz[tmp.x][tmp.y].baseColour]-1]->base->vida -= m->cristal;
                m->cristal = 0;  
                printf("Depositou na base %2d.\n", a->matriz[tmp.x][tmp.y].baseColour);
                break;     
            }
            if(a->matriz[tmp.x][tmp.y].ocup == 0){              
                a->matriz[tmp.x][tmp.y].cristal += m->cristal;                
                printf("Depositou na celula [%1d][%1d].\n", tmp.x, tmp.y);
                fprintf(display, "cristal %d %d %d\n", tmp.x, tmp.y, a->matriz[tmp.x][tmp.y].cristal);
                fflush(display);
                break;
            }
            break;
        case 'R':
            tmp = getNeighbour(m->position[0], m->position[1], op);
            if(tmp.x == MAXMATRIZL || tmp.y == MAXMATRIZC){
                printf("Tentativa de recolher cristal em célula inválida.\n");
                break;
            }
            if(a->matriz[tmp.x][tmp.y].ocup != 0){
                printf("Tentativa de recolher cristal em célula ocupada.\n");
                break;
            }
            if(a->matriz[tmp.x][tmp.y].cristal == 0){
                printf("Não há cristais para recolher nesta célula.\n");
                break;
            }
            m->cristal = m->cristal + a->matriz[tmp.x][tmp.y].cristal;
            a->matriz[tmp.x][tmp.y].cristal = 0;
            fprintf(display, "clean %d %d\n", tmp.x, tmp.y);
            fflush(display);
            printf("Recolheu da célula [%1d][%1d].\n", tmp.x, tmp.y);
            break;
        case 'A':
            tmp = getNeighbour(m->position[0], m->position[1], op);
            if(a->matriz[tmp.x][tmp.y].ocup == 0){
                printf("Tentativa de ataque em célula desocupada.\n");
                break;
            }
            if(a->matriz[tmp.x][tmp.y].ocup == MAXMAQ+1){
                printf("Tentativa de ataque em uma base. Não é possível atacar uma base diretamente.\n");
                break;
            }
            a->robos[a->matriz[tmp.x][tmp.y].ocup]->vida = a->robos[a->matriz[tmp.x][tmp.y].ocup]->vida - 1;
            fprintf(display, "%d %d %d %d %d %d\n", m->index-1, m->position[0], m->position[1], m->position[0], m->position[1], m->vida);
            fflush(display);
            printf("Efetuou o ataque na célula [%1d][%1d] atingindo o robô %3d.\n", tmp.x, tmp.y, a->matriz[tmp.x][tmp.y].ocup);
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
        if(co[i].x!=MAXMATRIZL && co[i].y!=MAXMATRIZC)
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
