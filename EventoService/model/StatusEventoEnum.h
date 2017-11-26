/*
	ESTRUTURA DE DADOS 2017/2
	Autores: Tiago Wolker Leite / Eduardo Moraes de Mello Alves / Bruno Vicente Alves
	Data: 19/11/2017
	�ltima atualiza��o: 19/11/2017
	Enumerador de status do evento referente ao EventoService.
*/

enum StatusEventoEnum {
	ATENDIDO = true,
	NAO_ATENDIDO = false,
};

const char * statusEventoLabel(StatusEventoEnum statusEvento) {
	
	switch (statusEvento) {
		case ATENDIDO:
			return "Atendido";
			break;
		case NAO_ATENDIDO:
		default:
			return "N�o atendido";
	}
}
