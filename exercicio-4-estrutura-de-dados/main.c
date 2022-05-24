#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista{
    int v;
    struct lista *prox;
    struct lista *ant;
}typedef lista;

int incrementaBlocks(int contBlocks){
    contBlocks++;
    return contBlocks;
}

int decrementaBlocks(int contBlocks){
    contBlocks--;
    return contBlocks;
}

lista *insere(lista *ini,int v){

    lista *aux = (struct lista *)malloc(sizeof(struct lista));
    aux->v = v;
    aux->prox = aux;
    aux->ant = aux;

    if(ini==NULL)
        ini = aux;
    else{ // jeito legal
        aux->ant = ini->ant;
        ini->ant->prox = aux;
        aux->prox = ini;
        ini->ant = aux;
    }
    return ini;
}

void mostrar(lista *ini,int contBlocks){

    /*lista *aux = ini;

    while(aux!=NULL){
        printf("%d -> ",aux->v);
        aux = aux->prox;
    }
    printf("\ncontBlocks -> %d\n",contBlocks);*/

    printf("Saindo %d e resta %d pessoas\n",ini->v,contBlocks);
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

int main()
{
    lista *ini = NULL;
    int contBlocks = 0;
    char frase[200];
    char delim[] = " ";

    while(gets(frase)){
        //printf("%s\n",frase);

        if(strcmp("Saida", frase)==0){

            if(contBlocks > 0){
                //printf("ini->v = %d\n",ini->v);
                contBlocks = decrementaBlocks(contBlocks);
                mostrar(ini,contBlocks);
                ini = deletar(ini,ini->v);
            }else{
                if(contBlocks==0)
                    printf("resta 0 pessoas\n");
            }

        }else{
            char *ptr = strtok(frase, delim);

            while(ptr != NULL)
            {
                //printf("'%s'\n", ptr);

                if(strcmp("Entrada", ptr)!=0){
                    //printf("PTR => %s\n",ptr);
                    ini = insere(ini,atoi(ptr));
                    contBlocks = incrementaBlocks(contBlocks);
                }

                ptr = strtok(NULL, delim);
            }
        }
    }

    limpaMemoria(ini);

    return 0;
}
