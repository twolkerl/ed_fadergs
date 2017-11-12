/*
	ESTRUTURA DE DADOS 2017/2
	Autores: Tiago Wolker Leite / Eduardo Moraes de Mello Alves / Bruno Vicente Alves
	Data: 05/11/2017
	�ltima atualiza��o: 11/11/2017
	Sistema EventoService.
*/

// -- BIBLIOTECAS --
#include <stdlib.h>
#include <locale.h>

#include "EventoStructs.h"
#include "Utilitarios.h"
#include "FuncoesTeste.h"

// -- CONSTANTES --


// -- PROT�TIPOS --
void cadastrarEvento(ListaEventos **listaEventos);
void listar(ListaEventos *listaEventos);

int menuPrincipal();
bool realizarCadastro(ListaEventos *novoNodo);

// -- PROGRAMA PRINCIPAL --
main() {
	
	setlocale(LC_ALL, "portuguese");
	
	ListaEventos *listaEventos = NULL, *filaReclamacoes = NULL, *pilhaComentarios = NULL, *eventosAtendidos = NULL;
	int opcao;
	
	do {
		
		switch (opcao = menuPrincipal()) {
			case 1:
				// Cadastrar evento
				cadastrarEvento(&listaEventos);
				break;
			case 2:
				// Encaminhar eventos
				break;
			case 3:
				// Apresentar eventos
				break;
			case 4:
				// Consumir eventos
				break;
			case 5:
				// Informa��es eventos
				break;
			case 100:
				// TESTE CADASTRAR 10
				cadDez(&filaReclamacoes, reclamacao);
				cadDez(&pilhaComentarios, comentario);
				break;
			case 101:
				// TESTE EXIBIR 10 FILA
				listar(filaReclamacoes);
				break;
			case 102:
				// TESTE EXIBIR 10 PILHA
				listar(pilhaComentarios);
				break;
			case 0:
				// Sair
				printf("Sistema encerrado...\n");
				break;
			default:
				// Inv�lido
				printf("Op��o inv�lida...\n");
		}
		
		system("pause");
		system("cls");
		
	} while (opcao != 0);
	
}

// -- FUN��ES --


/*
	Fun��o que mostra o menu principal e recebe a op��o digitada pelo usu�rio.
	
	return	=> N�mero da op��o digitada pelo usu�rio.
*/
int menuPrincipal() {
	/* TODO (Tiago_Wolker#1#): Verificar a possibilidade de usar a biblioteca 
                           stdarg.h e mover esta fun��o para a biblioteca 
                           Utilitarios.h */
    int opcao;
                           
	printf("\t\t===== [ EventoService ] =====");
	printf("\n[ 1 ] - Registrar Eventos");
	printf("\n[ 2 ] - Encaminhar Eventos");
	printf("\n[ 3 ] - Apresentar Eventos");
	printf("\n[ 4 ] - Consumir Eventos");
	printf("\n[ 5 ] - Informa��es Eventos");
	printf("\n[100] - TESTE - Cadastrar 10 filas e pilhas");
	printf("\n[101] - TESTE - Exibir a fila");
	printf("\n[102] - TESTE - Exibir a pilha");
	printf("\n[ 0 ] - Sair");
	printf("\n\nInforme a sua op��o: ");
	fflush(stdin);
	scanf("%i", &opcao);
	
	system("cls");
	
	return opcao;
	
}

/*
	Fun��o para cadastrar um novo evento na lista de eventos.
	
	**listaEventos	=> Primeiro novo da lista de eventos.
*/
void cadastrarEvento(ListaEventos **listaEventos) {
	
	ListaEventos *novoNodo = (ListaEventos*) malloc (sizeof (ListaEventos));
	
	if (novoNodo != NULL) {
		
		if (realizarCadastro(novoNodo)) {
			
			if (*listaEventos == NULL) {
				
				*listaEventos = novoNodo;
			} else {
				
				ListaEventos *auxiliar = *listaEventos;
				
				while (auxiliar->proximo != NULL) {
					auxiliar = auxiliar->proximo;
				}
				
				auxiliar->proximo = novoNodo;
			}
			
		} else {
			free(novoNodo);
		}
		
	} else {
		printf( "\nN�o h� mem�ria para cadastrar novo registro!\n" );
	}
	
}

/*
	Fun��o que l� do usu�rio os dados para cadastrar um novo nodo.
	
	return	=> Verdadeiro caso o usu�rio confirme o registro, caso contr�rio Falso.
*/
bool realizarCadastro(ListaEventos *novoNodo) {
	
	// Vari�vel est�tica para definir o n�mero do protocolo
	static int incrementador = 1;
	
	Evento novoEvento;
	novoEvento.protocolo = incrementador;
	
	printf("\t\t===== [ Cadastrar Evento ] =====");
	printf("\n[ 1 ] - Reclama��o");
	printf("\n[ 2 ] - Coment�rio");
	printf("\nInforme o tipo de mensagem: ");
	do {
		fflush(stdin);
		scanf("%i", &novoEvento.tipoMensagem);
		
		if (novoEvento.tipoMensagem != 1 && novoEvento.tipoMensagem != 2) {
			printf("Op��o inv�lida...\n");
		}
	} while (novoEvento.tipoMensagem != 1 && novoEvento.tipoMensagem != 2);
	
	printf("\nDigite a mensagem:\n");
	fflush(stdin);
	gets(novoEvento.mensagem);
	
	if (confirmar()) {
		
		novoNodo->evento = novoEvento;
		incrementador++;
		novoNodo->proximo = NULL;
		
		return true;
	}
	
	return false;
}


void listar(ListaEventos *listaEventos) {
	
	if (listaEventos != NULL) {
		
		printf("\n Protocolo: %i", listaEventos->evento.protocolo);
		printf("\n Tipo de mensagem: %s", tipoMensagemLabel(listaEventos->evento.tipoMensagem));
		printf("\n Mensagem: %s\n", listaEventos->evento.mensagem);
		
		listar(listaEventos->proximo);
		
	}
	
}
