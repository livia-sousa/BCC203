#ifndef analises_h
#define analises_h

#include <time.h>

typedef struct {
  int tranferencias;
  int comparacoes;
  double tempo;
  clock_t iniTempo, fimTempo;
} Analise; // A estrutura Analise é formada pelo número de transferências, comparações e o tempo

void iniciaAnalise(Analise *analise);

void iniciaContagemTempo(Analise *analise);

void finalizaContagemTempo(Analise *analise);

void imprimirAnalise(Analise *analise);

void atualizaTransferencias(Analise *analise, int n);

void atualizaComparacoes(Analise *analise, int n);

void atualizaTempo(Analise *analise);

#endif