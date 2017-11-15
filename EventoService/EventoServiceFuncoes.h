/*
	ESTRUTURA DE DADOS 2017/2
	Autores: Tiago Wolker Leite / Eduardo Moraes de Mello Alves / Bruno Vicente Alves
	Data: 15/11/2017
	Última atualização: 15/11/2017
	Biblioteca que contém as funções de EventoService.
*/

// -- BIBLIOTECAS --
#include "EventoStructs.h"
#include "Utilitarios.h"


// -- PROTÓTIPOS --
void cadastrarEvento(ListaEventos **listaEventos);
void listar(ListaEventos *listaEventos);
void menuConsumirEventos(ListaEventos **filaReclamacoes, ListaEventos **pilhaComentarios, ListaEventos **eventosAtendidos);
void consumirReclamacao(ListaEventos **filaReclamacoes, ListaEventos **eventosAtendidos);

int menuPrincipal();
bool realizarCadastro(ListaEventos *novoNodo);

// -- FUNÇÕES --

/*
	Função que mostra o menu principal e recebe a opção digitada pelo usuário.
	
	return	=> Número da opção digitada pelo usuário.
*/
int menuPrincipal() {
	/* TODO (Tiago_Wolker#1#): Verificar a possibilidade de usar a biblioteca 
                           stdarg.h e mover esta função para a biblioteca 
                           Utilitarios.h */
    int opcao;
                           
	printf("\t\t===== [ EventoService ] =====");
	printf("\n[ 1 ] - Registrar Eventos");
	printf("\n[ 2 ] - Encaminhar Eventos");
	printf("\n[ 3 ] - Apresentar Eventos");
	printf("\n[ 4 ] - Consumir Eventos");
	printf("\n[ 5 ] - Informações Eventos");
	printf("\n[100] - TESTE - Cadastrar 10 filas e pilhas");
	printf("\n[101] - TESTE - Exibir a fila");
	printf("\n[102] - TESTE - Exibir a pilha");
	printf("\n[ 0 ] - Sair");
	printf("\n\nInforme a sua opção: ");
	fflush(stdin);
	scanf("%i", &opcao);
	
	system("cls");
	
	return opcao;
	
}

/*
	Função para cadastrar um novo evento na lista de eventos.
	
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
		printf( "\nNão há memória para cadastrar novo registro!\n" );
	}
	
}

/*
	Função que lê do usuário os dados para cadastrar um novo nodo.
	
	return	=> Verdadeiro caso o usuário confirme o registro, caso contrário Falso.
*/
bool realizarCadastro(ListaEventos *novoNodo) {
	
	// Variável estática para definir o número do protocolo
	static int incrementador = 1;
	
	Evento novoEvento;
	novoEvento.protocolo = incrementador;
	
	printf("\t\t===== [ Cadastrar Evento ] =====");
	printf("\n[ 1 ] - Reclamação");
	printf("\n[ 2 ] - Comentário");
	printf("\nInforme o tipo de mensagem: ");
	do {
		fflush(stdin);
		scanf("%i", &novoEvento.tipoMensagem);
		
		if (novoEvento.tipoMensagem != 1 && novoEvento.tipoMensagem != 2) {
			printf("Opção inválida...\n");
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
	Função que exibe todos os eventos registrados na lista de eventos passada por parâmetro.
	
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
	Submenu que contém as opções do tipo de evento a ser consumido.
	
	**filaReclamacoes	=> Último evento que entrou na fila de reclamações.
	**pilhaComentarios	=> Último evento que entrou na pilha de comentários.
	**eventosAtendidos	=> Último evento que foi consumido.
*/
void menuConsumirEventos(ListaEventos **filaReclamacoes, ListaEventos **pilhaComentarios, ListaEventos **eventosAtendidos) {
	
	if (*filaReclamacoes != NULL && *pilhaComentarios != NULL) {
		
	    int opcao;
	                           
		printf("\t\t===== [ Consumir Eventos ] =====");
		printf("\n[ 1 ] - Reclamações");
		printf("\n[ 2 ] - Comentários");
		printf("\n[ 0 ] - Voltar");
		printf("\n\nInforme a sua opção: ");
		scanf("%i", &opcao);
		
		switch(opcao) {
			
			case 1:
				// Consumir reclamação da fila
				
				break;
			case 2:
				// Consumir comentário da pilha
				
				break;
			case 0:
				printf("Retornando ao menu principal...");
				break;
			default:
				printf("Opção inválida! Retornando ao menu principal...");
			
		}
		
	} else {
		
		printf("Não existem reclamações ou comentários registrados no momento. "
				"Utilize a opção [ 1 ] para registrar um novo evento e em seguida a "
				"opção [ 2 ] para encaminhar os eventos registrados e então "
				"tente novamente...\n");
	}
	
}


void consumirReclamacao(ListaEventos **filaReclamacoes, ListaEventos **eventosAtendidos) {
	
	if (*filaReclamacoes != NULL) {
		
		ListaEventos *anterior = *filaReclamacoes, *percorre = *filaReclamacoes->proximo;
		
		while(percorre != NULL) {
			
			
			
		}
		
	} else {
		
		printf("Não existem reclamações registradas no momento. "
				"Utilize a opção [ 1 ] para registrar um novo evento e em seguida a "
				"opção [ 2 ] para encaminhar os eventos registrados e então "
				"tente novamente...\n");
	}
	
}
