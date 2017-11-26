/*
	ESTRUTURA DE DADOS 2017/2
	Autores: Tiago Wolker Leite / Eduardo Moraes de Mello Alves / Bruno Vicente Alves
	Data: 05/11/2017
	Última atualização: 19/11/2017
	Estruturas relacionadas ao EventoService.
*/

// -- BIBLIOTECAS --
#include "TipoMensagemEnum.h"
#include "StatusEventoEnum.h"

typedef struct {
	int protocolo;
	TipoMensagemEnum tipoMensagem;
	StatusEventoEnum statusEvento;
	char mensagem[500];
	int segCadastro;
	int tempoAguardo;
} Evento;

typedef struct ListaEventos {
	Evento evento;
	ListaEventos *proximo;
} ListaEventos;
