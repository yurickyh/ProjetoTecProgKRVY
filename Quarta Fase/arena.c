#include <stdio.h>
#include <stdlib.h>
#include "arena.h"
#include <string.h>

Arena *a;
INSTR programa[MAXMAQ][2000];

int compilador(FILE *, INSTR *);

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

// Executa cada rodada
void Atualiza(int rodadas, FILE *display){
    int i;
    for(i=0;i<rodadas;i++){
        printf("!!*******Rodada %d*******!!\n", i+1);
        int u;
        int count = 0;
        int aux;
        int auxPosition1;
        int auxPosition2;

        //Checar se há apenas uma base ativa, isto é, checar se alguem ganhou.
        for(u=1;u<MAXEXERC+1;u++){
            if(a->baseCount[u] != 0){
                count++;
                if(count>1){
                    break;
                }
                aux = u;
            }
        }
        //Se houve algum ganhador, a aplicação encerra.
        if(count==1){
            printf("Fim de jogo! Exército %d ganhou\n", aux);
            exit(0);
        }

        //Loop para passar e executar as instruções de todos os robos.
        int j;
        for(j=0;j<MAXMAQ;j++){ 
            //printf("Teste ---- %d\n", j);

            //Checar se o robo ficou sem vida
            // Se sim, o remove.
            if(a->robos[j+1]!=NULL && a->robos[j+1]->vida <= 0){
                auxPosition1 = a->robos[j+1]->position[0];
                auxPosition2 = a->robos[j+1]->position[1];

                //Remover o robo na interface gráfica.           
                fprintf(display, "clean %d %d\n", auxPosition1, auxPosition2);
                fflush(display);

                //Verificar se o robo a ser removido carregava algum cristal.
                if((a->matriz[auxPosition1][auxPosition2].cristal + a->robos[j+1]->cristal) > 0){
                    //Adicionar os cristais do robo removido aos cristais presentes na célula em que ele estava.
                    a->matriz[auxPosition1][auxPosition2].cristal += a->robos[j+1]->cristal;
                    fprintf(display, "cristal %d %d %d\n", auxPosition1, auxPosition2, 
                        a->matriz[auxPosition1][auxPosition2].cristal);
                    fflush(display);
                }
                a->matriz[auxPosition1][auxPosition2].ocup = 0;//Desocupar a célula onde estava o robo derrotado.
                destroi_maquina(&a->robos[j+1]);//Remover o robo que ficou sem vida.
            }

            // Executa instruções do robô
            if(a->robos[j+1]!=NULL){ //Checar se o robo a ter as instruções executadas não foi removido.
                if(a->robos[j+1]->count!=0){ //Se estiver com algum valor no contador, o robo não poderá jogar essa rodada.
                    printf("Robo %d perde essa rodada.\n", a->robos[j+1]->index);
                    a->robos[j+1]->count--;
                }
                else{ //Senão, executar as instruções normalmente.
                    if(a->robos[j+1]->prog == NULL) printf("Vazio %d", j);
                    exec_maquina(a->robos[j+1], INSTRNUMBER, display);
                }
            }

            // Remove exército se vida da base <= 0
            int y;
            for(y=0;y<MAXEXERC;y++){ // Loop para checar todos os exércitos.
                if(a->exerc[y]!=NULL){ // Se o exército a ser checado não foi removido.
                    if(a->exerc[y]->base->vida <= 0){ // Checar se alguma base ficou sem vida e removê-la.
                        RemoveExercito(a->exerc[y], &a->exerc[y], display);
                        printf("Fim de jogo! Exército %d foi derrotado!\n", y+1);
                        exit(0);
                    }
                }
            }
        }

        //Ao fim de cada rodada, devem ser lidos os novos arquivos para cada robo
        if(i != rodadas - 1){
            for(j=0;j<MAXMAQ;j++){
                if(a->robos[j+1]!=NULL){
                    //isso eh feito da mesma forma quando se cria a maquina
                    FILE* file;
                    int res, nl;
                    char f[20];

                    // Caso as instr do arquivo dado possuam erros de sintaxe, pergunta novamente
                    do{
                        // Caso o arquivo dado não seja encontrado, pergunta novamente
                        do {
                            printf("Programa para o robo %i: ", j+1);
                            fgets(f, 20, stdin);

                            nl = strlen(f)-1;
                            if(f[nl] == '\n') f[nl] = '\0';

                            file = fopen(f, "r");
                            if(file == NULL)
                                printf("Arquivo não foi encontrado. Tente novamente. \n");
                        } while (file == NULL);
                        res = compilador(file, programa[j]);
                        if (res != 0)
                            printf("Arquivo possui comandos inválidos. Tente novamente.\n");
                    } while (res != 0);

                    a->robos[j+1]->prog = programa[j]; //Mudando do vetor de instrucoes a ser executado
                    a->robos[j+1]->ip = 0; //Reset do ip para comecar tudo de novo
                    fclose(file);
                } else { printf("Robo %d foi destruído.\n", j+1); }
            }    
        }
    }
}

Exercito *InsereExercito(int x, int y, /*INSTR *p, */FILE *display){ // x e y = coordenadas da base desse novo exército.
    Exercito *e = (Exercito*)malloc(sizeof(Exercito));
    if(!e) Fatal("Memória insuficiente",4);
    int i;
    e->base = createBase();
    a->matriz[x][y].baseColour = e->base->colour;
    a->matriz[x][y].cristal = 0;
    a->matriz[x][y].ocup = MAXMAQ+1;
    e->base->position[0] = x;
    e->base->position[1] = y;
    if(a->matriz[x][y].baseColour == 1){//Desenhar a base 1 na interface gráfica.
        fprintf(display, "base sprites/base1r.png %d %d %d\n", a->matriz[x][y].baseColour, x, y); //criar a base vermelha        
    }
    if(a->matriz[x][y].baseColour == 2){//Desenhar a base 2 na interface gráfica.
        fprintf(display, "base sprites/base2r.png %d %d %d\n", a->matriz[x][y].baseColour, x, y); //criar a base azul
    }
    fflush(display);  

    //Loop para criar todos os robos do exército.
    for(i=0;i<ROBOSONEXERC;i++) {
        FILE* file;
        int res, nl;
        char f[20];

        // Caso as instr do arquivo dado possuam erros de sintaxe, pergunta novamente
        do{
            // Caso o arquivo dado não seja encontrado, pergunta novamente
            do {
                printf("Programa para o robo %i: ", a->robosTopo);
                fgets(f, 20, stdin);

                nl = strlen(f)-1;
                if(f[nl] == '\n') f[nl] = '\0';

                file = fopen(f, "r");
                if(file == NULL)
                    printf("Arquivo não foi encontrado. Tente novamente. \n");
            } while (file == NULL);
            res = compilador(file, programa[a->robosTopo-1]);
            if (res != 0)
                printf("Arquivo possui comandos inválidos. Tente novamente.\n");
        } while (res != 0);

        Maquina *maq = cria_maquina(programa[a->robosTopo-1]);
        fclose(file);

        Coord aux = avaliableNeighbour(x, y); //Pega alguma célula vizinha disponível à base do exército.

        if(aux.x!=MAXMATRIZL && aux.y!=MAXMATRIZC){ //Se a função retornar as coordenadas (MAXMATRIZL, MAXMATRIZC), não há células disponíveis.	    
            maq->position[0] = aux.x;
            maq->position[1] = aux.y;
            maq->index = a->robosTopo;
            a->robos[a->robosTopo++] = maq;
            a->matriz[aux.x][aux.y].ocup = maq->index; 
        }
        if(a->matriz[x][y].baseColour == 1){ //Desenha o robo do exército 1 na interface gráfica numa célula vizinha disponível.
            fprintf(display, "rob sprites/robo1.png %d %d %d\n", maq->index-1, maq->position[0], maq->position[1]);            
            fflush(display); 
        }
        if(a->matriz[x][y].baseColour == 2){ //Desenha o robo do exército 2 na interface gráfica numa célula vizinha disponível.
            fprintf(display, "rob sprites/robo2.png %d %d %d\n", maq->index-1, maq->position[0], maq->position[1]);
            fflush(display); 
        }
        e->robots[i] = maq; //Adiciona o robo no vetor de robos do seu exército.
    }
    return e;
}

//Escolher e criar um número de base que ainda não está sendo usado.
Base *createBase(){
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
    int aux1;
    int aux2;
    a->matriz[e->base->position[0]][e->base->position[1]].ocup = 0; //Desocupa a célula onde estava a base do exército a ser removido.  
    for(j=(ROBOSONEXERC*(i-1));j<(i*ROBOSONEXERC);j++){ //Loop que passa apenas pelos indíces dos robos do exército a ser removido.   
        if(a->robos[j+1]!=NULL){
            aux1 = a->robos[j+1]->position[0];
            aux2 = a->robos[j+1]->position[1];
            fprintf(display, "clean %d %d\n", aux1, aux2); //Remove o robo na interface gráfica.
            fflush(display);

            //Adiciona os cristais que o robo a ser removido estava carregando à célula onde ele estava.
            a->matriz[aux1][aux2].cristal += a->robos[j+1]->cristal;
            if(a->matriz[aux1][aux2].cristal > 0){
                fprintf(display, "cristal %d %d %d\n", aux1, aux2, a->matriz[aux1][aux2].cristal);
                fflush(display);
            }
            a->matriz[aux1][aux2].ocup = 0;//Desocupar a célula do robo removido.
            destroi_maquina(&a->robos[j+1]);
        }
    }
    a->baseCount[i] = 0;
    acertaMatriz();
    fprintf(display, "clean %d %d\n", e->base->position[0], e->base->position[1]);
    fflush(display);
    destroiBase(&e->base);
    free(*ex);
    *ex = NULL;
}

//Garante que a células que eram bases sejam desocupadas.
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

// Chamada ao fim de todas as rodadas
// Se não houve vencedor ainda, verifica baseado nos pontos de vida das bases
void FimRodadas() {
    int fim = 0;
    int y;
    // Loop verifica os exércitos
    // Se algum já foi removido, o jogo já acabou
    for(y=0;y<MAXEXERC;y++){
        if(a->exerc[y]==NULL){
            fim = 1;
        }
    }
    
    if (!fim){  
        int vida_exercito1 = a->exerc[0]->base->vida;
        int vida_exercito2 = a->exerc[1]->base->vida;
        if (vida_exercito1 > vida_exercito2){
            printf("Fim de jogo! Por ter a base em melhores condições, o Exército 1 ganhou!\n");
        } else if (vida_exercito1 < vida_exercito2) {
            printf("Fim de jogo! Por ter a base em melhores condições, o Exército 2 ganhou!\n");
        } else {
            printf("Fim de jogo! Houve empate!\n");
        }
    }
}

void Sistema(Maquina *m, char code, int op, FILE *display){
    //Agora recebendo display para escrever a cada chamada de sistema.
    //op = ângulo da direção da ação.
    char *TER[] = {
        "road",
        "mountain",
        "river"
    };    
    switch (code) {
        int aux1;
        int aux2;
        Coord tmp;
        Coord tmp2;
        case 'M':
            if(m->count != 0){//Se o robo não estiver com o contador zerado, ele não pode andar.
                printf("Robo %d não pode se mover mais nessa rodada.\n", m->index);
                return;
            }
            tmp = getNeighbour(m->position[0], m->position[1], op);//Pega as coordenadas da célula na direção desejada.
            printf("Robo de índice: %d --- ", m->index);
            if(tmp.x == MAXMATRIZL || tmp.y == MAXMATRIZC){
                printf("Tentativa de movimento para célula inválida.\n");
                return;
            }
            if(a->matriz[tmp.x][tmp.y].ocup != 0){
                printf("Tentativa de movimento para célula ocupada.\n");
                return;
            }
            //Move o robo na interface gráfica.
            fprintf(display, "%d %d %d %d %d %d\n", m->index-1, m->position[0], m->position[1], tmp.x, tmp.y, m->vida);
            fflush(display);
            //Redesenha os cristais presentes na célula que o robo saiu.
            if(a->matriz[m->position[0]][m->position[1]].cristal > 0){
                fprintf(display, "cristal %d %d %d\n", m->position[0], m->position[1], a->matriz[m->position[0]][m->position[1]].cristal);
                fflush(display);
            }   
            printf("Andou de [%d][%d] para [%d][%d].\n", m->position[0], m->position[1], tmp.x, tmp.y);
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
            //Desocupar a célula que o robo saiu e ocupar a célula para qual o robo se moveu.
            a->matriz[tmp2.x][tmp2.y].ocup = 0;            
            a->matriz[tmp.x][tmp.y].ocup = m->index;            
            break;
        case 'D':
            tmp = getNeighbour(m->position[0], m->position[1], op);//Pega as coordenadas da célula na direção desejada.            
            printf("Robo de índice: %d --- ", m->index);
            if(tmp.x == MAXMATRIZL || tmp.y == MAXMATRIZC){
                printf("Tentativa de depósito em célula inválida.\n");
                break;
            }
            if(a->matriz[tmp.x][tmp.y].ocup != MAXMAQ+1 && a->matriz[tmp.x][tmp.y].ocup != 0){//Se a célula alvo estiver ocupada mas não for uma base.
                printf("Tentativa de depósito em célula ocupada por outro robo.\n");
                break;
            }
            if(m->cristal == 0){
                printf("O robo nao tem cristais para depositar.\n");
                break;
            }
            if(a->matriz[tmp.x][tmp.y].ocup == MAXMAQ+1){ //Se a célula alvo for uma base.
                a->exerc[a->baseCount[a->matriz[tmp.x][tmp.y].baseColour]]->base->vida -= m->cristal;//Reduzir a vida da base que está na célula alvo.
                m->cristal = 0;//Zerar os cristais carregados pelo robo.
                printf("Depositou na base %d.\n", a->matriz[tmp.x][tmp.y].baseColour);
                fprintf(display, "att_base %d %d\n", a->matriz[tmp.x][tmp.y].baseColour, a->exerc[a->baseCount[a->matriz[tmp.x][tmp.y].baseColour]]->base->vida); //Manda comando para atualizar representação gráfica da base
                fflush(display); 
                break;     
            }
            if(a->matriz[tmp.x][tmp.y].ocup == 0){//Se a célula estiver desocupada.              
                a->matriz[tmp.x][tmp.y].cristal += m->cristal;     
                m->cristal = 0;//Zerar os cristais carregados pelo robo.
                printf("Depositou na celula [%1d][%1d].\n", tmp.x, tmp.y);
                //Atualiza o número de cristais na célula alvo na interface gráfica.
                fprintf(display, "cristal %d %d %d\n", tmp.x, tmp.y, a->matriz[tmp.x][tmp.y].cristal);
                fflush(display);
                break;
            }
            break;
        case 'R':
            tmp = getNeighbour(m->position[0], m->position[1], op);//Pega as coordenadas da célula na direção desejada.
            printf("Robo de índice: %d --- ", m->index);
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
            printf("Recolheu %d cristais da célula [%d][%d].\n", a->matriz[tmp.x][tmp.y].cristal, tmp.x, tmp.y);
            //Adiciona aos cristais carregados pelo robo o número de cristais presentes na célula alvo.
            m->cristal += a->matriz[tmp.x][tmp.y].cristal;
            a->matriz[tmp.x][tmp.y].cristal = 0;//Zera os cristais na célula alvo.
            //Atualiza os cristais da célula alvo na interface gráfica.
            fprintf(display, "clean %d %d\n", tmp.x, tmp.y);
            fflush(display);
            break;
        case 'A':
            tmp = getNeighbour(m->position[0], m->position[1], op);//Pega as coordenadas da célula na direção desejada.
            printf("Robo de índice: %d --- ", m->index);
            if(tmp.x == MAXMATRIZL || tmp.y == MAXMATRIZC)
            {
                printf("Tentativa de ataque em célula inválida.\n");
                break;
            }
            if(a->matriz[tmp.x][tmp.y].ocup == 0){
                printf("Tentativa de ataque em célula desocupada.\n");
                break;
            }
            if(a->matriz[tmp.x][tmp.y].ocup == MAXMAQ+1){
                printf("Tentativa de ataque em uma base. Não é possível atacar uma base diretamente.\n");
                break;
            }
            //Reduz a vida do robo atacado.
            a->robos[a->matriz[tmp.x][tmp.y].ocup]->vida--;     
            aux1 = a->robos[a->matriz[tmp.x][tmp.y].ocup]->position[0];
            aux2 = a->robos[a->matriz[tmp.x][tmp.y].ocup]->position[1];
            //Atualiza a vida do robo atacado na interface gráfica.
            fprintf(display, "%d %d %d %d %d %d\n", a->matriz[tmp.x][tmp.y].ocup-1, aux1, aux2, aux1, aux2, a->robos[a->matriz[tmp.x][tmp.y].ocup]->vida);
            fflush(display);
            //Redesenha os cristais da célula onde está o robo que foi atacado.
            if(a->matriz[m->position[0]][m->position[1]].cristal > 0){
                fprintf(display, "cristal %d %d %d\n", aux1, aux2, a->matriz[aux1][aux2].cristal);
                fflush(display);
            }
            printf("Efetuou o ataque na célula [%1d][%1d] atingindo o robô %d.\n", tmp.x, tmp.y, a->matriz[tmp.x][tmp.y].ocup);
            break;
    }
}

//Função para devolver a célula vizinha na matriz hexagonal em um dado ângulo.
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
                if(l%2!=0){
                    cord.x = l+1;
                    cord.y = c+1;
                }
                else{
                    cord.x = l+1;
                    cord.y = c;
                }
            }
            break;
        default: // ângulo inválido -> célula inválida
            cord.x = MAXMATRIZL;
            cord.y = MAXMATRIZC;
            break;
    }
    return cord;
}

//Função para pegar alguma célula vizinha disponível. A ordem de checagem segue no sentido anti-horário.
Coord avaliableNeighbour(int l, int c) {
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

// Retorna atributo de célula vizinha
// t = 0 - retorna qual o terreno da célula
// t = 1 - retorna quantidade de cristais
// t = 2 - verifica se célula está ocupada
// t = 3 - verifica se célula possui base
int NeighbourLook(int x, int y, int angle, int t) {
    char *TER[] = {
        "road",
        "mountain",
        "river"
        };

    char terr[10];
    char mount[10];
    char riv[10];

    Coord cord = getNeighbour(x, y, angle);
    if(cord.x == MAXMATRIZL || cord.y == MAXMATRIZC) return -1;
    else {
        switch(t) {
            case(0):
                strcpy(terr, TER[a->matriz[cord.x][cord.y].terrain]);
                strcpy(riv, "river");
                strcpy(mount, "mountain");
                if(strcmp(terr, mount) == 0) return 1;
                if(strcmp(terr, riv) == 0) return 2;
                return 0;
                break;
            case(1):
                return a->matriz[cord.x][cord.y].cristal;
                break;
            case(2):
                return a->matriz[cord.x][cord.y].ocup;
                break;
            case(3):
                return a->matriz[cord.x][cord.y].baseColour;
                break;
        }
    }
}
