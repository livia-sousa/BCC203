#ifndef HEAP_H
#define HEAP_H

#include "registro.h"

#define N 20

typedef int Bool;
#define true 1
#define false 0

typedef Registro TipoChave;

typedef struct
{
  TipoChave chave;
  Bool isMarked;
  int fitaIndicator;
} TipoItem;

typedef TipoItem *TipoRegistro;

typedef struct
{
  TipoRegistro registros;
  int tam;
  int nMarked;
} TipoHeap;

//troca a <-> b
void heap_swap(TipoItem *, TipoItem *);

//imprime a heap
void heap_display(TipoHeap *);

// inicializa as variaveis para a heal e aloca a memoria para o array
void heap_constroiHeap(TipoHeap *, int);

// desaloca o array da heap
void heap_destroyHeap(TipoHeap *);

// retorna se todos os itens na heap estão marcados
Bool heap_hasFullMarked(TipoHeap *);

// retorna se a heap está cheia
Bool heap_isFull(TipoHeap *);

// retorna se a heap está vazia
Bool heap_isEmpty(TipoHeap *);

// retorna o manor valor da heap
TipoItem heap_minValue(TipoHeap *);

//insere um elemento na heap, funciona se a heap ainda não estiver completa
int heap_insertHeap(TipoHeap *, TipoItem, int, Analise *);

/*
  retorna o primeiro registro da heap, ou seja, o item na posição 0, e insere um novo registro
  de forma a manter as propriedades da heap
*/
TipoItem heap_organize(TipoHeap *, TipoChave, Bool, int, Analise *);

// remove sempre o primeiro item da heap e reorganiza a heap
TipoItem heap_remove(TipoHeap *, Analise *);

//insere e "monta" um novo registro na heap
void heap_addReg(TipoHeap *, TipoChave, Bool, int, Analise *analise);

// "transforma" todos os itens em não marcador
void heap_reset(TipoHeap *);

#endif