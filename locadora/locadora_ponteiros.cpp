/**
 * ESTRUTURA DE DADOS
 * Autor: Tiago Wolker Leite
 * Data: 07/09/2017
 * �ltima atualiza��o: 21/10/2017
 * Sistema para locadora de filmes - Listas Encadeadas
 */

// -- Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "basictwl.h"

// -- Constantes

// -- Estruturas
typedef struct {
	int codigo;
	char titulo[50];
} Filme;

typedef struct ListaFilmes {
	Filme filme;
	struct ListaFilmes *prox;
} ListaFilmes;

// -- Prot�tipos
int mostrarMenuPrincipal();

bool realizarCadastro(ListaFilmes *listaFilmes);

void cadastrarFilme(ListaFilmes **listaFilmes);
void listarFilmes(ListaFilmes **listaFilmes);
void mostrarFilme(Filme filme);
void excluirFilme(ListaFilmes **listaFilmes);
void subMenuCadastro(ListaFilmes **listaFilmes, ListaFilmes **novoFilmeLista);
void buscarFilme(ListaFilmes **listaFilmes);
int contarFilmes(ListaFilmes **listaFilmes);
void subMenuOrdenar(ListaFilmes **listaFilmes);
void ordenarFilmesPorNome(ListaFilmes **listaFilmes, int qtdFilmes);
void ordenarFilmesPorCodigo(ListaFilmes **listaFilmes, int qtdFilmes);
void buscarFilmePorNome(ListaFilmes **listaFilmes);

void selectSort(ListaFilmes **listaFilmes);

// -- Programa Principal
main() {
	
	// Declara��o do idioma
	setlocale(LC_ALL, "portuguese");
	
	// Vari�veis
	int op = 0;
	ListaFilmes *listaFilmes = NULL;
	//listaFilmes->incrementador = 1;
	
	// Menu
	do {
		
		op = mostrarMenuPrincipal();
		system("cls");
		
		switch (op) {
			case 1:
				// Cadastrar filme
				cadastrarFilme(&listaFilmes);
				break;
			case 2:
				// Listar filmes
				listarFilmes(&listaFilmes);
				break;
			case 3:
				// Excluir um filme
				excluirFilme(&listaFilmes);
				break;
			case 4:
				// Buscar um filme
				buscarFilme(&listaFilmes);
				break;
			case 5:
				// Submenu ordenar
				subMenuOrdenar(&listaFilmes);
				break;
			case 6:
				// Buscar um filme por nome
				buscarFilmePorNome(&listaFilmes);
				break;
			/*
			case #:
				// Modelo
				break;
			*/
			case 0:
				// Sair
				printf("Sistema encerrado!");
				break;
			default:
				printf ("Op��o inv�lida");
		}
		
		printf("\n");
		
		system("pause");
		system("cls");
		
	} while (op != 0);
	
}

// -- Fun��es

// Fun��o que mostra o menu principal, l� e retorna a op��o do usu�rio
int mostrarMenuPrincipal() {
	
	int op = 0;
	printf("====== [ MENU PRINCIPAL ] ======");
	printf("\n");
	printf("\n[1]  - Cadastrar filme");
	printf("\n[2]  - Listar filmes");
	printf("\n[3]  - Excluir filme");
	printf("\n[4]  - Buscar filme");
	printf("\n[5]  - Ordenar filmes");
	printf("\n[6]  - Buscar filme por nome");
	printf("\n[0]  - Sair");
	/*
	printf("\n[#]  - Modelo");
	*/
	printf("\n");
	printf("\nDigite a sua op��o: ");
	scanf("%i", &op);
	
	return op;
	
}

// Fun��o que realiza o cadastro de um novo filme.
// Se o cadastro for confirmado, retorna true, caso contr�rio retorna false.
bool realizarCadastro(ListaFilmes *listaFilmes) {
	
	// Vari�vel est�tica para definir o c�digo do filme
	static int incrementador = 1;

	Filme novoFilme;
	// Define ao c�digo do novo filme o valor atual do incrementador
	novoFilme.codigo = incrementador;
	
	printf("====== [ CADASTRAR FILME ] ======");
	printf("\nInforme o t�tulo do filme: ");
	fflush(stdin);
	gets(novoFilme.titulo);

	/*
    printf("\nModelo: ");
    fflush(stdin);
    scanf("%tipo", &listaFilmes->modelo.dados);
	*/
	
	if (confirmar()) {
		// Cadastra o novo filme na lista
		listaFilmes->filme = novoFilme;
		// Adiciona 1 ao incrementador
		incrementador++;
		// Define o ponteiro prox para nulo
		listaFilmes->prox = NULL;
		// Retorna verdadeiro ap�s concluir o cadastro
		return true;
	}
	// Caso a confirma��o retorne falso, o cadastro ser� cancelado e tamb�m retornar� falso.
	return false;
	
}

// Fun��o para incluir um novo filme no final da lista encadeada
void cadastrarFilme(ListaFilmes **listaFilmes) {

	// Aloca espa�o em mem�ria para o novo registro na lista
    ListaFilmes *novoFilmeLista = (ListaFilmes*) malloc (sizeof (ListaFilmes));
    
    // Verifica se foi poss�vel alocar mem�ria
    if (novoFilmeLista != NULL){
    	
    	// Caso haja mem�ria para um novo registro, as seguintes linhas de c�digo ser�o executadas:
		if (realizarCadastro(novoFilmeLista)) { // Chama a fun��o de realizar o cadastro
		
			// Caso o cadastro retorne true, as seguintes linhas de c�digo ser�o executadas:
			
			
			// Verifica se o ponteiro est� apontando para nulo
			if(*listaFilmes == NULL) {
				// Caso o ponteiro esteja apontando para nulo, recebe o endere�o do novo filme cadastrado
				*listaFilmes = novoFilmeLista;
			} else {
				// Exibe o submenu de cadastro
				subMenuCadastro(&*listaFilmes, &novoFilmeLista);
			}
		} else {
			
			// Caso o cadastro retorne false, aborta a opera��o
			return;
		}
	} else {
		printf( "\nN�o h� mem�ria para cadastrar novo registro!" );
	}
	
}

// Fun��o para listar os filmes cadastrados
void listarFilmes(ListaFilmes **listaFilmes) {
	
	if (*listaFilmes == NULL) {
		printf("\nN�o h� filmes cadastrados!");
	} else {
		
		ListaFilmes *aux = *listaFilmes;
		
		printf("====== [ LISTA DE FILMES ] ======");
		printf("\n------------------------------");
		// Percorre a lista, at� o ponteiro auxiliar se tornar nulo
		while (aux != NULL) {
			
			// Chama fun��o que imprime os dados do filme que est� na posi��o atual da lista
			mostrarFilme(aux->filme);
			printf("\n------------------------------");
			// Define o ponteiro auxiliar para o pr�ximo da lista
			aux = aux->prox;
		}
		
	}
	
}

// Fun��o para imprimir um filme
void mostrarFilme(Filme filme) {
	
	printf("\nFilme: %s", filme.titulo);
	printf("\nC�digo: %i", filme.codigo);
	
}

// Fun��o para excluir um filme da lista
void excluirFilme(ListaFilmes **listaFilmes) {
	
	if (*listaFilmes == NULL) {
		// Caso a lista esteja vazia:
		printf("\nN�o h� filmes cadastrados!");
	} else {
		
		int codPesquisa;
		printf("====== [ EXCLUIR FILME ] ======");
		printf("\nDigite o c�digo do filme a ser excluido: ");
		scanf("%i", &codPesquisa);
		
		ListaFilmes *aux = *listaFilmes;
		
		if (aux->filme.codigo == codPesquisa) {
			// Caso seja o primeiro registro da lista
			
			if (aux->prox == NULL) {
				// Caso seja o �nico registro da lista, define o mesmo para nulo.
				*listaFilmes = NULL;
			} else {
				// Caso haja mais de uma registro na lista, define o ponteiro inicial para o pr�ximo da lista
				// e libera a mem�ria que havia sido alocada para o primeiro registro.
				*listaFilmes = aux->prox;
				free(aux);
				printf("\nRegistro exclu�do!");
			}
			// Retorna para o menu principal
			return;
		} else {
		
			while (aux->prox != NULL) {

				ListaFilmes *anterior = aux;
				aux = aux->prox;

				if(aux->filme.codigo == codPesquisa) {

					anterior->prox = aux->prox;

					free(aux);

					printf("\nRegistro exclu�do!");

					return;

				}

			}
		
		}
		
		if (aux->prox == NULL) {
			printf("\nN�o foi encontrado filme para o c�digo informado!");
		}
	}
}

// Submenu de cadastro, para escolher a posi��o onde ser� salvo o registro
void subMenuCadastro(ListaFilmes **listaFilmes, ListaFilmes **novoFilmeLista) {
	
	int opcao;
	
	do {
		system("cls");
		printf("\nEscolha o m�todo para salvar: ");
		printf("\n[1] - Salvar no final da lista");
		printf("\n[2] - Salvar no in�cio da lista");
		printf("\n\nDigite a sua op��o: ");
		scanf("%i", &opcao);
		
		// Ponteiro auxiliar
		ListaFilmes *aux;
		
		switch (opcao) {
			case 1:
				// Salva no final da lista:	
				
				aux = *listaFilmes;
				
				// Percorre a lista encadeada para encontrar o �ltimo registro da lista
				while( aux->prox != NULL ) {
					// Enquanto n�o encontrar o ponteiro nulo, define o ponteiro auxiliar para o ponteiro que est� na posi��o atual da lista
					aux = aux->prox;
				}
				// Ao encontrar o �ltimo registro da lista (ponteiro nulo), define seu ponteiro para o novo filme cadastrado
				aux->prox = *novoFilmeLista;
				//} 
				
				printf("\nOpera��o realizada com sucesso!\n");
				
				break;
		
			case 2:
				// Salvar no in�cio da lista:
				
				// Faz com que o ponteiro do novo filme cadastrado aponte para o atual primeiro filme da lista
				aux = *novoFilmeLista;
				aux->prox = *listaFilmes;
				
				// Faz com que o ponteiro inicial da lista aponte para o novo filme cadastrado
				*listaFilmes = *novoFilmeLista;
				
				printf("\nOpera��o realizada com sucesso!\n");
				
				break;
				
			default:
				// Caso a op��o digitada seja inv�lida:
				printf("\nOp��o inv�lida! Tente novamente...\n");
				system("pause");
				system("cls");
		}
	} while (opcao < 0 || opcao > 2);

}

// Fun��o para buscar um filme da lista
void buscarFilme(ListaFilmes **listaFilmes) {
	
	if (*listaFilmes == NULL) {
		// Caso a lista esteja vazia:
		printf("\nN�o h� filmes cadastrados!");
	} else {
		
		int codPesquisa;
		printf("====== [ BUSCAR FILME ] ======");
		printf("\nDigite o c�digo do filme: ");
		scanf("%i", &codPesquisa);
		
		ListaFilmes *aux = *listaFilmes;
		
		
		while (aux != NULL) { // Enquanto aux for diferente de nulo:

			// Verifica se o c�digo informado corresponde ao c�digo do filme atual da lista
			if(aux->filme.codigo == codPesquisa) {
				// Chama a fun��o que imprime os dados do filme:
				printf("\n------------------------------");
				mostrarFilme(aux->filme);
				printf("\n------------------------------");
				// Retorna para o menu principal
				return;
			}
			// aux recebe o pr�ximo filme da lista
			aux = aux->prox;

		}
		
		if (aux->prox == NULL) {
			// Caso n�o seja encontrado registro:
			printf("\nN�o foi encontrado filme para o c�digo informado!");
		}
	}
}

// Fun��o para contar e retornar a quantidade de filmes cadastrados
int contarFilmes(ListaFilmes **listaFilmes){
	
	int contador = 0;
	
	ListaFilmes *aux = *listaFilmes;
	
	// Enquanto aux for diferente de nulo:
	while (aux != NULL) {
		// Incrementa o contador a cada itera��o
		contador++;
		aux = aux->prox;
	}
	
	return contador;
}

// Submenu para escolher o tipo de ordena��o
void subMenuOrdenar(ListaFilmes **listaFilmes) {
	
	int qtdFilmes = contarFilmes(&*listaFilmes);
	
	// Verifica se h� apenas um ou nenhum registro
	if (qtdFilmes < 2) {
		// Caso exista apenas um ou nenhum registro:
		printf("\nN�o � poss�vel ordenar filmes pois existe apenas um ou nenhum registro!");
	} else {
	
		int op = 0;
		printf("====== [ ORDENAR FILMES ] ======");
		printf("\n");
		printf("\n[1]  - Ordenar por nome");
		printf("\n[2]  - Ordenar por c�digo (Bubble Sort)");
		printf("\n[3]  - Ordenar por c�digo (Select Sort)");
		printf("\n[0]  - Voltar");
		/*
		printf("\n[#]  - Modelo");
		*/
		printf("\n");
		printf("\nDigite a sua op��o para ordenar ou qualquer n�mero diferente para retornar: ");
		scanf("%i", &op);
		
		switch(op) {
			
			case 1:
				// Ordenar por nome:
				ordenarFilmesPorNome(&*listaFilmes, qtdFilmes);
				break;
			case 2:
				// Ordenar por c�digo:
				ordenarFilmesPorCodigo(&*listaFilmes, qtdFilmes);
				break;
			case 3:
				// Ordenar por c�digo (select sort):
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

// Teste altera��o
// Fun��o para ordenar os filmes pelo nome em ordem alfab�tica
void ordenarFilmesPorNome(ListaFilmes **listaFilmes, int qtdFilmes) {
		
	for (int i = 0; i < qtdFilmes; i++) {
		
		ListaFilmes *aux = *listaFilmes;
	
		while (aux->prox != NULL) {
			
			ListaFilmes *anterior = aux;
			aux = aux->prox;
			// Realiza a compara��o do nome dos filmes. Se o nome do filme da
			// posi��o de "aux" for "menor" que o nome do filme da posi��o de
			// "anterior", ser� atribu�do -1 para a vari�vel comp.
			int comparacao = strcmpi(aux->filme.titulo, anterior->filme.titulo);
			
			// Caso a vari�vel comparacao seja menor que zero, � realizada a troca de
			// posi��es dos ponteiros dos filmes nas posi��es de "aux" e "anterior".
			if (comparacao < 0) {
				
				Filme filmeTemp = anterior->filme;
				anterior->filme = aux->filme;
				aux->filme = filmeTemp;
			}
		}
	} // fim for
	
	printf("Os filmes foram ordenados pelos seus nomes!");
	
}

// Fun��o para ordenar os filmes pelo c�digo em ordem crescente
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
	
	printf("Os filmes foram ordenados pelos seus c�digos!");
	
}

void buscarFilmePorNome(ListaFilmes **listaFilmes) {
	
	if (*listaFilmes == NULL) {
		// Caso a lista esteja vazia:
		printf("\nN�o h� filmes cadastrados!");
	} else {
		
		char nomePesquisa[50];
		printf("====== [ BUSCAR FILME ] ======");
		printf("\nDigite o c�digo do filme: ");
		fflush(stdin);
		gets(nomePesquisa);
		
		ListaFilmes *aux = *listaFilmes;
		
		
		while (aux->prox != NULL) { // Enquanto aux for diferente de nulo:

			// Verifica se o nome informado corresponde ao nome do filme atual da lista
			if(strcmpi(aux->filme.titulo, nomePesquisa) == 0) {
				// Chama a fun��o que imprime os dados do filme:
				printf("\n------------------------------");
				mostrarFilme(aux->filme);
				printf("\n------------------------------");
				// Retorna para o menu principal
				return;
			}
			// aux recebe o pr�ximo filme da lista
			aux = aux->prox;

		}
		
		/* TODO (Tiago#1#): FIXME: Poss�vel melhorar este m�todo */
		if (aux->prox == NULL && strcmpi(aux->filme.titulo, nomePesquisa) == 0) {
			// Chama a fun��o que imprime os dados do filme:
			printf("\n------------------------------");
			mostrarFilme(aux->filme);
			printf("\n------------------------------");
			// Retorna para o menu principal
			return;
		} else {
			// Caso n�o seja encontrado registro:
			printf("\nN�o foi encontrado filme para o c�digo informado!");
		}
	}
	
}

void selectSort(ListaFilmes **listaFilmes) {
	
	ListaFilmes *percorre = *listaFilmes; // ponteiro que ir� percorrer a lista, recebe a posi��o do primeiro filme da lista
	
	while (percorre->prox != NULL) { // enquanto o prox do ponteiro "percorre" nao for nulo, ira repetir
		
		ListaFilmes *percorreProx = percorre->prox; // ponteiro que ira percorrer o segundo while
		ListaFilmes *menor = percorre; // ponteiro para guardar a posi��o do que cont�m o menor c�digo
		
		while (percorreProx != NULL) { // enquanto o ponteiro "percorreProx" nao for nulo, ira repetir
			
			if (menor->filme.codigo > percorreProx->filme.codigo) {
				// se o codigo do filme da posi��o percorreProx for menor que
				// o codigo do filme do ponteiro que guarda o menor, o ponteiro menor
				// apontar� para este
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
