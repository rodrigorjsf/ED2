/*
 ============================================================================
 Name        : RBtree.c
 Author      : Rodrigo Franca
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef enum cores {red, black }Cores;


typedef struct noRb {
	int n, status;
	Cores cor;
	struct noRb * esq, * dir, * pai;
}noRB;

typedef struct no {
     noRB * info;
    struct no * prox;
} TNo;

typedef struct descritor {
    TNo *inicio, *fim;
} TDescritor;

typedef TDescritor * Queue;


//noRB * CriarNo (int num);

void LL(noRB ** r, noRB *k);
void LR(noRB ** r, noRB *k);
void RR(noRB ** r, noRB *k);
void RL(noRB ** r, noRB *k);
void recolorir(noRB *k);
noRB * buscar (noRB * aux, int num);
void removerP (noRB * raiz, int num);
int isEmpty (Queue fila);
void enqueue (Queue fila, noRB * n);
noRB * dequeue (Queue fila);
//int head (Queue fila);
void initialize (Queue * fila);
void percorrerPorNivel(noRB * raiz);
void RBInsert (noRB **raiz, int elem);
void RBInsertFixup (noRB **raiz, noRB *k);
void removeAll(noRB **raiz);
void removerTodos (noRB **raiz);

int main(void) {
	system("color F0");
	noRB * arvoreRB = NULL;
	char op;
	int num;
	do {
		system ("cls");
		printf ("-------------------- ARVORE RED BLACK -------------------- \n");
		printf ("1 - Inserir \n");
		printf ("2 - Remover \n");
		//printf ("3 - Exibir \n");
		//printf ("4 - Alterar \n");
		printf ("3 - Listar \n");
		printf ("4 - Sair \n");
		printf ("informe a opcao: ");
		op = getchar(); fflush (stdin);
		switch(op){
		case '1': printf ("\n - Informe o numero: ");
		          scanf ("%d", &num); fflush (stdin);
		          RBInsert (&arvoreRB, num);
		          break;
		case '2': printf ("\n - Informe o numero: ");
		          scanf ("%d", &num); fflush (stdin);
                  removerP (arvoreRB, num);
                  break;
		/*case '3': printf ("\n - Informe o codigo: ");
		          fgets(num, sizeof(num), stdin); fflush (stdin);
                  exibir (arvoreAvl, num);
                  break;
		case '4': printf ("\n - Informe o codigo: ");
                  fgets(num, sizeof(num), stdin); fflush (stdin);
                  alterar (&arvoreAvl, num);
                  break;*/
		case '3': percorrerPorNivel (arvoreRB);
		          system ("pause");
                  break;
		case '4': removerTodos (&arvoreRB);
		          printf ("Memoria limpa.\n");
                  break;
		default:  printf ("Opcao invalida \n");
		}

	}while (op != '4');
	system ("pause");
	return 0;
}


void LL(noRB ** r, noRB *k) {             // rotação simples a direita do INSERIR
	noRB* p = k->pai;
	noRB* g = k->pai->pai;
	noRB *aux = g->pai;
	if (g->pai == NULL){
		g->esq = p->dir;
		p->dir = g;
		g->pai = p;
		p->pai = aux;
		p->cor = black;
		g->cor = red;
		*r = p;
	}
	else{
		g->esq = p->dir;
		p->dir = g;
		g->pai = p;
		p->pai = aux;
		p->cor = black;
		g->cor = red;
		if(aux->dir == g)
			aux->dir = p;
		else
			aux->esq = p;
	}
}

void LR(noRB ** r, noRB *k) {            // rotação dupla a direita do INSERIR
	noRB *g = k->pai->pai;
	noRB *p = k->pai;
	noRB *aux = g->pai;;
	if (g->pai == NULL){
		g->esq = k->dir;
		p->dir = k->esq;
		k->esq = p;
		k->dir = g;
		g->pai = k;
		p->pai = k;
		k->pai = aux;
		k->cor = black;
		g->cor = red;
		*r = k;
	}
	else{
		g->esq = k->dir;
		p->dir = k->esq;
		k->esq = p;
		k->dir = g;
		g->pai = k;
		p->pai = k;
		k->pai = aux;
		k->cor = black;
		g->cor = red;
		if(aux->dir == g)
			aux->dir = k;
		else
			aux->esq = k;
	}
}

void RR(noRB ** r, noRB *k) {                  // rotação simples a esquerda do INSERIR
	noRB* p = k->pai;
	noRB* g = k->pai->pai;
	noRB *aux = g->pai;
	if (g->pai == NULL){
		g->dir = p->esq;
		p->esq = g;
		g->pai = p;
		p->pai = aux;
		p->cor = black;
		g->cor = red;
		*r = p;
	}
	else{
		g->dir = p->esq;
		p->esq = g;
		g->pai = p;
		p->pai = aux;
		p->cor = black;
		g->cor = red;
		if(aux->dir == g)
			aux->dir = p;
		else
			aux->esq = p;
	}
}
void RL(noRB ** r, noRB *k) {                 // rotação dupla a esquerda do INSERIR
	noRB *g = k->pai->pai;
	noRB *p = k->pai;
	noRB *aux = g->pai;;
	if (g->pai == NULL){
		g->dir = k->esq;
		p->esq = k->dir;
		k->dir = p;
		k->esq = g;
		g->pai = k;
		p->pai = k;
		k->pai = aux;
		k->cor = black;
		g->cor = red;
		*r = k;
	}
	else{
		g->dir = k->esq;
		p->esq = k->dir;
		k->dir = p;
		k->esq = g;
		g->pai = k;
		p->pai = k;
		k->pai = aux;
		k->cor = black;
		g->cor = red;
		if(aux->dir == g)
			aux->dir = k;
		else
			aux->esq = k;
	}
}

void recolorir(noRB *k) {                  // rotação simples a esquerda do INSERIR
	noRB* p = k->pai;
	noRB* g = k->pai->pai;
	noRB * s;
	if (p->pai->esq == p)
		s = g->dir;
	else if (p->pai->dir == p)
		s = g->esq;
	if (g->pai == NULL){
		p->cor = black;
		s->cor = black;
	}
	else{
		g->cor = red;
		p->cor = black;
		s->cor = black;
	}
}

void RBInsert (noRB **raiz, int elem) {
	noRB * novo, *x = *raiz, *y = NULL;
	novo = (noRB *) malloc (sizeof (noRB));
	novo->n = elem;
	while (x != NULL) {
		y = x;
		if (novo->n < x->n)
			x = x->esq;
		else
			x = x->dir;
	}
	novo->pai = y;
	if (y == NULL)
			*raiz = novo;
	else if (novo->n < y->n)
		y->esq = novo;
	else
		y->dir = novo;
	novo->status = 1;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->cor = red;
	RBInsertFixup (raiz, novo);
}

void RBInsertFixup (noRB **raiz, noRB *k) {
	noRB * s,* g;
	if (k->pai != NULL) {
		while (k->pai != NULL && k->pai->cor == red) {
			if (k->pai == k->pai->pai->esq) { // tio S é o filho da direita
				s = k->pai->pai->dir;
				if (s == NULL || s->cor == black) {
					if (k == k->pai->dir) {
						LR (raiz, k); // dupla
						break;
					}
					else {
						LL (raiz, k); // simples
						break;
					}
				}
				else { // s->cor == red
					g = k->pai->pai;
					recolorir(k);
					k = g;
					}
			}
			else { // tio S é o filho da esquerda
				s = k->pai->pai->esq;
				if (s == NULL || s->cor == black) {
					if (k == k->pai->esq) {
						RL (raiz, k);
						break;
					}
					else {
						RR (raiz, k);
						break;
					}
				}
				else { // s->cor == red
					g = k->pai->pai;
					recolorir(k);
					k = g;
					}
			}
		} // fim while
		} // fim do if
	else
		(*raiz)->cor = black;
}

/*noRB * CriarNo (int num){
	noRB *raiz;
	raiz = (noRB *)malloc(sizeof(noRB));
	//strcpy (raiz->cod, codigo);                        //raiz->cod = codigo;
	raiz->esq = NULL;
	raiz->dir = NULL;
	raiz->pai =
	raiz->fatbal = 0;
	printf("Descreva o produto: \n");
	fgets (info, sizeof(info), stdin);
	strcpy(raiz->desc, info);                          //raiz->desc = info;
	printf("Digite o preco do produto: \n");
	scanf("%f", &raiz->preco); fflush (stdin);
	printf("Quantidade do produto em estoque: \n");
	scanf("%d", &raiz->estoque); fflush (stdin);
	return raiz;
}*/

noRB * buscar (noRB * raiz, int num) {
	noRB * aux;
	aux = raiz;
	if (aux == NULL)
		return 0;
	while (aux != NULL){
    if (aux->n == num && aux->status == 1)
		return aux;
    else if (aux->n > num)
		aux = aux->esq;
	else
		aux = aux->dir;
	}
	return -1;
}

void removerP (noRB * raiz, int num){
	noRB * aux;
	aux = buscar(raiz, num);
	if (aux == 0)
		printf ("Arvore vazia.\n");
	else if (aux == -1)
		printf ("Numero nao cadastrado.\n");
	else{
		aux->status = 0;
		printf ("Numero removido com sucesso!\n");
	}
	system ("pause");
}
	/*int cont = -1, status;
	noRB c;

	while (1) {
		status = fread (&c, sizeof (noARQ), 1, projeto);
		if (status != 1) {
			if (!feof(projeto))
			    return -2; // erro de leitura
			else
				return -1; // nao achou
		}
		else {
			cont++;
			if (c.status == 1 && strcmp (c.num, num) == 0)
				return cont;
		}
	}
}*/

int isEmpty (Queue fila) {
    if (fila->inicio == NULL)
       return TRUE;
    else
       return FALSE;
}

void enqueue (Queue fila, noRB * n) {
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

noRB * dequeue (Queue fila) {
     TNo * aux;
     noRB * n;
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

void percorrerPorNivel(noRB * raiz) {
  Queue fila;
  noRB * aux;
  if (raiz != NULL) {
      initialize(&fila);
      enqueue (fila, raiz);
      while (isEmpty(fila) == FALSE) {                    //stdbool
            aux = dequeue(fila);
         if (aux->esq != NULL)
           enqueue(fila,aux->esq);
         if (aux->dir != NULL)
           enqueue(fila,aux->dir);
         if (aux->status == 1)
           printf("Num: %d Cor: %d \n", aux->n, aux->cor);
         }
  }
}

void removeAll(noRB **raiz){
     noRB * pos;
     pos = *raiz;
     *raiz = NULL;
     free (pos);
}

void removerTodos (noRB **raiz) {
    if (*raiz != NULL) {
        removerTodos(&(*raiz)->esq);
        removerTodos(&(*raiz)->dir);
        removeAll(&(*raiz));
        }
}
