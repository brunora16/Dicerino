# Dicerino: Jogo de Dados em C

## Sobre o Projeto
Dicerino é um jogo de dados desenvolvido em linguagem C, inspirado em clássicos como Yahtzee. Ele mistura elementos de sorte e estratégia, combinando as combinações de mãos do pôquer com o preenchimento de uma cartela de pontuação, similar ao bingo.

Este projeto foi desenvolvido como trabalho final da disciplina de Programação de Computadores 2, com o objetivo de aplicar de forma prática os principais conceitos de programação em C aprendidos em sala de aula, como estruturas de dados, alocação dinâmica e manipulação de arquivos.

## Funcionalidades
Menu Interativo: Navegue facilmente entre Iniciar um Novo Jogo, ver o Histórico de Partidas ou consultar o Ranking.

Jogabilidade Clássica: Você tem 3 rolagens por rodada para tentar formar a melhor combinação de 5 dados.

Segurar Dados: A cada rolagem, escolha quais dados manter ("segurar") para otimizar sua pontuação.

Duração Variável: Escolha jogar de 1 a 12 rodadas.

Sistema de Pontuação: 11 combinações diferentes para preencher, cada uma com sua própria regra de pontuação.

Histórico Persistente: Todas as partidas são salvas automaticamente em um arquivo historicoDICE.txt.

Ranking de Jogadores: O jogo calcula e exibe um ranking baseado na maior pontuação (recorde) obtida em partidas de 6 rodadas (duração padrão).

## Conceitos Aplicados
Este projeto foi uma oportunidade para implementar e consolidar diversos conceitos fundamentais da linguagem C:

Estruturas de Dados (struct): Utilizadas para modelar a CARTELA (cartela de pontuação), o PERFIL do jogador e os COMBOS de pontuação.

Listas Encadeadas: A cartela de cada jogador é implementada como uma lista encadeada, permitindo flexibilidade e gerenciamento dinâmico.

Alocação Dinâmica de Memória: Uso de malloc() e free() para gerenciar a memória das listas encadeadas e de vetores auxiliares.

Manipulação de Ponteiros: Conceito central para a implementação e navegação das listas encadeadas.

Leitura e Escrita de Arquivos (File I/O): Funções como fopen(), fprintf(), fgets() e sscanf() são usadas para criar, ler e atualizar o arquivo historicoDICE.txt, garantindo a persistência dos dados.

Modularização com Funções: O código é organizado em diversas funções, cada uma com uma responsabilidade única (ex: jogarDados, calcularPontos, ranquear_jogadores).
