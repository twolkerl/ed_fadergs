/*
	ESTRUTURA DE DADOS 2017/2
	Autores: Tiago Wolker Leite / Eduardo Moraes de Mello Alves / Bruno Vicente Alves
	Data: 05/11/2017
	Última atualização: 03/12/2017
	Sistema EventoService.
*/

// -- BIBLIOTECAS --

#include "controller/EventoServiceFuncoes.h"
//#include "controller/FuncoesTeste.h" // retirar as barras para utilizar as funções de teste

// -- CONSTANTES --

// -- PROGRAMA PRINCIPAL --
main() {
	
	setlocale(LC_ALL, "portuguese");
	
	ListaEventos *listaEventos = NULL, *filaReclamacoes = NULL, *pilhaComentarios = NULL, *eventosAtendidos = NULL;
	int opcao;
	
	do {
		
		switch (opcao = menu_principal()) {
			case 1:
				// Cadastrar evento
				cadastrar_evento(&listaEventos);
				break;
			case 2:
				// Encaminhar eventos
				encaminhar_eventos(&listaEventos, &filaReclamacoes, &pilhaComentarios);
				break;
			case 3:
				// Apresentar eventos
				apresentar_evento(listaEventos, filaReclamacoes, pilhaComentarios, eventosAtendidos);
				break;
			case 4:
				// Consumir eventos
				menu_consumir_eventos(&filaReclamacoes, &pilhaComentarios, &eventosAtendidos);
				break;
			case 5:
				// Informações eventos
				menu_info_eventos(listaEventos, filaReclamacoes, pilhaComentarios, eventosAtendidos);
				break;
//			case 100: // Função para testar
//				cad_dez(&listaEventos, RECLAMACAO);
//				cad_dez(&filaReclamacoes, RECLAMACAO);
//				cad_dez(&pilhaComentarios, COMENTARIO);
//				break;
			case 0:
				// Sair
				printf("Sistema encerrado...\n");
				break;
			default:
				// Inválido
				printf("Opção inválida...\n");
		}
		
		printf("\n");
		system("pause");
		system("cls");
		
	} while (opcao != 0);
	
}
