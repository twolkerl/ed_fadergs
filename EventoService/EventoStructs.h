/*
	ESTRUTURA DE DADOS 2017/2
	Autores: Tiago Wolker Leite / Eduardo Moraes de Mello Alves / Bruno Vicente Alves
	Data: 05/11/2017
	�ltima atualiza��o: 15/11/2017
	Estruturas relacionadas ao EventoService.
*/

// -- BIBLIOTECAS --
#include "TipoMensagemEnum.h"

typedef struct {
	int protocolo;
	TipoMensagemEnum tipoMensagem;
	char mensagem[500];
} Evento;

typedef struct ListaEventos {
	Evento evento;
	ListaEventos *proximo;
} ListaEventos;
