#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "heap.h"

void heap_swap(TipoItem *a, TipoItem *b)
{
  TipoItem tmp = *a;
  *a = *b;
  *b = tmp;
}

void heap_display(TipoHeap *heap)
{
  for (int i = 0; i < heap->tam; i++)
    printf("%d %s %.1lf %d\n", heap->registros[i].fitaIndicator - 1, heap->registros[i].chave.inscricao, heap->registros[i].chave.nota, heap->registros[i].isMarked);
  printf("\n");
}

void heap_constroiHeap(TipoHeap *heap, int n)
{
  heap->tam = 0;
  heap->nMarked = 0;
  heap->registros = (TipoItem *)malloc(sizeof(TipoItem) * n);
}

void heap_destroyHeap(TipoHeap *heap)
{
  heap->tam = 0;
  heap->nMarked = 0;
  free(heap->registros);
  heap->registros = NULL;
}

Bool heap_hasFullMarked(TipoHeap *heap)
{
  return heap->nMarked == N;
}

Bool heap_isFull(TipoHeap *heap)
{
  return heap->tam == N;
}

Bool heap_isEmpty(TipoHeap *heap)
{
  return heap->tam == 0;
}

TipoItem heap_minValue(TipoHeap *heap)
{
  return heap->registros[0];
}

int heap_insertHeap(TipoHeap *heap, TipoItem item, int i, Analise *analise)
{
  int parent;
  int n = i;
  heap->registros[n] = item;
  parent = (n - 1) / 2;

  //percorre a heap pelo pai e troca caso seja maior que o pai
  while (parent >= 0 && heap->registros[n].chave.nota < heap->registros[parent].chave.nota)
  {
    atualizaComparacoes(analise, 1);
    heap_swap(&heap->registros[n], &heap->registros[parent]);
    n = parent;
    parent = (n - 1) / 2;
  }

  return 1;
}

TipoItem heap_organize(TipoHeap *heap, TipoChave ch, Bool isMarked, int nFita, Analise *analise)
{
  TipoItem nReg;
  nReg.chave = ch;
  nReg.isMarked = isMarked;
  nReg.fitaIndicator = nFita;
  if (isMarked)
    heap->nMarked += 1;

  TipoItem tmp = heap->registros[0]; //"retirando" o maior valor

  int i = 0;
  int min = i;
  int leftChild = 2 * i + 1;
  int rightChild = 2 * i + 2;
  heap->registros[0] = nReg;

  while (1)
  {
    if (heap->registros[min].isMarked)
    { //menor
      if (leftChild < heap->tam)
      {
        if (heap->registros[leftChild].isMarked)
        { //o registro a ser comparado também está marcado
          atualizaComparacoes(analise, 1);
          if (heap->registros[min].chave.nota > heap->registros[leftChild].chave.nota)
            min = leftChild;
        }
        else
        { //não está marcado, logo automaticamente chave é menor
          min = leftChild;
        }
      }

      if (rightChild < heap->tam)
      {
        if (heap->registros[rightChild].isMarked)
        { //o registro a ser comparado também está marcado
          atualizaComparacoes(analise, 1);
          if (heap->registros[min].chave.nota > heap->registros[rightChild].chave.nota && heap->registros[leftChild].isMarked)
            min = rightChild;
        }
        else if (heap->registros[min].chave.nota > heap->registros[rightChild].chave.nota)
        {
          atualizaComparacoes(analise, 1);
          min = rightChild;
        }
        else if (heap->registros[leftChild].isMarked)
        {                                //não está marcado, logo automaticamente chave é menor
          atualizaComparacoes(analise, 1); //conta 1 da do if acima
          min = rightChild;
        }
      }
    }
    else
    {

      if (leftChild < heap->tam && !heap->registros[leftChild].isMarked)
      {
        atualizaComparacoes(analise, 1);
        if (heap->registros[min].chave.nota > heap->registros[leftChild].chave.nota)
          min = leftChild;
      }

      if (rightChild < heap->tam && !heap->registros[rightChild].isMarked)
      {
        atualizaComparacoes(analise, 1);
        if (heap->registros[min].chave.nota > heap->registros[rightChild].chave.nota)
          min = rightChild;
      }
    }

    if (min != i)
    {
      heap_swap(&heap->registros[i], &heap->registros[min]);
      leftChild = 2 * min + 1;
      rightChild = 2 * min + 2;
      i = min;
    }
    else
    {
      break;
    }
  }

  return tmp; //retorna o maior valor
}

TipoItem heap_remove(TipoHeap *heap, Analise *analise)
{
  TipoItem tmp = heap->registros[0];

  int j = heap->tam - 1; //pega sempre o ultimo filho

  if (heap->registros[j].isMarked)
    heap->nMarked -= 1;

  if (j != 0)
  { //tem filho para susbstituir
    heap_organize(heap, heap->registros[j].chave, heap->registros[j].isMarked, heap->registros[j].fitaIndicator, analise);
  }

  heap->tam -= 1;
  return tmp;
}

void heap_addReg(TipoHeap *heap, TipoChave ch, Bool isMarked, int nFita, Analise *analise)
{
  TipoItem nReg;
  nReg.chave = ch;
  nReg.isMarked = isMarked;
  nReg.fitaIndicator = nFita;
  heap_insertHeap(heap, nReg, heap->tam, analise);
  heap->tam += 1;
  if (isMarked)
    heap->nMarked += 1;
}

void heap_reset(TipoHeap *heap)
{
  for (int i = 0; i < heap->tam; i++)
  {
    heap->registros[i].isMarked = false;
    heap->nMarked -= 1;
  }
}