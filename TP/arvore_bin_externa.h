#ifndef arvore_bin_externa_h
#define arvore_bin_externa_h

#include <time.h>
#include "registro.h"
#include "analises.h"

typedef Registro TipoItem;

typedef struct {
  TipoItem item;
  int esq;
  int dir;
} TipoNo;

TipoNo criaNovoNo(TipoItem *item);
int insercao(FILE *arquivo, TipoItem *item, int pos, Analise *analise);
int insercaoOrdenada(FILE *arquivo, TipoItem *item, int pos, Analise *analise);
int arvoreBinariaExterna(TipoItem *itemP, Analise *analise, int situacao, int quantidade);

#endif