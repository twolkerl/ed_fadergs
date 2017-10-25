typedef struct {
	int codigo;
	char titulo[50];
} Filme;

typedef struct ListaFilmes {
	Filme filme;
	struct ListaFilmes *prox;
} ListaFilmes;
