/*
	ESTRUTURA DE DADOS 2017/2
	Autores: Tiago Wolker Leite / Eduardo Moraes de Mello Alves / Bruno Vicente Alves
	Data: 11/11/2017
	�ltima atualiza��o: 15/11/2017
	Biblioteca para fun��es utilit�rias.
 */

// -- BIBLIOTECAS --
 #include <ctype.h>
 #include <stdio.h>
 #include <stdbool.h>

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
