/*
	ESTRUTURA DE DADOS 2017/2
	Autores: Tiago Wolker Leite / Eduardo Moraes de Mello Alves / Bruno Vicente Alves
	Data: 05/11/2017
	Última atualização: 15/11/2017
	Sistema EventoService.
*/

// -- BIBLIOTECAS --
#include <stdlib.h>
#include <locale.h>

#include "EventoServiceFuncoes.h"
#include "FuncoesTeste.h"

// -- CONSTANTES --

// -- PROGRAMA PRINCIPAL --
main() {
	
	setlocale(LC_ALL, "portuguese");
	
	ListaEventos *listaEventos = NULL, *filaReclamacoes = NULL, *pilhaComentarios = NULL, *eventosAtendidos = NULL;
	int opcao;
	
	do {
		
		switch (opcao = menuPrincipal()) {
			case 1:
				// Cadastrar evento
				cadastrarEvento(&listaEventos);
				break;
			case 2:
				// Encaminhar eventos
				break;
			case 3:
				// Apresentar eventos
				break;
			case 4:
				// Consumir eventos
				menuConsumirEventos(&filaReclamacoes, &pilhaComentarios, &eventosAtendidos);
				break;
			case 5:
				// Informações eventos
				break;
			case 100:
				// TESTE CADASTRAR 10
				cadDez(&filaReclamacoes, reclamacao);
				cadDez(&pilhaComentarios, comentario);
				break;
			case 101:
				// TESTE EXIBIR 10 FILA
				listar(filaReclamacoes);
				break;
			case 102:
				// TESTE EXIBIR 10 PILHA
				listar(pilhaComentarios);
				break;
			case 0:
				// Sair
				printf("Sistema encerrado...\n");
				break;
			default:
				// Inválido
				printf("Opção inválida...\n");
		}
		
		system("pause");
		system("cls");
		
	} while (opcao != 0);
	
}
