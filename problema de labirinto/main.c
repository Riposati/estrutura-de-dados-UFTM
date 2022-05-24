#include <stdio.h>
#include <stdlib.h>

struct estruturaMatriz{

    int valor;
    int flag_marca_visitado;

}typedef EstruturaMatriz;

void resposta(EstruturaMatriz **m,int linha,int coluna,int qtdLinhas,int qtdColunas){

    int valorLinha,valorColuna;
    int f1=0,f2=0,f3=0,f4=0,i,j;
    // olharei nas 4 direcoes adjacentes ( cima, baixo, esquerda, direita )

    if(m[linha][coluna].valor==0){

        m[linha][coluna].flag_marca_visitado = 1; // marca como visitado o vertice que chegar
        valorLinha = linha;
        valorColuna = coluna;

        if(valorColuna > 0 && m[valorLinha][valorColuna-1].valor==0 &&
           m[valorLinha][valorColuna-1].flag_marca_visitado==0){

            //printf("esquerda = %d\n\n",m[valorLinha][valorColuna-1].valor);
            f1 = 1;
            resposta(m,valorLinha,valorColuna-1,qtdLinhas, qtdColunas);
        }

        if(valorColuna < qtdColunas && m[valorLinha][valorColuna+1].valor==0 &&
           m[valorLinha][valorColuna+1].flag_marca_visitado==0){

            //printf("direita = %d\n\n",m[valorLinha][valorColuna+1].valor);
            f2 = 1;
            resposta(m,valorLinha,valorColuna+1,qtdLinhas, qtdColunas);
        }

        if(valorLinha > 0 && m[valorLinha-1][valorColuna].valor==0 &&
           m[valorLinha-1][valorColuna].flag_marca_visitado==0){

            //printf("cima = %d\n\n",m[valorLinha-1][valorColuna].valor);
            f3 = 1;
            resposta(m,valorLinha-1,valorColuna,qtdLinhas, qtdColunas);
        }

       if(valorLinha < qtdLinhas && m[valorLinha+1][valorColuna].valor==0 &&
           m[valorLinha+1][valorColuna].flag_marca_visitado==0){

            //printf("abaixo = %d\n\n",m[valorLinha+1][valorColuna].valor);
            f4 = 1;
            resposta(m,valorLinha+1,valorColuna,qtdLinhas, qtdColunas);
        }

        else {
            /*printf("voltei no backtracking!\n");
            printf("valor da linha = %d\n",valorLinha);
            printf("valor da coluna = %d\n",valorColuna);*/
            return;
       }

    }// fim do if que verifica se e 0
}

struct estruturaMatriz **inicializaMatriz(int i, int j){

    int x,y;

    struct estruturaMatriz **matriz = (EstruturaMatriz **)malloc(i * j * sizeof(EstruturaMatriz)); // alocando as linhas

    for (x=0; x < i; x++) {
        matriz[x] = (EstruturaMatriz *)malloc(j * sizeof(EstruturaMatriz)); // alocando as colunas
    } // ate aqui somente alocacao dinamica

    return matriz;
}

int main()
{
    int i,j,x,y,posSx,posSy,posDx,posDy;
    char aux;

    scanf("%d %d",&i,&j); // largura e altura labirinto
    scanf("\n"); // precisa ler pra nao ocasionar erro pois o C interpreta como caracter que deve ser processado tambem

    struct estruturaMatriz **m = inicializaMatriz(i,j);

    for(x=0;x<i;x++){

        for(y=0;y<j;y++){

            scanf("%c",&aux);
            m[x][y].valor = aux; // lendo o labirinto

            if(m[x][y].valor==35){ // codigo ascii char '#'

                m[x][y].valor = 1; // parede e nao pode passar
            }

            if(m[x][y].valor==32 || m[x][y].valor==83 || m[x][y].valor==68){ // codigo ascii char '', 'S' e 'D'

                m[x][y].valor = 0; // existe a possibilidade de passar por esse caminho
            }

            // trato o labirinto aqui pra funcao que resolve ele logo abaixo funcionar ja que ele analisa 0's e 1's e nao os valores ascii dos chars digitados

            if(aux=='S'){ // passar pra funcao o vertice inicial
                posSx = x;
                posSy = y;
            }

            if(aux=='D'){ // qual destino olharei pra saber se cheguei la
                posDx = x;
                posDy = y;
            }

            m[x][y].flag_marca_visitado = 0; // inicializar todos vertices como abertos
        }
         getchar(); // nao colocar o char de enter (\n) na matriz
    }

    /*printf("POSSX -> %d\n",posSx);
    printf("POSSY -> %d\n",posSy);

    printf("POSDX -> %d\n",posDx);
    printf("POSDY -> %d\n",posDy);*/

    resposta(m,posSx,posSy,i-1,j-1); // resolve ou nao o labirinto?

    // abaixo e pra ver a nossa matriz do labirinto caso necessario

    /*printf("\n");

    for(x=0;x<i;x++){

        for(y=0;y<j;y++){

            printf("%d ",m[x][y].valor);
        }

        printf("\n");
    }*/

    if(m[posDx][posDy].flag_marca_visitado==1){ // se a posicao D estiver fechada e porque sim resolve

        printf("vai ao ponto de carga\n");

    }else{

        printf("fica no mesmo lugar\n"); // vertice destino fechado, nao tem como chegar ate ele!
    }

    return 0;
}
