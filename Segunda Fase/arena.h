#include "maq.h"

#define MAXMAQ 100
#define MAXEXERC 20
#define ROBOSONEXERC 5
#define MAXMATRIZL 4
#define MAXMATRIZC 8
#define BASELIFE 20

typedef enum{
	road,
	mountain,
	river
	//adicionar mais depois
} Terreno;

//Colour = 0 -> não é base
//Colour = outro numero -> é base
typedef struct{
	int vida;
	int colour; //identificação da base	
} Base;

typedef struct{
	Terreno terrain;
	int cristal;
	int ocup;
	int baseColour;
	//Base base;
} Celula;

typedef struct{
	Maquina* robots[ROBOSONEXERC];
	Base* base;
} Exercito;

typedef struct{
	Maquina* robos[MAXMAQ];
	int robosTopo;
	Celula matriz[MAXMATRIZL][MAXMATRIZC];
	Exercito* exerc[MAXEXERC];
	int exercTopo;	
	int baseCount[MAXEXERC+1];
	//int roboCount[MAXMAQ];
} Arena;

Arena *CriaArena();
void Atualiza();
Exercito *InsereExercito(Arena *a, int x, int y);
Base *createBase(Arena *a);
void destroiBase(Base** b);
void RemoveExercito(Arena *a, Exercito *e, Exercito** ex);
void acertaMatriz(Arena *a);
void Sistema(char code, int op);