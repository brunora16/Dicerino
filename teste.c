#include <stdio.h>
#include <stdlib.h>


void **criando_ponteiro(int **m, int L, int C) {
    m = (int**) malloc(L*sizeof(int*));
    if(!m) {
        printf("Erro 1\n");
    }

    for(int i = 0; i < L; i++) {
        if((m[i] = (int*) malloc(C*sizeof(int))) == NULL) {
            printf("Erro %d\n", i);
        }
    }
}

int main () {
    int **matriz;
    criando_ponteiro(&matriz, 3, 3);

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            matriz[i][j] = i + j;
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    free(matriz);
    return 0;
}