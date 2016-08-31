/*
 * AVL.c
 *
 *  Created on: 27 de ago de 2016
 *      Author: Rodrigo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include "AVL.h"
#define TRUE 1
#define FALSE 0

noAVL * CriarNo (FILE * projeto, char codigo[]){
	noAVL * raiz;
	char info [100];
	int status;

	fseek (projeto, 0, 2);
	raiz = (noAVL *)malloc(sizeof(noAVL));
	strcpy (raiz->matricula, codigo);                        //raiz->cod = codigo;
	raiz->esq = NULL;
	raiz->dir = NULL;
	raiz->fatbal = 0;
	raiz->status = 1;
	printf("Digite o nome do Aluno: \n");
	fgets (info, sizeof(info), stdin);
	strcpy(raiz->nome, info);                               //raiz->nome = info;
	printf("Digite a media do aluno: \n");
	scanf("%f", &raiz->media); fflush (stdin);
	printf("Quantidade de faltas do aluno: \n");
	scanf("%d", &raiz->faltas); fflush (stdin);
	status = fwrite(raiz,sizeof(noAVL),1,projeto);
	if (status != 1){
			printf ("Erro de gravacao \n");
			system("pause");
	}
		else{
			printf ("Contato cadastrado com sucesso \n");
			system("pause");
		}
	return raiz;
}

int buscar (FILE * projeto, char matricula[]) {
	int cont = -1, status;
	noAVL c;

	fseek (projeto, 0, 0);
	while (1) {
		status = fread (&c, sizeof (noAVL), 1, projeto);
		if (status != 1) {
			if (!feof(projeto))
			    return -2; // erro de leitura
			else
				return -1; // nao achou
		}
		else {
			cont++;
			if (c.status == 1 && strcmp (c.nome, matricula) == 0)
				return cont;
		}
	}
}

int carregaArquivo(FILE * projeto, noAVL **raiz, int * status){
	noAVL * aux;
    fseek(projeto,0,SEEK_END);
    if(ftell(projeto) == 0)              // FTELL retorna a posição corrente de leitura ou escrita no arquivo (em bytes). Se for 0, arquivo vazio
    	return 0;
    fseek(projeto,0,SEEK_SET);
    if(projeto == NULL) {
    	return 0;
    }
    else {
    	while(!feof(projeto)) {
    		fread (aux, sizeof(noAVL), 1, projeto);
            inserir_do_Arq (&(*raiz),&aux, status);
        }
    	printf ("Arquivo carregado com sucesso!\n");
        system("pause");
        system("cls");
    }
    return 1;
}

int isEmpty (Queue fila) {
    if (fila->inicio == NULL)
       return TRUE;
    else
       return FALSE;
}

void enqueue (Queue fila, noAVL * n) {
     TNo * novo;
     novo = (TNo *) malloc (sizeof (TNo));
     novo->info = n;
     novo->prox = NULL;
     if (isEmpty (fila) == TRUE)
        fila->inicio = novo;
     else
        fila->fim->prox = novo;
     fila->fim = novo;
}

noAVL * dequeue (Queue fila) {
     TNo * aux;
     noAVL * n;
     aux = fila->inicio;
     fila->inicio = fila->inicio->prox;
     if (isEmpty (fila) == TRUE)
        fila->fim = NULL;
     n = aux->info;
     free (aux);
return n;
}

/*int head (Queue fila) {
  return fila->inicio->info;
}*/

void initialize (Queue * fila) {
     *fila = (TDescritor *) malloc (sizeof (TDescritor));
     (*fila)->inicio = NULL;
     (*fila)->fim = NULL;
}

void percorrerPorNivel(noAVL * raiz) {
  Queue fila;
  noAVL * aux;
  if (raiz != NULL) {
      initialize(&fila);
      enqueue (fila, raiz);
      while (isEmpty(fila) == FALSE) {                    //stdbool
            aux = dequeue(fila);
         if (aux->esq != NULL)
           enqueue(fila,aux->esq);
         if (aux->dir != NULL)
           enqueue(fila,aux->dir);
         printf("%s FB:%d \n", aux->matricula, aux->fatbal);
         }
  }
}

int altura(noAVL* t) {
	if (t == NULL)
		return 0;
	int hesq = altura(t->esq);
	int hdir = altura(t->dir);
	return hesq > hdir ? hesq + 1 : hdir + 1;
}

void LL(noAVL** r) {             // rotação simples a direita do INSERIR
	noAVL* b = *r;
	noAVL* a = b->esq;
	b->esq = a->dir;
	a->dir = b;
	a->fatbal = 0;
	b->fatbal = 0;
	*r = a;
}

void LR(noAVL** r) {            // rotação dupla a direita do INSERIR
	noAVL *a = *r;
	noAVL *b = a->esq;
	noAVL *c = b->dir;
	a->esq = c->dir;
	b->dir = c->esq;
	c->esq = b;
	c->dir = a;
	switch (c->fatbal) {
	case -1:
		b->fatbal = 0;
		a->fatbal = 1;
		break;
	case 0:
		b->fatbal = 0;
		a->fatbal = 0;
		break;
	case +1:
		b->fatbal = -1;
		a->fatbal = 0;
		break;
	}
	c->fatbal = 0;
	*r = c;
}

void RR(noAVL** r) {                  // rotação simples a esquerda do INSERIR
	noAVL* a = *r;
	noAVL* b = a->dir;
	a->dir = b->esq;
	b->esq = a;
	a->fatbal = 0;
	b->fatbal = 0;
	*r = b;
}

void RL(noAVL** r) {                 // rotação dupla a esquerda do INSERIR
	noAVL *a = *r;
	noAVL *c = a->dir;
	noAVL *b = c->esq;
	c->esq = b->dir;
	a->dir = b->esq;
	b->esq = a;
	b->dir = c;
	switch (b->fatbal) {
	case -1:
		a->fatbal = 0;
		c->fatbal = 1;
		break;
	case 0:
		a->fatbal = 0;
		c->fatbal = 0;
		break;
	case +1:
		a->fatbal = -1;
		c->fatbal = 0;
		break;
	}
	b->fatbal = 0;
	*r = b;
}

void LLRem(noAVL** r) {                   // rotação simples a direita do REMOVER
	noAVL* a = *r;
	noAVL* b = a->esq;
	a->esq = b->dir;
	b->dir = a;
	if (b->fatbal == -1)
		a->fatbal = 0;
	else{
		b->fatbal = 1;
		a->fatbal = -1;
	}
	*r = b;
}

void LRRem (noAVL ** raiz) {                 // rotação dupla a direita do REMOVER
	noAVL * b, * c;
	  b = (*raiz)->esq;
	  c = b->dir;
      b->dir = c->esq;
      c->esq = b;
      (*raiz)->esq = c->dir;
      c->dir = *raiz;
      switch (c->fatbal) {
            case 1: (*raiz)->fatbal = 0;
                    b->fatbal = -1;
                    break;
            case 0: (*raiz)->fatbal = 0;            //duvida c->fatbal = 0
          		    b->fatbal = 0;
                    break;
            case -1:(*raiz)->fatbal = 1;
                    b->fatbal = 0;
                    break;
      }
       *raiz = c;
      (*raiz)->fatbal = 0;
}

void RRRem(noAVL** r) {                         //rotacão simples a esquerda do REMOVER
	noAVL* a = *r;
	noAVL* b = a->dir;
	a->dir = b->esq;
	b->esq = a;
	if (b->fatbal == 1)
		a->fatbal = 0;
	else{
		a->fatbal = 1;
		b->fatbal = -1;
	}
	*r = b;
}

void RLRem (noAVL ** raiz) {                     // rotação dupla a Esquerda do REMOVER
	noAVL * b, * c;
	  b = (*raiz)->dir;
	  c = b->esq;
      b->esq = c->dir;
      c->esq = b;
      (*raiz)->esq = c->dir;
      c->dir = *raiz;
      switch (c->fatbal) {
      case 1: (*raiz)->fatbal = -1;
              b->fatbal = 0;
              break;
      case 0: (*raiz)->fatbal = 0;           //duvida c->fatbal = 0
    		  b->fatbal = 0;
              break;
      case -1:(*raiz)->fatbal = 0;
              b->fatbal = 1;
              break;
      }
       *raiz = c;
      (*raiz)->fatbal = 0;
}

void exibir_noTodo (FILE * projeto, char matricula[]) {
	noAVL aux;
	int pos, status;
	pos = buscar (projeto, matricula);
	if (pos == -1)
	    			printf ("Contato nao cadastrado \n");
	    	else if (pos == -2)
	    			printf ("Erro de leitura \n");
	    	else {
	    			fseek(projeto, pos * sizeof (noAVL), 0);   //duvida de fseek
	    			status = fread (&aux,sizeof (noAVL), 1, projeto);
	    			if (status != 1)
	    				printf ("Erro de leitura \n");
	    			else {
	    				printf ("Aluno: %s \n", aux.nome);
	    				printf ("Matricula: %s \n", aux.matricula);
	    				printf ("Media do Aluno: %.2f \n", aux.media);
	    				printf ("Quantidade de faltas do Aluno: %i \n\n", aux.faltas);
	    			}
	    		}
}

void exibir_no (FILE * projeto, char matricula[]) {
	noAVL aux;
	int pos, status;
	pos = buscar (projeto, matricula);
	if (pos == -1)
	    			printf ("Contato nao cadastrado \n");
	    	else if (pos == -2)
	    			printf ("Erro de leitura \n");
	    	else {
	    			fseek(projeto, pos * sizeof (noAVL), 0);   //duvida de fseek
	    			status = fread (&aux,sizeof (noAVL), 1, projeto);
	    			if (status != 1)
	    				printf ("Erro de leitura \n");
	    			else {
	    				printf ("Aluno: %s \n", aux.nome);
	    				printf ("Media do Aluno: %.2f \n", aux.media);
	    				printf ("Quantidade de faltas do Aluno: %i \n", aux.faltas);
	    			}
	    		}
}

void exibir (FILE * projeto, noAVL *raiz, char matricula[]) {
	if (raiz == NULL){
		printf ("Matricula de Aluno nao cadastrada! \n");
		system ("pause");
	}
    else if (strcmp(matricula, raiz->matricula) == 0){
    	exibir_no (projeto, matricula);
		system ("pause");
		return;
    }
	else if (strcmp(matricula, raiz->matricula) < 0)
		exibir (raiz->esq, matricula);
	else
		exibir (raiz->dir, matricula);
}

void alterar_no (FILE * projeto, char matricula[]) {
	    noAVL aux;
	    char op;
		int pos, status;
		pos = buscar (projeto, matricula);
		if (pos == -1)
			printf ("Contato nao cadastrado \n");
		else if (pos == -2)
			printf ("Erro de leitura \n");
		else {
			fseek(projeto, pos * sizeof (noAVL), 0);
			status = fread (&aux,sizeof (noAVL), 1, projeto);
			if (status != 1)
				printf ("Erro de leitura \n");
			else {
					 printf("1 - ALterar Media do aluno  \n");
					 printf("2 - ALterar quantidade de faltas do aluno  \n");
					 printf("3 - ALterar Media e quantidade de faltas do aluno  \n");
					 op = getchar(); fflush (stdin);
					    switch(op){
					    case '1':printf ("Alteracao de dados de %s \n", aux.nome);
					             printf ("Informe a nova media do Aluno: \n");
					    		 gets (aux.media); fflush (stdin);
					    		 fseek(projeto, -sizeof(noAVL), 1);
					    		 status = fwrite (&aux,sizeof (noAVL), 1, projeto);
					    		 if (status != 1)
					    			 printf ("Erro de gravacao \n");
					    		 else
					    		 	 printf ("Contato alterado com sucesso \n");
					             break;
					    case '2':printf ("Alteracao de dados de %s \n", aux.nome);
					             printf ("Informe a nova quantidade de faltas: \n");
					    		 gets (aux.faltas); fflush (stdin);
					    		 fseek(projeto, -sizeof(noAVL), 1);
					    		 status = fwrite (&aux,sizeof (noAVL), 1, projeto);
					    		 if (status != 1)
					    			 printf ("Erro de gravacao \n");
					    	     else
					    			 printf ("Contato alterado com sucesso \n");
					             break;
						case '3':printf ("Alteracao de dados de %s \n", aux.nome);
						         printf ("Informe a nova media do Aluno: \n");
								 gets (aux.media); fflush (stdin);
								 printf ("Informe a nova quantidade de faltas: \n");
								 gets (aux.faltas); fflush (stdin);
								 fseek(projeto, -sizeof(noAVL), 1);
								 status = fwrite (&aux,sizeof (noAVL), 1, projeto);
								 if (status != 1)
									 printf ("Erro de gravacao \n");
								 else
									 printf ("Contato alterado com sucesso \n");
					             break;
						default: printf("Operador inválido\n");
					    }
			}

		}
}


	/*char info [100];
		printf(" - Alteracao de informacoes do Aluno - \n");
		printf("Descreva o produto: \n");
		fgets (info, sizeof(info), stdin);
		strcpy((*raiz)->nome, info);
		printf("Digite o preco do produto: \n");
		scanf("%f", &(*raiz)->media); fflush (stdin);
		printf("Quantidade do produto em estoque: \n");
		scanf("%d", &(*raiz)->faltas); fflush (stdin);
}*/

void alterar (FILE * projeto, noAVL **raiz, char matricula[]) {
	if (*raiz == NULL){
		printf ("Matricula de Aluno nao cadastrada! \n");
		system ("pause");
	}
    else if (strcmp(matricula, (*raiz)->matricula) == 0){
		alterar_no (projeto, matricula);
		printf ("Registro de Aluno alterado com sucesso! \n");
		system ("pause");
		return;
    }
	else if (strcmp(matricula, (*raiz)->matricula) < 0)
		alterar (&(*raiz)->esq, matricula);
	else
		alterar (&(*raiz)->dir, matricula);
}

void inserir (FILE * projeto, noAVL **raiz,char codigo[], int *status){

	if (*raiz == NULL){
		*raiz = CriarNo (codigo);
		*status = 1;
	}
	else if (strcmp(codigo, (*raiz)->matricula) == 0) {
		printf ("Matricula de Aluno repetida! \n");
		system ("pause");
	}
	else if (strcmp(codigo, (*raiz)->matricula) < 0) {
		inserir (projeto, &(*raiz)->esq, codigo, status);
		     if (*status == 1)
		       switch ((*raiz)->fatbal) {
		         case 1 : (*raiz)->fatbal = 0;
		                  *status = 0;
		                  break;
		         case 0 : (*raiz)->fatbal = -1;
		                  break;
		         case -1 : if((*raiz)->esq->fatbal == -1 )
		        	           LL(raiz);                   // rotação simples a direita  LL = Left Left - direção dos filhos de 'A'
		                   else
		                	   LR(raiz);                   // rotação dupla a esquerda   LR = Left Right - direção dos filhos de 'A'
		                   *status = 0;                    //alteração de status fora dos procedimentos de rotação
		                   break;
		       }
	}
	else {
		inserir (projeto, &(*raiz)->dir, codigo, status);
		     if (*status == 1)
		       switch ((*raiz)->fatbal) {
		       case -1 : (*raiz)->fatbal = 0;
		                *status = 0;
		                break;
		       case 0 : (*raiz)->fatbal = 1;
                        break;
		       case 1 : if((*raiz)->dir->fatbal == 1)
		    	           RR(raiz);                     // rotação simples a esquerda RR = Right Right - direção dos filhos de 'A'
		                else
		                   RL(raiz);                     //rotação dupla a esquerda    RL = Right Left - direção dos filhos de 'A'
		                *status = 0;                     //alteração de status fora dos procedimentos de rotação
                        break;
		}
	}
}

void inserir_do_Arq (noAVL **raiz,noAVL **aux, int *status){

	if (*raiz == NULL){
		*raiz = *aux;
		*status = 1;
	}
	else if (strcmp((*aux)->matricula, (*raiz)->matricula) == 0) {
		printf ("Matricula de Aluno repetida! \n");
		system ("pause");
	}
	else if (strcmp((*aux)->matricula, (*raiz)->matricula) < 0) {
		inserir (&(*raiz)->esq, &(*aux), status);
		     if (*status == 1)
		       switch ((*raiz)->fatbal) {
		         case 1 : (*raiz)->fatbal = 0;
		                  *status = 0;
		                  break;
		         case 0 : (*raiz)->fatbal = -1;
		                  break;
		         case -1 : if((*raiz)->esq->fatbal == -1 )
		        	           LL(raiz);                   // rotação simples a direita  LL = Left Left - direção dos filhos de 'A'
		                   else
		                	   LR(raiz);                   // rotação dupla a esquerda   LR = Left Right - direção dos filhos de 'A'
		                   *status = 0;                    //alteração de status fora dos procedimentos de rotação
		                   break;
		       }
	}
	else {
		inserir (&(*raiz)->dir, &(*aux), status);
		     if (*status == 1)
		       switch ((*raiz)->fatbal) {
		       case -1 : (*raiz)->fatbal = 0;
		                *status = 0;
		                break;
		       case 0 : (*raiz)->fatbal = 1;
                        break;
		       case 1 : if((*raiz)->dir->fatbal == 1)
		    	           RR(raiz);                     // rotação simples a esquerda RR = Right Right - direção dos filhos de 'A'
		                else
		                   RL(raiz);                     //rotação dupla a esquerda    RL = Right Left - direção dos filhos de 'A'
		                *status = 0;                     //alteração de status fora dos procedimentos de rotação
                        break;
		}
	}
}


noAVL * maior(noAVL **raiz) {
    noAVL *aux;
    if ((*raiz)->dir == NULL) {
        aux = *raiz;
        *raiz = (*raiz)->esq;
    }
    else {
        aux = maior(&((*raiz)->dir));
           switch ((*raiz)->fatbal) {
              case 1 : (*raiz)->fatbal = 0; break;
              case 0 : (*raiz)->fatbal = -1; break;
              case -1 : if((*raiz)->esq->fatbal == -1 || (*raiz)->esq->fatbal == 0)  //rotacaoDirRem(raiz); break;
     	                   LLRem(raiz);
                        else
             	           LRRem(raiz);
                        break;
           }
    }
return aux;
}

void remover_no(noAVL **raiz) {
     noAVL * pos;
     pos = *raiz;
     if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) // Não tem filhos
        *raiz = NULL;
     else if ((*raiz)->esq == NULL) // Não tem filho a esquerda
        *raiz = (*raiz)->dir;
     else if ((*raiz)->dir == NULL) // Não tem filho a direita
        *raiz = (*raiz)->esq;
     else {                        // Tem ambos os filhos
        pos = maior(&((*raiz)->esq));
        strcpy((*raiz)->matricula, pos->matricula);
        strcpy((*raiz)->nome, pos->nome);
        (*raiz)->media = pos->media;
        (*raiz)->faltas = pos->faltas;
     }
free (pos);
}

void remover(noAVL **raiz, char codigo[], int * cont) {
	int altesq, altdir;
    if (*raiz == NULL){
       printf("Matricula nao encontrada.\n");
       system ("pause");
    }
    else if (strcmp(codigo,(*raiz)->matricula) == 0) {
       remover_no(raiz);
              if (cont == 0) {
                  altesq = altura ((*raiz)->esq);                            //TIRAR DUVIDA
                  altdir = altura ((*raiz)->dir);
            	  if (altdir - altesq == -1)
            		  (*raiz)->fatbal = -1;
            	 else if (altdir - altesq == 0)
            		  (*raiz)->fatbal = 0;
            	 else
            		  (*raiz)->fatbal = 1;
              }
              printf("Registro de Aluno Deletado! \n");
              system ("pause");
    }
    else if (strcmp(codigo, (*raiz)->matricula) < 0) {
       remover(&((*raiz)->esq),codigo, cont++);
         switch ((*raiz)->fatbal) {
             case -1 : (*raiz)->fatbal = 0; break;
             case 0 : (*raiz)->fatbal = 1; break;
             case 1 : if((*raiz)->dir->fatbal == 0 || (*raiz)->dir->fatbal == 1)   // rotacaoEsqRem(raiz); break;
            	        RRRem(raiz);
                      else
                    	RLRem(raiz);
                      break;
         }
    }
    else {
       remover(&((*raiz)->dir),codigo, cont++);
         switch ((*raiz)->fatbal) {
             case 1 : (*raiz)->fatbal = 0; break;
             case 0 : (*raiz)->fatbal = -1; break;
             case -1 : if((*raiz)->esq->fatbal == -1 || (*raiz)->esq->fatbal == 0)  //rotacaoDirRem(raiz); break;
            	         LLRem(raiz);
                       else
                    	 LRRem(raiz);
                       break;
         }
    }
}

void removeAll(noAVL **raiz){
     noAVL * pos;
     pos = *raiz;
     *raiz = NULL;
     free (pos);
}

void removerTodos (noAVL **raiz) {
    if (*raiz != NULL) {
        removerTodos(&(*raiz)->esq);
        removerTodos(&(*raiz)->dir);
        removeAll(&(*raiz));   //printf(“%i \n”, raiz->cod);
        }
}

void listarTodos (FILE * projeto) {
	int status;
	noAVL c;

	fseek (projeto, 0, 0);
	while (1) {
		status = fread (&c, sizeof (noAVL), 1, projeto);
		if (status != 1) {
			if (!feof(projeto))
			    printf ("Erro de leitura \n");
			break;
		}
		else {
			if (c.status == 1) {
				printf ("Matricula: %d \n", c.matricula);
				printf ("Nome: %s \n", c.nome);
				printf ("Media: %s \n", c.media);
				printf ("Faltas: %s \n", c.faltas);
			}
		}
	}
}


void ExibirEmOrdem (FILE * projeto, noAVL **raiz) {
    if (*raiz != NULL) {
    	ExibirEmOrdem(projeto, &(*raiz)->esq);
    	ExibirEmOrdem(projeto, &(*raiz)->dir);
        exibir_noTodo(projeto, (*raiz)->matricula);   //printf(“%i \n”, raiz->cod);
        }
}
