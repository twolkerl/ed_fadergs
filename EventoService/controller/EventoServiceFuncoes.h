/*
	ESTRUTURA DE DADOS 2017/2
	Autores: Tiago Wolker Leite / Eduardo Moraes de Mello Alves / Bruno Vicente Alves
	Data: 15/11/2017
	Última atualização: 26/11/2017
	Biblioteca que contém as funções de EventoService.
*/

// -- BIBLIOTECAS --
#include "../model/EventoStructs.h"
#include "Utilitarios.h"


// -- PROTÓTIPOS --
void cadastrar_evento(ListaEventos **listaEventos);
void listar(ListaEventos *listaEventos);
void exibir_evento(Evento evento);
void menu_consumir_eventos(ListaEventos **filaReclamacoes, ListaEventos **pilhaComentarios, ListaEventos **eventosAtendidos);
void consumir_reclamacao(ListaEventos **filaReclamacoes, ListaEventos **eventosAtendidos);
void consumir_comentario(ListaEventos **pilhaComentarios, ListaEventos **eventosAtendidos);
void receber_atendido(ListaEventos **atendido, ListaEventos **eventosAtendidos);
void encaminhar_eventos(ListaEventos **listaEventos, ListaEventos **filaReclamacoes, ListaEventos **pilhaComentarios);
void apresentar_evento(ListaEventos *listaEventos, ListaEventos *filaReclamacoes, ListaEventos *pilhaComentarios, ListaEventos *eventosAtendidos);

int menu_principal();
bool realizar_cadastro(ListaEventos *novoNodo);
bool buscar_evento_protocolo(int protocolo, ListaEventos *listaEventos, bool achou);

// -- FUNÇÕES --

/*
	Função que mostra o menu principal e recebe a opção digitada pelo usuário.
	
	return	=> Número da opção digitada pelo usuário.
*/
int menu_principal() {
    int opcao;
                           
	printf("\t\t===== [ EventoService ] =====");
	printf("\n[ 1 ] - Registrar Eventos");
	printf("\n[ 2 ] - Encaminhar Eventos");
	printf("\n[ 3 ] - Apresentar Evento");
	printf("\n[ 4 ] - Consumir Evento");
	printf("\n[ 5 ] - Informações Eventos");
	printf("\n[100] - TESTE - Cadastrar 10 em cada estrutura");
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
void cadastrar_evento(ListaEventos **listaEventos) {
	
	ListaEventos *novoNodo = (ListaEventos*) malloc (sizeof (ListaEventos));
	
	if (novoNodo != NULL) {
		
		if (realizar_cadastro(novoNodo)) {
			
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
bool realizar_cadastro(ListaEventos *novoNodo) {
	
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
		
		exibir_evento(listaEventos->evento);
		listar(listaEventos->proximo);
	}
}

/*
	Função que exibe os dados do evento passado por parâmetro.
	
	evento	=> Evento a ser exibido em tela.
*/
void exibir_evento(Evento evento) {
	
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
	
	**filaReclamacoes	=> Primeiro evento que entrou na fila de reclamações.
	**pilhaComentarios	=> Último evento que entrou na pilha de comentários.
	**eventosAtendidos	=> Último evento que foi atendido.
*/
void menu_consumir_eventos(ListaEventos **filaReclamacoes, ListaEventos **pilhaComentarios, ListaEventos **eventosAtendidos) {
	
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
				consumir_reclamacao(&*filaReclamacoes, &*eventosAtendidos);
				break;
			case 2:
				// Consumir comentário da pilha
				consumir_comentario(&*pilhaComentarios, &*eventosAtendidos);
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
	
	**filaReclamacoes	=> Primeiro evento que entrou na fila de reclamações.
	**eventosAtendidos	=> Último evento que foi atendido.
*/
void consumir_reclamacao(ListaEventos **filaReclamacoes, ListaEventos **eventosAtendidos) {
	
	if (*filaReclamacoes != NULL) {
		
		printf("\t\t==== Deseja consumir este evento? ====\n");
		exibir_evento((*filaReclamacoes)->evento);
		if (confirmar()) {
			// Caso digite a opção SIM
			(*filaReclamacoes)->evento.statusEvento = ATENDIDO;
			(*filaReclamacoes)->evento.tempoAguardo = time(NULL) - (*filaReclamacoes)->evento.segCadastro;
			
			ListaEventos *reclamacaoAtendida = *filaReclamacoes;
			*filaReclamacoes = (*filaReclamacoes)->proximo;
			
			receber_atendido(&reclamacaoAtendida, &*eventosAtendidos);
			
		} else {
			// Caso digite a opção NÃO
			return;
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
void consumir_comentario(ListaEventos **pilhaComentarios, ListaEventos **eventosAtendidos) {
	
	if (*pilhaComentarios != NULL) {
		
		ListaEventos *consumido = *pilhaComentarios;
		
		printf("\t\t==== Deseja consumir este evento? ====\n");
		exibir_evento(consumido->evento);
		if (confirmar()) {
			// Caso digite a opção SIM
			consumido->evento.statusEvento = ATENDIDO;
			consumido->evento.tempoAguardo = time(NULL) - consumido->evento.segCadastro;
			*pilhaComentarios = (*pilhaComentarios)->proximo;
			receber_atendido(&consumido, &*eventosAtendidos);
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
void receber_atendido(ListaEventos **atendido, ListaEventos **eventosAtendidos) {
	
	(*atendido)->proximo = *eventosAtendidos;
	(*eventosAtendidos) = *atendido;
}

/*
	Função que encaminha os eventos para sua fila ou pilha com base no tipo de mensagem que foi informada.
	
	**listaEventos		=> Último evento que entrou na lista de eventos principal.
	**filaReclamacoes	=> Primeiro evento que entrou na fila de reclamações.
	**pilhaComentarios	=> Último evento que entrou na pilha de comentários.
*/
void encaminhar_eventos(ListaEventos **listaEventos, ListaEventos **filaReclamacoes, ListaEventos **pilhaComentarios) {
	
	if (*listaEventos != NULL) {

		while (*listaEventos != NULL) {
			ListaEventos *auxiliar = *listaEventos;
			*listaEventos = (*listaEventos)->proximo;
			
			switch (auxiliar->evento.tipoMensagem) {
				case RECLAMACAO:
					// Insere no fim da fila de reclamações
					
					if (*filaReclamacoes == NULL) {
						auxiliar->proximo = NULL;
						*filaReclamacoes = auxiliar;
					} else {
						
						ListaEventos *percorreFila = *filaReclamacoes;
						
						while (percorreFila->proximo != NULL) {
							percorreFila = percorreFila->proximo;
						}
						auxiliar->proximo = NULL;
						percorreFila->proximo = auxiliar;
					}
					
					break;
					
				case COMENTARIO:
				default:
					// Insere no topo da pilha de comentários
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
	
	*listaEventos		=> Primeiro evento da lista de eventos não encaminhados.
	*filaReclamacoes	=> Primeiro evento que entrou na fila de reclamações.
	*pilhaComentarios	=> Último evento que entrou na pilha de comentários.
	*eventosAtendidos	=> Primeiro evento da lista de eventos atendidos.
*/
void apresentar_evento(ListaEventos *listaEventos, ListaEventos *filaReclamacoes, ListaEventos *pilhaComentarios, ListaEventos *eventosAtendidos){
	
	if (listaEventos != NULL || filaReclamacoes != NULL || pilhaComentarios != NULL || eventosAtendidos != NULL){
		
		bool achou = false;
		int busca;
		ListaEventos *aux = filaReclamacoes;
		
		printf("Digite o protocolo a ser buscado: ");
		fflush(stdin);
		scanf("%i", &busca);
		
		achou = buscar_evento_protocolo(busca, listaEventos, achou);
		if (!achou) achou = buscar_evento_protocolo(busca, filaReclamacoes, achou);
		if (!achou) achou = buscar_evento_protocolo(busca, pilhaComentarios, achou);
		if (!achou) achou = buscar_evento_protocolo(busca, eventosAtendidos, achou);
		
		if(!achou) {
			printf("Protocolo não encontado!\n");
		}
		
	} else {
		
		printf("Não existem reclamações ou comentários registrados no momento. "
				"Utilize a opção [ 1 ] para registrar um novo evento e em seguida a "
				"opção [ 2 ] para encaminhar os eventos registrados e então "
				"tente novamente...\n");
	}
	
}

/*
	Busca um evento pelo protocolo informado na lista de eventos passada por parâmetro.
	
	protocolo		=> Número do protocolo a ser buscado.
	*listaEventos	=> Primeiro evento da lista de eventos informada.
	achou			=> Booleana que representa se o protocolo foi encontrado.
	
	return	=> Verdadeiro caso tenha sido encontrado, caso contrário retorna falso.
*/
bool buscar_evento_protocolo(int protocolo, ListaEventos *listaEventos, bool achou) {
	
	ListaEventos *aux = listaEventos;
	
	while(aux != NULL && !achou){
		
		if(aux->evento.protocolo == protocolo){
			exibir_evento(aux->evento);
			return true;
		}
		aux = aux->proximo;
	}
	
	return false;
}
