Nome: Kaique Kazuyoshi Komata    10297741
      Ricardo Hideki Hangai Kojo 10295429
      Vitor Matsubara            6473889
      Yurick Yussuke Honda       10258984

TODOS OS CÓDIGOS FORAM TESTADOS EM LINUX UBUNTU 16.04 LTS

*** CORREÇÕES - PRIMEIRA FASE

    As instruções da primeira fase foram corrigidas. Anteriormente, nosso RBP era uma variável local da função exec_maquina() que era manipulada como um inteiro local.
    Agora RBP é um atributo da máquina, que é empilhado e desempilhado nas instruções CALL e RET. Da mesma forma, IP agora é empilhado e desempilhado junto com o RBP.

*** INSTR.H
	
    Os argumentos da struct INSTR foram alterados. Agora a INSTR é formada pelo enum OpCode e struct Operando.

*** INSTRUÇÃO ATR

    Para o "ATR", tivemos que alterar a forma do operando. Assim, o uso da union criada é facultativo, permitindo que não a use, ou deixe valores inutilizáveis nela. Por isso, o operando adquiriu a forma como está, assim quando ATR é chamada, verifica-se o tipo do operando, pois para ATR funcionar, o operando deve ser do tipo célula. Com isso, de acordo com a ordem dos atributos definidos na struct célula, o argumento solicitado, um determinado atributo da célula é acessado e empilha-se um operando do tipo {NUM, [valor do atributo recolhido]}, assim como solicitado na documentação, bem como discutido e dito pelos monitores/professor no PACA.

*** MAC.C e MAC.H
	
    Na struct Maquina, foram adicionados os seguintes atributos:
        - int rbp: correção da primeira fase;
        - int position[2]: posição do robô na Arena;
        - int cristal: quantidade de cristais que o robô está carregando;
        - int vida: quantidade de vida do robô (cada robô começa com 3 de vida);
        - int index: posição do robô na pilha de robôs (atributo de Arena).

    Além da instrução ATR, já descrita no tópico anterior, foram adicionadas as instruções MOVE, RECO, DEPO, ATAQ que são ações de um robô. Cada uma delas faz uma chamada de Sistema, definido em "arena.c" e explicada no próximo tópico.

    Outras instruções sofreram alterações para se adaptar ao novo formato da struct INSTR. Mudanças mais significativas foram:
        - ADD, SUB, MUL, DIV: agora verificam se os operandos são números (NUM), já que anteriormente Operando era int;
        - CALL e RET: correção da primeira fase;
        - PRN: prints diferentes para diferentes tipos de Operando.

*** ARENA.C e ARENA.H

    A arena:
        possui o vetor de todos os robôs na arena, um topo para o vetor de robôs, a matriz que representa o grid hexagonal (sendo que o tamanho do grid é definido pelos macros, aparentemente quando se aumenta a matriz, as máquinas que utilizamos para programar não suportavam, portanto diminuímos o grid), um vetor para os exércitos, um topo para o vetor de exércitos e um vetor para as bases.

    Terreno:
        foram estipulados três tipos de terrenos: "road", "mountain" e "river", porém não foram estipulados nenhuma diferença no movimento em diferentes terrenos.

    Base:
        possui a "vida"(basicamente a quantidade de cristais que devem ser depositados) e o "colour"(id que relaciona a base com o exército).

    Exercito:
        possui um vetor de ponteiros dos robôs no exército e um ponteiro de sua base. Sendo que a quantidade de robôs em um exército é definido no macro, estamos utilizando 5 robôs.

    void Erro(char *msg) e void Fatal(char *msg, int cod):
        assim como em maq.c enviado pelo professor na primeira fase, tais métodos servem para reportar erros durante a execução e uso do código.

    CriaArena():
        como estamos trabalhando com uma arena apenas, declaramos ela como uma variável global. Foi dito em sala que evitar variáveis globais é uma prática de programação, porém nesse caso o grupo atentou-se aos malefícios que isso pode causar. Em análise a isso, o resultado foi a percepção de que isso não afetaria negativamente o algoritmo. Logo, o método criaArena(), assim como em maq.c aloca memória ao ponteiro e inicializa alguns de seus atributos que devem tomar valor zero, no início da partida.

    void Atualiza(int rodadas):
        assim como discutido no PACA e dito pelo próprio monitor, representa o escalonador, ou seja, o método recebe a quantidade de rodadas e executa os robôs para cada rodada. Uma rodada equivale a executar as instruções de todos os robôs. Assim, o atualiza, por enquanto, checa se alguém ganhou, analisando se há alguma base ativa. Para verificar se um exército ganhou, o escalonador faz a constante checagem, analisando se há apenas um exército na arena, pois isso indica que todos os outros exércitos foram removidos/"destruídos". Além disso, há as checagens de ver se algum robô ficou sem vida, sendo que quando isso ocorre a consequência é a arena destruí-lo, e ver se a base está sem vida, nesse caso remove-se o exército inteiro e conta como uma equipe "morta". 

    Exercito *InsereExercito(int x, int y):
        esse método é do tipo Exercito e retorna um ponteiro para um exército. Com isso, ele recebe como argumentos uma coordanada da matriz que representa o grid para inserir o exército na posição desejada. Assim, o método aloca memória para um exército e roda uma iteração para criar as máquinas do exército, portanto para cada robô criado no InsereExercito(), há a inserção dele tanto no vetor de robôs da arena quando no vetor de robôs do exército. Além disso, para cada criação do exército uma base será criada, que logo abaixo será dito, bem como a inicialização dos atributos de base: baseColour(como um id de cada time/base), cristal(uma base não pode ter cristal nela) e ocup (como todas as máquina "spawnam" na base, então a ocupação delas são todos os robôs do exército). Lembrando, que há macros que definem a quantidade de máquinas em cada exército, no nosso caso, utilizamos 5 máquinas.

    Base *createBase():
        esse método é do tipo "Base" e retorna um ponteiro para uma base. Para cada exército criado, um ponteiro de base é criado e aloca-se memória a ele. Além disso, seus atributos são inicializados: vida(foi definido um macro de vida para a base como 20 cristais) e colour(para cada base é definida uma cor, que a princípio é um int e funciona mais como um id).

    void destroiBase(Base** b):
        esse método desaloca a memória de uma base e iguala o ponteiro da base a NULL direto em seu endereço, assim tem-se o controle de quais bases foram destruídas.

    void RemoveExercito(Exercito *e, Exercito** ex):
        "RemoveExercito" utiliza o id da base do exército(baseColour) e por meio de um trabalho matemático com os índices, identifica os robôs que fazem parte do exército a ser removido direto no vetor de robôs da arena, assim para cada robô do exército roda-se o método "destroi_maquina()". Além disso, no vetor de bases da arena, a base do exército referido leva valor zero, pois estamos utilizando o valor 0 para quando a base não existe mais. Por fim, a matriz é "acertada" (será explicado abaixo), a base é destruída e o exército possui sua memória liberada e seu ponteiro igualado a NULL, para controle.

    void acertaMatriz():
        o método identifica o local em que a base do exército removido estava e acerta o grid por meio de seus atributos. Assim, o atributo que identifica o id da base/exercito é igualado a zero(não é base) e ocupado é igualado a zero também(o valor zero indica que a célula não está ocupada).

    Coord getNeighbour(int l, int c, int angle): o
        o método é do tipo "Coord" que possui dois atributos (x, y), que são dois inteiros e representa os índices da matriz do grid. Os argumentos a recolhidos pela função são: linha, coluna e ângulo, respectivamente. O ângulo foi definido pelo grupo como a direção e sentido de movimento: 45(nordeste), 90(norte), 135(noroeste), 225(sudoeste), 270(sul) e  315(sudeste). Assim, o índice do vizinho é calculado de acordo com a direção estipulada.

    void Sistema(Maquina *m, char code, int op):
        para entender o que esse método faz, é preciso saber as novas instruções adicionadas nos operandos e suas funções em "maq.c". Dito isso, os argumentos do método são: um ponteiro de máquina, um char que representa o código e um int pra operação. Assim, de acordo com o código, uma ação é feita. Caso código igual a 'M', é feito o cálculo da célula vizinha no ângulo(operação) solicitado e, caso a máquina solicite o movimento para uma célula inválida(fora dos limites da arena) ou uma célula já ocupada, então uma mensagem de alerta é emitida e o robô perde a sua vez; caso contrário, a arena altera os atributos do robô e torna a célula ocupada pelo robô movimentado, isso é feito por meio do atributo ocup da célula que indica o id do robô que a ocupa. Caso código igual a 'D', é feito o cálculo da célula vizinha no ângulo(operação) solicitado e, caso a máquina solicite o depósito de cristais em células inválidas ou células ocupadas, um alerta é emitido e o robô perde a vez; caso contrário, o robô pode depositar os cristais recolhidos por ele em sua base, resultando em uma contabilização na vida da base, ou pode depositar os cristais em uma célula, em ambos os casos, o atributo que quantifica os cristais que o robô carrega são zerados. Caso código igual a 'R', é feito o cálculo da célula vizinha no ângulo(operação) solicitado e, caso a máquina solicite recolher cristais de uma célula inválida, célula ocupada ou célula sem cristais, um alerta é emitido e robô perde a vez; caso contrário, o robô recolhe os cristais da célula tornando a quantidade de cristais da célula igual a 0 e aumentando o atributo cristais do robô. Caso código igual a 'A', é feito o cálculo da célula vizinha no ângulo(operação) solicitado e, caso a máquina solicite atacar uma célula que está desocupada ou uma base, um alerta é emitido e o robô perde a vez; caso contrário, o robô atacado perde uma unidade de vida. Da maneira como foi criada, permite-se o chamado "fogo amigo", pois nada impede que um robô ataque outro do mesmo time.

*** TESTES

    Os testes aplicados estão no arquivo "motor.c".
    São 11 testes no total:
        - Teste da criação da arena;
        - Inserção e remoção de exércitos;
        - Declaração de exército vencedor;
        - Remoção de exército que teve vida da base zerada;
        - Remoção de robô que teve vida zerada;
        - Criação de dois exército, com cada robô executando uma lista de instruções (Fibonacci no teste);
        - Ação MOVE de robôs na arena;
        - Ação RECOLHER;
        - Ação DEPOSITAR;
        - Ação ATACAR;
        - Teste da instrução ATR.
    Todos os códigos estão comentados na função Main de "motor.c". Basta "descomentar" o teste a ser executado e, se necessário, o trecho correspondente ao teste no vetor INSTR programa[].
