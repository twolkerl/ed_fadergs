#include <stdio.h>
#include <string.h>
#include "filme.h"


int contarFilmes(ListaFilmes **listaFilmes);
void subMenuOrdenar(ListaFilmes **listaFilmes);
void ordenarFilmesPorNome(ListaFilmes **listaFilmes, int qtdFilmes);
void ordenarFilmesPorCodigo(ListaFilmes **listaFilmes, int qtdFilmes);
void selectSort(ListaFilmes **listaFilmes);

// Função para contar e retornar a quantidade de filmes cadastrados
int contarFilmes(ListaFilmes **listaFilmes){
	
	int contador = 0;
	
	ListaFilmes *aux = *listaFilmes;
	
	// Enquanto aux for diferente de nulo:
	while (aux != NULL) {
		// Incrementa o contador a cada iteração
		contador++;
		aux = aux->prox;
	}
	
	return contador;
}

// Submenu para escolher o tipo de ordenação
void subMenuOrdenar(ListaFilmes **listaFilmes) {
	
	int qtdFilmes = contarFilmes(&*listaFilmes);
	
	// Verifica se há apenas um ou nenhum registro
	if (qtdFilmes < 2) {
		// Caso exista apenas um ou nenhum registro:
		printf("\nNão é possível ordenar filmes pois existe apenas um ou nenhum registro!");
	} else {
	
		int op = 0;
		printf("====== [ ORDENAR FILMES ] ======");
		printf("\n");
		printf("\n[1]  - Ordenar por nome");
		printf("\n[2]  - Ordenar por código (Bubble Sort)");
		printf("\n[3]  - Ordenar por código (Select Sort)");
		printf("\n[0]  - Voltar");
		/*
		printf("\n[#]  - Modelo");
		*/
		printf("\n");
		printf("\nDigite a sua opção para ordenar ou qualquer número diferente para retornar: ");
		scanf("%i", &op);
		
		switch(op) {
			
			case 1:
				// Ordenar por nome:
				ordenarFilmesPorNome(&*listaFilmes, qtdFilmes);
				break;
			case 2:
				// Ordenar por código:
				ordenarFilmesPorCodigo(&*listaFilmes, qtdFilmes);
				break;
			case 3:
				// Ordenar por código (select sort):
				selectSort(&*listaFilmes);
				break;
			/*
			case #:
				// Modelo
				break;
			*/
			default:
				return;
			
		}
	}
	
}

// Função para ordenar os filmes pelo nome em ordem alfabética
void ordenarFilmesPorNome(ListaFilmes **listaFilmes, int qtdFilmes) {
		
	for (int i = 0; i < qtdFilmes; i++) {
		
		ListaFilmes *aux = *listaFilmes;
	
		while (aux->prox != NULL) {
			
			ListaFilmes *anterior = aux;
			aux = aux->prox;
			// Realiza a comparação do nome dos filmes. Se o nome do filme da
			// posição de "aux" for "menor" que o nome do filme da posição de
			// "anterior", será atribuído -1 para a variável comp.
			int comparacao = strcmpi(aux->filme.titulo, anterior->filme.titulo);
			
			// Caso a variável comparacao seja menor que zero, é realizada a troca de
			// posições dos ponteiros dos filmes nas posições de "aux" e "anterior".
			if (comparacao < 0) {
				
				Filme filmeTemp = anterior->filme;
				anterior->filme = aux->filme;
				aux->filme = filmeTemp;
			}
		}
	} // fim for
	
	printf("Os filmes foram ordenados pelos seus nomes!");
	
}

// Função para ordenar os filmes pelo código em ordem crescente
void ordenarFilmesPorCodigo(ListaFilmes **listaFilmes, int qtdFilmes) {
		
	for (int i = 0; i < qtdFilmes; i++) {
		
		ListaFilmes *aux = *listaFilmes;
	
		while (aux->prox != NULL) {
			
			ListaFilmes *anterior = aux;
			aux = aux->prox;
			
			if (aux->filme.codigo < anterior->filme.codigo) {
				
				Filme filmeTemp = anterior->filme;
				anterior->filme = aux->filme;
				aux->filme = filmeTemp;
			}
		}
	} // fim for
	
	printf("Os filmes foram ordenados pelos seus códigos!");
	
}

void selectSort(ListaFilmes **listaFilmes) {
	
	ListaFilmes *percorre = *listaFilmes; // ponteiro que irá percorrer a lista, recebe a posição do primeiro filme da lista
	
	while (percorre->prox != NULL) { // enquanto o prox do ponteiro "percorre" nao for nulo, ira repetir
		
		ListaFilmes *percorreProx = percorre->prox; // ponteiro que ira percorrer o segundo while
		ListaFilmes *menor = percorre; // ponteiro para guardar a posição do que contém o menor código
		
		while (percorreProx != NULL) { // enquanto o ponteiro "percorreProx" nao for nulo, ira repetir
			
			if (menor->filme.codigo > percorreProx->filme.codigo) {
				// se o codigo do filme da posição percorreProx for menor que
				// o codigo do filme do ponteiro que guarda o menor, o ponteiro menor
				// apontará para este
				menor = percorreProx;
			}
			
			percorreProx = percorreProx->prox;
		}
		
		if (percorre->filme.codigo > menor->filme.codigo) {
			// realiza a troca
			Filme filmeTemp = percorre->filme;
			percorre->filme = menor->filme;
			menor->filme = filmeTemp;
			
			
		}
		
		percorre = percorre->prox;
	}
	
}
