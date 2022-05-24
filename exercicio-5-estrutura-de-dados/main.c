#include <stdio.h>
#include <stdlib.h>

void quick_sort(int *a, int left, int right) {
    int i, j, x, y;

    i = left;
    j = right;
    x = a[(left + right) / 2];

    while(i <= j) {
        while(a[i] < x && i < right) {
            i++;
        }
        while(a[j] > x && j > left) {
            j--;
        }
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }

    if(j > left) {
        quick_sort(a, left, j);
    }
    if(i < right) {
        quick_sort(a, i, right);
    }
}

int main()
{
    int i,a,aux;

    while(scanf("%d",&a) != EOF){

        int *arr = (int*) malloc(a * sizeof(int));
        int *arr2 = (int*) malloc(a * sizeof(int));


        for(i=0;i<a;i++){
            scanf("%d",&aux);
            arr[i] = aux;
        }

        for(i=0;i<a;i++){
            scanf("%d",&aux);
            arr2[i] = aux;
        }

        quick_sort(arr, 0, a - 1);
        quick_sort(arr2, 0, a - 1);

        int cont1,cont2,cont3,j;
        cont1 = cont2 = cont3 = 0;

        for(i=0;i<a;i++){

                for(j=0;j<a;j++){

                  if(arr2[i] > arr[j] && arr[j]!=0){
                    cont1++;
                    arr[j] = 0;
                    i++;
                  }
                }
        }

        printf("%d\n",cont1);
    }
    return 0;
}
