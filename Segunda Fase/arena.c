#include <stdio.h>
#include <stdlib.h>
#include "arena.h"
//teste2

static void Erro(char *msg) {
  fprintf(stderr,"%s\n", msg);
}

static void Fatal(char *msg, int cod) {
  Erro(msg);
  exit(cod);
}

Arena *CriaArena(){
	Arena *a = (Arena*)malloc(sizeof(Arena));
	if (!a) Fatal("Memória insuficiente",4);
	a->robosTopo = 0;
	a->exercTopo = 0;	
	return a;
}

void Atualiza(int rodadas, Arena *a){
	int i;
	for(i=0;i<rodadas;i++){
		int u;
		int count = 0;
		int aux;
		for(u=1;u<MAXEXERC+1;u++){//checar se há apenas uma base ativa, isto é, checar se alguem ganhou
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
						
			if(!a->robos[j]){
				//printf("IGUAL NULL %2d \n", j);						
			}	
			else{
				//printf("NAO NULL %2d  %1d  %1d\n", j, a->robos[j]->position[0], a->robos[j]->position[1]);
				exec_maquina(a->robos[j], 50);
			}
			int y;
			for(y=0;y<MAXEXERC;y++){
				if(a->exerc[y]!=NULL){
					if(a->exerc[y]->base->vida <= 0){
						RemoveExercito(a, a->exerc[y], &a->exerc[y]);						
					}
				}
			}//checar se alguma base foi destruida. Antes ou depois da rodada?			
		}
	}
}

INSTR p[] = {{PUSH, {NUM,  5}},	{PRN,  {NUM,  0}}, {END,  {NUM,  0}}};

Exercito *InsereExercito(Arena *a, int x, int y){//x e y = coordenadas da base desse novo exercito
	Exercito *e = (Exercito*)malloc(sizeof(Exercito));
	if(!e) Fatal("Memória insuficiente",4);
	int i;
	for(i=0;i<ROBOSONEXERC;i++){				
		Maquina *maq = cria_maquina(p);
		//Robos spawnam em cima da própria base
		maq->position[0] = x;
		maq->position[1] = y;
		a->robos[a->robosTopo++] = maq;
		e->robots[i] = maq;
	}	
	e->base = createBase(a);
	a->matriz[x][y].baseColour = e->base->colour;
	a->matriz[x][y].cristal = 0;
	a->matriz[x][y].ocup = 1;
	return e;
}

Base *createBase(Arena *a){//escolher e criar uma base que ainda não esta sendo usado
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

void RemoveExercito(Arena *a, Exercito *e, Exercito** ex){
	int i = e->base->colour;
	int j;
	//for(i=0;i<ROBOSONEXERC;i++){
	//	destroi_maquina(&e->robots[i]);
	//}
	for(j=(5*(i-1));j<(i*5);j++){
		destroi_maquina(&a->robos[j]);
	}
	a->baseCount[i] = 0;
	acertaMatriz(a);
	destroiBase(&e->base);
	free(*ex);
	*ex = NULL;
}

void acertaMatriz(Arena *a){
	int i;
	for(i=0;i<MAXMATRIZL;i++){
		int j;
		for(j=0;j<MAXMATRIZC;j++){
			if(a->matriz[i][j].baseColour != 0){
				if(a->baseCount[a->matriz[i][j].baseColour] == 0){
					a->matriz[i][j].baseColour = 0;
					a->matriz[i][j].ocup = 0;
					//Acertar a ocupação da célula. Desocupar a célula ao destruir a base e mudar as caracteristicas da celula ou apenas desocupar a celula?
					return;
				}
			}
		}
	}
}

//As chamadas do sistema mexem com a pilha de dados que são utilizadas apenas pelas maquinas. "eventuais operandos estão colocados na pilha de dados", a arena teria que acessar 
//esses operandos??? #N faz sentido
void Sistema(char code, int op){
	//op = direção -> angulo


}