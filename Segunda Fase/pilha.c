Nome: Kaique Kazuyoshi Komata 10297741
	  Ricardo Hideki Hangai Kojo 10295429
	  Vitor Matsubara 6473889
	  Yurick Yussuke Honda 10258984

As instruções ALC e FRE foram criadas tais como solicitadas no programa exemplo fatorial. ALC acerta o rbp para a posição do endereço de retorno como o topo da pilha de execução menos uma unidade, além disso altera o topo, de modo a alocar na pilha a quantidade de dados necessário. FRE define o topo da pilha de execução para o topo menos a quantidade de dados solicitada para ser liberada da pilha, além disso acerta o rbp, assim como em ALC, para a posição do topo da pilha de execução menos uma unidade.
No exemplo programa fatorial disponibilizada, foi necessário realizar algumas mudanças de maneira que o fatorial de n fosse calculado, pois da maneira indicada a ser 