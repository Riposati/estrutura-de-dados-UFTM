#include <stdio.h>
#include <stdlib.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))

struct tree{
    int key;
    struct tree *esq;
    struct tree *dir;
    int equals;
    int height;
}typedef Tree;

int height(Tree *N){
    if (N == NULL)
        return 0;
    return N->height;
}

int getBalance(Tree *N){
    if (N == NULL)
        return 0;
    return height(N->esq) - height(N->dir);
}

Tree *rightRotate(Tree *y){
    //cout<<"Rotacao simples direita na entrada da chave = "<<y->chave<<endl;

    Tree *x = y->esq;
    Tree *T2 = x->dir;

    // Perform rotation
    x->dir = y;
    y->esq = T2;

    // Update heights
    y->height = max(height(y->esq), height(y->dir))+1;
    x->height = max(height(x->esq), height(x->dir))+1;

    return x;
}

Tree *leftRotate(Tree *x){
    //cout<<"Rotacao simples a esquerda na entrada da chave = "<<x->chave<<endl;

    Tree *y = x->dir;
    Tree *T2 = y->esq;

    // Perform rotation
    y->esq = x;
    x->dir = T2;

    //  Update heights
    x->height = max(height(x->esq), height(x->dir))+1;
    y->height = max(height(y->esq), height(y->dir))+1;

    return y;
}

Tree *balanceamentoPosInsercao(Tree *raiz,int chave){

    raiz->height = 1 + max(height(raiz->esq),height(raiz->dir));

    int balanco = getBalance(raiz);

    /// ( rotação simples a direita )

    if(balanco > 1 && chave < raiz->esq->key){

        return rightRotate(raiz);
    }

    /// ( rotação simples a esquerda )

    if(balanco < -1 && chave > raiz->dir->key){

        return leftRotate(raiz);
    }

    /// esq dir ( dupla rotação a direita )

    if(balanco > 1 && chave > raiz->esq->key){

        //cout<<"************Rotacao dupla a direita na entrada da chave = "<<chave<<endl;

        raiz->esq = leftRotate(raiz->esq);

        return rightRotate(raiz);
    }

    /// dir esq ( dupla rotação a esquerda )

    if(balanco < -1 && chave < raiz->dir->key){

        //cout<<"************Rotacao dupla a esquerda na entrada da chave = "<<chave<<endl;

        raiz->dir = rightRotate(raiz->dir);

        return leftRotate(raiz);
    }

    return raiz;
}

Tree *putMine(Tree *raiz,int chave){

    // insere normalmente como numa arvore sem balanceamento
    Tree *aux = (Tree *)malloc(sizeof(Tree));
    aux->key = chave;
    aux->dir = NULL;
    aux->esq = NULL;
    aux->height = 0;
    aux->equals = 1;

    if(raiz==NULL){

        raiz = aux;
        aux = NULL;

    }else{

        if(raiz->key == chave){
            //printf("raiz->key = %d\n",raiz->key);
            raiz->equals+=1;
            //printf("raiz->equals = %d\n",raiz->equals);
            return raiz;
        }

        if(raiz->key > chave){

            raiz->esq = putMine(raiz->esq,chave);

        }else{

            if(raiz->key < chave){

                raiz->dir = putMine(raiz->dir,chave);
            }
        }
    }

    /// parte do balanceamento

    raiz = balanceamentoPosInsercao(raiz,chave);

    return raiz;
}

void infixa(Tree *r, int *limite){
    if(r!=NULL){
        infixa(r->esq, limite);
        if(r->equals > 1 && *limite > 0){
            printf("%d ",r->key);
            //printf("limite -> %d\n",*limite);
            *limite-=1;
        }
        infixa(r->dir, limite);
    }
}

Tree *clearBuffer(Tree *raiz){

    if(raiz==NULL)return raiz;

    raiz->esq = clearBuffer(raiz->esq);
    raiz->dir = clearBuffer(raiz->dir);

    if(raiz->esq==NULL && raiz->dir==NULL){
        //printf("\nchave deletada = %d\n",raiz->key);
        free(raiz);raiz = NULL;return raiz;
    }
}

int number_of_duplicates(Tree *node) {
    int ans = 0;
    if (node) {
        ans = number_of_duplicates(node->esq);
        if(node->equals > 1) {
            //printf("value: %d  frequency: %d\n", node->key, node->equals);
            ans += node->equals;
        }
        ans += number_of_duplicates(node->dir);
    }
    return ans;
}

void infixaAVL(Tree *raiz){

    if(raiz!=NULL){
        infixaAVL(raiz->esq);
        printf("%d ",raiz->key);
        infixaAVL(raiz->dir);
    }
}

void prefixa(Tree *raiz){

    if(raiz!=NULL){
        printf("%d ",raiz->key);
        prefixa(raiz->esq);
        prefixa(raiz->dir);
    }
}

void posfixa(Tree *raiz){

    if(raiz!=NULL){
        posfixa(raiz->esq);
        posfixa(raiz->dir);
        printf("%d ",raiz->key);
    }
}

int main() {
    //freopen("in", "r", stdin);
    //freopen("out", "w", stdout);
    int n, k, limite;
    int cnt = 0;
    Tree *root;

    while(scanf("%d%d", &n, &k) != EOF) {

        root = NULL;
        limite = k;

        while(n--) {
            int v; scanf("%d", &v);
            //inserts(&node, v);
            //insertion(v, &root);
            root = putMine(root,v);
        }

        //printf("qqqqqqqqroot->key = %d\n",root->key);

        int r = number_of_duplicates(root);
        printf("%d\n", r);

        if(r == 0 || k == 0) {
            printf("empty\n");
            continue;
        }

        //inorderTraversal(root, &k, k);
        infixa(root, &limite);
        //printf("\n");
        cnt++;
       // release_mem(node);
       if(cnt)
         printf("\n");

       // printf("chaves na arvore:\n");
        //posfixa(root);

        root = clearBuffer(root);
        //printf("POSFIXA\n");
        //posfixa(root); // so pra validar a "limpeza" na arvore
    }
    return 0;
}
