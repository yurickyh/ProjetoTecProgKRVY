#include "maq.h"

#define MAXMAQ 4
#define MAXEXERC 2
#define ROBOSONEXERC 2
#define MAXMATRIZL 4
#define MAXMATRIZC 8
#define BASELIFE 20
#define INSTRNUMBER 50
//Ao mudar o valor de MAXMAQ ou MAXEXERC ou ROBOSONEXERC, e preciso acertar os valores dos outros de modo que MAXMAQ=MAXEXERC*ROBOSONEXERC

typedef enum{
    road,
    mountain,
    river
    //Adicionar mais depois
} Terreno;

//Colour = 0 -> não é base
//Colour = outro numero -> é base
typedef struct{
    int vida;
    int colour; //Identificação da base 
} Base;

typedef struct{
    Terreno terrain;
    int cristal;
    int ocup; //0 = desocupada; 1 ate MAXMAQ = indice do robo no vetor de endereços de maquina da arena; MAXMAQ+1 = base;
    int baseColour;
} Celula;

typedef struct{
    Maquina* robots[ROBOSONEXERC];
    Base* base;
} Exercito;

typedef struct{
    Maquina* robos[MAXMAQ+1];
    int robosTopo;
    Celula matriz[MAXMATRIZL][MAXMATRIZC];
    Exercito* exerc[MAXEXERC];
    int exercTopo;
    int baseCount[MAXEXERC+1];
} Arena;

extern Arena *a;

typedef struct{
    int x;
    int y;
} Coord;

void CriaArena();
void Atualiza();
Exercito *InsereExercito(int x, int y, INSTR *p, FILE *display);
Base *createBase();
void destroiBase(Base** b);
void RemoveExercito(Exercito *e, Exercito** ex);
void acertaMatriz();
void Sistema(Maquina *m, char code, int op);
Coord getNeighbour(int l, int c, int angle);
Coord avaliableNeighbour(int l, int c);
