#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define true 1
#define false 0
#define tamNORMAL 11
#define MAX 200

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
    int Rodadas;
} PERFIL;

void inicializarCARTELA(CARTELA *);
int tamanhoCARTELA(CARTELA *);
int tamanhoPERFIL(PERFIL *);
void alterarPONTUACAO(CARTELA *, int, int);
bool insereCARTELA(CARTELA *, ELEMENTO, int);
void mostraCARTELA(CARTELA *);
void iniciar_jogoNORMAL(CARTELA *c);
int pontuacaoTOTAL(CARTELA *);
bool criar_PERFIL(PERFIL *, char []);
bool ordenar_COMBO(PERFIL *, int);
void preencher_PERFIL(PERFIL *, CARTELA *);
void salvar_PERFIS_txt(PERFIL *);
void imprimir_HISTORICO_txt();
void jogarDados(int dados[], int segurados[]);
void mostrarDados(int dados[], int segurados[]);
int escolherDadosParaSegurar(int dados[], int segurados[]);
int escolherCombinacao(CARTELA *c);
int calcularPontos(int dados[], int escolha);
void ranquear_jogadores();
int escolher_Opcao(int , int);

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limpar_tela() {
    for(int i = 0; i < 50; i++) {
        printf(" \n");
    }
}

void menu_inicial();
void novo_jogo();

int main () {
    srand(time(NULL));
    menu_inicial();
    return 0;
}

void menu_inicial() {
    int OPCAO = 1;
    while(OPCAO != 0) {
        limpar_tela();
        printf("=================================\n");
        printf("             M E N U             \n");
        printf("=================================\n");
        printf("- Novo Jogo                   [1]\n");
        printf("_________________________________\n");
        printf("- Ver Historico               [2]\n");
        printf("_________________________________\n");
        printf("- Ver Ranking                 [3]\n");
        printf("_________________________________\n");
        printf("- Sair                        [0]\n");
        printf("_________________________________\n"); 
        printf("Digite: ");
        OPCAO = escolher_Opcao(0,3);
        switch (OPCAO) {
        case 1:
            limpar_tela();
            novo_jogo();
            limpar_tela();
            break;
        case 2:
            limpar_tela();
            imprimir_HISTORICO_txt();
            limpar_tela();
            break;
        case 3:
            limpar_tela();
            ranquear_jogadores();
            limpar_tela();
            break;
        default:
            break;
        }
    }
}

void novo_jogo() {
    CARTELA AGORA;
    inicializarCARTELA(&AGORA);
    iniciar_jogoNORMAL(&AGORA);

    PERFIL User;
    char nome[MAX];
    printf("Digite seu nome: ");
    limpar_buffer(); // Limpa o buffer antes de ler a entrada do usuário
    fgets(nome, MAX, stdin);
    nome[strcspn(nome, "\n")] = 0; // Remove newline character
    criar_PERFIL(&User, nome);
    printf("Lembrando que apenas partidas de duracao padrao - 6 rodadas - sao contabilizadas no ranking.\n");
    printf("Digite o numero de rodadas [1 - 12]: ");
    User.Rodadas = escolher_Opcao(1, 12);

    limpar_tela();
    int rodadas = 0;
    int dados[5];
    int segurados[5] = {0, 0, 0, 0, 0};
    mostraCARTELA(&AGORA);
    while (User.Rodadas > rodadas) {
        printf("__________________________________________\n\n");
        printf("             R O D A D A  |%d|            \n", rodadas+1);
        printf("__________________________________________\n\n");
        //jogarDados(dados, segurados);
        //mostrarDados(dados, segurados);

        for (int i = 0; i < 3; i++) {
            printf("\n> ROLAGEM -- (%d)\n\n", i+1);
            jogarDados(dados, segurados);
            mostrarDados(dados, segurados);
            printf("__________________________________________\n\n");
            if(i + 1 == 3) break;
            escolherDadosParaSegurar(dados, segurados);
            //if (escolha == 0) break;
            if(segurados[0] > 0 && segurados[1] && segurados[2] > 0 && segurados[3] > 0 && segurados[4] > 0 ) break; //Para caso ja tenha segurado todos os dados, nao precisa rolar dnv
        }
        for(int i = 0; i < 5; i++) {
            segurados[i] = 0;
        }
        
        int combinacao = escolherCombinacao(&AGORA);
        limpar_tela();
        if(combinacao != -1) {
            int pontos = calcularPontos(dados, combinacao);
            alterarPONTUACAO(&AGORA, combinacao, pontos);
        }
        printf("__________________________________________\n\n");
        mostraCARTELA(&AGORA);
        rodadas++;
    }

    preencher_PERFIL(&User, &AGORA);
    ordenar_COMBO(&User, tamNORMAL);
    salvar_PERFIS_txt(&User);
    limpar_tela();
    printf("__________________________________________\n\n");
    printf("           F I M   D E   J O G O          \n");
    printf("__________________________________________\n\n");
    mostraCARTELA(&AGORA);
    imprimir_HISTORICO_txt();
}

// Funções de inicialização, manipulação de dados e outras funções auxiliares

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

int tamanhoPERFIL(PERFIL *p){
    COMBOS *aux = p->inicio;
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
    printf("\n");
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

bool criar_PERFIL(PERFIL *p, char nome_USER[]) {
    strcpy(p->USUARIO, nome_USER);
    p->inicio = NULL;
    p->pTOTAL = 0;
    return true;
}

bool ordenar_COMBO(PERFIL *p, int tam) { //Ordena o combo do maior para o menor
    int **vetor = (int**) malloc(tam * sizeof(int*));
    if (!vetor) {
        printf("erro ao alocar memoria\n");
        return false;
    }

    COMBOS * aux = p->inicio;
    for(int i = 0; i < tam; i++) {
        vetor[i] = (int *)malloc(2 * sizeof(int)); //Armazenara o indice e o ponto do indice
        if (!vetor[i]) {
            printf("erro ao alocar memoria no v[%d]\n", i);
            for (int j = 0; j < i; j++) { //Libera memoria ja alocada anteriomente
                free(vetor[j]);
            }
            return false;
        }
        vetor[i][0] = aux->pontosT;
        vetor[i][1] = aux->codCOMBINACAO;
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

    aux = p->inicio;
    for(int i = 0; aux != NULL; i++) {
        aux->pontosT = vetor[i][0];
        aux->codCOMBINACAO = vetor[i][1];
        aux = aux->prox;
    }

    for (int i = 0; i < tam; i++) {
        free(vetor[i]);
    }
    free(vetor);

    return true;
}

void preencher_PERFIL(PERFIL *p, CARTELA *c) {
    COMBOS *aux = p->inicio;
    ELEMENTO *aux_c = c->inicio;
    int SomaTotal = 0;
    for(int i = 1; aux_c != NULL; i++) {
        COMBOS *novo_combo = (COMBOS *)malloc(sizeof(COMBOS));
        if (novo_combo == NULL) {
            printf("Erro ao alocar memoria\n");
            return;
        }
        
        novo_combo->pontosT = aux_c->pontos;
        novo_combo->codCOMBINACAO = i;
        SomaTotal += aux_c->pontos;

        if (p->inicio == NULL) {
            p->inicio = novo_combo;
            aux = p->inicio;
        } else {
            aux->prox = novo_combo;
            aux = aux->prox;
        }

        aux_c = aux_c->prox;
    }
    p->pTOTAL = SomaTotal;
    if (aux != NULL) {
        aux->prox = NULL;
    }
}

void salvar_PERFIS_txt(PERFIL *p) {
    FILE *arquivo = fopen("historicoDICE.txt", "a"); //Verifica se existe esse arquivo para leitura e escrita
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }


    fprintf(arquivo, "Usuario:%s| Rodadas:%d| Pontuacao:%d", p->USUARIO, p->Rodadas, p->pTOTAL);
    //COMBOS * aux = p->inicio; //Caso eu queria salvar os combos feitos
    //while(aux != NULL) {
    //    fprintf(arquivo, "[%d =", aux->codCOMBINACAO);
    //    fprintf(arquivo, "%d] ", aux->pontosT);
    //    aux = aux->prox;
    //}
    fprintf(arquivo, "\n");
    
    fclose(arquivo);
}

void imprimir_HISTORICO_txt() {
    FILE *arquivo;
    arquivo = fopen("historicoDICE.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    char linha[MAX];
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
    }
    limpar_buffer();
    char press;
    
    printf("Digite qualquer tecla para voltar: ");
    scanf("%c", &press);   
    fclose(arquivo);
}

void jogarDados(int dados[], int segurados[]) {
    for(int i = 0; i < 5; i++) {
        if(segurados[i] == 0) {
            dados[i] = rand() % 6 + 1;
        }
    }
}

void mostrarDados(int dados[], int segurados[]) {
    printf("Dados:     ");
    for (int i = 0; i < 5; i++) {
        printf("[%d] ", dados[i]);
    }
    printf("\nSegurados: ");
    for (int i = 0; i < 5; i++) {
        if (segurados[i]) {
            printf("[X] ");
        } else {
            printf("[ ] ");
        }
    }
    printf("\n");
}

int escolherDadosParaSegurar(int dados[], int segurados[]) {
    int escolha;
    printf("Escolha os dados para segurar (1-5) ou 0 para continuar: ");
    while (1) {
        scanf("%d", &escolha);
        if (escolha == 0) {
            return 0;
        }
        if (escolha > 0 && escolha <= 5) {
            segurados[escolha - 1] = 1;
        } else {
            printf("Escolha invalida. Tente novamente: ");
        }
    }
    escolha = dados[0];
}

int escolherCombinacao(CARTELA *c) {
    mostraCARTELA(c);
    int escolha;
    printf("> Escolha uma combinacao (1-11)\n(12) para pular: ");
    while (1) {
        scanf("%d", &escolha);
        if (escolha >= 1 && escolha <= 11) {
            return escolha - 1;
        } 
        else {
            if(escolha == 12) {
                return -1;
            }
            else {
                printf("Escolha invalida. Tente novamente: ");
            }
        }
    }
}

int calcularPontos(int dados[], int escolha) {
    int pontos = 0;
    switch (escolha) {
        case 0: // Soma apenas os 1
            for (int i = 0; i < 5; i++) {
                if (dados[i] == 1) {
                    pontos += 1;
                }
            } // 5
            break;
        case 1: // Soma apenas os 2
            for (int i = 0; i < 5; i++) {
                if (dados[i] == 2) {
                    pontos += 2;
                }
            } // 10
            break;
        case 2: // Soma apenas os 3
            for (int i = 0; i < 5; i++) {
                if (dados[i] == 3) {
                    pontos += 3;
                }
            } // 15
            break;
        case 3: // Soma apenas os 4
            for (int i = 0; i < 5; i++) {
                if (dados[i] == 4) {
                    pontos += 4;
                }
            } // 20
            break;
        case 4: // Soma apenas os 5
            for (int i = 0; i < 5; i++) {
                if (dados[i] == 5) {
                    pontos += 5;
                }
            } // 25
            break;
        case 5: // Soma apenas os 6
            for (int i = 0; i < 5; i++) {
                if (dados[i] == 6) {
                    pontos += 6;
                }
            } // 30
            break;
        case 6: // Choice
            for (int i = 0; i < 5; i++) {
                pontos += dados[i];
            } 
            pontos += 10;
            // 40
            break;
        case 7: // Quadra
            {
                int freq[7] = {0};
                for (int i = 0; i < 5; i++) {
                    freq[dados[i]]++;
                }
                for (int i = 1; i <= 6; i++) {
                    if (freq[i] >= 4) {
                        pontos = 11 * i ;
                        break;
                    }
                }
            } // 66
            break;
        case 8: // Full House
            {
                int freq[7] = {0};
                for (int i = 0; i < 5; i++) {
                    freq[dados[i]]++;
                }
                int threeOfKind = 0;
                int pair = 0;
                for (int i = 1; i <= 6; i++) {
                    if (freq[i] == 3) {
                        threeOfKind = i;
                    }
                    if (freq[i] == 2) {
                        pair = i;
                    }
                }
                if (threeOfKind && pair) {
                    pontos = (threeOfKind * 4 + pair * 3) * 2;
                }
            }
            break; // 78
        case 9: // Diferentes
            {
                int freq[7] = {0};
                for (int i = 0; i < 5; i++) {
                    freq[dados[i]]++;
                }
                int countDifferent = 0;
                for (int i = 1; i <= 6; i++) {
                    if (freq[i] > 0) {
                        countDifferent++;
                    }
                }
                if (countDifferent == 5) {
                    for(int j = 0; j < 5; j++) pontos += dados[j];
                    
                    pontos = pontos * 5; 
                }
            }
            break; // 100
        case 10: // Tudo Igual
            {
                int first = dados[0];
                bool allEqual = true;
                for (int i = 1; i < 5; i++) {
                    if (dados[i] != first) {
                        allEqual = false;
                        break;
                    }
                }
                if (allEqual) {
                    pontos = first * 25;
                }
            } // 150
            break;
    }
    return pontos;
}

// Nova função para ranquear os jogadores

void ranquear_jogadores() {
    FILE *arquivo;
    arquivo = fopen("historicoDICE.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    typedef struct {
        char nome[MAX];
        int rounds; // rounds / 12 = num de partidas 
        int pontos; // pontos / num de partidas = media
        int record; // melhor pontuacao do usario
        
    } JOGADOR; // jogador com maior media rank 1

    JOGADOR jogadores[MAX];
    int n_jogadores = 0;
    
    char linha[MAX];
    while (fgets(linha, sizeof(linha), arquivo)) {
        char nome[MAX];
        int pontos;
        int rounds = 0; 
        //Usuario: %s | Rodadas: %d | Pontuacao: %d 
        sscanf(linha, "Usuario: %[^|]| Rodadas: %d | Pontuacao: %d", nome, &rounds, &pontos);

        if(rounds != 6) continue; // Se tiver menos que 12 rodadas nao merece entrar no ranking

        bool encontrado = false;
        
        for (int i = 0; i < n_jogadores; i++) {                        
            
            if (strcmp(jogadores[i].nome, nome) == 0) {
                // record recebe o valor da primeira partida do usuario

                if(jogadores[i].record < pontos) 
                jogadores[i].record = pontos; // se a partida atual tiver mais pontos que a record, ela se torna o novo record
                
                jogadores[i].pontos += pontos;
                jogadores[i].rounds += rounds;
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            strcpy(jogadores[n_jogadores].nome, nome);
            jogadores[n_jogadores].pontos = pontos;
            jogadores[n_jogadores].rounds = rounds;
            jogadores[n_jogadores].record = pontos;
            n_jogadores++;
        }
    }
    fclose(arquivo);

    // Ordenar jogadores por pontuação (bubble sort)
    for (int i = 0; i < n_jogadores - 1; i++) {
        for (int j = 0; j < n_jogadores - i - 1; j++) {
            if (jogadores[i].record < jogadores[i + 1].record) {
                JOGADOR temp = jogadores[j];
                jogadores[j] = jogadores[j + 1];
                jogadores[j + 1] = temp;
            }
        }
    }
    printf("------------------------------------------\n");
    printf("|         Ranking dos Jogadores:         |\n");
    printf("------------------------------------------\n\n");
    for (int i = 0; i < n_jogadores; i++) {
        printf("[%s] \nL> |Record: %d| - Media: %d - P.Total: %d - Partidas: %d \n", jogadores[i].nome, jogadores[i].record, (jogadores[i].pontos)/(jogadores[i].rounds/6), jogadores[i].pontos, (jogadores[i].rounds)/6);
    }   
    limpar_buffer();
    char press;
    
    printf("Digite qualquer tecla para voltar: ");
    scanf("%c", &press);   
}

int escolher_Opcao(int ini, int fim) {
    int opcao;
    while (1) {
        scanf("%d", &opcao);
        if (opcao >= ini && opcao <= fim) {
            return opcao;
        }
        limpar_buffer();
        if(ini != fim) {
            printf("Entrada invalida!\nDigite novamente entre [%d - %d]: ", ini, fim);
        }
        else {
            printf("Entrada invalida!\nDigite novamente [%d]: ", ini);
        }
    }
}
