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
#define tamNORMAL 11

//Tam 29 de caracteres usados
const char* NORMAL[] = {
    "01 - Soma apenas os   -   [1]" , //
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

typedef struct LISTA{
    ELEMENTO * inicio;
} CARTELA;

typedef struct aux1{
    int pontosT;
    int codCOMBINACAO;

    struct aux1 *prox;
} COMBOS;

typedef struct _LISTA{
    COMBOS * inicio;

    char USUARIO[MAX];
    int pTOTAL;
} PERFIL;

void criar_PERFIL(PERFIL *, char []);
int **ordenar_COMBO(CARTELA, int);

void inicializarCARTELA(CARTELA *);
int tamanhoCARTELA(CARTELA *);
void alterarPONTUACAO(CARTELA *, int, int);
bool insereCARTELA(CARTELA *, ELEMENTO, int);
void mostraCARTELA(CARTELA *);
void iniciar_jogoNORMAL(CARTELA *c);
int pontuacaoTOTAL(CARTELA *);

int main () {
    CARTELA AGORA;
    inicializarCARTELA(&AGORA);
    iniciar_jogoNORMAL(&AGORA);
    mostraCARTELA(&AGORA);
    printf("\n");
    alterarPONTUACAO(&AGORA, 10, 15);
    alterarPONTUACAO(&AGORA, 5, 45);
    mostraCARTELA(&AGORA);
    printf("TAM : %d\n", tamanhoCARTELA(&AGORA));
    return 0;
}

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
    for(int i = 0; i < tamNORMAL; i++) {
        strcpy(aux.nomeCOMBINACAO, NORMAL[i]);
        aux.check = ' ';
        aux.pontos = 0;
        insereCARTELA(c, aux, i);
    }
}

int pontuacaoTOTAL(CARTELA *c) {
    int pTOTAL = 0;
    ELEMENTO * aux = c->inicio;
    while(aux != NULL) {
        pTOTAL += aux->pontos;
        aux = aux->prox;
    }
    return pTOTAL;
}

void criar_PERFIL(PERFIL *p, char nome_USER[]) {
    strcpy(p->USUARIO, nome_USER);
    p->inicio = NULL;
    p->pTOTAL = 0;
}

int **ordenar_COMBO(CARTELA c, int tam) { //Ordena o combo do maior para o menor
    int **vetor = (int**) malloc(tam * sizeof(int*));
    if (!vetor) {
        printf("erro ao alocar memoria\n");
        return NULL;
    }

    ELEMENTO *aux = c.inicio;
    for(int i = 0; i < tam; i++) {
        vetor[i] = (int *)malloc(2 * sizeof(int)); //Armazenara o indice e o ponto do indice
        if (!vetor[i]) {
            printf("erro ao alocar memoria no v[%d]\n", i);
            return NULL;
        }
        vetor[i][0] = aux->pontos;
        vetor[i][1] = i;
        aux = aux->prox;
    }

    for (int i = 0; i < tam - 1; i++) {
        for (int j = 0; j < tam - i - 1; j++) {
            if (vetor[j][0] < vetor[j + 1][0]) { //Ordenar em ordem decrescente
            int *aux_2 = vetor[j];
            vetor[j] = vetor[j + 1];
            vetor[j + 1] = aux_2;
            }
        }
    }

    return vetor; //vetor[posicao][0 = pontos; 1 = indice]
}

