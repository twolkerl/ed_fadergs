/*
	ESTRUTURA DE DADOS 2017/2
	Autores: Tiago Wolker Leite / Eduardo Moraes de Mello Alves / Bruno Vicente Alves
	Data: 15/11/2017
	�ltima atualiza��o: 15/11/2017
	Biblioteca que cont�m as fun��es de EventoService.
*/

// -- BIBLIOTECAS --
#include "EventoStructs.h"
#include "Utilitarios.h"


// -- PROT�TIPOS --
void cadastrarEvento(ListaEventos **listaEventos);
void listar(ListaEventos *listaEventos);
void menuConsumirEventos(ListaEventos **filaReclamacoes, ListaEventos **pilhaComentarios, ListaEventos **eventosAtendidos);
void consumirReclamacao(ListaEventos **filaReclamacoes, ListaEventos **eventosAtendidos);

int menuPrincipal();
bool realizarCadastro(ListaEventos *novoNodo);

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

/*
	Fun��o que exibe todos os eventos registrados na lista de eventos passada por par�metro.
	
	*listaEventos	=> Primeiro nodo da lista de eventos a ser exibida.
*/
void listar(ListaEventos *listaEventos) {
	
	if (listaEventos != NULL) {
		
		printf("\n Protocolo: %i", listaEventos->evento.protocolo);
		printf("\n Tipo de mensagem: %s", tipoMensagemLabel(listaEventos->evento.tipoMensagem));
		printf("\n Mensagem: %s\n", listaEventos->evento.mensagem);
		
		listar(listaEventos->proximo);
		
	}
	
}

/*
	Submenu que cont�m as op��es do tipo de evento a ser consumido.
	
	**filaReclamacoes	=> �ltimo evento que entrou na fila de reclama��es.
	**pilhaComentarios	=> �ltimo evento que entrou na pilha de coment�rios.
	**eventosAtendidos	=> �ltimo evento que foi consumido.
*/
void menuConsumirEventos(ListaEventos **filaReclamacoes, ListaEventos **pilhaComentarios, ListaEventos **eventosAtendidos) {
	
	if (*filaReclamacoes != NULL && *pilhaComentarios != NULL) {
		
	    int opcao;
	                           
		printf("\t\t===== [ Consumir Eventos ] =====");
		printf("\n[ 1 ] - Reclama��es");
		printf("\n[ 2 ] - Coment�rios");
		printf("\n[ 0 ] - Voltar");
		printf("\n\nInforme a sua op��o: ");
		scanf("%i", &opcao);
		
		switch(opcao) {
			
			case 1:
				// Consumir reclama��o da fila
				
				break;
			case 2:
				// Consumir coment�rio da pilha
				
				break;
			case 0:
				printf("Retornando ao menu principal...");
				break;
			default:
				printf("Op��o inv�lida! Retornando ao menu principal...");
			
		}
		
	} else {
		
		printf("N�o existem reclama��es ou coment�rios registrados no momento. "
				"Utilize a op��o [ 1 ] para registrar um novo evento e em seguida a "
				"op��o [ 2 ] para encaminhar os eventos registrados e ent�o "
				"tente novamente...\n");
	}
	
}


void consumirReclamacao(ListaEventos **filaReclamacoes, ListaEventos **eventosAtendidos) {
	
	if (*filaReclamacoes != NULL) {
		
		ListaEventos *anterior = *filaReclamacoes, *percorre = *filaReclamacoes->proximo;
		
		while(percorre != NULL) {
			
			
			
		}
		
	} else {
		
		printf("N�o existem reclama��es registradas no momento. "
				"Utilize a op��o [ 1 ] para registrar um novo evento e em seguida a "
				"op��o [ 2 ] para encaminhar os eventos registrados e ent�o "
				"tente novamente...\n");
	}
	
}
