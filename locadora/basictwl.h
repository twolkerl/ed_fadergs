/**
 * ESTRUTURA DE DADOS
 * Autor: Tiago Wolker Leite
 * Data: 03/09/2017
 * Biblioteca b�sica
 */
 
 #include <ctype.h>
 #include <stdio.h>
 #include <stdbool.h>
 
// Verifica se h� dados no array
bool temDados(int index) {
	
	if (index > 0) {
		return true;
	}
	return false;
}

// Fun��o que verifica se h� espa�o no array
bool temEspaco(int index, int capacidade) {
	
	if (index == capacidade) {
		return false;
	}
	return true;
}

// Fun��o de confirma��o
bool confirmar() {
	
	char confirma;
	
	do {
		
		printf("\nConfirme a opera��o [S - Sim | N - N�o]: ");
		fflush(stdin);
		scanf("%c", &confirma);
		
		confirma = toupper(confirma);
		
		if(confirma != 'S' && confirma != 'N') {
			printf("Op��o inv�lida! Tente novamente...");
		}
		
	} while(confirma != 'S' && confirma != 'N');
	
	if(confirma == 'S') {
		printf("Opera��o realizada com sucesso!");
		return true;
	}
	printf("Opera��o cancelada!");
	return false;
	
}
