/*
	ESTRUTURA DE DADOS 2017/2
	Autores: Tiago Wolker Leite / Eduardo Moraes de Mello Alves / Bruno Vicente Alves
	Data: 05/11/2017
	Última atualização: 19/11/2017
	Enumerador de tipo de mensagem referente ao EventoService.
*/

enum TipoMensagemEnum {
	RECLAMACAO = 1,
	COMENTARIO = 2,
};

const char * tipoMensagemLabel(TipoMensagemEnum tipoMensagem) {
	
	switch (tipoMensagem) {
		case RECLAMACAO:
			return "Reclamação";
			break;
		case COMENTARIO:
		default:
			return "Comentário";
	}
}
