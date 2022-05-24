#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int contZeros;

struct lista{
    int v;
    int isContaminado;
    int proximoAContaminar;
    int souPrimeiro;
    int souUltimo;
    struct lista *prox;
    struct lista *ant;
    int fechado;
}typedef lista;

struct listaIndice{
    lista *indice;
    struct listaIndice *prox;
    struct listaIndice *ant;
}typedef listaIndice;

lista *insere(lista *ini,int v){

    lista *aux = (struct lista *)malloc(sizeof(struct lista));
    aux->v = v;
    aux->prox = aux;
    aux->ant = aux;
    aux->isContaminado = 0;
    aux->proximoAContaminar = 0;
    aux->souPrimeiro = 0;
    aux->souUltimo = 1;
    aux->fechado = 0;

    if(ini==NULL){
        ini = aux;
        ini->souPrimeiro = 1;
    }
    else{ // jeito legal
        aux->ant = ini->ant;
        ini->ant->prox = aux;
        aux->prox = ini;
        ini->ant->souUltimo = 0;
        ini->ant = aux;
    }
    return ini;
}

lista *insereIndice(listaIndice *iniIndices, lista *ini){

    listaIndice *aux = (struct listaIndice *)malloc(sizeof(struct listaIndice));
    aux->indice = NULL;
    aux->prox = aux;
    aux->ant = aux;

    if(iniIndices==NULL){
        iniIndices = aux;
        iniIndices->indice = ini;
    }
    else{ // jeito legal
        aux->indice = ini;
        aux->ant = iniIndices->ant;
        iniIndices->ant->prox = aux;
        aux->prox = iniIndices;
        iniIndices->ant = aux;
    }

    return iniIndices;
}

int incrementaCont(int cont){
    cont++;
    return cont;
}

void show(lista *ini){

    if(ini==NULL){
        printf("A lista esta vazia!\n");
    }else{

        lista *aux = ini;

        while(aux->prox!=ini){
            printf("%d -> ",aux->isContaminado);
            aux = aux->prox;
        }
        printf("%d -> ",aux->isContaminado);
    }
}

void showIndices(listaIndice *ini){

    printf("Lista de indices:\n");

    if(ini==NULL){
        printf("A lista de indices esta vazia!\n");
    }else{

        listaIndice *aux = ini;

        while(aux->prox!=ini){
            printf("%d -> ",aux->indice->v);
            aux = aux->prox;
        }
        printf("%d -> ",aux->indice->v);
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

lista *deletarIndices(listaIndice *ini,int chave){

    listaIndice *aux = ini;

    if(ini->indice->v==chave){ // é o primeiro bloco

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

    }else if(aux->prox!=ini && aux->indice->v!=chave){

        while(aux->indice->v!=chave && aux->prox!=ini){
            aux = aux->prox;
        }

        if(aux->prox!=ini && aux->indice->v==chave){ // tá no meio

            lista *aux2 = aux->ant;
            aux2->prox=aux->prox;
            aux2->prox->ant=aux2;
            free(aux);

        }else if(aux->prox==ini && aux->indice->v==chave){ // tá no final da lista

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

listaIndice *limpaMemoriaIndices(listaIndice *ini){

    listaIndice *aux = ini;

    while(aux!=NULL){
        aux = deletarIndices(aux,aux->indice->v);
    }
}

void contaminaAdj(listaIndice *ini){

    listaIndice *aux = ini;

    //printf("proximo a contaminar -> %d\n",aux->v);

    if(aux->indice->souPrimeiro == 1){

        //printf("Sou o primeiro!\n");
        if(aux->indice->prox->isContaminado == 0){
            aux->indice->prox->isContaminado = 1;
            contZeros--;
        }
    }

    if(aux->indice->souUltimo == 1){

        //printf("Sou o ultimo!\n");
        if(aux->indice->ant->isContaminado == 0){
            aux->indice->ant->isContaminado = 1;
            contZeros--;
        }

    }else{

        if(aux->indice->souPrimeiro == 0 && aux->indice->souUltimo == 0){ // MEIO LISTA

            if(aux->indice->prox->isContaminado == 0){
                aux->indice->prox->isContaminado = 1;
                contZeros--;
            }

            if(aux->indice->ant->isContaminado == 0){
                aux->indice->ant->isContaminado = 1;
                contZeros--;
            }
        }
    }
}

void contamina(lista *ini,int valor,int firsts){

    lista *aux = ini;
    listaIndice *indices = NULL;

    if(firsts){
        while(aux->prox!=ini && aux->v != valor){ // NECESSARIO CONTAMINAR INICIAIS
            aux = aux->prox;
        }
        aux->isContaminado = 1;
    }else{

        //show(ini);
        //printf("\n");

        aux = ini;
        while(aux->prox!=ini){ // PASSAGEM NA LISTA
            if(aux->isContaminado == 1 && aux->fechado==0){
                //printf("chave while 1 -> %d\n",aux->v);
                aux->proximoAContaminar = 1;
                indices = insereIndice(indices,aux);
            }
            aux = aux->prox;
        }
        if(aux->isContaminado == 1 && aux->fechado==0){
            //printf("chave while 1 -> %d\n",aux->v);
            aux->proximoAContaminar = 1;
            indices = insereIndice(indices,aux);
        }

        listaIndice *auxIndice = indices;
        while(auxIndice->prox!=indices){ // PASSAGEM NA LISTA DE INDICES ( CONTAMINADOS )
            contaminaAdj(auxIndice);
            auxIndice->indice->fechado = 1;
            auxIndice = auxIndice->prox;
        }

        contaminaAdj(auxIndice); // ultimo tab indices
        auxIndice->indice->fechado = 1;

        //showIndices(indices);
        //printf("\n");

        //printf("LIMPEI A TABELA DE INDICES\n");
        indices = limpaMemoriaIndices(indices);
    }
}

int main()
{
    lista *ini = NULL;
    int a,b,i,valor,resp = 0,cont=0,f;

    while(scanf("%d %d",&a,&b)!=EOF){

        f = 0;

        for(i=0;i<a;i++){
            ini = insere(ini,i+1);
        }

        for(i=0;i<b;i++){
            scanf("%d",&valor);

            if((b==1 || b==a) && (valor==ini->v || valor==ini->ant->v)){
                printf("Processando...\n%d\n",a-1);
            }else{

                contamina(ini,valor,1); // contamina os iniciais
                f = 1;
            }
        }

        if(f){
            printf("Processando...\n");
            contZeros = a-b;

            while(contZeros > 0){
                contamina(ini,valor,0);
                cont = incrementaCont(cont);
                //printf("ContZeros => %d\n",contZeros);
            }
            printf("%d\n",cont);
            cont = 0;
        }

        ini = limpaMemoria(ini);

    }

    ini = limpaMemoria(ini);

    return 0;
}
