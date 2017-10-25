/**
 * ESTRUTURA DE DADOS
 * Autor: Tiago Wolker Leite
 * Data: 03/09/2017
 * Biblioteca básica
 */
 
 #include <ctype.h>
 #include <stdio.h>
 #include <stdbool.h>
 
// Verifica se há dados no array
bool temDados(int index) {
	
	if (index > 0) {
		return true;
	}
	return false;
}

// Função que verifica se há espaço no array
bool temEspaco(int index, int capacidade) {
	
	if (index == capacidade) {
		return false;
	}
	return true;
}

// Função de confirmação
bool confirmar() {
	
	char confirma;
	
	do {
		
		printf("\nConfirme a operação [S - Sim | N - Não]: ");
		fflush(stdin);
		scanf("%c", &confirma);
		
		confirma = toupper(confirma);
		
		if(confirma != 'S' && confirma != 'N') {
			printf("Opção inválida! Tente novamente...");
		}
		
	} while(confirma != 'S' && confirma != 'N');
	
	if(confirma == 'S') {
		printf("Operação realizada com sucesso!");
		return true;
	}
	printf("Operação cancelada!");
	return false;
	
}
