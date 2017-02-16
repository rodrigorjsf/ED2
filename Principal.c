#include <stdio.h>
#include "Header.h"

FILE * criarArquivo (char nome[]) { 
	FILE * arq;
	arq = fopen (nome, "r+b");
	if (arq == NULL) {
		arq = fopen (nome, "w+b");
	}
	return arq;
}

int main () {
	char op, codAux[100], nomeArq [] = "papelaria.dat";
	FILE * arq;
	arq = criarArquivo (nomeArq);
	if (arq == NULL) 
		printf ("Erro ao tentar criar/abrir arquivo \n");
	else {
	    do {
	   	   printf ("1 - Cadastrar Produto \n2 - Alterar preco do Produto \n");
		   printf ("3 - Consultar Produto \n4 - Remover Produto \n");
		   printf ("5 - Listar todos \n6 - Sair \n");
		   printf ("Digite a opcao: ");
		   op = getchar (); fflush (stdin);
		   switch (op) {
		   case '1': printf ("Informe o codigo: ");
			      gets (codAux); fflush (stdin);
				  cadastrar (arq, codAux);
				  break;
		   case '2': printf ("Informe o codigo: ");
			      gets (codAux); fflush (stdin);
				  alterar (arq, codAux);
				  break;
		   case '3': printf ("Informe o codigo: ");
			      gets (codAux); fflush (stdin);
				  consultar (arq, codAux);
				  break;
		   case '4': printf ("Informe o codigo: ");
			      gets (codAux); fflush (stdin);
				  remover (arq, codAux);
				  break;
		   case '5': listarTodos (arq);
			         break;
		   case '6': manutencao (arq);
			         break;
		   default: printf ("Opcao invalida \n");
		   }
		} while (op != '6');
	}
    return 0;
}
 

