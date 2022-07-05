#include <stdio.h>
#include <stdbool.h>
#include "analises.h"
#include "registro.h"

// Definição das ordens (MM pode ser diferente de MM2)
#define MESTRELA 2
#define MMESTRELA 2*MESTRELA
#define MM2 5 

typedef Registro TipoChaveBEstr;

//Criando TipoRegistroBEstr para guardar as chaves
typedef struct TipoRegistroBEstr{
    TipoChaveBEstr chave;
} TipoRegistroBEstr;

//Tipo que só pode receber 2 valores: Interna/Externa 
typedef enum{Interna, Externa} TipoIntExt;

typedef struct TipoPaginaBEstr *TipoApontadorBEstr;

//Tipo pagina contém 2 campos, Pt e UU (U0-> INTERNA ou U1-> EXTERNA)
typedef struct TipoPaginaBEstr{
    TipoIntExt pt;  //Diz se a página é interna ou externa 
    union{
        struct {
            int ni; 
            TipoChaveBEstr ri[MMESTRELA];
            TipoApontadorBEstr pi[MMESTRELA + 1];
        } U0;  // Página interna
        struct{ 
            int ne;
            TipoRegistroBEstr re[MM2];
        } U1; // Página externa
    }UU; //Campo do tipo união
}TipoPaginaBEstr;

//Prototipos
void InicializaBEstr(TipoApontadorBEstr *ap);
int liberarArvoreBEstr(TipoApontadorBEstr ap);
bool arvoreBEstrela(TipoChaveBEstr *chave, Analise *analise, int quantidade);
void ImprimeBEstr(TipoApontadorBEstr ap);
void InsereBEstr(TipoRegistroBEstr reg, TipoApontadorBEstr *ap, Analise *analise);
void InsereNaPaginaBEstr(TipoApontadorBEstr ap, TipoRegistroBEstr reg, TipoApontadorBEstr apDir, Analise *analise);
void InsBEstr(TipoRegistroBEstr reg, TipoApontadorBEstr ap, short *cresceu, TipoRegistroBEstr *regRetorno, TipoApontadorBEstr *apRetorno, Analise *analise);
bool PesquisaBEstr(TipoChaveBEstr *x, TipoApontadorBEstr *ap, Analise *analise);
