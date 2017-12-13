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

*** AJUSTES EM MAC.C e ARENA.C:
    # TODO

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
        **
        A cada rodada, são executadas até 3 instruções para cada robô (definido pela constante INSTRNUMBER em arena.h);
        Se o arquivo com o conjunto de instruções não for encontrado, será pedido um novo arquivo (até ser dado um arquivo existente);
        Se o arquivo com o conjunto de instruções possuir erros de sintaxe, será pedido um novo arquivo (até ser dado um arquivo válido);
        Se o arquivo com o conjunto de instruções possuir mais que 3 instruções, apenas as 3 primeiras serão executadas;
        Se o arquivo com o conjunto de instruções possuir menos que 3 instruções, serão executadas apenas as instruções dadas;
        ** 
        (Por questões de teste, o valor de INSTRNUMBER é 80 (para poder testar fatorial e fibonacci por exemplo). No entanto, os teste criados forem criados com 3 instruções por rodada).
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
    #TODO

*** TRIVIA E OUTRAS IDEIAS DE IMPLEMENTAÇÃO:
    IDEIAS:
        Respawn de robôs, escolher configuração da arena (número de linhas, colunas), diferentes tipos de ataque, possibildade do robô recuperar vida, possibilidade da base recuperar vida... 
    TRIVIA:
        Destruir todos os robôs inimigos não resulta em vitória imediata. O objetivo de um MOBA é destruir a base inimiga, portanto, o exército ainda deve depositar cristais na base inimiga.
        Se o exército sobrevivente não conseguir deixar a base inimiga com menos pontos de vida que a própria base até o final da partida (todas as rodadas terem ocorrido), o exército oposto pode vencer mesmo sem possuir nenhum robô.