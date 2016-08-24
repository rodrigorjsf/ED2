/*
 ============================================================================
 Name        : AVL.c
 Author      : Rodrigo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
2 *  �?rvore AVL
 *  (Adelson-Velskii e Landis)
 *
 *  Fator de balanceamento = hdir - hesq
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#define TRUE 1
#define FALSE 0

typedef struct noAvl {
	char cod [10], desc [100];
	float preco;
	int estoque;
	struct noAvl * esq, * dir;
	int fatbal;
}noAVL;

typedef struct no {
     noAVL * info;
    struct no * prox;
} TNo;

typedef struct descritor {
    TNo *inicio, *fim;
} TDescritor;

typedef TDescritor * Queue;

noAVL * CriarNo (char codigo[]);

int isEmpty (Queue fila);

void enqueue (Queue fila, noAVL * n);

noAVL * dequeue (Queue fila);

//int head (Queue fila);

void initialize (Queue * fila);

void percorrerPorNivel(noAVL * raiz);

int altura(noAVL* t);

void LL(noAVL** r);

void LR(noAVL** r);

void RR(noAVL** r);

void RL(noAVL** r);

void LLRem(noAVL** r);

void LRRem (noAVL ** raiz);

void RRRem(noAVL** r);

void RLRem (noAVL ** raiz);

void exibir_no (noAVL *raiz);

void exibir (noAVL *raiz, char codigo[]);

void alterar_no (noAVL ** raiz);

void alterar (noAVL **raiz, char codigo[]);

void inserir (noAVL **raiz,char codigo[], int *status);

void remover(noAVL **raiz, char codigo[]);

void removeAll(noAVL **raiz);

void removerTodos (noAVL **raiz);

void emOrdem (noAVL * raiz);

int main () {
	system("color F0");
	noAVL * arvoreAvl = NULL;
	char op;
	char cod[10];
	int status = 0;
	do {
		system ("cls");
		printf ("-------------------- ARVORE AVL -------------------- \n");
		printf ("1 - Inserir \n");
		printf ("2 - Remover \n");
		printf ("3 - Exibir \n");
		printf ("4 - Alterar \n");
		printf ("5 - Listar \n");
		printf ("6 - Sair \n");          //teste
		printf ("informe a opcao: ");
		op = getchar(); fflush (stdin);
		switch(op){
		case '1': printf ("\n - Informe o codigo: ");
		          fgets(cod, sizeof(cod), stdin); fflush (stdin);
		          inserir (&arvoreAvl, cod, &status);
		          break;
		case '2': printf ("\n - Informe o codigo: ");
		          fgets(cod, sizeof(cod), stdin); fflush (stdin);
                  remover (&arvoreAvl, cod);
                  break;
		case '3': printf ("\n - Informe o codigo: ");
		          fgets(cod, sizeof(cod), stdin); fflush (stdin);
                  exibir (arvoreAvl, cod);
                  break;
		case '4': printf ("\n - Informe o codigo: ");
                  fgets(cod, sizeof(cod), stdin); fflush (stdin);
                  alterar (&arvoreAvl, cod);
                  break;
		case '5': percorrerPorNivel (arvoreAvl);
		          system ("pause");
                  break;
		case '6': removerTodos (&arvoreAvl);
                  break;
		default:  printf ("Opcao invalida \n");
		}

	}while (op != '6');
	system ("pause");
	return 0;
}

noAVL * CriarNo (char codigo[]){
	noAVL *raiz;
	char info [100];
	raiz = (noAVL *)malloc(sizeof(noAVL));
	strcpy (raiz->cod, codigo);                        //raiz->cod = codigo;
	raiz->esq = NULL;
	raiz->dir = NULL;
	raiz->fatbal = 0;
	printf("Descreva o produto: \n");
	fgets (info, sizeof(info), stdin);
	strcpy(raiz->desc, info);                          //raiz->desc = info;
	printf("Digite o preco do produto: \n");
	scanf("%f", &raiz->preco); fflush (stdin);
	printf("Quantidade do produto em estoque: \n");
	scanf("%d", &raiz->estoque); fflush (stdin);
	return raiz;
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
         printf("%s FB:%d \n", aux->cod, aux->fatbal);
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
	printf ("Produto: %s \n", raiz->desc);
	printf ("Codigo: %s \n", raiz->cod);
	printf ("Preco: %.2f \n", raiz->preco);
	printf ("Em Estoque: %d \n", raiz->estoque);
}

void exibir (noAVL *raiz, char codigo[]) {
	if (raiz == NULL){
		printf ("Codigo de produto nao cadastrado! \n");
		system ("pause");
	}
    else if (strcmp(codigo, raiz->cod) == 0){
		exibir_no (raiz);
		system ("pause");
		return;
    }
	else if (strcmp(codigo, raiz->cod) < 0)
		exibir (raiz->esq, codigo);
	else
		exibir (raiz->dir, codigo);
}

void alterar_no (noAVL ** raiz) {
	char info [100];
		printf(" - Alteracao de informacoes do Produto - \n");
		printf("Descreva o produto: \n");
		fgets (info, sizeof(info), stdin);
		strcpy((*raiz)->desc, info);
		printf("Digite o preco do produto: \n");
		scanf("%f", &(*raiz)->preco); fflush (stdin);
		printf("Quantidade do produto em estoque: \n");
		scanf("%d", &(*raiz)->estoque); fflush (stdin);
}

void alterar (noAVL **raiz, char codigo[]) {
	if (*raiz == NULL){
		printf ("Codigo de produto nao cadastrado! \n");
		system ("pause");
	}
    else if (strcmp(codigo, (*raiz)->cod) == 0){
		alterar_no (raiz);
		printf ("Produto alterado com sucesso! \n");
		system ("pause");
		return;
    }
	else if (strcmp(codigo, (*raiz)->cod) < 0)
		alterar (&(*raiz)->esq, codigo);
	else
		alterar (&(*raiz)->dir, codigo);
}

void inserir (noAVL **raiz,char codigo[], int *status){

	if (*raiz == NULL){
		*raiz = CriarNo (codigo);
		*status = 1;
	}
	else if (strcmp(codigo, (*raiz)->cod) == 0) {
		printf ("Codigo de produto repetido! \n");
		system ("pause");
	}
	else if (strcmp(codigo, (*raiz)->cod) < 0) {
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
        strcpy((*raiz)->cod, pos->cod);
        strcpy((*raiz)->desc, pos->desc);
        (*raiz)->preco = pos->preco;
        (*raiz)->estoque = pos->estoque;
     }
free (pos);
}

void remover(noAVL **raiz, char codigo[]) {
	int altesq, altdir;
    if (*raiz == NULL){
       printf("Elemento não encontrado.\n");
       system ("pause");
    }
    else if (strcmp(codigo,(*raiz)->cod) == 0) {
       remover_no(raiz);
              if (*raiz == NULL){
    	           printf("Produto deletado! \n");
    	           system("pause");
    	           return;
              }
              else {
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
    else if (strcmp(codigo, (*raiz)->cod) < 0) {
       remover(&((*raiz)->esq),codigo);
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
       remover(&((*raiz)->dir),codigo);
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

void emOrdem (noAVL * raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%s \n", raiz->cod);
        emOrdem(raiz->dir);
        }
}
