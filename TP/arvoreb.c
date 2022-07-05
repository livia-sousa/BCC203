#include "arvoreb.h"

//inicializando a arvore, a raiz recebe valor nulo 
void Inicializa (TipoApontador Arvore){
    Arvore = NULL;
}


//pesquisa por uma chave
//se encontra, retorna True = 1, caso contrario retorna False = 0
int pesquisaB(TipoChave *x, TipoApontador Ap, Analise *analise){
    
    long i =1;

    if(Ap == NULL){
        printf("Tipo registro nao esta presente na arvore\n");
        return False;
    }

    //verifica qual posicao o item esta na pagina 
    while (i < Ap->n && x->chave > Ap->r[i-1].chave.chave){
         atualizaComparacoes_depois(analise, 1);
         i++;
    }
       
    //verifica se o item eh o procurado
    if (x->chave == Ap->r[i-1].chave.chave){
        atualizaComparacoes_depois(analise, 1);
        *x = Ap->r[i-1].chave;
        return True;
    }

    atualizaComparacoes_depois(analise,1);
    //verifica qual caminho seguir dentro da arvore
    if (x->chave < Ap->r[i-1].chave.chave){
        return pesquisaB(x, Ap->p[i-1], analise);
    }
    else{
        return pesquisaB(x, Ap->p[i], analise);
    } 

    return False

}



// -> insercao na arvore B

//funcao que insere UM item na pagina
void InsereNaPagina(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir){
    short NaoAchouPosicao;
    int k;

    k = Ap->n;
    NaoAchouPosicao = k > 0; //verifica se a página é vazia. 
    //se a pagina eh vazia, insere nela

    //verifica em qual lugar da pagina colocar o registro
    while(NaoAchouPosicao){
        //verifica se o registro possui chave maior que o ultimo
        //se sim, sai do laco e adiciona na posicao seguinte a ultima
        if (Reg.chave.chave >= Ap->r[k-1].chave.chave){
            NaoAchouPosicao = 0;
            break;
        }

        //move o registros para posição da frente para liberar espaço 
        //para o novo registro ser inserido de forma ordenada
        Ap->r[k] = Ap->r[k-1];
        Ap->p[k+1] = Ap->p[k];
        k--;

        if (k<1)
            NaoAchouPosicao = 0; //False = 0
    }

    Ap->r[k] = Reg;
    Ap->p[k + 1] = ApDir;
    Ap->n++;

}


void Ins(TipoRegistro Reg, TipoApontador Ap, short *Cresceu, TipoRegistro *RegRetorno,  TipoApontador *ApRetorno, Analise *analise){
    
    long i=1;
    long j;
    TipoApontador ApTemp;


    //verifica se a pagina eh nula
    //ou chegou na pagina folha
    //ou a arvore e vazia
    if(Ap == NULL){
        //cresceu indica se a pagina sera dividida ou não 
        *Cresceu = 1; //true=1
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;
        return;
    }

    //atualizaComparacoes_antes(analise,1);
    //verifica em qual posicao a chave desejada esta na pagina
    while (i < Ap->n && Reg.chave.chave > Ap->r[i-1].chave.chave){
        i++;
        atualizaComparacoes_antes(analise,1);
    }

    //verifica se a chave foi encontrada
    if (Reg.chave.chave == Ap->r[i-1].chave.chave){
        *Cresceu = 0; // false = 0;
        atualizaComparacoes_antes(analise,1);
        return;
    }

    //Verificação para saber qual dos filhos da página deve ser analisado, esq ou dir.
    if (Reg.chave.chave < Ap->r[i-1].chave.chave){
        i--;
        atualizaComparacoes_antes(analise, 1);
    }

    Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno, analise);

    //se cresceu é verdadeiro, o procedimento nao finaliza
    if (!*Cresceu)
        return;
    
    //insere na pagina caso haja espaco 
    if (Ap->n < MM){
        //Pagina tem espaco
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
        *Cresceu = 0;
        return;
    }

    //overflow
    //pagina tem que ser dividida
    ApTemp = (TipoApontador)malloc(sizeof(TipoPagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;


    //Verifica se o item será inserido na primeira metade da página; 
    //Caso for, insere na nova pagina temporaria o ultimo item da pagina atual 
    //e libera 1 espaço para inserção do item na pagina
  

    if(i< M+1){
        InsereNaPagina(ApTemp, Ap->r[MM-1], Ap->p[MM]);
        Ap->n--;
        InsereNaPagina(Ap,*RegRetorno, *ApRetorno);
    }

    //Caso esteja na segunda metade da pagina, ele é inserido direto na nova pagina temporaria;
    else InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);

    //Insere toda o resto da segunda metadee na pagina temporaria
    for (j=M+2; j<= MM; j++){
        InsereNaPagina(ApTemp, Ap->r[j-1], Ap->p[j]);
    }

    //atualiza a quantidade de itens que ficaram na pagina
    //depois de toda as movimentacoes
    Ap->n = M;
    ApTemp->p[0] = Ap->p[M+1];
    *RegRetorno = Ap->r[M];
    *ApRetorno = ApTemp;
}

//funcao principal de inserçao
void Insere(TipoRegistro *Reg, TipoApontador *Ap, Analise *analise){
    short Cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;

    Ins(*Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno, analise);

    if (Cresceu){
        //arvore cresce na altura pela raiz
        //criar nova pagina raiz 
        ApTemp = (TipoPagina*)malloc(sizeof(TipoPagina));
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap;
        *Ap = ApTemp;
    }
}


int arvoreB(TipoChave *ch, Analise *analise, int quantidade){

    iniciaAnalise(analise);
    TipoApontador arv = NULL;
    TipoRegistro itens[quantidade];

    FILE *arq = fopen("data.bin", "rb");

    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    iniciaContagemTempo(analise);
    
    while (fread(&itens, sizeof(TipoRegistro), quantidade, arq)) 
    {

        for (int i = 0; i < quantidade; i++){
            //insere cada um dos dados na árvore em memória principal
            Insere(&itens[i], &arv, analise); 
            atualizaTransferencias_antes(analise, 1);
        }
    }
    fclose(arq);

    finalizaContagemTempo(analise);
    atualizaTempo_antes(analise);
    iniciaContagemTempo(analise);

    //Pesquisa a chave dentro da árvore lida a partir do arquivo;
    if (pesquisaB(ch, arv, analise)){
        finalizaContagemTempo(analise);
        atualizaTempo_depois(analise);
        liberarArvore(arv);
        return 1;
    }
    else
    {
        finalizaContagemTempo(analise);
        atualizaTempo_depois(analise);
        liberarArvore(arv);
        return 0;
    }
}

//caminhamento para impressao
void Imprime(TipoApontador arvore){
    int i = 0;

    if (arvore == NULL) return;

    while (i <= arvore->n) {
        Imprime(arvore->p[i]);

        if (i != arvore->n)
            printf(" %d ", arvore->r[i].chave.chave);
        i++;
    }
}

//funcao que desaloca a memoria alocada para a arvore
int liberarArvore(TipoApontador ap){
  int i = 0;
  if (ap == NULL)
    return 0;

  while (i <= ap->n)
  {
    liberarArvore(ap->p[i]);
    i++;
  }
  free(ap);
  
  return 1;
}