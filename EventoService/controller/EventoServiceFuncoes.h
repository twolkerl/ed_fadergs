/*
	ESTRUTURA DE DADOS 2017/2
	Autores: Tiago Wolker Leite / Eduardo Moraes de Mello Alves / Bruno Vicente Alves
	Data: 15/11/2017
	�ltima atualiza��o: 03/12/2017
	Biblioteca que cont�m as fun��es de EventoService.
*/

// -- BIBLIOTECAS --
#include "../model/EventoStructs.h"
#include "Utilitarios.h"


// -- PROT�TIPOS --
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

// -- FUN��ES --

/*
	Fun��o que mostra o menu principal e recebe a op��o digitada pelo usu�rio.
	
	return	=> N�mero da op��o digitada pelo usu�rio.
*/
int menu_principal() {
    int opcao;
                           
	printf("\t\t===== [ EventoService ] =====");
	printf("\n[ 1 ] - Registrar Eventos");
	printf("\n[ 2 ] - Encaminhar Eventos");
	printf("\n[ 3 ] - Apresentar Evento");
	printf("\n[ 4 ] - Consumir Evento");
	printf("\n[ 5 ] - Informa��es Eventos");
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
void cadastrar_evento(ListaEventos **listaEventos) {
	
	ListaEventos *novoNodo = (ListaEventos*) malloc (sizeof (ListaEventos));
	
	if (novoNodo != NULL) { // verifica se foi poss�vel alocar mem�ria
		
		// Chama a fun��o de cadastro ondem ser�o digitados os dados...
		if (realizar_cadastro(novoNodo)) { // Caso o cadastro seja confirmado...
			
			if (*listaEventos == NULL) {
				// se a  lista estiver vazia, o ponteiro aponta para o novo registro
				*listaEventos = novoNodo;
			} else {
				
				ListaEventos *auxiliar = *listaEventos; // auxiliar para percorrer a lista
				
				while (auxiliar->proximo != NULL) { // enquanto n�o encontrar o �ltimo registro...
					auxiliar = auxiliar->proximo;
				}
				
				auxiliar->proximo = novoNodo; // faz com que o ponteiro "proximo" do ultimo registro aponte para o novo registro
			}
			
		} else {
			// Caso o cadastro seja cancelado, libera o espa�o em mem�ria alocado para o novo registro
			free(novoNodo);
		}
		
	} else {
		// caso n�o haja mem�ria suficiente...
		printf( "\nN�o h� mem�ria para cadastrar novo registro!\n" );
	}
	
}

/*
	Fun��o que l� do usu�rio os dados para cadastrar um novo nodo.
	
	return	=> Verdadeiro caso o usu�rio confirme o registro, caso contr�rio Falso.
*/
bool realizar_cadastro(ListaEventos *novoNodo) {
	
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
		
		exibir_evento(listaEventos->evento);
		listar(listaEventos->proximo);
	}
}

/*
	Fun��o que exibe os dados do evento passado por par�metro.
	
	evento	=> Evento a ser exibido em tela.
*/
void exibir_evento(Evento evento) {
	
	printf("\n==================================");
	printf("\n Protocolo: %i", evento.protocolo);
	printf("\n Status: %s", statusEventoLabel(evento.statusEvento));
	if (evento.statusEvento == ATENDIDO) { // se o evento j� foi atendido, mostra quanto tempo demorou...
		printf("\n Tempo de aguardo para atendimento: %i segundos", evento.tempoAguardo);
	}
	printf("\n Tipo de mensagem: %s", tipoMensagemLabel(evento.tipoMensagem));
	printf("\n Mensagem: %s\n", evento.mensagem);
	printf("\n==================================");
}

/*
	Submenu que cont�m as op��es do tipo de evento a ser consumido.
	
	**filaReclamacoes	=> Primeiro evento que entrou na fila de reclama��es.
	**pilhaComentarios	=> �ltimo evento que entrou na pilha de coment�rios.
	**eventosAtendidos	=> �ltimo evento que foi atendido.
*/
void menu_consumir_eventos(ListaEventos **filaReclamacoes, ListaEventos **pilhaComentarios, ListaEventos **eventosAtendidos) {
	
	// verifica se ao menos uma das listas possui registros cadastrados
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
				consumir_reclamacao(&*filaReclamacoes, &*eventosAtendidos);
				break;
			case 2:
				// Consumir coment�rio da pilha
				consumir_comentario(&*pilhaComentarios, &*eventosAtendidos);
				break;
			case 0:
				printf("Retornando ao menu principal...");
				break;
			default:
				printf("Op��o inv�lida! Retornando ao menu principal...");
			
		}
		
	} else {
		// caso n�o haja reclama��es nem coment�rios cadastrados...
		printf("N�o existem reclama��es ou coment�rios registrados no momento. "
				"Utilize a op��o [ 1 ] para registrar um novo evento e em seguida a "
				"op��o [ 2 ] para encaminhar os eventos registrados e ent�o "
				"tente novamente...\n");
	}
	
}

/*
	Fun��o para atender a primeira reclama��o da fila.
	
	**filaReclamacoes	=> Primeiro evento que entrou na fila de reclama��es.
	**eventosAtendidos	=> �ltimo evento que foi atendido.
*/
void consumir_reclamacao(ListaEventos **filaReclamacoes, ListaEventos **eventosAtendidos) {
	
	if (*filaReclamacoes != NULL) { // verifica se h� reclama��es cadastradas
		
		printf("\t\t==== Deseja consumir este evento? ====\n");
		exibir_evento((*filaReclamacoes)->evento);
		if (confirmar()) {
			// Caso digite a op��o SIM
			(*filaReclamacoes)->evento.statusEvento = ATENDIDO; // define o status como atendido
			(*filaReclamacoes)->evento.tempoAguardo = time(NULL) - (*filaReclamacoes)->evento.segCadastro; // calcula o tempo que levou at� ser atendido
			
			ListaEventos *reclamacaoAtendida = *filaReclamacoes; // ponteiro que ir� apontar para a reclama��o a ser consumida
			*filaReclamacoes = (*filaReclamacoes)->proximo; // reposiciona o ponteiro que aponta para a primeira reclama��o da fila
			
			receber_atendido(&reclamacaoAtendida, &*eventosAtendidos); // lista *eventosAtendidos recebe o evento consumido 
			
		} else {
			// Caso digite a op��o N�O
			return;
		}
		
	} else {
		// caso n�o haja reclama��es cadastradas...
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
void consumir_comentario(ListaEventos **pilhaComentarios, ListaEventos **eventosAtendidos) {
	
	if (*pilhaComentarios != NULL) { //verifica se h� coment�rios cadastrados
		
		ListaEventos *consumido = *pilhaComentarios; // ponteiro que ir� apontar para o comentario a ser consumido
		
		printf("\t\t==== Deseja consumir este evento? ====\n");
		exibir_evento(consumido->evento);
		if (confirmar()) {
			// Caso digite a op��o SIM
			consumido->evento.statusEvento = ATENDIDO; // define o status como atendido
			consumido->evento.tempoAguardo = time(NULL) - consumido->evento.segCadastro; // calcula o tempo que levou at� ser atendido
			*pilhaComentarios = (*pilhaComentarios)->proximo; // reposiciona o ponteiro que aponta para o topo da pilha de coment�rios
			receber_atendido(&consumido, &*eventosAtendidos); // lista *eventosAtendidos recebe o evento consumido 
		} else {
			// Caso digite a op��o N�O
			return;
		}
		
	} else {
		// caso n�o haja coment�rios cadastrados...
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
void receber_atendido(ListaEventos **atendido, ListaEventos **eventosAtendidos) {
	
	(*atendido)->proximo = *eventosAtendidos;
	(*eventosAtendidos) = *atendido;
}

/*
	Fun��o que encaminha os eventos para sua fila ou pilha com base no tipo de mensagem que foi informada.
	
	**listaEventos		=> �ltimo evento que entrou na lista de eventos principal.
	**filaReclamacoes	=> Primeiro evento que entrou na fila de reclama��es.
	**pilhaComentarios	=> �ltimo evento que entrou na pilha de coment�rios.
*/
void encaminhar_eventos(ListaEventos **listaEventos, ListaEventos **filaReclamacoes, ListaEventos **pilhaComentarios) {
	
	if (*listaEventos != NULL) { // verifica se h� eventos na lista

		while (*listaEventos != NULL) { // enquanto a *listaEventos for diferente de NULL...
			ListaEventos *auxiliar = *listaEventos; // ponteiro auxiliar que aponta para o primeiro evento da lista de eventos a serem encaminhados
			*listaEventos = (*listaEventos)->proximo; // primeiro ponteiro da lista � reposicionado para o pr�ximo
			
			switch (auxiliar->evento.tipoMensagem) { // verifica o tipo de mensagem
				case RECLAMACAO:
					// Insere no fim da fila de reclama��es
					
					if (*filaReclamacoes == NULL) { // se a fila estiver vazia, *filaReclamacoes aponta para o auxiliar
						auxiliar->proximo = NULL;
						*filaReclamacoes = auxiliar;
					} else {
						
						ListaEventos *percorreFila = *filaReclamacoes;
						
						while (percorreFila->proximo != NULL) { // percorre a fila at� encontrar o �ltimo
							percorreFila = percorreFila->proximo;
						}
						auxiliar->proximo = NULL;
						percorreFila->proximo = auxiliar;
					}
					
					break;
					
				case COMENTARIO:
				default:
					// Insere no topo da pilha de coment�rios
					auxiliar->proximo = *pilhaComentarios;
					*pilhaComentarios = auxiliar;
			}
		}
		tempo(&*filaReclamacoes, &*pilhaComentarios); // verifica se h� eventos atrasados para atendimento
		printf("Eventos encaminhados com sucesso!\n");
	} else {
		// caso n�o haja eventos na lista...
		printf("N�o existem eventos registrados no momento. Utilize a op��o "
				"[ 1 ] para registrar um novo evento e ent�o tente novamente...\n");
	}
	
}

/*
	Fun��o para buscar e apresentar em tela as informa��es de um evento.
	
	*listaEventos		=> Primeiro evento da lista de eventos n�o encaminhados.
	*filaReclamacoes	=> Primeiro evento que entrou na fila de reclama��es.
	*pilhaComentarios	=> �ltimo evento que entrou na pilha de coment�rios.
	*eventosAtendidos	=> Primeiro evento da lista de eventos atendidos.
*/
void apresentar_evento(ListaEventos *listaEventos, ListaEventos *filaReclamacoes, ListaEventos *pilhaComentarios, ListaEventos *eventosAtendidos){
	
	// Verifica se ao menos uma lista de eventos � diferente de NULL
	if (listaEventos != NULL || filaReclamacoes != NULL || pilhaComentarios != NULL || eventosAtendidos != NULL){
		
		bool achou = false;
		int busca;
		
		printf("Digite o protocolo a ser buscado: ");
		fflush(stdin);
		scanf("%i", &busca);
		
		achou = buscar_evento_protocolo(busca, listaEventos, achou); // busca o protoc�lo digitado em "listaEventos"
		if (!achou) achou = buscar_evento_protocolo(busca, filaReclamacoes, achou); // caso n�o tenha encontrado, busca o protoc�lo digitado em "filaReclamacoes"
		if (!achou) achou = buscar_evento_protocolo(busca, pilhaComentarios, achou); // caso n�o tenha encontrado, busca o protoc�lo digitado em "pilhaComentarios"
		if (!achou) achou = buscar_evento_protocolo(busca, eventosAtendidos, achou); // caso n�o tenha encontrado, busca o protoc�lo digitado em "eventosAtendidos"
		
		if(!achou) { //caso n�o tenha encontrado em nenhuma das listas
			printf("Protocolo n�o encontado!\n");
		}
		
	} else {
		// caso todas as listas sejam igual a NULL
		printf("N�o existem reclama��es ou coment�rios registrados no momento. "
				"Utilize a op��o [ 1 ] para registrar um novo evento e em seguida a "
				"op��o [ 2 ] para encaminhar os eventos registrados e ent�o "
				"tente novamente...\n");
	}
	
}

/*
	Busca um evento pelo protocolo informado na lista de eventos passada por par�metro.
	
	protocolo		=> N�mero do protocolo a ser buscado.
	*listaEventos	=> Primeiro evento da lista de eventos informada.
	achou			=> Booleana que representa se o protocolo foi encontrado.
	
	return	=> Verdadeiro caso tenha sido encontrado, caso contr�rio retorna falso.
*/
bool buscar_evento_protocolo(int protocolo, ListaEventos *listaEventos, bool achou) {
	
	while(listaEventos != NULL && !achou){
		// enquanto a posi��o atual da lista for diferente de NULL e enquanto o protoc�lo n�o for encontrado... 
		
		if(listaEventos->evento.protocolo == protocolo){ // compara o protocolo digitado para pesquisa com o protocolo da posi��o atual
			exibir_evento(listaEventos->evento); // exibe o evento em tela caso a compara��o seja verdadeira
			return true; // retorna verdadeiro
		}
		listaEventos = listaEventos->proximo; // avan�a para a pr�xima posi��o da lista
	}
	
	return false; // retorna falso caso n�o tenha encontrado o protoc�lo digitado
}

/*
	Fun��o para ver qual reclama��o e qual comentario pasou o tempo de ser atendido.
	
	*filaReclamacoes	=> Primeiro evento que entrou na fila de reclama��es.
	*pilhaComentarios	=> �ltimo evento que entrou na pilha de coment�rios.
*/
void tempo(ListaEventos **filaReclamacoes, ListaEventos **pilhaComentarios){
	
	ListaEventos *aux = *filaReclamacoes;//ponteiro auxiliar
	int t;//variavel auxiliar
	if (aux != NULL){	//se for diferente de null ate achar null
		while (aux != NULL) {//percorre minha struct
			t = time(NULL) - aux->evento.segCadastro;//verfica o tempo da struct filareclamacao com  o tempo da maquina 
			if (t > 60){//se o tempo for maior que 60 segundos 
				printf("\nA reclama��o do protocolo %i passou do tempo de atendimento.\n", aux->evento.protocolo);	//imprime aviso informando qual protocolo passou do tempo
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
					printf("\nO coment�rio  do protocolo %i passou do tempo de atendimento.\n", aux->evento.protocolo);//imprime aviso informando qual protocolo passou do tempo
					t = NULL; //zera minha variavel para poder verficar outra struct
				}
			aux = aux->proximo;	
		}
	}
}

/*
	Submenu para op��o de listar eventos ou exibir relat�rios.
	
	*listaEventos		=> Primeiro evento da lista de eventos n�o encaminhados.
	*filaReclamacoes	=> Primeiro evento que entrou na fila de reclama��es.
	*pilhaComentarios	=> �ltimo evento que entrou na pilha de coment�rios.
	*eventosAtendidos	=> Primeiro evento da lista de eventos atendidos.	
*/
void menu_info_eventos(ListaEventos *listaEventos, ListaEventos *filaReclamacoes, ListaEventos *pilhaComentarios, ListaEventos *eventosAtendidos) {
	
	// Verifica se ao menos uma lista de eventos � diferente de NULL
	if (listaEventos != NULL || filaReclamacoes != NULL || pilhaComentarios != NULL || eventosAtendidos != NULL) {
		
	    int opcao;
	    
		printf("\t\t===== [ Informa��es dos Eventos ] =====");
		printf("\n[ 1 ] - Listar");
		printf("\n[ 2 ] - Relat�rio");
		printf("\n[ 0 ] - Voltar");
		printf("\n\nInforme a sua op��o: ");
		scanf("%i", &opcao);
		
		switch(opcao) {
			
			case 1:
				// Menu Listar
				menu_listar_eventos(listaEventos, filaReclamacoes, pilhaComentarios, eventosAtendidos);
				break;
			case 2:
				// Relat�rio
				relatorio(listaEventos, filaReclamacoes, pilhaComentarios, eventosAtendidos);
				break;
			case 0:
				printf("Retornando ao menu principal...");
				break;
			default:
				printf("Op��o inv�lida! Retornando ao menu principal...");
			
		}
		
	} else {
		// caso todas as listas sejam igual a NULL
		printf("N�o existem eventos registrados no momento!");
	}
}

/*
	Submenu com as op��es para listar eventos.
	
	*listaEventos		=> Primeiro evento da lista de eventos n�o encaminhados.
	*filaReclamacoes	=> Primeiro evento que entrou na fila de reclama��es.
	*pilhaComentarios	=> �ltimo evento que entrou na pilha de coment�rios.
	*eventosAtendidos	=> Primeiro evento da lista de eventos atendidos.	
*/
void menu_listar_eventos(ListaEventos *listaEventos, ListaEventos *filaReclamacoes, ListaEventos *pilhaComentarios, ListaEventos *eventosAtendidos) {
	
	int opcao;
    
	printf("\t\t===== [ Listar Eventos ] =====");
	// Exibe a op��o caso a lista em quest�o seja diferente de NULL
	if (listaEventos != NULL) printf("\n[ 1 ] - Eventos aguardando encaminhamento"); 
	if (filaReclamacoes != NULL) printf("\n[ 2 ] - Fila de reclama��es");
	if (pilhaComentarios != NULL) printf("\n[ 3 ] - Pilha  de coment�rios");
	if (eventosAtendidos != NULL) printf("\n[ 4 ] - Eventos atendidos");
	printf("\n[ 0 ] - Voltar");
	printf("\n\nInforme a sua op��o: ");
	scanf("%i", &opcao);
	system("cls");
	
	switch(opcao) {
		
		case 1:
			// Eventos aguardando encaminhamento
			listar(listaEventos);
			break;
		case 2:
			// Fila de reclama��es
			listar(filaReclamacoes);
			break;
		case 3:
			// Pilha  de coment�rios
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
			printf("Op��o inv�lida! Retornando ao menu principal...");
		
	}
}

/*
	Fun��o que mostra o relat�rio geral com as quantidades de eventos nas listas.
	
	*listaEventos		=> Primeiro evento da lista de eventos n�o encaminhados.
	*filaReclamacoes	=> Primeiro evento que entrou na fila de reclama��es.
	*pilhaComentarios	=> �ltimo evento que entrou na pilha de coment�rios.
	*eventosAtendidos	=> Primeiro evento da lista de eventos atendidos.	
*/
void relatorio(ListaEventos *listaEventos, ListaEventos *filaReclamacoes, ListaEventos *pilhaComentarios, ListaEventos *eventosAtendidos) {
    
	printf("\t\t===== [ Relat�rio Geral ] =====");
	
	int contador = 0; // contador que ir� guardar a quantidade de eventos em uma das listas
	int total = 0; // vari�vel que ir� guardar o total de eventos de todas as listas juntas
	
	printf("\nQuantidade de eventos aguardando encaminhamento: %i", contador = contar_eventos(listaEventos));
	
	total += contador; // adiciona no total geral
	contador = 0; // zera o contador
	
	printf("\nQuantidade de reclama��es aguardando atendimento: %i", contador = contar_eventos(filaReclamacoes));
	
	total += contador; // adiciona no total geral
	contador = 0; // zera o contador
	
	printf("\nQuantidade de coment�rios aguardando atendimento: %i", contador = contar_eventos(pilhaComentarios));
	
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
	
	while (listaEventos != NULL) { // enquanto a posi��o for diferente de NULL...
		contador++; // incrementa o contador
		listaEventos = listaEventos->proximo; // avan�a para o pr�ximo nodo da lista
	}
	
	return contador;
}
