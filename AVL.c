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

noAVL * CriarNo (char codigo[]){
	noAVL *raiz;
	char info [100];
	raiz = (noAVL *)malloc(sizeof(noAVL));
	strcpy (raiz->matricula, codigo);                        //raiz->cod = codigo;
	raiz->esq = NULL;
	raiz->dir = NULL;
	raiz->fatbal = 0;
	printf("Descreva o produto: \n");
	fgets (info, sizeof(info), stdin);
	strcpy(raiz->nome, info);                          //raiz->nome = info;
	printf("Digite a media do aluno: \n");
	scanf("%f", &raiz->media); fflush (stdin);
	printf("Quantidade de faltas do aluno: \n");
	scanf("%d", &raiz->faltas); fflush (stdin);
	return raiz;
}

int buscar (FILE * arq, char matAux[]) {
    int cont = -1, status;
    noAVL c;    //ponteiro ou nao?
    fseek (arq, 0, 0);
    while (1) {
        status = fread (&c, sizeof (noAVL), 1, arq);
        if (status != 1) {
            if (!feof(arq))
                return -2; // erro de leitura
            else
                return -1; // nao achou
        }
        else {
            cont++;
            if (c.status == 1 && strcmp (c.nome, nomeAux) == 0)
                return cont;
        }
    }
}

int carregaArquivo(noAVL **raiz){
    int elemento;                          /* variavel do tipo inteiro*/
    FILE* arquivo;                          /*variavel do tipo FILE*/
    arquivo = fopen("avl.txt","r");             /*arquivo aberto para leitura*/
    fseek(arquivo,0,SEEK_END);            /*recebendo coordenadas do arquivo*/
    if(ftell(arquivo) == 0)
      return 0;                         /*retorna 0*/
    fseek(arquivo,0,SEEK_SET);            /*recebendo coordenadas do arquivo */
    if(arquivo == NULL) {
        return 0;                          /* Retorna 0*/
    }
    else {
        while(!feof(arquivo)) {              /*se feof(arquivo)for diferente de NULL*/
          fscanf(arquivo,"%d",&elemento);       /*retira os elemento do arquivo*/
          inserir(&(*raiz),elemento);        /*insere os elementos do arquivo na arvore*/
        }
        system("cls");
    }
    fclose(arquivo);  /*fecha o arquivo*/
    return 1; /*retorna 1*/
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

void exibir_no (noAVL *raiz) {               //testar depois de ter tirado os *
	printf ("Produto: %s \n", raiz->nome);
	printf ("Codigo: %s \n", raiz->matricula);
	printf ("Preco: %.2f \n", raiz->media);
	printf ("Em Estoque: %d \n", raiz->faltas);
}

void exibir (noAVL *raiz, char codigo[]) {
	if (raiz == NULL){
		printf ("Codigo de produto nao cadastrado! \n");
		system ("pause");
	}
    else if (strcmp(codigo, raiz->matricula) == 0){
		exibir_no (raiz);
		system ("pause");
		return;
    }
	else if (strcmp(codigo, raiz->matricula) < 0)
		exibir (raiz->esq, codigo);
	else
		exibir (raiz->dir, codigo);
}

void alterar_no (noAVL ** raiz) {
	char info [100];
		printf(" - Alteracao de informacoes do Produto - \n");
		printf("Descreva o produto: \n");
		fgets (info, sizeof(info), stdin);
		strcpy((*raiz)->nome, info);
		printf("Digite o preco do produto: \n");
		scanf("%f", &(*raiz)->media); fflush (stdin);
		printf("Quantidade do produto em estoque: \n");
		scanf("%d", &(*raiz)->faltas); fflush (stdin);
}

void alterar (noAVL **raiz, char codigo[]) {
	if (*raiz == NULL){
		printf ("Codigo de produto nao cadastrado! \n");
		system ("pause");
	}
    else if (strcmp(codigo, (*raiz)->matricula) == 0){
		alterar_no (raiz);
		printf ("Produto alterado com sucesso! \n");
		system ("pause");
		return;
    }
	else if (strcmp(codigo, (*raiz)->matricula) < 0)
		alterar (&(*raiz)->esq, codigo);
	else
		alterar (&(*raiz)->dir, codigo);
}

void inserir (noAVL **raiz,char codigo[], int *status){

	if (*raiz == NULL){
		*raiz = CriarNo (codigo);
		*status = 1;
	}
	else if (strcmp(codigo, (*raiz)->matricula) == 0) {
		printf ("Codigo de produto repetido! \n");
		system ("pause");
	}
	else if (strcmp(codigo, (*raiz)->matricula) < 0) {
		inserir (&(*raiz)->esq, codigo, status);
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
		inserir (&(*raiz)->dir, codigo, status);
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
       printf("Elemento não encontrado.\n");
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
              printf("Produto deletado! \n");
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
