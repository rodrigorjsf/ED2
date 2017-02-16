#ifndef ESTRUTURAS
#define ESTRUTURAS
#include <stdio.h>
typedef struct produto {
	char descricao [100];
	char cod [10];
	float preco;
	int estoque;
    int status;
} TProduto;

void cadastrar (FILE * arq, char codAux[]);
void alterar (FILE * arq, char codAux[]);
int buscarPos (FILE * arq, char codAux[]);
int buscar (FILE * arq, char codAux[]);
void consultar (FILE * arq, char codAux[]);
void remover (FILE * arq, char codAux[]);
void listarTodos (FILE * arq);
void manutencao (FILE * arq);

#endif
