/*
	ESTRUTURA DE DADOS 2017/2
	Autores: Tiago Wolker Leite / Eduardo Moraes de Mello Alves / Bruno Vicente Alves
	Data: 15/11/2017
	Última atualização: 19/11/2017
	Biblioteca que contém as funções de EventoService.
*/

// -- BIBLIOTECAS --
#include "../model/EventoStructs.h"
#include "Utilitarios.h"


// -- PROTÓTIPOS --
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
	printf("\n[ 3 ] - Apresentar Evento");
	printf("\n[ 4 ] - Consumir Evento");
	printf("\n[ 5 ] - Informações Eventos");
	printf("\n[100] - TESTE - Cadastrar 10 filas e pilhas");
	printf("\n[101] - TESTE - Exibir a fila");
	printf("\n[102] - TESTE - Exibir a pilha");
	printf("\n[103] - TESTE - Exibir atendidos");
	printf("\n[ 0 ] - Sair");
	printf("\n\nInforme a sua opção: ");
	fflush(stdin);
	scanf("%i", &opcao);
	
	system("cls");
	
	return opcao;
	
}

/*
	Função para cadastrar um novo evento na lista de eventos.
	
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
	novoEvento.statusEvento = NAO_ATENDIDO;
	novoEvento.segCadastro = time(NULL);
	
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
		
		exibirEvento(listaEventos->evento);
		listar(listaEventos->proximo);
	}
}

/*
	Função que exibe os dados do evento passado por parâmetro.
	
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
	Submenu que contém as opções do tipo de evento a ser consumido.
	
	**filaReclamacoes	=> Último evento que entrou na fila de reclamações.
	**pilhaComentarios	=> Último evento que entrou na pilha de comentários.
	**eventosAtendidos	=> Último evento que foi atendido.
*/
void menuConsumirEventos(ListaEventos **filaReclamacoes, ListaEventos **pilhaComentarios, ListaEventos **eventosAtendidos) {
	
	if (*filaReclamacoes != NULL || *pilhaComentarios != NULL) {
		
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
				consumirReclamacao(&*filaReclamacoes, &*eventosAtendidos);
				break;
			case 2:
				// Consumir comentário da pilha
				consumirComentario(&*pilhaComentarios, &*eventosAtendidos);
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

/*
	Função para atender a primeira reclamação da fila.
	
	**filaReclamacoes	=> Último evento que entrou na fila de reclamações.
	**eventosAtendidos	=> Último evento que foi atendido.
*/
void consumirReclamacao(ListaEventos **filaReclamacoes, ListaEventos **eventosAtendidos) {
	
	if (*filaReclamacoes != NULL) {
		/* TODO (Tiago_Wolker#2#): Verificar a possibilidade de tornar esta função 
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
				// Caso digite a opção SIM
				percorre->evento.statusEvento = ATENDIDO;
				percorre->evento.tempoAguardo = time(NULL) - percorre->evento.segCadastro;
				receberAtendido(&percorre, &*eventosAtendidos);
				anterior->proximo = NULL;
				
			} else {
				// Caso digite a opção NÃO
				return;
			}
		} else {
			// Caso a fila contenha apenas 1 registro:
			printf("\t\t==== Deseja consumir este evento? ====\n");
			exibirEvento(anterior->evento);
			
			if (confirmar()) {
				// Caso digite a opção SIM
				receberAtendido(&anterior, &*eventosAtendidos);
				*filaReclamacoes = NULL;
				
			} else {
				// Caso digite a opção NÃO
				return;
			}
		}
		
	} else {
		
		printf("Não existem reclamações registradas no momento. "
				"Utilize a opção [ 1 ] para registrar um novo evento e em seguida a "
				"opção [ 2 ] para encaminhar os eventos registrados e então "
				"tente novamente...\n");
	}
	
}

/*
	Função para consumir o comentário que está no topo da pilha.
	
	**pilhaComentarios	=> Último evento que entrou na pilha de comentários.
	**eventosAtendidos	=> Último evento que foi atendido.
*/
void consumirComentario(ListaEventos **pilhaComentarios, ListaEventos **eventosAtendidos) {
	
	if (*pilhaComentarios != NULL) {
		
		ListaEventos *consumido = *pilhaComentarios;
		
		printf("\t\t==== Deseja consumir este evento? ====\n");
		exibirEvento(consumido->evento);
		if (confirmar()) {
			// Caso digite a opção SIM
			/* TODO (Tiago_Wolker#1#): CORRIGIR => Não está definindo o status e o 
			                           tempo de aguardo do último evento da lista */
			consumido->evento.statusEvento = ATENDIDO;
			consumido->evento.tempoAguardo = time(NULL) - consumido->evento.segCadastro;
			*pilhaComentarios = (*pilhaComentarios)->proximo;
			receberAtendido(&consumido, &*eventosAtendidos);
		} else {
			// Caso digite a opção NÃO
			return;
		}
		
	} else {
		
		printf("Não existem comentários registrados no momento. "
				"Utilize a opção [ 1 ] para registrar um novo evento e em seguida a "
				"opção [ 2 ] para encaminhar os eventos registrados e então "
				"tente novamente...\n");
	}
	
}

/*
	Função que adiciona um evento na lista de eventos atendidos.
	
	**atendido			=> Evento a entrar na lista.
	**eventosAtendidos	=> Último evento que foi atendido.
*/
void receberAtendido(ListaEventos **atendido, ListaEventos **eventosAtendidos) {
	
	(*atendido)->proximo = *eventosAtendidos;
	(*eventosAtendidos) = *atendido;
}

/*
	Função que encaminha os eventos para sua fila ou pilha com base no tipo de mensagem que foi informada.
	
	**listaEventos		=> Último evento que entrou na lista de eventos principal.
	**filaReclamacoes	=> Último evento que entrou na fila de reclamações.
	**pilhaComentarios	=> Último evento que entrou na pilha de comentários.
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
		
		printf("Não existem eventos registrados no momento. Utilize a opção "
				"[ 1 ] para registrar um novo evento e então tente novamente...\n");
	}
	
}

/*
	Função para buscar e apresentar em tela as informações de um evento.
	
	*filaReclamacoes	=> Último evento que entrou na fila de reclamações.
	*pilhaComentarios	=> Último evento que entrou na pilha de comentários.
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
			printf("Protocolo não encontado!");
		}
		
	} else {
		
		printf("Não existem reclamações ou comentários registrados no momento. "
				"Utilize a opção [ 1 ] para registrar um novo evento e em seguida a "
				"opção [ 2 ] para encaminhar os eventos registrados e então "
				"tente novamente...\n");
	}
	
}
