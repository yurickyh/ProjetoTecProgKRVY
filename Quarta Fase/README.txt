Nome: Kaique Kazuyoshi Komata    10297741
      Ricardo Hideki Hangai Kojo 10295429
      Yurick Yussuke Honda       10258984

TODOS OS CÓDIGOS FORAM TESTADOS EM LINUX UBUNTU 16.04 LTS

*** NOVA INSTRUÇÃO "LOOK":
    "look" é uma nova instrução que permite ao robô verificar informações de células vizinhas (tipo de terreno, quantidade de cristais, se a célula está ocupada (tanto por robô quanto por base).
    A instrução possui o formato: "look ângulo número;".
    O número representa qual atributo da célula o robô quer verificar:
        número = 0 - verifica qual o terreno da célula vizinha escolhida;
        número = 1 - verifica quantidade de cristais na célula vizinha escolhida;
        número = 2 - verifica se célula vizinha escolhida está ocupada por um robô;
        número = 3 - verifica se célula vizinha escolhida está ocupada por uma base;

*** FLEX
    No arquivo Flex foram adicionados os seguintes padrões: "move", "deposit", "take", "attack" e "look". Movimentar, depositar cristas, recolher cristal, atacar e olhar célula, respectivamente.
    Cada um deles reconhece um token do Bison.

*** BISON
    Foram adicionados 5 tokens:
        MOVEt - referente ao padrão "move" do Flex;
        RECOt - referente ao padrão "take" do Flex;
        ATAQt - referente ao padrão "attack" do Flex;
        DEPOt - referente ao padrão "deposit" do Flex;
        ATRt - referente ao padrão "look" do Flex;
    Foi adicionado 1 comando não-terminal:
        Acao - que pode ser um dos tokens comentados acima seguido de um token NUMt (ou dois NUMt no caso de ATRt).
    Sendo assim, as instruções possíveis possuem o formato:
        "instrução número;", sendo o número um ângulo (0°, 45°, 135°, 180°, 225° ou 315°). Este ângulo representa qual a direção da célula na qual a instrução deve ser executada. Isto se deve ao formato hexagonal da célula.
        Como foi explicado acima, a instrução "look" possui um formato diferente.
        Exemplos:
            "move 0;" move o robô para a célula à direita;
            "take 315;" recolhe os cristais da célula à sudeste.

*** ARENA.C E ARENA.H:
    Em "arena.c" as funções InsereExército() e Atualiza() passaram a usar os arquivos lidos (e verificados pelo Flex+Bison) como conjunto de instruções, baseado no exemplo dado pelo professor em "motor.c";
    Foi criada a função auxiliar avaliableNeighbour() para verificar células vazias vizinhas à base (para posicionar os robôs nestas);
    Foi criada a função auxiliar NeighbourLook() para a nova instrução "look";

    Em "arena.h" foi criada uma matriz "programa" na qual as linhas representam um vetor com x instruções, sendo x o número de colunas da matriz (2000 por default);

*** MAC.C:
    "mac.c" foi atualizado com as mudanças feitas pelo professor. Além disso, foi adicionada a instrução ATR que funciona como o comando "look" para os robôs.

*** COMO O JOGO FUNCIONA (REGRAS DO JOGO):
    ARENA:
        A arena possui o formato 8x8 células;
        Cada célula pode ser de um dos 3 tipos de terreno: "road", "mountain" e "river";
        Há 40 pelo menos cristais espalhados pelas células da arena;
        As bases estão localizadas nos cantos extremo esquerdo superior e extremo direito inferior da arena.

    PARTIDA:
        Cada partida é formada por 2 exércitos com 2 jogadores cada;
        Cada partida possui 30 rodadas (definido pelo argumento dado para a função Atualiza(), chamada em motor.c);
        Cada robô possui 3 pontos de vida iniciais;
        Cada base possui 20 pontos de vida iniciais.

    RODADAS:
        A cada rodada, cada jogador deve mandar para o robô um arquivo com um conjunto de instruções no formato permitido pelo Flex+Bison;
        A cada rodada, são executadas até 3 instruções para cada robô (definido pela constante INSTRNUMBER em arena.h);
        Se o arquivo com o conjunto de instruções não for encontrado, será pedido um novo arquivo (até ser dado um arquivo existente);
        Se o arquivo com o conjunto de instruções possuir erros de sintaxe, será pedido um novo arquivo (até ser dado um arquivo válido);
        Se o arquivo com o conjunto de instruções possuir mais que 3 instruções, apenas as 3 primeiras serão executadas;
        Se o arquivo com o conjunto de instruções possuir menos que 3 instruções, serão executadas apenas as instruções dadas;
        Instruções inválidas, como tentar se movimentar para célula inexistente (fora da arena), serão contadas.

    FORMATO DAS INSTRUÇÕES:
        As instruções possuem o formato "instrução ângulo;". Apenas a instrução "look" possui o formato diferente: "look ângulo ação;".
        O ângulo pode ser 0°, 45°, 135°, 180°, 225° ou 315°. Este ângulo representa qual a direção da célula na qual a instrução deve ser executada. Isto se deve ao formato hexagonal da célula.
        Caso o ângulo dado seja inválido, a instrução será contada (nada acontece).
        Exemplos de instrução:
            "move 0;" move o robô para a célula à direita;
            "take 315;" recolhe os cristais da célula à sudeste;
            "deposit 45;" deposita cristais na célula à nordeste;
            "attack 135;" ataca célula à noroeste;
            "look 180 1;" verifica se célula à esquerda possui cristais.

    AÇÕES POSSÍVEIS:
        MOVIMENTAR:
            Cada robô pode se mover apenas 1 vez por rodada;
            Depedendo do terreno da célula, o robô pode perder rodadas:
                1 rodada, caso se movimente para "mountain";
                2 rodadas, caso se movimente para "river";
            Não é possível se movimentar para células já ocupadas (por robôs ou base);
            Não é possível se movimentar para "fora" da arena;

        RECOLHER E DEPOSITAR CRISTAIS:
            O comando "take" pega todos os cristais da célula;
            O comando "deposit" deposita todos os cristais na célula;
            Ao ser destruído, caso um robô possua cristais, estes são derrubados na célula na qual o robô foi destruído;
            Ao depositar cristais numa base, a base perde pontos de vida baseado na quantidade de cristais depositados (5 depositados = -5 pontos de vida);
            É possível depositar cristais em qualquer célula;
            É possível depositar cristais na própria base;
            É possível tentar recolher cristais numa célula que não possui cristais (nada acontece);
            Não é possível recolher ou depositar cristais em células já ocupadas (por robôs ou base).
                Da regra acima temos que não possível recolher/depositar cristais na célula atual (ou seja, na célula em que o próprio robô está).

        ATAQUE:
            Cada ataque tira 1 de vida do robô atacado;
            É possível atacar robôs aliados;
            É possível tentar atacar uma célula vazia ou que possui uma base (nada acontece).

        VERIFICAR CÉLULA VIZINHA:
            Qualquer célula vizinha pode ser verificada (desde que exista na arena);
            Esta ação conta como instrução numa rodada (ou seja, ao usar 3 comandos "look" a rodada do robô termina).

    CONDIÇÕES DE VITÓRIA:
        Se a base de um exército for destruída (vida chegar a 0), este perde o jogo;
        Se ao final das 30 rodadas nenhuma das condições de vitória acima forem alcançadas, vence a equipe cuja base possui mais pontos de vida;
            Caso as duas estejam com a mesma quantidade de pontos de vida, ocorre um empate.

*** MOTOR.C E TESTES:
    A estrutura de "motor.c" continua a mesma da fase anterior.
    Quanto aos testes, estes deixaram de ser feitos pelo vetor de INSTR em "motor.c".
    Como o jogo funciona com o input de arquivos com as instruções para cada robô, os testes passaram para arquivos separados.
    Todos os arquivos de teste estão na pasta "testes".

    EXPLICANDO OS TESTES:
        Como está descrito nas REGRAS DO JOGO, idealmente cada robô executa 3 instruções por rodada e há 30 rodadas.
        No entanto, para testes, os valores foram alterados para 200 instruções** por rodada e apenas 5 rodadas (as variáveis para alterar os valores são INSTRNUMBER em "arena.h" e o primeiro argumento de Atualiza() em "motor.c").
        **200 para poderem executar "fatorial" e "fibo" como parte dos testes.

        Foram criados testes simples, que mostram as ações básicas do robô (mover, coletar, depositar, atacar e olhar).
        Estes estão nos arquivos "t0", "t1", "t2, "t3", "t4":
            t1 = arquivo com 1 instrução de movimentação para a esquerda (180°);
            t2 = arquivo com 8 instruções: coletar em volta do robô, depositar à esquerda e depositar à direita;
            t3 = arquivo com 6 instruções: ataque em volta do robô;
            t4 = arquivo com 24 instruções: verificar todos os atributos das células em volta do robô.

        O teste "tbase" foi criado para verificar uma das condições de vitória de jogo.
            tbase = arquivo com 4 comandos: olhar esquerda e direita, coletar da esquerda e depositar à direita.

        Os erros possíveis erros em arquivos estão representados em "erro1" e "erro2":
            erro1 = arquivo formado por apenas 1 instrução com erro de sintaxe;
            erro2 = arquivo formado por apenas 1 instrução que não possui erros de sintaxe, mas possui um ângulo inválido.
    
    COMO TESTAR:
        Basta executar o comando "make" no terminal e depois "./motor".
        A interface gráfica irá aparecer e deverá ser digitado no terminal os nomes dos arquivos que contém o conjunto de instruções para cada robô.
        Basta digitar o caminho para o arquivo descrito nos testes e verificar o que ocorre. Por questão de organização, estão todos na pasta "testes", mas fica mais fácil colocar na mesma pasta do executável "motor".
        * Todos os robôs devem receber um arquivo antes das instruções serem efetivadas.
        ** Quando a descrição do teste diz "podem receber qualquer arquivo", utilize "fibo" (faz o robô imprimir os 8 primeiros números da sequência de Fibonacci) ou "fatorial" (faz o robô imprimir o fatorial de 4) pois mostram que o robô executa instruções e não interfere na arena.

        TESTE 1: Movimentação
            Todos os robôs recebem o arquivo "t1".
            O robô 1 não se movem pois a célula à esquerda está ocupada pela base.
            O robô 2 não se movem pois não há célula mais à esquerda.
            Os robôs 3 e 4 devem se mover para a esquerda. Como o robô 3 se move para uma célula de "river" e o robô 4 para uma célula de "mountain", o robô 3 perde duas rodadas e o 4 perde uma.
            Serão apontados no terminal quais robôs perderam a rodada.
            O intuito do teste é mostrar a movimentação de personagens, condição de movimentação e perda de rodadas por movimentação em diferentes terrenos.

        TESTE 2: Coleta e deposição
            O robô 1 recebe o arquivo "t2". Pode ser testada apenas para o robô 1 e apenas na primeira rodada.
            Os outros robôs podem receber qualquer arquivo.
            O robô tentará coletar cristais em todas as células em volta dele (sentido anti-horário), depositar em sua base (à esquerda, 180°) e depois tentar depositar à direita (0°).
            Serão apontados no terminal os cristais coletados, quais células não possuem cristais, quais são inválidas, deposição na base 1 e tentativa de deposição.
            O intuito do teste é mostrar coleta de cristais, condições de coleta, deposição, condições de deposição e perda de vida da base.

        TESTE 3: Ataque
            Todos os robôs rebecem o arquivo "t3".
            Todos os robôs tentam atacar todas as células à sua volta.
            Serão apontados no terminal os ataques efetivados, quais foram feitos à células vazias e quais foram feitos à células inválidas. Ao final os robôs devem ter 2 de vida.
            O intuito do teste é mostrar ataque, condições de ataque e diminuição de vida do robô.

        TESTE 4: Olhar
            Todos os robôs rebecem o arquivo "t4".
            Todos os robôs verificam os atributos de todas as células à sua volta (sentido anti-horário): tipo de terreno, quantidade de cristais, se está ocupado ou se é uma base.
            Serão apontados no terminal todas as informações na ordem.
            O intuito do teste é mostrar a funcionalidade da nova instrução.

        TESTE 5: Vitória por destruição da base
            O robô 4 recebe o arquivo "tbase"
            Os outros robôs podem receber qualquer arquivo.
            O robô 4 irá olhar a quantidade de cristais à sua esquerda, olhar a base à direita, recolher os cristais (foram colocados 21 para este teste) e depositar em sua própria base à esquerda.
            O intuito do teste é verificar a principal condição de vitória, que é destruir uma base (vida da base <= 0);

        TESTE 6: Vitória após final das rodadas
            O robô 1 recebe o arquivo "t2" na primeira rodada. Nas próximas, recebe "fatorial" ou "fibo".
             Os outros robôs recebem "fatorial".
            Após o término de todas as rodadas, como a quantidade de vida das base 1 é inferior à da base 2, o exército 2 é declarado vencedor.
            O intuito do teste é verificar a condição vitória após o término de todas as rodadas.

        TESTE 7: Empate
            Todos os robôs recebem "fatorial" ou "fibo" em todas as 5 rodadas.
            Todos os robôs devem imprimir o fatorial de 4 a cada rodada (ou os 8 primeiros números de Fibonacci).
            Após o término de todas as rodadas, como a quantidade de vida das duas bases são iguais, o jogo deve declarar um empate.
            O intuito do teste é verificar a condição de empate após o término de todas as rodadas.

        TESTE 8: Arquivo com erro de sintaxe
            Qualquer robô recebe o arquivo "erro1" a qualquer momento.
            Pode ser feito no meio de outros testes.
            Ao chamá-lo, o jogo deve apontar que há erro de sintaxe no arquivo e pedir um novo arquivo (até ser digitado um arquivo válido).

        TESTE 9: Arquivo com erro no ângulo da instrução
            Qualquer robô recebe o arquivo "erro2" a qualquer momento.
            Pode ser feito no meio de outros testes.
            Ao chamá-lo, o jogo deve apontar a instrução "move" para uma célula inválida e continuar o jogo (o robô praticamente executa um "do nothing").

        TESTE 10: Arquivo não encontrado
            Qualquer robô recebe um nome de arquivo que não existe.
            Pode ser feito no meio de outros testes.
            Ao chamá-lo, o jogo deve apontar que o arquivo não existe e pedir um novo arquivo (até ser digitado um arquivo existente).


*** TRIVIA E OUTRAS IDEIAS DE IMPLEMENTAÇÃO:
    IDEIAS:
        Respawn de robôs, escolher configuração da arena (número de linhas, colunas), diferentes tipos de ataque, possibildade do robô recuperar vida, possibilidade da base recuperar vida... 
    TRIVIA:
        Destruir todos os robôs inimigos não resulta em vitória imediata. O objetivo de um MOBA é destruir a base inimiga, portanto, o exército ainda deve depositar cristais na base inimiga.
        Se o exército sobrevivente não conseguir deixar a base inimiga com menos pontos de vida que a própria base até o final da partida (todas as rodadas terem ocorrido), o exército oposto pode vencer mesmo sem possuir nenhum robô.