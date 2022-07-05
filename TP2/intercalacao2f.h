#ifndef INTERCALACAO2F_H
#define INTERCALACAO2F_H

#include "heap.h"

const char *intercalacaoSPS(char *, int, Analise *, Analise *);

void geracaoBlocosOrdenados(char *, TipoHeap *, const char *[], int[], int, Analise *);

void intercalacao(TipoHeap *, FILE *[], const char *[], int[], int *, Analise *);

void insereRegistro(TipoHeap *, const char *[], int[], int *, TipoChave, Analise *);

#endif