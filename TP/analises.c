#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "analises.h"

//funcoes para analises solicitadas
// aqui faz-se a analise para as etapas de criacao dos indices 
// e a analise para a pesquisa em si
void iniciaAnalise(Analise *analise){
  //depois -> analise da pesquisa
  analise->tranferencias_depois = 0; 
  analise->comparacoes_depois = 0;

  //antes -> analise da criacao 
  analise->tranferencias_antes = 0;
  analise->comparacoes_antes = 0;
}

//funcoes para contagem do tempo de execucao
//inicia e finaliza o clock - relogiinho
void iniciaContagemTempo(Analise *analise){
  analise->iniTempo = clock();
}

void finalizaContagemTempo(Analise *analise){
  analise->fimTempo = clock();
}

//funcoes para verificacao do numero de transferencias
void atualizaTransferencias_depois(Analise *analise, int qtd){
  analise->tranferencias_depois += qtd;
}

void atualizaTransferencias_antes(Analise *analise, int qtd){
  analise->tranferencias_antes += qtd;
}

//funcoes para verificacao do numero de comparacoes
void atualizaComparacoes_depois(Analise *analise, int qtd){
  analise->comparacoes_depois += qtd;
}

void atualizaComparacoes_antes(Analise *analise, int qtd){
  analise->comparacoes_antes += qtd;
}

//funcoes para atualizacao do tempo
void atualizaTempo_antes(Analise *analise){
  //calcula o tempo o converte para milissegundos
  analise->tempo_antes = ((double)(analise->fimTempo - analise->iniTempo) * 1000 / CLOCKS_PER_SEC);
}

void atualizaTempo_depois(Analise *analise){
  //calculando e convertendo tempo total para milissegundos
  analise->tempo_depois = ((double)(analise->fimTempo - analise->iniTempo) * 1000 / CLOCKS_PER_SEC);
}

//funcao para impressao dos dados 
void imprimirDados(Analise *analise){
  printf("Dados da execução para criação dos índices:\n");
  printf("⏰  - Tempo de execução: %.4lfms\n", analise->tempo_antes);
  printf("📈  - Quantidade de comparação(ões): %d\n", analise->comparacoes_antes);
  printf("📊  - Quantidade de transferencia(s): %d\n\n", analise->tranferencias_antes);

  printf("Dados da execução da pesquisa:\n");
  printf("⏰  - Tempo de execução: %.4lfms\n", analise->tempo_depois);
  printf("📈  - Quantidade de comparação(ões): %d\n", analise->comparacoes_depois);
  printf("📊  - Quantidade de transferencia(s): %d\n", analise->tranferencias_depois);
}
