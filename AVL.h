/*
 * AVL.h
 *
 *  Created on: 27 de ago de 2016
 *      Author: Rodrigo
 */

#ifndef AVL_H_
#define AVL_H_
typedef struct noAvl {
	char matricula [10], nome [100];
	float media;
	int faltas;
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
int buscar (FILE * arq, char matAux[]);
int isEmpty (Queue fila);
void enqueue (Queue fila, noAVL * n);
noAVL * dequeue (Queue fila);
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
void remover(noAVL **raiz, char codigo[], int * cont);
void removeAll(noAVL **raiz);
void removerTodos (noAVL **raiz);


#endif /* AVL_H_ */
