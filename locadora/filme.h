/**
 * ESTRUTURA DE DADOS
 * Autor: Tiago Wolker Leite
 * Data: 07/09/2017
 * Última atualização: 29/10/2017
 * Estruturas relacionadas à Filme.
 */

typedef struct {
	int codigo;
	char titulo[50];
} Filme;

typedef struct ListaFilmes {
	Filme filme;
	struct ListaFilmes *prox;
} ListaFilmes;
