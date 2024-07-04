/*
    CARTELA (Printar; Alterar e Atualizar as informacoes; Uma Struct para cada tipo!; Inicializar, Apagar, Salvar, 
    Um perfil pro Usuario (Quantos combos realizados; Pontos));  -  
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200
#define true 1
#define false 0

//Tam 29 de caracteres usados
const char* NORMAL[] = {
    "01 - Soma apenas os   -   [1]", //
    "02 - Soma apenas os   -   [2]", //
    "03 - Soma apenas os   -   [3]", //
    "04 - Soma apenas os   -   [4]", //
    "05 - Soma apenas os   -   [5]", //
    "06 - Soma apenas os   -   [6]", //
    "07 - Choice       [? ? ? ? ?]", //
    "08 - Quadra       [# # # # ?]", //
    "09 - Full House   [# # # + +]", //
    "10 - Diferentes   [# + - . ,]", //
    "11 - Tudo Igual   [# # # # #]", //
};

typedef int bool;

typedef struct aux{
    char nomeCOMBINACAO[MAX];
    char check; //Caso check = ' ' e por que nao fez o ponto, caso 'X' e por que conseguiu fazer essa combinacao
    int pontos; //Caso a pontuacao seja diferente de 0 e por que e possivel preencher a cartela

    struct aux *prox;
} ELEMENTO;

typedef struct __lista{
    ELEMENTO * inicio;
} CARTELA;

void inicializarCARTELA(CARTELA *c) {
    c->inicio = NULL;
}

int tamanhoCARTELA(CARTELA *c){
    ELEMENTO *aux = c->inicio;
    int tamanho = 0;
    while(aux != NULL){
        tamanho++;
        aux = aux->prox;
    }
    return tamanho;
}

void alterarPONTUACAO(CARTELA *c, int posicao, int pontos) {
    if (posicao < 0 || posicao >= tamanhoCARTELA(c)) {
        printf("Posicao invalida.\n");
        return;
    }

    ELEMENTO *aux = c->inicio;
    for (int i = 0; i < posicao; ++i) {
        aux = aux->prox;
    }
    aux->check = 'X';
    aux->pontos = pontos;
}

bool insereCARTELA(CARTELA *c, ELEMENTO elemento, int posicao){
    ELEMENTO * novo = (ELEMENTO*)malloc(sizeof(ELEMENTO));
    if(novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        return false;
    }

    strcpy(novo->nomeCOMBINACAO, elemento.nomeCOMBINACAO);
    novo->check = elemento.check;
    novo->pontos = elemento.pontos;

    if(posicao < 0 || posicao > tamanhoCARTELA(c)) {
        free(novo);
        return false;
    } 

    if(posicao == 0){
        novo->prox = c->inicio;
        c->inicio = novo;
        return true;
    }

    ELEMENTO *aux = c->inicio;

    for(int i = 0 ; i < posicao -1 ; ++i) {
        aux = aux->prox;
    }

    novo->prox = aux->prox;
    aux->prox = novo;
    return true;  
}

void mostraCARTELA(CARTELA *c){
    ELEMENTO * aux = c->inicio;
    while(aux != NULL){
        printf("%s [%c] --> [%d]\n", aux->nomeCOMBINACAO, aux->check, aux->pontos);
        aux = aux->prox;
    }
}

void iniciar_jogoNORMAL(CARTELA *c) {
    ELEMENTO aux;
    for(int i = 0; i < 11; i++) {
        strcpy(aux.nomeCOMBINACAO, NORMAL[i]);
        aux.check = ' ';
        aux.pontos = 0;
        insereCARTELA(c, aux, i);
    }
}

int main () {
    CARTELA AGORA;
    inicializarCARTELA(&AGORA);
    iniciar_jogoNORMAL(&AGORA);
    mostraCARTELA(&AGORA);
    printf("\n");
    alterarPONTUACAO(&AGORA, 10, 15);
    mostraCARTELA(&AGORA);
    return 0;
}