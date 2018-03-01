/*
	ESTRUTURA DE DADOS 2017/2
	Autores: Tiago Wolker Leite / Eduardo Moraes de Mello Alves / Bruno Vicente Alves
	Data: 11/11/2017
	Última atualização: 03/12/2017
	Biblioteca para funções utilitárias e includes.
 */

// -- BIBLIOTECAS --
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

// Função de confirmação
bool confirmar() {
	
	char confirma;
	
	do {
		
		printf("\nConfirme a operação [S - Sim | N - Não]: ");
		fflush(stdin);
		scanf("%c", &confirma);
		
		confirma = toupper(confirma);
		
		if(confirma != 'S' && confirma != 'N') {
			printf("Opção inválida! Tente novamente...\n");
		}
		
	} while(confirma != 'S' && confirma != 'N');
	
	if(confirma == 'S') {
		printf("Operação realizada com sucesso!\n");
		return true;
	}
	printf("Operação cancelada!\n");
	return false;
	
}
