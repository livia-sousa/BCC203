#ifndef analise_h
#define analise_h

#include <time.h>

//a analise eh dormado por numero de transferencias, comparacoes e o tempo
typedef struct{
  int tranferencias_antes, tranferencias_depois;
  int comparacoes_antes, comparacoes_depois;
  double tempo_depois, tempo_antes;

  clock_t iniTempo, fimTempo;
} Analise;


//funcao que inicia as analises
void iniciaAnalise(Analise *analise);

//funcao que imprime os dados obtidos na analise 
void imprimirDados(Analise *analise);

//funcoes para contagem do tempo 
void iniciaContagemTempo(Analise *analise);
void finalizaContagemTempo(Analise *analise);

//funcoes para numero de transfencias
void atualizaTransferencias_antes(Analise *analise, int qtd);
void atualizaTransferencias_depois(Analise *analise, int qtd);

//funcoes para numero de comparacoes
void atualizaComparacoes_antes(Analise *analise, int qtd);
void atualizaComparacoes_depois(Analise *analise, int qtd);

//funcoes para atualizacao do tempo de contagem
void atualizaTempo_antes(Analise *analise);
void atualizaTempo_depois(Analise *analise);

#endif