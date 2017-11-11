/*
	ESTRUTURA DE DADOS 2017/2
	Autores: Tiago Wolker Leite / Eduardo Moraes de Mello Alves / Bruno Vicente Alves
	Data: 05/11/2017
	�ltima atualiza��o: 05/11/2017
	Enumerador de tipo de mensagem referente ao EventoService.
*/

enum TipoMensagemEnum {
	reclamacao = 1,
	comentario = 2,
};

const char * tipoMensagemLabel(TipoMensagemEnum tipoMensagem) {
	
	switch (tipoMensagem) {
		case 1:
			return "Reclama��o";
			break;
		case 2:
			return "Coment�rio";
			break;
		default:
			return "";
	}
}
