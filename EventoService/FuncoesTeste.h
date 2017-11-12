/*
	FUNÇÕES DE TESTE
*/
#include <string.h>

void cadastroAutomatico(ListaEventos *novoNodo, TipoMensagemEnum tipoMensagem);
void cadastrarDez(ListaEventos **listaEventos, TipoMensagemEnum tipoMensagem);
void cadDez(ListaEventos **listaEventos, TipoMensagemEnum tipoMensagem); // USAR ESTE PARA CADASTRAR 10 REGISTROS, PASSAR POR PARÂMETRO A LISTA/FILA/PILHA DESEJADA E O TIPO DE MENSAGEM


void cadastroAutomatico(ListaEventos *novoNodo, TipoMensagemEnum tipoMensagem){
	
	static int incrementador = 100;
	char inc[10];
	Evento novoEvento;
	novoEvento.protocolo = incrementador;
	novoEvento.tipoMensagem = tipoMensagem;
	
	strcpy(novoEvento.mensagem, "Mensagem_Automatica_");
	sprintf(inc, "%d", incrementador);
	strcat(novoEvento.mensagem, inc);
	
	novoNodo->evento = novoEvento;
	incrementador++;
	novoNodo->proximo = NULL;
}


void cadastrarDez(ListaEventos **listaEventos, TipoMensagemEnum tipoMensagem) {
	
	ListaEventos *novoNodo = (ListaEventos*) malloc (sizeof (ListaEventos));
	
	if (novoNodo != NULL) {
		
		cadastroAutomatico(novoNodo, tipoMensagem);
		
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
		printf( "\nNão há memória para cadastrar novo registro!\n" );
	}
	
}

void cadDez(ListaEventos **listaEventos, TipoMensagemEnum tipoMensagem) {
	
	for (int i = 0; i < 10; i++) {
		cadastrarDez(&*listaEventos, tipoMensagem);
	}
	
}
