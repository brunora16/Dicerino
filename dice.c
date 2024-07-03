#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Para chamar algum desse caracter e so pedir : faces[numero - 1]
//So funcionar aqueles que tem suporte a Unicode!!!

/*
    Geracao de dado
    srand(time(NULL)) para sempre que abrir o programa tera um reset
    rand()%6 de 0 ate 5, so colocar mais 1

    srand(time(NULL));
    for(int i = 0; i > -1; i++) {
        printf("%d\n", rand()%6 + 1);
    }
*/

//Atualmente os textos obedecem 33 de tamanho de caracteres.

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int escolher_Opcao(int ini, int fim) {
    int opcao;
    while (1) {
        printf("Digite: ");
        scanf("%d", &opcao);
        if (opcao >= ini && opcao <= fim) {
            return opcao;
        }
        limpar_buffer();
    }
}

void limpar_tela() {
    for(int i = 0; i < 50; i++) {
        printf(" \n");
    }
}

void menu_inicial() {
    int OPCAO = 1;
    while(OPCAO != 0) {
        printf("=================================\n");
        printf("             M E N U             \n");
        printf("=================================\n");
        printf("- Novo Jogo                   [1]\n");
        printf("_________________________________\n");
        printf("- Ver Score                   [2]\n");
        printf("_________________________________\n");
        printf("- Sair                        [0]\n");
        printf("_________________________________\n"); 
        OPCAO = escolher_Opcao(0,2);
        switch (OPCAO) {
        case 1:
            limpar_tela();
            novo_jogo();
            break;
        case 2:
            limpar_tela();

            break;
        default:
            break;
        }
    }
}

void novo_jogo() {
int OPCAO = 1;
    while(OPCAO != 0) {
        printf("=================================\n");
        printf("  S E L E C I O N E  O  M O D O  \n");
        printf("=================================\n");
        printf("- Padrao                      [1]\n");
        printf("_________________________________\n");
        printf("- Desafiador                  [2]\n");
        printf("_________________________________\n");
        printf("- Voltar                      [0]\n");
        printf("_________________________________\n");
        OPCAO = escolher_Opcao(0,2);
        switch (OPCAO) {
        case 1:
            limpar_tela();

            break;
        case 2:
            limpar_tela();

            break;
        default:
            limpar_tela();
            break;
        }
    }
}


int main () {
    limpar_tela(); //Para comecar a printar la em baixo do console
    menu_inicial();
    return 0;
}