#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista{
    int v;
    struct lista *prox;
}typedef lista;

int incrementaBlocks(int contBlocks){
    contBlocks++;
    return contBlocks;
}

int decrementaBlocks(int contBlocks){
    contBlocks--;
    return contBlocks;
}

lista *insere(lista *ini, int v){

    lista *aux = (struct lista *)malloc(sizeof(struct lista));
    aux->v = v;
    aux->prox = NULL;

    if(ini==NULL){

        ini = aux;
    }else{

        lista *temp = ini;
        while(temp->prox != NULL){

            temp = temp->prox;
        }

        temp->prox = aux;
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

lista *remover(lista *inicio, int valor) {

		lista *aux = inicio;
		lista *aux2 = NULL;

		while(aux != NULL && aux->v != valor) {
			aux2 = aux;
			aux = aux->prox;
		}

		if (aux != NULL) {

			//printf("removi o valor -> %d\n",valor);

			// para primeiro bloco
			if (aux == inicio && aux->v == valor) {

				inicio = inicio->prox;
			} else {

				// para blocos do meio
				if (aux != inicio && aux->prox != NULL && aux->v == valor) {

					aux2->prox = aux->prox;
				} else {

					// para blocos do final
					if (aux != inicio && aux->prox == NULL && aux->v == valor) {

						aux2->prox = NULL;
					}
				}
			}
		}else{

			//printf("valor nao existe -> %d\n",valor);
		}

		return inicio;
	}

lista *limpaMemoria(lista *ini){

    lista *aux = ini;

    while(aux!=NULL){
        aux = remover(aux,aux->v);
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
                ini = remover(ini,ini->v);
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
