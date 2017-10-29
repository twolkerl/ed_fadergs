/**
 * ESTRUTURA DE DADOS
 * Autor: Tiago Wolker Leite
 * Data: 07/09/2017
 * Última atualização: 29/10/2017
 * Sistema para locadora de filmes - Exercício Listas Encadeadas
 */

// -- Bibliotecas
#include <stdlib.h>
#include <locale.h>

#include "basictwl.h"
#include "filme_funcoes.h"

// -- Protótipos
int mostrarMenuPrincipal();

bool realizarCadastro(ListaFilmes *listaFilmes);

void cadastrarFilme(ListaFilmes **listaFilmes);
void listarFilmes(ListaFilmes **listaFilmes);
void mostrarFilme(Filme filme);
void excluirFilme(ListaFilmes **listaFilmes);
void subMenuCadastro(ListaFilmes **listaFilmes, ListaFilmes **novoFilmeLista);
void buscarFilme(ListaFilmes **listaFilmes);
void buscarFilmePorNome(ListaFilmes **listaFilmes);

// -- Programa Principal
main() {
	
	// Declaração do idioma
	setlocale(LC_ALL, "portuguese");
	
	// Variáveis
	int op = 0;
	ListaFilmes *listaFilmes = NULL;
	
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
				printf ("Opção inválida");
		}
		
		printf("\n");
		
		system("pause");
		system("cls");
		
	} while (op != 0);
	
}

// -- Funções

// Função que mostra o menu principal, lê e retorna a opção do usuário
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
	printf("\nDigite a sua opção: ");
	scanf("%i", &op);
	
	return op;
	
}

// Função que realiza o cadastro de um novo filme.
// Se o cadastro for confirmado, retorna true, caso contrário retorna false.
bool realizarCadastro(ListaFilmes *listaFilmes) {
	
	// Variável estática para definir o código do filme
	static int incrementador = 1;

	Filme novoFilme;
	// Define ao código do novo filme o valor atual do incrementador
	novoFilme.codigo = incrementador;
	
	printf("====== [ CADASTRAR FILME ] ======");
	printf("\nInforme o título do filme: ");
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
		// Retorna verdadeiro após concluir o cadastro
		return true;
	}
	// Caso a confirmação retorne falso, o cadastro será cancelado e também retornará falso.
	return false;
	
}

// Função para incluir um novo filme no final da lista encadeada
void cadastrarFilme(ListaFilmes **listaFilmes) {

	// Aloca espaço em memória para o novo registro na lista
    ListaFilmes *novoFilmeLista = (ListaFilmes*) malloc (sizeof (ListaFilmes));
    
    // Verifica se foi possível alocar memória
    if (novoFilmeLista != NULL){
    	
    	// Caso haja memória para um novo registro, as seguintes linhas de código serão executadas:
		if (realizarCadastro(novoFilmeLista)) { // Chama a função de realizar o cadastro
		
			// Caso o cadastro retorne true, as seguintes linhas de código serão executadas:
			
			// Verifica se o ponteiro está apontando para nulo
			if(*listaFilmes == NULL) {
				// Caso o ponteiro esteja apontando para nulo, recebe o endereço do novo filme cadastrado
				*listaFilmes = novoFilmeLista;
			} else {
				// Exibe o submenu de cadastro
				subMenuCadastro(&*listaFilmes, &novoFilmeLista);
			}
		} else {
			
			// Caso o cadastro retorne false, aborta a operação
			return;
		}
	} else {
		printf( "\nNão há memória para cadastrar novo registro!" );
	}
	
}

// Função para listar os filmes cadastrados
void listarFilmes(ListaFilmes **listaFilmes) {
	
	if (*listaFilmes == NULL) {
		printf("\nNão há filmes cadastrados!");
	} else {
		
		ListaFilmes *aux = *listaFilmes;
		
		printf("====== [ LISTA DE FILMES ] ======");
		printf("\n------------------------------");
		// Percorre a lista, até o ponteiro auxiliar se tornar nulo
		while (aux != NULL) {
			
			// Chama função que imprime os dados do filme que está na posição atual da lista
			mostrarFilme(aux->filme);
			printf("\n------------------------------");
			// Define o ponteiro auxiliar para o próximo da lista
			aux = aux->prox;
		}
		
	}
	
}

// Função para imprimir um filme
void mostrarFilme(Filme filme) {
	
	printf("\nFilme: %s", filme.titulo);
	printf("\nCódigo: %i", filme.codigo);
	
}

// Função para excluir um filme da lista
void excluirFilme(ListaFilmes **listaFilmes) {
	
	if (*listaFilmes == NULL) {
		// Caso a lista esteja vazia:
		printf("\nNão há filmes cadastrados!");
	} else {
		
		int codPesquisa;
		printf("====== [ EXCLUIR FILME ] ======");
		printf("\nDigite o código do filme a ser excluido: ");
		scanf("%i", &codPesquisa);
		
		ListaFilmes *aux = *listaFilmes;
		
		if (aux->filme.codigo == codPesquisa) {
			// Caso seja o primeiro registro da lista
			
			if (aux->prox == NULL) {
				// Caso seja o único registro da lista, define o mesmo para nulo.
				*listaFilmes = NULL;
			} else {
				// Caso haja mais de uma registro na lista, define o ponteiro inicial para o próximo da lista
				// e libera a memória que havia sido alocada para o primeiro registro.
				*listaFilmes = aux->prox;
				free(aux);
				printf("\nRegistro excluído!");
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

					printf("\nRegistro excluído!");

					return;

				}

			}
		
		}
		
		if (aux->prox == NULL) {
			printf("\nNão foi encontrado filme para o código informado!");
		}
	}
}

// Submenu de cadastro, para escolher a posição onde será salvo o registro
void subMenuCadastro(ListaFilmes **listaFilmes, ListaFilmes **novoFilmeLista) {
	
	int opcao;
	
	do {
		system("cls");
		printf("\nEscolha o método para salvar: ");
		printf("\n[1] - Salvar no final da lista");
		printf("\n[2] - Salvar no início da lista");
		printf("\n\nDigite a sua opção: ");
		scanf("%i", &opcao);
		
		// Ponteiro auxiliar
		ListaFilmes *aux;
		
		switch (opcao) {
			case 1:
				// Salva no final da lista:	
				
				aux = *listaFilmes;
				
				// Percorre a lista encadeada para encontrar o último registro da lista
				while( aux->prox != NULL ) {
					// Enquanto não encontrar o ponteiro nulo, define o ponteiro auxiliar para o ponteiro que está na posição atual da lista
					aux = aux->prox;
				}
				// Ao encontrar o último registro da lista (ponteiro nulo), define seu ponteiro para o novo filme cadastrado
				aux->prox = *novoFilmeLista;
				//} 
				
				printf("\nOperação realizada com sucesso!\n");
				
				break;
		
			case 2:
				// Salvar no início da lista:
				
				// Faz com que o ponteiro do novo filme cadastrado aponte para o atual primeiro filme da lista
				aux = *novoFilmeLista;
				aux->prox = *listaFilmes;
				
				// Faz com que o ponteiro inicial da lista aponte para o novo filme cadastrado
				*listaFilmes = *novoFilmeLista;
				
				printf("\nOperação realizada com sucesso!\n");
				
				break;
				
			default:
				// Caso a opção digitada seja inválida:
				printf("\nOpção inválida! Tente novamente...\n");
				system("pause");
				system("cls");
		}
	} while (opcao < 0 || opcao > 2);

}

// Função para buscar um filme da lista
void buscarFilme(ListaFilmes **listaFilmes) {
	
	if (*listaFilmes == NULL) {
		// Caso a lista esteja vazia:
		printf("\nNão há filmes cadastrados!");
	} else {
		
		int codPesquisa;
		printf("====== [ BUSCAR FILME ] ======");
		printf("\nDigite o código do filme: ");
		scanf("%i", &codPesquisa);
		
		ListaFilmes *aux = *listaFilmes;
		
		
		while (aux != NULL) { // Enquanto aux for diferente de nulo:

			// Verifica se o código informado corresponde ao código do filme atual da lista
			if(aux->filme.codigo == codPesquisa) {
				// Chama a função que imprime os dados do filme:
				printf("\n------------------------------");
				mostrarFilme(aux->filme);
				printf("\n------------------------------");
				// Retorna para o menu principal
				return;
			}
			// aux recebe o próximo filme da lista
			aux = aux->prox;

		}
		
		if (aux->prox == NULL) {
			// Caso não seja encontrado registro:
			printf("\nNão foi encontrado filme para o código informado!");
		}
	}
}

void buscarFilmePorNome(ListaFilmes **listaFilmes) {
	
	if (*listaFilmes == NULL) {
		// Caso a lista esteja vazia:
		printf("\nNão há filmes cadastrados!");
	} else {
		
		char nomePesquisa[50];
		printf("====== [ BUSCAR FILME ] ======");
		printf("\nDigite o código do filme: ");
		fflush(stdin);
		gets(nomePesquisa);
		
		ListaFilmes *aux = *listaFilmes;
		
		
		while (aux->prox != NULL) { // Enquanto aux for diferente de nulo:

			// Verifica se o nome informado corresponde ao nome do filme atual da lista
			if(strcmpi(aux->filme.titulo, nomePesquisa) == 0) {
				// Chama a função que imprime os dados do filme:
				printf("\n------------------------------");
				mostrarFilme(aux->filme);
				printf("\n------------------------------");
				// Retorna para o menu principal
				return;
			}
			// aux recebe o próximo filme da lista
			aux = aux->prox;

		}
		
		/* TODO (Tiago#1#): FIXME: Possível melhorar este método */
		if (aux->prox == NULL && strcmpi(aux->filme.titulo, nomePesquisa) == 0) {
			// Chama a função que imprime os dados do filme:
			printf("\n------------------------------");
			mostrarFilme(aux->filme);
			printf("\n------------------------------");
			// Retorna para o menu principal
			return;
		} else {
			// Caso não seja encontrado registro:
			printf("\nNão foi encontrado filme para o código informado!");
		}
	}
	
}
