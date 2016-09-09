#include <stdio.h>
#include "AvlArquivo.h"

FILE * criarArquivo (char nome[]) {
	FILE * arq;
	arq = fopen (nome, "r+b");
	if (arq == NULL) {
		arq = fopen (nome, "w+b");
	}
	return arq;
}

int main () {
	system("color F0");
	FILE * projeto;
	noAVL * arvoreAvl = NULL;
	char op, nomeArq[] = "Contato.txt";
	char mat[10];
	int status = 0;
	int c = 0;
	projeto = criarArquivo (nomeArq);
	carregaArquivo(projeto, &arvoreAvl, &status);
	if (projeto == NULL)
			printf ("Erro ao tentar criar/abrir arquivo \n");
	else {
	   do {
		system ("cls");
		printf ("-------------------- ARVORE AVL -------------------- \n");
		printf ("1 - Inserir \n"); 		
		printf ("2 - Remover \n"); 
		printf ("3 - Exibir \n"); 
		printf ("4 - Alterar \n"); 
		printf ("5 - Listar \n"); 
		printf ("6 - Listar em ordem de matricula \n");
		printf ("7 - Sair \n");         
		printf ("informe a opcao: ");
		op = getchar(); fflush (stdin);
		switch(op){
		case '1': printf ("\n - Imforme a Matricula do aluno: ");
		          fgets(mat, sizeof(mat), stdin); fflush (stdin);
		          inserir (&arvoreAvl, mat, &status);
		          break;
		case '2': printf ("\n - Imforme a Matricula do aluno: ");
		          fgets(mat, sizeof(mat), stdin); fflush (stdin);
                  remover (&arvoreAvl, mat, &c);
                  break;
		case '3': printf ("\n - Imforme a Matricula do aluno: ");
		          fgets(mat, sizeof(mat), stdin); fflush (stdin);
                  exibir (arvoreAvl, mat);
                  break;
		case '4': printf ("\n - Imforme a Matricula do aluno: ");
                  fgets(mat, sizeof(mat), stdin); fflush (stdin);
                  alterar (arvoreAvl, mat);
                  break;
		case '5': listarTodos (); 
		          system ("pause");
                  break;
		case '6': ExibirEmOrdem (arvoreAvl);
		          system ("pause");
                  break;
		case '7': manutencao ();
			      removerTodos (&arvoreAvl);
                  break;
		default:  printf ("Opcao invalida \n");
		}

	}while (op != '7');
	system ("pause");
	}
	return 0;
}

