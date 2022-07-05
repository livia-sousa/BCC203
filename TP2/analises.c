#include <stdio.h>
#include <stdlib.h>
#include "analises.h"

// Funções para análises solicitadas

void iniciaAnalise(Analise *analise) {
    analise->tranferencias = 0;
    analise->comparacoes = 0;
}

// Funções para contagem do tempo de execução
// Inicia e finaliza o clock - reloginho
void iniciaContagemTempo(Analise *analise) {
    analise->iniTempo = clock();
}

void finalizaContagemTempo(Analise *analise) {
    analise->fimTempo = clock();
}

// Função para verificação do número de transferências
void atualizaTransferencias(Analise *analise, int n) {
    analise->tranferencias += n;
}

// Função para verificação do número de comparações
void atualizaComparacoes(Analise *analise, int n) {
    analise->comparacoes += n;
}

// Calcula e converte o tempo total para milissegundos
void atualizaTempo(Analise *analise) {
    analise->tempo = ((double)(analise->fimTempo - analise->iniTempo) * 1000 / CLOCKS_PER_SEC);
}

// Função para impressão dos dados 
void imprimirAnalise(Analise *analise) {
    printf("⏰  - Tempo de execução: %.4lfms\n", analise->tempo);
    printf("📈  - Quantidade de comparação(ões): %d\n", analise->comparacoes);
    printf("📊  - Quantidade de transferencia(s): %d\n", analise->tranferencias);
}