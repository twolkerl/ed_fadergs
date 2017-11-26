/*
	FUN��ES DE TESTE
*/
#include <string.h>

void cadastro_automatico(ListaEventos *novoNodo, TipoMensagemEnum tipoMensagem); // Fun��o interna da biblioteca, n�o utilizar!
void cadastrar_dez(ListaEventos **listaEventos, TipoMensagemEnum tipoMensagem); // Fun��o interna da biblioteca, n�o utilizar!
void cad_dez(ListaEventos **listaEventos, TipoMensagemEnum tipoMensagem); // USAR ESTE PARA CADASTRAR 10 REGISTROS, PASSAR POR PAR�METRO A LISTA/FILA/PILHA DESEJADA E O TIPO DE MENSAGEM


void cadastro_automatico(ListaEventos *novoNodo, TipoMensagemEnum tipoMensagem){
	
	static int incrementador = 100;
	char inc[10];
	Evento novoEvento;
	novoEvento.protocolo = incrementador;
	novoEvento.tipoMensagem = tipoMensagem;
	novoEvento.statusEvento = NAO_ATENDIDO;
	novoEvento.segCadastro = time(NULL);
	
	strcpy(novoEvento.mensagem, "Mensagem_Automatica_");
	sprintf(inc, "%d", incrementador);
	strcat(novoEvento.mensagem, inc);
	
	novoNodo->evento = novoEvento;
	incrementador++;
	novoNodo->proximo = NULL;
}


void cadastrar_dez(ListaEventos **listaEventos, TipoMensagemEnum tipoMensagem) {
	
	ListaEventos *novoNodo = (ListaEventos*) malloc (sizeof (ListaEventos));
	
	if (novoNodo != NULL) {
		
		cadastro_automatico(novoNodo, tipoMensagem);
			
		switch (tipoMensagem) {
			case RECLAMACAO:
				// Cadastra na fila
				if (*listaEventos == NULL) {
					
					*listaEventos = novoNodo;
				} else {
					ListaEventos *percorreFila = *listaEventos;
					
					while (percorreFila->proximo != NULL) {
						percorreFila = percorreFila->proximo;
					}
					
					percorreFila->proximo = novoNodo;
				}
				
				break;
				
			case COMENTARIO:
			default:
				// Cadastra na pilha
				novoNodo->proximo = *listaEventos;
				*listaEventos = novoNodo;
		}
		
	} else {
		printf( "\nN�o h� mem�ria para cadastrar novo registro!\n" );
	}
	
}

void cad_dez(ListaEventos **listaEventos, TipoMensagemEnum tipoMensagem) {
	
	for (int i = 0; i < 10; i++) {
		cadastrar_dez(&*listaEventos, tipoMensagem);
	}
	
}
