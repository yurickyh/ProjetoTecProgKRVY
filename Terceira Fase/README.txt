Nome: Kaique Kazuyoshi Komata    10297741
      Ricardo Hideki Hangai Kojo 10295429
      Yurick Yussuke Honda       10258984

TODOS OS CÓDIGOS FORAM TESTADOS EM LINUX UBUNTU 16.04 LTS

*** SISTEMA DO JOGO

    As alterações foram feitas conforme o enunciado. Em "arena.c", as funções que executam ações de inserir e remover exércitos, e de chamadas do Sistema foram alteradas para mandar entradas para "apres". Foram adicionados comandos "fprintf" e "fflush" para que as ações que ocorriam na arena fossem mostradas graficamente. Detalhes estão comentados no código.

*** TAMANHO DA ARENA

    Testamos diferentes tamanhos em diferentes computadores. Em um dos computadores, uma arena 9x9 causava um "segmentation fault" e os processos não funcionavam corretamente. Em outro, 9x9 funcionava normalmente, mas 10x10 não. Sendo assim, decidimos fixar o tamanho da arena em 8x8 para que pudesse funcionar em todos que usamos para o trabalho.

*** REPRESENTAÇÃO GRÁFICA

    As alterações feitas em "apres" foram baseadas no código criado pelo professor. Foram criados os objetos "Base" e "Cristal", baseados em "Robô", para desenhar os elementos na tela. Na leitura de entrada padrão, foram adicionados os comandos "base" (para adicionar objetos Base), "cristal" (para adicioanr objetos Cristal) e "clean" (para apagar robôs e/ou cristais da célula).
    Também foi adicionado pygame.font para mostrar valores importantes para o jogo:
        - no Robô, o número à esquerda representa seu id, enquanto o número verde à direita representa a quantidade de vida (de 0 a 3);
        - no Cristal, o número branco representa a quantidade de cristais na célula.
        - na Base, o número vermelho escuro representa a quantidade de vida (de 0 até a variável BASELIFE em arena.h)

*** MOTOR.C E TESTES
    
    No "motor.c" estão definidos os tipos de terreno, cores utilizadas por cada um deles e uma matriz (arena) para testes.
    A arena é inserida na representação gráfica por comandos "fprintf". Logo após são inseridos dois exércitos, executados os comandos de cada máquina, o segundo exército é removido (de forma forçada) e o jogo termina.
    O conjunto de instruções está no array de INSTR "programa", definido no início do código. Vale lembrar que todos os robôs executaram o mesmo conjunto de instruções em nosso teste.
        - Teste 1: testa movimentação em diferentes terrenos e perda de rodadas;
        - Teste 2: testa ataque e vida dos robôs e remoção de robô sem vida; depósito de cristais na base e perda de vida da base;
        - Teste 3: testa coleta e depósito de cristais; perda de vida da base.
