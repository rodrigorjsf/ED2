
#include "AvlArquivo.h"

noAVL * CriarNo (char codigo[]){
	FILE * projeto;
	noARQ aux;
	noAVL * raiz;
	char info [100];
	int status;
	projeto = fopen("Contato.txt", "a+b");
	if (projeto == NULL)
		return NULL;
	raiz = (noAVL *)malloc(sizeof(noAVL));
	strcpy (raiz->matricula, codigo);                        //raiz->cod = codigo;
	strcpy (aux.matricula, codigo);
	raiz->esq = NULL;
	raiz->dir = NULL;
	raiz->fatbal = 0;
	aux.status = 1;
	printf("Digite o nome do Aluno: \n");
	fgets (info, sizeof(info), stdin);
	strcpy(aux.nome, info);//raiz->nome = info;
	do{
	printf("Digite a media do aluno: \n");
	scanf("%f", &aux.media); fflush (stdin);
	if (aux.media > 10)
		printf("Media invalida. Ex: de 0 a 10. \n");
	}while (aux.media > 10);
	printf("Quantidade de faltas do aluno: \n");
	scanf("%d", &aux.faltas); fflush (stdin);
	status = fwrite(&aux,sizeof(noARQ),1,projeto);
	if (status != 1)
			printf ("Erro de gravacao \n");
		else
			printf ("Contato cadastrado com sucesso \n");
	system ("pause");
	fclose(projeto);
	return raiz;
}

int buscar (FILE * projeto, char matricula[]) {
	int cont = -1, status;
	noARQ c;

	fseek (projeto, 0, 0);
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
			if (c.status == 1 && strcmp (c.matricula, matricula) == 0)
				return cont;
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

void exibir_no (char matricula[]) {
	FILE * projeto;
	noARQ aux;
	int pos, status;
	projeto = fopen ("Contato.txt", "rb");
	if (projeto == NULL)
		return;
	pos = buscar (projeto, matricula);
	if (pos == -1)
		printf ("Contato nao cadastrado \n");
	else if (pos == -2)
		printf ("Erro de leitura \n");
	else {
	    fseek(projeto, pos * sizeof (noARQ), 0);   //duvida de fseek
	    status = fread (&aux,sizeof (noARQ), 1, projeto);
		if (status != 1)
			printf ("Erro de leitura \n");
	    else {
			printf ("Aluno: %s \n", aux.nome);
			printf ("Media do Aluno: %.2f \n", aux.media);
	    	printf ("Quantidade de faltas do Aluno: %i \n", aux.faltas);
		}
	}
	fclose(projeto);
}

void exibir (noAVL *raiz, char matricula[]) {
	if (raiz == NULL)
		printf ("\nMatricula de Aluno nao cadastrada! \n");

    else if (strcmp(matricula, raiz->matricula) == 0)
    	exibir_no (matricula);

	else if (strcmp(matricula, raiz->matricula) < 0)
		exibir (raiz->esq, matricula);
	else
		exibir (raiz->dir, matricula);
	system ("pause");
}

void alterar_no (char matricula[]) {
	FILE * projeto; 
	noARQ aux;
	char op;
    int pos, status;
	projeto = fopen ("Contato.txt", "r+b");
	if (projeto == NULL)
		return;
	pos = buscar (projeto, matricula);
	if (pos == -1)
		printf ("Contato nao cadastrado \n");
	else if (pos == -2)
		printf ("Erro de leitura \n");
	else {
		fseek(projeto, pos * sizeof (noARQ), 0);
		status = fread (&aux,sizeof (noARQ), 1, projeto);
		if (status != 1)
			printf ("Erro de leitura \n");
		else {
			printf("1 - ALterar Media do aluno  \n");
			printf("2 - ALterar quantidade de faltas do aluno  \n");
			printf("3 - ALterar Media e quantidade de faltas do aluno  \n");
			op = getchar(); fflush (stdin);
			switch(op){
			case '1':
				printf ("Alteracao de dados de %s \n", aux.nome);
				do{
				printf ("Informe a nova media do Aluno: \n");
				scanf("%f", &aux.media); fflush (stdin);
				if (aux.media > 10)
					printf("Media invalida. Ex: de 0 a 10. \n");
				}while (aux.media > 10);
				fseek(projeto, -sizeof(noARQ), 1);
				status = fwrite (&aux,sizeof (noARQ), 1, projeto);
				if (status != 1)
					printf ("Erro de gravacao \n");
				else
					printf ("Media alterada com sucesso. \n");
				break;
			case '2':
				printf ("Alteracao de dados de %s \n", aux.nome);
				printf ("Informe a nova quantidade de faltas: \n");
				scanf("%d", &aux.faltas); fflush (stdin);
				fseek(projeto, -sizeof(noARQ), 1);
				status = fwrite (&aux,sizeof (noARQ), 1, projeto);
				if (status != 1)
					printf ("Erro de gravacao \n");
				else
					printf ("Quantidade de faltas alterada com sucesso. \n");
				break;
			case '3':
				printf ("Alteracao de dados de %s \n", aux.nome);
				do{
				printf ("Informe a nova media do Aluno: \n");
				scanf("%f", &aux.media); fflush (stdin);
				if (aux.media > 10)
					printf("Media invalida. Ex: de 0 a 10. \n");
				}while (aux.media > 10);
				printf ("Informe a nova quantidade de faltas: \n");
				scanf("%d", &aux.faltas); fflush (stdin);
				fseek(projeto, -sizeof(noARQ), 1);
				status = fwrite (&aux,sizeof (noARQ), 1, projeto);   //duvida &aux
				if (status != 1)
					printf ("Erro de gravacao \n");
				else
					printf ("Media e quantidade de faltas alterada com sucesso. \n");
				break;
			default: 
				printf("Operador inválido\n");
			}
		}
	}
	system ("pause");
	fclose(projeto);
}

void alterar (noAVL *raiz, char matricula[]) {
	if (raiz == NULL)
		printf ("\nMatricula de Aluno nao cadastrada! \n");
    else if (strcmp(matricula, raiz->matricula) == 0)
		alterar_no (matricula);
	else if (strcmp(matricula, raiz->matricula) < 0)
		alterar (raiz->esq, matricula);
	else
		alterar (raiz->dir, matricula);
	system ("pause");
}

void inserir (noAVL **raiz,char codigo[], int *status){

	if (*raiz == NULL){
		*raiz = CriarNo (codigo);
		*status = 1;
	}
	else if (strcmp(codigo, (*raiz)->matricula) == 0){
		printf ("\nMatricula de Aluno repetida!\n");
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

void carregaArquivo(FILE * projeto, noAVL **raiz, int * status){
	noARQ aux;
	int statusA;
    fseek(projeto,0,SEEK_END);
    if(ftell(projeto) == 0)              // FTELL retorna a posição corrente de leitura ou escrita no arquivo (em bytes). Se for 0, arquivo vazio
    	printf ("Arquivo Vazio.\n");
    fseek(projeto,0,SEEK_SET);
    if(projeto == NULL)
    	printf ("Erro ao tentar carregar o arquivo. \n");
    else {
    	while(!feof(projeto)) {
    		statusA = fread (&aux, sizeof(noARQ), 1, projeto);
    		if (statusA != 1){
    			if(!feof(projeto)){
    				printf ("Erro ao carregar o Arquivo\n");
    				break;
    			}
    			else
    				break;
    		}
            inserir_do_Arq (&(*raiz), aux.matricula, status);
    	}
    	printf ("Arquivo carregado com sucesso!\n");
    }
    system ("pause");
	fclose(projeto);
}

noAVL * mudaTipo (char matricula[]){
	noAVL * raiz;
	raiz = (noAVL *)malloc(sizeof(noAVL));
	strcpy (raiz->matricula, matricula);                        //raiz->cod = codigo;
	raiz->esq = NULL;
	raiz->dir = NULL;
	raiz->fatbal = 0;
	return raiz;
}

void inserir_do_Arq (noAVL **raiz,char mat[], int *status){

	if (*raiz == NULL){
		*raiz = mudaTipo(mat);
		*status = 1;
	}
	else if (strcmp(mat, (*raiz)->matricula) == 0){
		printf ("Matricula de Aluno repetida! \n");
		system ("pause");
	}
	else if (strcmp(mat, (*raiz)->matricula) < 0) {
		inserir_do_Arq (&(*raiz)->esq, mat, status);
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
		inserir_do_Arq (&(*raiz)->dir, mat, status);
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

void alterarStatus (char mat[]){
	FILE * projeto;
	noARQ aux;
	int pos, status;
	projeto = fopen ("Contato.txt", "r+b");
	if (projeto == NULL)
		return;
	pos = buscar (projeto, mat);
	if (pos == -1)
		printf ("Contato nao cadastrado \n");
	else if (pos == -2)
		printf ("Erro de leitura \n");
	else {
		fseek(projeto, pos * sizeof (noARQ), 0);
		status = fread (&aux,sizeof (noARQ), 1, projeto);
		if (status != 1)
			printf ("Erro de leitura \n");
		else {
			aux.status = 0;
			fseek(projeto, -sizeof(noARQ), 1);
			status = fwrite (&aux,sizeof (noARQ), 1, projeto);
			if (status != 1)
				printf ("Erro de gravacao \n");
			else
				printf ("Contato removido com sucesso \n");
		}
	}
	system ("pause");
	fclose (projeto);
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
     }
free (pos);
}

void remover(noAVL **raiz, char matricula[], int * cont) {

    if (*raiz == NULL){
       printf("\nMatricula nao encontrada.\n");
       system ("pause");
    }
    else if (strcmp(matricula,(*raiz)->matricula) == 0) {
    	alterarStatus(matricula);
    	remover_no(raiz);
    	int altesq, altdir;
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
    }
    else if (strcmp(matricula, (*raiz)->matricula) < 0) {
       remover(&((*raiz)->esq),matricula, cont++);
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
       remover(&((*raiz)->dir),matricula, cont++);
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

void listarTodos () {
	FILE * projeto;
	int status;
	noARQ aux;
	projeto = fopen ("Contato.txt", "rb");
	if (projeto == NULL)
		return;
	while (1) {
		status = fread (&aux, sizeof (noARQ), 1, projeto);
		if (status != 1) {
			if (!feof(projeto))
			    printf ("Erro de leitura \n");
			break;
		}
		else {
			if (aux.status == 1) {
				printf ("\nMatricula: %s", aux.matricula);
				printf ("Nome: %s ", aux.nome);
				printf ("Media: %.2f \n", aux.media);
				printf ("Faltas: %d \n\n", aux.faltas);
			}
		}
	}
	fclose(projeto);
}

void exibir_noTodo (noAVL *raiz) {
	FILE * projeto;
	noARQ aux;
	int pos, status;
	char info[100];
	projeto = fopen ("Contato.txt", "rb");
	if (projeto == NULL)
		return;
	strcpy(info, raiz->matricula);
	pos = buscar (projeto, info);
	if (pos == -1)
		printf ("Contato nao cadastrado \n");
	else if (pos == -2)
		printf ("Erro de leitura \n");
	else {
		fseek(projeto, pos * sizeof (noARQ), 0);   //duvida de fseek
		status = fread (&aux,sizeof (noARQ), 1, projeto);
		if (status != 1)
			printf ("Erro de leitura \n");
		else {
			printf ("Aluno: %s \n", aux.nome);
			printf ("Matricula: %s \n", aux.matricula);
			printf ("Media do Aluno: %.2f \n", aux.media);
			printf ("Quantidade de faltas do Aluno: %i \n", aux.faltas);
		}
	}
	fclose(projeto);
}

void ExibirEmOrdem (noAVL *raiz) {
    if (raiz != NULL) {
    	ExibirEmOrdem(raiz->esq);
    	exibir_noTodo(raiz);   //printf(“%i \n”, raiz->cod);
    	ExibirEmOrdem(raiz->dir);
        }
}

void manutencao () {
	FILE * projeto;
	int status;
	noARQ sup;
	FILE * aux;
	projeto = fopen ("Contato.txt", "r+b");
	if (projeto == NULL){
		printf ("Erro ao executar o processo de manutenção do arquivo \n");
	    fclose (projeto);
	}
	aux = fopen ("auxiliar", "w+b");
	if (aux == NULL) {
		printf ("Erro ao executar o processo de manutenção do arquivo \n");
		fclose (projeto);
	}
	else {
	    while (1) {
		     status = fread (&sup, sizeof (noARQ), 1, projeto);
		     if (status != 1) {
			      if (!feof(projeto)) {
			            printf ("Erro ao executar o processo de manutenção do arquivo \n");
						fclose (projeto);
						fclose (aux);
						remove ("auxiliar");
						return;
				  }
				  else
			            break;
		    }
		    else {
			    if (sup.status == 1) {
				     status = fwrite (&sup, sizeof (noARQ), 1, aux);
				     if (status != 1) {
					    printf ("Erro ao executar o processo de manutenção do arquivo \n");
					    fclose (projeto);
					    fclose (aux);
					    remove ("auxiliar");
					    return;
				     }
			   }
		   }
	    }
        fclose (projeto);
	    fclose (aux);
	    remove ("Contato.txt");
	    rename ("auxiliar", "Contato.txt");
   }
	system ("pause");
}
