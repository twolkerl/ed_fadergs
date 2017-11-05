/*
	ESTRUTURA DE DADOS 2017/2
	Autores: Tiago Wolker Leite / Eduardo Moraes de Mello Alves / Bruno Vicente Alves
	Data: 05/11/2017
	Última atualização: 05/11/2017
	Enumerador de tipo de mensagem referente ao EventoService.
*/

enum TipoMensagemEnum {
	reclamacao = 1,
	comentario = 2,
};

const char * tipoMensagemLabel(TipoMensagemEnum tipoMensagem) {
	
	switch (tipoMensagem) {
		case 1:
			return "Reclamação";
			break;
		case 2:
			return "Comentário";
			break;
		default:
			return "";
	}
}
