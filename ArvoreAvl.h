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
	int status;
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

int buscar (FILE * projeto, char matricula[]);
int carregaArquivo(FILE * projeto, noAVL **raiz, int * status);
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
void exibir_noTodo (FILE * projeto, char matricula[]);
void exibir_no (FILE * projeto, int pos);
void exibir (FILE * projeto, noAVL *raiz, char matricula[]);
void alterar_no (FILE * projeto, char matricula[]);
void alterar (FILE * projeto, noAVL **raiz, char matricula[]);
void inserir (FILE * projeto, noAVL **raiz,char codigo[], int *status);
void inserir_do_Arq (noAVL **raiz,noAVL **aux, int *status);
void remover(noAVL **raiz, char codigo[], int * cont);
void removeAll(noAVL **raiz);
void removerTodos (noAVL **raiz);
void listarTodos (FILE * projeto);
void ExibirEmOrdem (FILE * projeto, noAVL **raiz);


#endif /* AVL_H_ */
