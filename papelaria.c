#include <stdio.h>
#include <string.h>
#include "Header.h"

int buscar (FILE * arq, char codAux[]) {
	int cont = -1, status;
	TProduto c;

	fseek (arq, 0, 0);
	while (1) {
		status = fread (&c, sizeof (TProduto), 1, arq);
		if (status != 1) {
			if (!feof(arq))
			    return -2; // erro de leitura
			else
				return -1; // nao achou
		}
		else {
			cont++;
			if (c.status == 1 && strcmp (c.cod, codAux) == 0)
				return cont;
		}
	}
}
/*int buscar (FILE * arq, char codAux[]) {
	int cont = -1, status;
	TProduto c;

	fseek (arq, 0, 0);
	while (1) {
		status = fread (&c, sizeof (TProduto), 1, arq);
		if (status != 1) {
			if (!feof(arq))
			    return -2; // erro de leitura
			else
				return -1; // nao achou
		}
		else {
			if (c.status == 1 && strcmp (c.cod, codAux) == 0)
				return 1;
		}
	}
}*/

void cadastrar (FILE * arq, char codAux[]) {
	TProduto c;
	int pos, status;

	pos = buscar (arq, codAux);
	if (pos != -1){
		printf ("Erro. Codigo de produto ja cadastado.\n");
		return;
	}
	else if (pos == -2){
		printf ("Erro de leitura \n");
		return;
	}
	fseek (arq, 0, 2);
	strcpy (c.cod, codAux);
	printf ("Informe a descricao do produto: ");
	gets (c.descricao); fflush (stdin);
	printf ("Informe o codigo do produto: ");
	gets (c.cod); fflush (stdin);
	printf ("Informe o preco do produto: ");
	scanf("%f", &c.preco); fflush (stdin);
	printf ("Informe o estoque do produto: ");
	scanf("%d", &c.estoque); fflush (stdin);
	c.status = 1;
	status = fwrite (&c, sizeof (TProduto), 1, arq);
	if (status != 1)
		printf ("Erro de gravacao \n");
	else
		printf ("Produto cadastrado com sucesso \n");
}

void alterar (FILE * arq, char codAux[]) {
	TProduto c;
	int pos, status;

	pos = buscar (arq, codAux);
	if (pos == -1)
		printf ("Produto nao cadastrado \n");
	else if (pos == -2)
		printf ("Erro de leitura \n");
	else {
		fseek(arq, pos * sizeof (TProduto), 0);
		status = fread (&c,sizeof (TProduto), 1, arq);
		if (status != 1)
			printf ("Erro de leitura \n");
		else {
			printf ("Informe o novo preco: ");
			scanf("%f", &c.preco); fflush (stdin);
			fseek(arq, -sizeof(TProduto), 1);
			status = fwrite (&c,sizeof (TProduto), 1, arq);
			if (status != 1)
				printf ("Erro de gravacao \n");
			else
				printf ("Produto alterado com sucesso \n");
		}
	}
}
void consultar (FILE * arq, char codAux[]) {
	TProduto c;
	int pos, status;

	pos = buscar (arq, codAux);
	if (pos == -1)
		printf ("Produto nao cadastrado \n");
	else if (pos == -2)
		printf ("Erro de leitura \n");
	else {
		fseek(arq, pos * sizeof (TProduto), 0);
		status = fread (&c,sizeof (TProduto), 1, arq);
		if (status != 1)
			printf ("Erro de leitura \n");
		else {
			printf ("Descricao: %s \n", c.descricao);
			printf ("Quantidade em estoque: %d \n", c.estoque);
		}
	}
}
void remover (FILE * arq, char codAux[]) {
	TProduto c;
	int pos, status;

	pos = buscar (arq, codAux);
	if (pos == -1)
		printf ("Produto nao cadastrado \n");
	else if (pos == -2)
		printf ("Erro de leitura \n");
	else {
		fseek(arq, pos * sizeof (TProduto), 0);
		status = fread (&c,sizeof (TProduto), 1, arq);
		if (status != 1)
			printf ("Erro de leitura \n");
		else {
			c.status = 0;
			fseek(arq, -sizeof(TProduto), 1);
			status = fwrite (&c,sizeof (TProduto), 1, arq);
			if (status != 1)
				printf ("Erro de gravacao \n");
			else
				printf ("Produto removido com sucesso \n");
		}
	}
}

void listarTodos (FILE * arq) {
	int status;
	TProduto c;

	fseek (arq, 0, 0);
	while (1) {
		status = fread (&c, sizeof (TProduto), 1, arq);
		if (status != 1) {
			if (!feof(arq)) 
			    printf ("Erro de leitura \n");
			break;
		}
		else {
			if (c.status == 1) {
				printf ("Descricao: %s \n", c.descricao);
				printf ("Codigo: %s \n", c.cod);
				printf ("Quantidade em estoque: %d \n", c.estoque);
				printf ("Preco: %f \n\n", c.preco);
			}
		}
	}
}

void manutencao (FILE * arq) {
	int status;
	TProduto c;
	FILE * aux;

	aux = fopen ("auxiliar", "w+b");
	if (aux == NULL) {
		printf ("Erro ao executar o processo de manutenção do arquivo \n");
		fclose (arq);
	}
	else {
	    fseek (arq, 0, 0);
	    while (1) {
		     status = fread (&c, sizeof (TProduto), 1, arq);
		     if (status != 1) {
			      if (!feof(arq)) {
			            printf ("Erro ao executar o processo de manutenção do arquivo \n");
						fclose (arq);
						fclose (aux);
						remove ("auxiliar");
						return;
				  }
				  else // fim de arquivo
			            break;
		    }
		    else {
			    if (c.status == 1) {
				     status = fwrite (&c, sizeof (TProduto), 1, aux);
				     if (status != 1) {
					    printf ("Erro ao executar o processo de manutenção do arquivo \n");
					    fclose (arq);
					    fclose (aux);
					    remove ("auxiliar");
					    return;
				     }
			   }
		   }
	    } // fim while
           fclose (arq);
		   fclose (aux);
	    remove ("papelaria.dat");
	    rename ("auxiliar", "papelaria.dat");
   }
}
