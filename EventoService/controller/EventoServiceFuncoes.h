/*
	ESTRUTURA DE DADOS 2017/2
	Autores: Tiago Wolker Leite / Eduardo Moraes de Mello Alves / Bruno Vicente Alves
	Data: 15/11/2017
	Última atualização: 03/12/2017
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
void tempo(ListaEventos **filaReclamacoes, ListaEventos **pilhaComentarios);
void menu_info_eventos(ListaEventos *listaEventos, ListaEventos *filaReclamacoes, ListaEventos *pilhaComentarios, ListaEventos *eventosAtendidos);
void menu_listar_eventos(ListaEventos *listaEventos, ListaEventos *filaReclamacoes, ListaEventos *pilhaComentarios, ListaEventos *eventosAtendidos);
void relatorio(ListaEventos *listaEventos, ListaEventos *filaReclamacoes, ListaEventos *pilhaComentarios, ListaEventos *eventosAtendidos);

int menu_principal();
int contar_eventos(ListaEventos *listaEventos);
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
	
	if (novoNodo != NULL) { // verifica se foi possível alocar memória
		
		// Chama a função de cadastro ondem serão digitados os dados...
		if (realizar_cadastro(novoNodo)) { // Caso o cadastro seja confirmado...
			
			if (*listaEventos == NULL) {
				// se a  lista estiver vazia, o ponteiro aponta para o novo registro
				*listaEventos = novoNodo;
			} else {
				
				ListaEventos *auxiliar = *listaEventos; // auxiliar para percorrer a lista
				
				while (auxiliar->proximo != NULL) { // enquanto não encontrar o último registro...
					auxiliar = auxiliar->proximo;
				}
				
				auxiliar->proximo = novoNodo; // faz com que o ponteiro "proximo" do ultimo registro aponte para o novo registro
			}
			
		} else {
			// Caso o cadastro seja cancelado, libera o espaço em memória alocado para o novo registro
			free(novoNodo);
		}
		
	} else {
		// caso não haja memória suficiente...
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
	
	printf("\n==================================");
	printf("\n Protocolo: %i", evento.protocolo);
	printf("\n Status: %s", statusEventoLabel(evento.statusEvento));
	if (evento.statusEvento == ATENDIDO) { // se o evento já foi atendido, mostra quanto tempo demorou...
		printf("\n Tempo de aguardo para atendimento: %i segundos", evento.tempoAguardo);
	}
	printf("\n Tipo de mensagem: %s", tipoMensagemLabel(evento.tipoMensagem));
	printf("\n Mensagem: %s\n", evento.mensagem);
	printf("\n==================================");
}

/*
	Submenu que contém as opções do tipo de evento a ser consumido.
	
	**filaReclamacoes	=> Primeiro evento que entrou na fila de reclamações.
	**pilhaComentarios	=> Último evento que entrou na pilha de comentários.
	**eventosAtendidos	=> Último evento que foi atendido.
*/
void menu_consumir_eventos(ListaEventos **filaReclamacoes, ListaEventos **pilhaComentarios, ListaEventos **eventosAtendidos) {
	
	// verifica se ao menos uma das listas possui registros cadastrados
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
		// caso não haja reclamações nem comentários cadastrados...
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
	
	if (*filaReclamacoes != NULL) { // verifica se há reclamações cadastradas
		
		printf("\t\t==== Deseja consumir este evento? ====\n");
		exibir_evento((*filaReclamacoes)->evento);
		if (confirmar()) {
			// Caso digite a opção SIM
			(*filaReclamacoes)->evento.statusEvento = ATENDIDO; // define o status como atendido
			(*filaReclamacoes)->evento.tempoAguardo = time(NULL) - (*filaReclamacoes)->evento.segCadastro; // calcula o tempo que levou até ser atendido
			
			ListaEventos *reclamacaoAtendida = *filaReclamacoes; // ponteiro que irá apontar para a reclamação a ser consumida
			*filaReclamacoes = (*filaReclamacoes)->proximo; // reposiciona o ponteiro que aponta para a primeira reclamação da fila
			
			receber_atendido(&reclamacaoAtendida, &*eventosAtendidos); // lista *eventosAtendidos recebe o evento consumido 
			
		} else {
			// Caso digite a opção NÃO
			return;
		}
		
	} else {
		// caso não haja reclamações cadastradas...
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
	
	if (*pilhaComentarios != NULL) { //verifica se há comentários cadastrados
		
		ListaEventos *consumido = *pilhaComentarios; // ponteiro que irá apontar para o comentario a ser consumido
		
		printf("\t\t==== Deseja consumir este evento? ====\n");
		exibir_evento(consumido->evento);
		if (confirmar()) {
			// Caso digite a opção SIM
			consumido->evento.statusEvento = ATENDIDO; // define o status como atendido
			consumido->evento.tempoAguardo = time(NULL) - consumido->evento.segCadastro; // calcula o tempo que levou até ser atendido
			*pilhaComentarios = (*pilhaComentarios)->proximo; // reposiciona o ponteiro que aponta para o topo da pilha de comentários
			receber_atendido(&consumido, &*eventosAtendidos); // lista *eventosAtendidos recebe o evento consumido 
		} else {
			// Caso digite a opção NÃO
			return;
		}
		
	} else {
		// caso não haja comentários cadastrados...
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
	
	if (*listaEventos != NULL) { // verifica se há eventos na lista

		while (*listaEventos != NULL) { // enquanto a *listaEventos for diferente de NULL...
			ListaEventos *auxiliar = *listaEventos; // ponteiro auxiliar que aponta para o primeiro evento da lista de eventos a serem encaminhados
			*listaEventos = (*listaEventos)->proximo; // primeiro ponteiro da lista é reposicionado para o próximo
			
			switch (auxiliar->evento.tipoMensagem) { // verifica o tipo de mensagem
				case RECLAMACAO:
					// Insere no fim da fila de reclamações
					
					if (*filaReclamacoes == NULL) { // se a fila estiver vazia, *filaReclamacoes aponta para o auxiliar
						auxiliar->proximo = NULL;
						*filaReclamacoes = auxiliar;
					} else {
						
						ListaEventos *percorreFila = *filaReclamacoes;
						
						while (percorreFila->proximo != NULL) { // percorre a fila até encontrar o último
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
		tempo(&*filaReclamacoes, &*pilhaComentarios); // verifica se há eventos atrasados para atendimento
		printf("Eventos encaminhados com sucesso!\n");
	} else {
		// caso não haja eventos na lista...
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
	
	// Verifica se ao menos uma lista de eventos é diferente de NULL
	if (listaEventos != NULL || filaReclamacoes != NULL || pilhaComentarios != NULL || eventosAtendidos != NULL){
		
		bool achou = false;
		int busca;
		
		printf("Digite o protocolo a ser buscado: ");
		fflush(stdin);
		scanf("%i", &busca);
		
		achou = buscar_evento_protocolo(busca, listaEventos, achou); // busca o protocólo digitado em "listaEventos"
		if (!achou) achou = buscar_evento_protocolo(busca, filaReclamacoes, achou); // caso não tenha encontrado, busca o protocólo digitado em "filaReclamacoes"
		if (!achou) achou = buscar_evento_protocolo(busca, pilhaComentarios, achou); // caso não tenha encontrado, busca o protocólo digitado em "pilhaComentarios"
		if (!achou) achou = buscar_evento_protocolo(busca, eventosAtendidos, achou); // caso não tenha encontrado, busca o protocólo digitado em "eventosAtendidos"
		
		if(!achou) { //caso não tenha encontrado em nenhuma das listas
			printf("Protocolo não encontado!\n");
		}
		
	} else {
		// caso todas as listas sejam igual a NULL
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
	
	while(listaEventos != NULL && !achou){
		// enquanto a posição atual da lista for diferente de NULL e enquanto o protocólo não for encontrado... 
		
		if(listaEventos->evento.protocolo == protocolo){ // compara o protocolo digitado para pesquisa com o protocolo da posição atual
			exibir_evento(listaEventos->evento); // exibe o evento em tela caso a comparação seja verdadeira
			return true; // retorna verdadeiro
		}
		listaEventos = listaEventos->proximo; // avança para a próxima posição da lista
	}
	
	return false; // retorna falso caso não tenha encontrado o protocólo digitado
}

/*
	Função para ver qual reclamação e qual comentario pasou o tempo de ser atendido.
	
	*filaReclamacoes	=> Primeiro evento que entrou na fila de reclamações.
	*pilhaComentarios	=> Último evento que entrou na pilha de comentários.
*/
void tempo(ListaEventos **filaReclamacoes, ListaEventos **pilhaComentarios){
	
	ListaEventos *aux = *filaReclamacoes;//ponteiro auxiliar
	int t;//variavel auxiliar
	if (aux != NULL){	//se for diferente de null ate achar null
		while (aux != NULL) {//percorre minha struct
			t = time(NULL) - aux->evento.segCadastro;//verfica o tempo da struct filareclamacao com  o tempo da maquina 
			if (t > 60){//se o tempo for maior que 60 segundos 
				printf("\nA reclamação do protocolo %i passou do tempo de atendimento.\n", aux->evento.protocolo);	//imprime aviso informando qual protocolo passou do tempo
				t=NULL;	//zera minha variavel para poder verficar outra struct
			}
			aux = aux->proximo;
		}	
	}
  	aux = *pilhaComentarios;//atribui inicio da minha struct pilha comentario
	if (aux != NULL){//verfica
		while (aux != NULL){//percorre minha struct ate achar null
			 t = time(NULL) - aux->evento.segCadastro;//verfica o tempo da struct filareclamacao com  o tempo da maquina 
				if (t > 120){
					printf("\nO comentário  do protocolo %i passou do tempo de atendimento.\n", aux->evento.protocolo);//imprime aviso informando qual protocolo passou do tempo
					t = NULL; //zera minha variavel para poder verficar outra struct
				}
			aux = aux->proximo;	
		}
	}
}

/*
	Submenu para opção de listar eventos ou exibir relatórios.
	
	*listaEventos		=> Primeiro evento da lista de eventos não encaminhados.
	*filaReclamacoes	=> Primeiro evento que entrou na fila de reclamações.
	*pilhaComentarios	=> Último evento que entrou na pilha de comentários.
	*eventosAtendidos	=> Primeiro evento da lista de eventos atendidos.	
*/
void menu_info_eventos(ListaEventos *listaEventos, ListaEventos *filaReclamacoes, ListaEventos *pilhaComentarios, ListaEventos *eventosAtendidos) {
	
	// Verifica se ao menos uma lista de eventos é diferente de NULL
	if (listaEventos != NULL || filaReclamacoes != NULL || pilhaComentarios != NULL || eventosAtendidos != NULL) {
		
	    int opcao;
	    
		printf("\t\t===== [ Informações dos Eventos ] =====");
		printf("\n[ 1 ] - Listar");
		printf("\n[ 2 ] - Relatório");
		printf("\n[ 0 ] - Voltar");
		printf("\n\nInforme a sua opção: ");
		scanf("%i", &opcao);
		
		switch(opcao) {
			
			case 1:
				// Menu Listar
				menu_listar_eventos(listaEventos, filaReclamacoes, pilhaComentarios, eventosAtendidos);
				break;
			case 2:
				// Relatório
				relatorio(listaEventos, filaReclamacoes, pilhaComentarios, eventosAtendidos);
				break;
			case 0:
				printf("Retornando ao menu principal...");
				break;
			default:
				printf("Opção inválida! Retornando ao menu principal...");
			
		}
		
	} else {
		// caso todas as listas sejam igual a NULL
		printf("Não existem eventos registrados no momento!");
	}
}

/*
	Submenu com as opções para listar eventos.
	
	*listaEventos		=> Primeiro evento da lista de eventos não encaminhados.
	*filaReclamacoes	=> Primeiro evento que entrou na fila de reclamações.
	*pilhaComentarios	=> Último evento que entrou na pilha de comentários.
	*eventosAtendidos	=> Primeiro evento da lista de eventos atendidos.	
*/
void menu_listar_eventos(ListaEventos *listaEventos, ListaEventos *filaReclamacoes, ListaEventos *pilhaComentarios, ListaEventos *eventosAtendidos) {
	
	int opcao;
    
	printf("\t\t===== [ Listar Eventos ] =====");
	// Exibe a opção caso a lista em questão seja diferente de NULL
	if (listaEventos != NULL) printf("\n[ 1 ] - Eventos aguardando encaminhamento"); 
	if (filaReclamacoes != NULL) printf("\n[ 2 ] - Fila de reclamações");
	if (pilhaComentarios != NULL) printf("\n[ 3 ] - Pilha  de comentários");
	if (eventosAtendidos != NULL) printf("\n[ 4 ] - Eventos atendidos");
	printf("\n[ 0 ] - Voltar");
	printf("\n\nInforme a sua opção: ");
	scanf("%i", &opcao);
	system("cls");
	
	switch(opcao) {
		
		case 1:
			// Eventos aguardando encaminhamento
			listar(listaEventos);
			break;
		case 2:
			// Fila de reclamações
			listar(filaReclamacoes);
			break;
		case 3:
			// Pilha  de comentários
			listar(pilhaComentarios);
			break;
		case 4:
			// Eventos atendidos
			listar(eventosAtendidos);
			break;
		case 0:
			printf("Retornando ao menu principal...");
			break;
		default:
			printf("Opção inválida! Retornando ao menu principal...");
		
	}
}

/*
	Função que mostra o relatório geral com as quantidades de eventos nas listas.
	
	*listaEventos		=> Primeiro evento da lista de eventos não encaminhados.
	*filaReclamacoes	=> Primeiro evento que entrou na fila de reclamações.
	*pilhaComentarios	=> Último evento que entrou na pilha de comentários.
	*eventosAtendidos	=> Primeiro evento da lista de eventos atendidos.	
*/
void relatorio(ListaEventos *listaEventos, ListaEventos *filaReclamacoes, ListaEventos *pilhaComentarios, ListaEventos *eventosAtendidos) {
    
	printf("\t\t===== [ Relatório Geral ] =====");
	
	int contador = 0; // contador que irá guardar a quantidade de eventos em uma das listas
	int total = 0; // variável que irá guardar o total de eventos de todas as listas juntas
	
	printf("\nQuantidade de eventos aguardando encaminhamento: %i", contador = contar_eventos(listaEventos));
	
	total += contador; // adiciona no total geral
	contador = 0; // zera o contador
	
	printf("\nQuantidade de reclamações aguardando atendimento: %i", contador = contar_eventos(filaReclamacoes));
	
	total += contador; // adiciona no total geral
	contador = 0; // zera o contador
	
	printf("\nQuantidade de comentários aguardando atendimento: %i", contador = contar_eventos(pilhaComentarios));
	
	total += contador; // adiciona no total geral
	contador = 0; // zera o contador
	
	printf("\nQuantidade de eventos atendidos: %i", contador = contar_eventos(eventosAtendidos));
	
	total += contador; // adiciona no total geral
	
	printf("\nQuantidade total de eventos registrados: %i", total);
}

/*
	Conta a quantidade de eventos na lista informada.
	
	*listaEventos	=> Primeiro evento da lista de eventos a ser contada.
	
	return	=> Quantidade total de eventos na lista.
*/
int contar_eventos(ListaEventos *listaEventos) {
	
	int contador = 0;
	
	while (listaEventos != NULL) { // enquanto a posição for diferente de NULL...
		contador++; // incrementa o contador
		listaEventos = listaEventos->proximo; // avança para o próximo nodo da lista
	}
	
	return contador;
}
