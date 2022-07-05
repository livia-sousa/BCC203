#ifndef ARVOREB_H

#include <stdio.h>
#include <stdlib.h>

#include "registro.h"
#include "analises.h"

typedef int bool;
#define True 1;
#define False 0;

#define ARVOREB_H
#define MM (2*M)
#define M 2

typedef Registro TipoChave;

typedef struct TipoRegistro{
    TipoChave chave;
    //mais o que tiver pra por
} TipoRegistro;

typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina{
    
    short n; 
    TipoRegistro r[MM];
    TipoApontador p[MM+1];
} TipoPagina;

void Inicializa(TipoApontador Arvore);

void imprime(TipoApontador arv);

int pesquisaB(TipoChave *x, TipoApontador ap, Analise *analise);

void insereArvB(TipoRegistro *reg, TipoApontador *ap, Analise *analise);

void ins(TipoRegistro reg, TipoApontador ap, short *cresceu, TipoRegistro *regRetorno, TipoApontador *apRetorno, Analise *analise);

void insereNaPagina(TipoApontador ap, TipoRegistro reg, TipoApontador apDir);

int arvoreB(TipoChave *ch, Analise *analise, int quantidade);

int liberarArvore(TipoApontador ap);

#endif