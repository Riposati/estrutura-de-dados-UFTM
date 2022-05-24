#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

void contaminaAdj(lista *ini){

    lista *aux = ini;

    //printf("proximo a contaminar -> %d\n",aux->v);

    if(aux->souPrimeiro == 1){

        //printf("Sou o primeiro!\n");
        if(aux->prox->isContaminado == 0){
            aux->prox->isContaminado = 1;
        }
    }

    if(aux->souUltimo == 1){

        //printf("Sou o ultimo!\n");

        if(aux->ant->isContaminado == 0){
            aux->ant->isContaminado = 1;
        }
    }else{

        if(aux->souPrimeiro == 0 && aux->souUltimo == 0){ // MEIO LISTA

            if(aux->prox->isContaminado == 0){
                aux->prox->isContaminado = 1;
            }

            if(aux->ant->isContaminado == 0){
                aux->ant->isContaminado = 1;
            }
        }
    }
}

int contamina(lista *ini,int valor,int firsts){

    lista *aux = ini;
    int f = 0;

    if(firsts){
        while(aux->prox!=ini && aux->v != valor){ // NECESSARIO
            aux = aux->prox;
        }
        aux->isContaminado = 1;
    }else{

        //show(ini);
        //printf("\n");

        aux = ini;

        while(aux->prox!=ini){ // PASSAGEM NA LISTA
            if(aux->isContaminado==0)
                f = 1; // serve pra saber se ainda precisa contaminar alguem
            if(aux->isContaminado == 1 && aux->fechado==0){
                //printf("chave while 1 -> %d\n",aux->v);
                aux->proximoAContaminar = 1;
            }
            aux = aux->prox;
        }

        //printf("\n");

        if(aux->isContaminado==0) // ultimo bloco
            f = 1;

        if(aux->isContaminado == 1 && aux->fechado==0){
            //printf("chave -> %d\n",aux->v);
            aux->proximoAContaminar = 1;
        }

        aux = ini;
        while(aux->prox!=ini){ // MELHORAR AQUI! USAR LISTA DE INDICES ( CONTAMINADOS )
            if(aux->proximoAContaminar == 1 && aux->fechado == 0){
                //printf("chave while 2 -> %d\n",aux->v);
                contaminaAdj(aux);
                aux->fechado = 1;
            }

            aux = aux->prox;
        }

        if(aux->proximoAContaminar == 1 && aux->fechado == 0){
            //printf("chave -> %d\n",aux->v);
            contaminaAdj(aux);
            aux->fechado = 1;
        }
    }

    return f;
}

int main()
{
    lista *ini = NULL;
    int a,b,i,valor,resp = 0,cont=0;

    while(scanf("%d %d",&a,&b)!=EOF){

        for(i=0;i<a;i++){
            ini = insere(ini,i+1);
        }

        if(b==1){

            scanf("%d",&valor);

            if(valor==1 || valor==a){

                printf("%d\n",a-1);
            }

            else{

                printf("%d\n",a-valor);
            }
        }else{

            for(i=0;i<b;i++){
                scanf("%d",&valor);
                contamina(ini,valor,1); // contamina os iniciais
            }

            resp = contamina(ini,valor,0); // ainda tem zeros preciso executar de novo

            while(resp){
                resp = contamina(ini,valor,0);
                cont = incrementaCont(cont);
            }

            printf("%d\n",cont);
            cont = 0;
        }
        ini = limpaMemoria(ini);
    }

    ini = limpaMemoria(ini);

    return 0;
}
