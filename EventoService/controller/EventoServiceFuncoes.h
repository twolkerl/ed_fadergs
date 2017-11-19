/*
	ESTRUTURA DE DADOS 2017/2
	Autores: Tiago Wolker Leite / Eduardo Moraes de Mello Alves / Bruno Vicente Alves
	Data: 15/11/2017
	�ltima atualiza��o: 19/11/2017
	Biblioteca que cont�m as fun��es de EventoService.
*/

// -- BIBLIOTECAS --
#include "../model/EventoStructs.h"
#include "Utilitarios.h"


// -- PROT�TIPOS --
void cadastrarEvento(ListaEventos **listaEventos);
void listar(ListaEventos *listaEventos);
void exibirEvento(Evento evento);
void menuConsumirEventos(ListaEventos **filaReclamacoes, ListaEventos **pilhaComentarios, ListaEventos **eventosAtendidos);
void consumirReclamacao(ListaEventos **filaReclamacoes, ListaEventos **eventosAtendidos);
void consumirComentario(ListaEventos **pilhaComentarios, ListaEventos **eventosAtendidos);
void receberAtendido(ListaEventos **atendido, ListaEventos **eventosAtendidos);
void encaminharEventos(ListaEventos **listaEventos, ListaEventos **filaReclamacoes, ListaEventos **pilhaComentarios);
void apresentarEvento(ListaEventos *filaReclamacoes, ListaEventos *pilhaComentarios);

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
	printf("\n[ 3 ] - Apresentar Evento");
	printf("\n[ 4 ] - Consumir Evento");
	printf("\n[ 5 ] - Informa��es Eventos");
	printf("\n[100] - TESTE - Cadastrar 10 filas e pilhas");
	printf("\n[101] - TESTE - Exibir a fila");
	printf("\n[102] - TESTE - Exibir a pilha");
	printf("\n[103] - TESTE - Exibir atendidos");
	printf("\n[ 0 ] - Sair");
	printf("\n\nInforme a sua op��o: ");
	fflush(stdin);
	scanf("%i", &opcao);
	
	system("cls");
	
	return opcao;
	
}

/*
	Fun��o para cadastrar um novo evento na lista de eventos.
	
	**listaEventos	=> Primeiro nodo da lista de eventos.
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
	novoEvento.statusEvento = NAO_ATENDIDO;
	novoEvento.segCadastro = time(NULL);
	
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
		
		exibirEvento(listaEventos->evento);
		listar(listaEventos->proximo);
	}
}

/*
	Fun��o que exibe os dados do evento passado por par�metro.
	
	evento	=> Evento a ser exibido em tela.
*/
void exibirEvento(Evento evento) {
	
	printf("\n Protocolo: %i", evento.protocolo);
	printf("\n Status: %s", statusEventoLabel(evento.statusEvento));
	if (evento.statusEvento == ATENDIDO) {
		printf("\n Tempo de aguardo para atendimento: %i segundos", evento.tempoAguardo);
	}
	printf("\n Tipo de mensagem: %s", tipoMensagemLabel(evento.tipoMensagem));
	printf("\n Mensagem: %s\n", evento.mensagem);
}

/*
	Submenu que cont�m as op��es do tipo de evento a ser consumido.
	
	**filaReclamacoes	=> �ltimo evento que entrou na fila de reclama��es.
	**pilhaComentarios	=> �ltimo evento que entrou na pilha de coment�rios.
	**eventosAtendidos	=> �ltimo evento que foi atendido.
*/
void menuConsumirEventos(ListaEventos **filaReclamacoes, ListaEventos **pilhaComentarios, ListaEventos **eventosAtendidos) {
	
	if (*filaReclamacoes != NULL || *pilhaComentarios != NULL) {
		
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
				consumirReclamacao(&*filaReclamacoes, &*eventosAtendidos);
				break;
			case 2:
				// Consumir coment�rio da pilha
				consumirComentario(&*pilhaComentarios, &*eventosAtendidos);
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

/*
	Fun��o para atender a primeira reclama��o da fila.
	
	**filaReclamacoes	=> �ltimo evento que entrou na fila de reclama��es.
	**eventosAtendidos	=> �ltimo evento que foi atendido.
*/
void consumirReclamacao(ListaEventos **filaReclamacoes, ListaEventos **eventosAtendidos) {
	
	if (*filaReclamacoes != NULL) {
		/* TODO (Tiago_Wolker#2#): Verificar a possibilidade de tornar esta fun��o 
		                           recursiva. */
		
		ListaEventos *anterior = *filaReclamacoes, *percorre = anterior->proximo;
		
		if (percorre != NULL) {
			
			while (percorre->proximo != NULL) {
				
				anterior = percorre;
				percorre = percorre->proximo;
			}
			
			printf("\t\t==== Deseja consumir este evento? ====\n");
			exibirEvento(percorre->evento);
			if (confirmar()) {
				// Caso digite a op��o SIM
				percorre->evento.statusEvento = ATENDIDO;
				percorre->evento.tempoAguardo = time(NULL) - percorre->evento.segCadastro;
				receberAtendido(&percorre, &*eventosAtendidos);
				anterior->proximo = NULL;
				
			} else {
				// Caso digite a op��o N�O
				return;
			}
		} else {
			// Caso a fila contenha apenas 1 registro:
			printf("\t\t==== Deseja consumir este evento? ====\n");
			exibirEvento(anterior->evento);
			
			if (confirmar()) {
				// Caso digite a op��o SIM
				receberAtendido(&anterior, &*eventosAtendidos);
				*filaReclamacoes = NULL;
				
			} else {
				// Caso digite a op��o N�O
				return;
			}
		}
		
	} else {
		
		printf("N�o existem reclama��es registradas no momento. "
				"Utilize a op��o [ 1 ] para registrar um novo evento e em seguida a "
				"op��o [ 2 ] para encaminhar os eventos registrados e ent�o "
				"tente novamente...\n");
	}
	
}

/*
	Fun��o para consumir o coment�rio que est� no topo da pilha.
	
	**pilhaComentarios	=> �ltimo evento que entrou na pilha de coment�rios.
	**eventosAtendidos	=> �ltimo evento que foi atendido.
*/
void consumirComentario(ListaEventos **pilhaComentarios, ListaEventos **eventosAtendidos) {
	
	if (*pilhaComentarios != NULL) {
		
		ListaEventos *consumido = *pilhaComentarios;
		
		printf("\t\t==== Deseja consumir este evento? ====\n");
		exibirEvento(consumido->evento);
		if (confirmar()) {
			// Caso digite a op��o SIM
			/* TODO (Tiago_Wolker#1#): CORRIGIR => N�o est� definindo o status e o 
			                           tempo de aguardo do �ltimo evento da lista */
			consumido->evento.statusEvento = ATENDIDO;
			consumido->evento.tempoAguardo = time(NULL) - consumido->evento.segCadastro;
			*pilhaComentarios = (*pilhaComentarios)->proximo;
			receberAtendido(&consumido, &*eventosAtendidos);
		} else {
			// Caso digite a op��o N�O
			return;
		}
		
	} else {
		
		printf("N�o existem coment�rios registrados no momento. "
				"Utilize a op��o [ 1 ] para registrar um novo evento e em seguida a "
				"op��o [ 2 ] para encaminhar os eventos registrados e ent�o "
				"tente novamente...\n");
	}
	
}

/*
	Fun��o que adiciona um evento na lista de eventos atendidos.
	
	**atendido			=> Evento a entrar na lista.
	**eventosAtendidos	=> �ltimo evento que foi atendido.
*/
void receberAtendido(ListaEventos **atendido, ListaEventos **eventosAtendidos) {
	
	(*atendido)->proximo = *eventosAtendidos;
	(*eventosAtendidos) = *atendido;
}

/*
	Fun��o que encaminha os eventos para sua fila ou pilha com base no tipo de mensagem que foi informada.
	
	**listaEventos		=> �ltimo evento que entrou na lista de eventos principal.
	**filaReclamacoes	=> �ltimo evento que entrou na fila de reclama��es.
	**pilhaComentarios	=> �ltimo evento que entrou na pilha de coment�rios.
*/
void encaminharEventos(ListaEventos **listaEventos, ListaEventos **filaReclamacoes, ListaEventos **pilhaComentarios) {
	
	if (*listaEventos != NULL) {

		while (*listaEventos != NULL) {
			ListaEventos *auxiliar = *listaEventos;
			*listaEventos = (*listaEventos)->proximo;
			
			switch (auxiliar->evento.tipoMensagem) {
				case RECLAMACAO:
					auxiliar->proximo = *filaReclamacoes;
					*filaReclamacoes = auxiliar;
					break;
					
				case COMENTARIO:
				default:
					auxiliar->proximo = *pilhaComentarios;
					*pilhaComentarios = auxiliar;
			}
		}
		
		printf("Eventos encaminhados com sucesso!\n");
	} else {
		
		printf("N�o existem eventos registrados no momento. Utilize a op��o "
				"[ 1 ] para registrar um novo evento e ent�o tente novamente...\n");
	}
	
}

/*
	Fun��o para buscar e apresentar em tela as informa��es de um evento.
	
	*filaReclamacoes	=> �ltimo evento que entrou na fila de reclama��es.
	*pilhaComentarios	=> �ltimo evento que entrou na pilha de coment�rios.
*/
void apresentarEvento(ListaEventos *filaReclamacoes, ListaEventos *pilhaComentarios){
	
	int busca;
	bool achou = false;

	if (filaReclamacoes != NULL || pilhaComentarios != NULL){
		
		ListaEventos *aux = filaReclamacoes;
		
		printf("Digite o protocolo a ser buscado: ");
		fflush(stdin);
		scanf("%i", &busca);
		
		while(aux != NULL && !achou){
			
			if(aux->evento.protocolo == busca){
				exibirEvento(aux->evento);
				achou = true;
			}
			aux = aux->proximo;
		}
		
		aux = pilhaComentarios;
		
		while(aux != NULL && !achou){
			
			if(aux->evento.protocolo == busca){
				exibirEvento(aux->evento);
				achou = true;
			}
			aux = aux->proximo;
		}
		
		if(!achou) {
			printf("Protocolo n�o encontado!");
		}
		
	} else {
		
		printf("N�o existem reclama��es ou coment�rios registrados no momento. "
				"Utilize a op��o [ 1 ] para registrar um novo evento e em seguida a "
				"op��o [ 2 ] para encaminhar os eventos registrados e ent�o "
				"tente novamente...\n");
	}
	
}
