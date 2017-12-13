#include "compila.tab.h"
#include "maq.h"

#define MAXMAQ 4
#define MAXEXERC 2
#define ROBOSONEXERC 2
#define MAXMATRIZL 8
#define MAXMATRIZC 8
#define BASELIFE 20
#define INSTRNUMBER 80 // Numero de instrucoes que cada robo tem por rodada
//Ao mudar o valor de MAXMAQ ou MAXEXERC ou ROBOSONEXERC, e preciso acertar os valores dos outros de modo que MAXMAQ=MAXEXERC*ROBOSONEXERC

typedef enum{
    road,
    mountain,
    river
} Terreno;

//Colour = 0 -> não é base.
//Colour = outro número -> é base.
typedef struct{
    int vida;
    int colour; //Identificação da base.
    int position[2];
} Base;

typedef struct{
    Terreno terrain;
    int cristal;
    int ocup; //0 = desocupada; 1 ate MAXMAQ = índice do robo no vetor de endereços de máquinas da arena; MAXMAQ+1 = base;
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
extern INSTR programa[MAXMAQ][2000];

typedef struct{
    int x;
    int y;
} Coord;

void CriaArena();
void Atualiza(int rodadas, FILE *display);
Exercito *InsereExercito(int x, int y, /*INSTR *p, */FILE *display);
Base *createBase();
void destroiBase(Base** b);
void RemoveExercito(Exercito *e, Exercito** ex, FILE *display);
void acertaMatriz();
void Sistema(Maquina *m, char code, int op, FILE *display);
Coord getNeighbour(int l, int c, int angle);
Coord avaliableNeighbour(int l, int c);
int NeighbourLook(int x, int y, int angle, int t);
void FimRodadas();
