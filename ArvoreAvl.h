#ifndef AVLARQUIVO_H_
#define AVLARQUIVO_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

/****************
**  Estruturas **
*****************/

typedef struct noAvl {
	char matricula [10];
	struct noAvl * esq, * dir;
	int fatbal;
}noAVL;

typedef struct noArq {
	char matricula [10], nome [100];
	float media;
	int faltas;
	int status;
}noARQ;

noAVL * CriarNo (char codigo[]);
int buscar (FILE * projeto, char matricula[]);  //funcao de buscar posicao do registro do aluno
int altura(noAVL* t);
void LL(noAVL** r);
void LR(noAVL** r);
void RR(noAVL** r);
void RL(noAVL** r);
void LLRem(noAVL** r);
void LRRem (noAVL ** raiz);
void RRRem(noAVL** r);
void RLRem (noAVL ** raiz);
void exibir_no (char matricula[]);
void exibir (noAVL *raiz, char matricula[]);
void alterar_no (char matricula[]);
void alterar (noAVL *raiz, char matricula[]);
void inserir (noAVL **raiz,char codigo[], int *status);
void carregaArquivo(FILE * projeto, noAVL **raiz, int * status);  //carregar arquivo na arvore
noAVL * mudaTipo (char matricula[]);
void inserir_do_Arq (noAVL **raiz,char mat[], int *status);
noAVL * maior(noAVL **raiz);
void alterarStatus (char mat[]);
void remover_no(noAVL **raiz);
void remover(noAVL **raiz, char codigo[], int * cont);
void removeAll(noAVL **raiz);
void removerTodos (noAVL **raiz);
void listarTodos ();
void exibir_noTodo (noAVL *raiz);
void ExibirEmOrdem (noAVL *raiz);
void manutencao ();

#endif
