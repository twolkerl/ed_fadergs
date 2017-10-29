/**
 * ESTRUTURA DE DADOS
 * Autor: Tiago Wolker Leite
 * Data: 07/09/2017
 * �ltima atualiza��o: 29/10/2017
 * Sistema para locadora de filmes - Exerc�cio Listas Encadeadas
 */

// -- Bibliotecas
#include <stdlib.h>
#include <locale.h>

#include "basictwl.h"
#include "filme_funcoes.h"

// -- Prot�tipos
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
	
	// Declara��o do idioma
	setlocale(LC_ALL, "portuguese");
	
	// Vari�veis
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
