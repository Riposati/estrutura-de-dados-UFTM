#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct lista{
    int v;
    struct lista *prox;
    struct lista *ant;
}typedef lista;

lista *insere(lista *ini,int v){

    lista *aux = (struct lista *)malloc(sizeof(struct lista));
    aux->v = v;
    aux->prox = aux;
    aux->ant = aux;

    if(ini==NULL){
        ini = aux;
    }
    else{ // jeito legal
        aux->ant = ini->ant;
        ini->ant->prox = aux;
        aux->prox = ini;
        ini->ant = aux;
    }
    return ini;
}

void show(lista *ini){

    if(ini==NULL){
        printf("A lista esta vazia!\n");
    }else{

        lista *aux = ini;

        while(aux->prox!=ini){
            printf("%d -> ",aux->v);
            aux = aux->prox;
        }
        printf("%d -> ",aux->v);
    }
}

lista *deletar(lista *ini, int chave){

    lista *aux = ini;

    if(ini->v==chave){ // é o primeiro bloco

        aux = ini->prox;
        aux->ant = ini->ant;
        ini->ant->prox=aux;

        if(ini->prox==ini && ini->ant==ini){ // se for só um bloco

            free(ini);
            ini = NULL;

        }else{

            free(ini);
            ini = aux;
        }

    }else if(aux->prox!=ini && aux->v!=chave){

        while(aux->v!=chave && aux->prox!=ini){
            aux = aux->prox;
        }

        if(aux->prox!=ini && aux->v==chave){ // tá no meio

            lista *aux2 = aux->ant;
            aux2->prox=aux->prox;
            aux2->prox->ant=aux2;
            free(aux);

        }else if(aux->prox==ini && aux->v==chave){ // tá no final da lista

            lista *aux2 = aux->ant;
            aux2->prox = ini;
            ini->ant = aux2;
            free(aux);
        }
    }

    return ini;
}

lista *limpaMemoria(lista *ini){

    lista *aux = ini;

    while(aux!=NULL){
        aux = deletar(aux,aux->v);
    }
}

//lista *ultimo = NULL; // precisei utilizar globalmente para saber a referencia do ultimo inserido na lista 2 de forma rápida

lista *respondeExercicio(lista *aux, lista *ini2,int *valorUltimo){

    lista *aux2 = (struct lista *)malloc(sizeof(struct lista));
    aux2->v = aux->v;
    aux2->prox = aux2;
    aux2->ant = aux2;

    if(ini2==NULL){

        ini2 = aux2;
        //ultimo = ini2;
        *valorUltimo = ini2->v;

    }else{

        aux2->ant = ini2->ant;
        ini2->ant->prox = aux2;
        aux2->prox = ini2;
        ini2->ant = aux2;

        if(aux->v > *valorUltimo){ // encadia no final normalmente

            //ultimo = aux2;
            *valorUltimo = aux2->v;

        }else{ // encadia no inicio

            ini2 = aux2;
            //ultimo = ini2;
            *valorUltimo = ini2->v;
        }
    }

    return ini2;
}

lista *percorreListaOriginal(lista *ini,lista *ini2,int *valorUltimo){

    lista *aux = ini;

    while(aux->ant != ini){
        //printf("%d -> ",aux->ant->v);
        ini2 = respondeExercicio(aux->ant,ini2,&valorUltimo);
        aux = aux->ant;
    }
    //printf("%d -> ",aux->ant->v);
    ini2 = respondeExercicio(aux->ant,ini2,&valorUltimo);

    return ini2;
}

void showLista2(lista *ini){

    if(ini!=NULL){
        lista *aux = ini;

        while(aux->prox!=ini){
            printf("%d\n",aux->v);
            aux = aux->prox;
        }
        printf("%d\n",aux->v);
    }
}

int main()
{
    lista *ini = NULL;
    lista *ini2 = NULL;
    int valorUltimo;
    int a;

    while(scanf("%d",&a)!=EOF){
        ini = insere(ini,a);
    }

    if(ini != NULL){

        valorUltimo = ini->ant->v;

        ini2 = percorreListaOriginal(ini,ini2,&valorUltimo);

        //printf("\n");
        showLista2(ini2);
        //printf("\n");
        ini2 = limpaMemoria(ini2);
    }

    ini = limpaMemoria(ini);
    //system("pause");

    return 0;
}
