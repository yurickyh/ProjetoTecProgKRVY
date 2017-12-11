#include <stdio.h>
#include "arena.h"
#include <string.h>
//#include "compila.tab.h"

FILE *display;
//INSTR programa[2000];
/*INSTR programa[] = {   
	{MOVE, {ACAO, 0}},
	{MOVE, {ACAO, 135}},
	{ATAQ, {ACAO, 0}},
	{RECO, {ACAO, 225}},
	{DEPO, {ACAO, 315}},
	{ATAQ, {ACAO, 180}}

};*/

int main(int ac, char **argv) {
    //Descomentar os testes no vetor programa, um por execução.
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
    Celula c[MAXMATRIZL][MAXMATRIZC] = {
        {{road, 0, 1, 0}, {road, 2, 0, 0}, {mountain, 0, 0, 0}, {road, 0, 0, 0}, {road, 0, 0, 0}, {river, 1, 0, 0}, {mountain, 2, 0, 0}, {road, 1, 0, 0}},
        {{mountain, 0, 0, 0}, {mountain, 1, 0, 0}, {road, 3, 0, 0}, {mountain, 1, 0, 0}, {river, 0, 0, 0}, {mountain, 1, 0, 0}, {river, 1, 0, 0}, {mountain, 0, 0, 0}},
        {{road, 0, 0, 0}, {mountain, 2, 0, 0}, {river, 1, 0, 0}, {river, 0, 0, 0}, {mountain, 3, 0, 0}, {road, 2, 0, 0}, {river, 0, 0, 0}, {river, 2, 0, 0}},
        {{road, 2, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {mountain, 2, 0, 0}, {mountain, 1, 0, 0}, {mountain, 1, 0, 0}, {mountain, 0, 0, 0}, {river, 2, 0, 0}},
        {{road, 2, 0, 0}, {river, 1, 0, 0}, {road, 2, 0, 0}, {road, 1, 0, 0}, {mountain, 3, 0, 0}, {road, 0, 0, 0}, {road, 2, 0, 0}, {river, 2, 0, 0}},
        {{road, 1, 0, 0}, {mountain, 2, 0, 0}, {road, 1, 0, 0}, {road, 3, 0, 0}, {road, 1, 0, 0}, {mountain, 3, 0, 0}, {road, 0, 0, 0}, {river, 2, 0, 0}},
        {{river, 0, 0, 0}, {road, 0, 0, 0}, {river, 3, 0, 0}, {mountain, 1, 0, 0}, {mountain, 2, 0, 0}, {road, 0, 0, 0}, {mountain, 2, 0, 0}, {road, 1, 0, 0}},
        {{river, 1, 0, 0}, {road, 1, 0, 0}, {mountain, 0, 0, 0}, {road, 0, 0, 0}, {river, 0, 0, 0}, {river, 0, 0, 0}, {mountain, 0, 0, 0}, {road, 0, 1, 0}}
    };
    memcpy(a->matriz, c, sizeof(a->matriz));
    display = popen("./apres", "w"); //Criação do pipe para o apres.
    if (display == NULL) {//Verificar se o display é nulo.
        fprintf(stderr, "Não encontrei o programa de exibição\n");
        return 1;
    }  
    //Desenha as características da matriz na interface gráfica.
    for (lin = 0; lin < MAXMATRIZL; lin++){
        for (col = 0; col < MAXMATRIZC; col++){      
            fprintf(display, "cel %d %d %s\n", lin, col, Color[a->matriz[lin][col].terrain]);
            if(a->matriz[lin][col].cristal != 0){
                fprintf(display, "cristal %d %d %d\n", lin, col, a->matriz[lin][col].cristal);
            }                 
            fflush(display);   
        }
    }
    //Adiciona os 2 exércitos.
    a->exerc[a->exercTopo++] = InsereExercito(0, 0, display);
    a->exerc[a->exercTopo++] = InsereExercito(7, 7, display);
    //Executa 2 instruções por rodada para 6 rodadas;
    Atualiza(2, display);
    //RemoveExercito(a->exerc[1], &a->exerc[1], display);
    Atualiza(2, display);
    pclose(display);//Fecha o pipe.
    return 0;
}
