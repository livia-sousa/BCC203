#include "arvore_bin_externa.h"
#include <stdio.h>

TipoNo criaNovoNo(TipoItem *item) { // Função que cria um novo nó na árvore externa
    
    TipoNo novo;
    novo.item = *item;
    novo.esq = -1; // Inicialmente não possui nenhum filho
    novo.dir = -1;
    return novo;

}

int insercao(FILE *arquivo, TipoItem *item, int pos, Analise *analise) { // Função que realiza inserção de dados na árvore externa a partir de um arquivo desordenado
    
    if (pos == 0) { // Caso a árvore esteja vazia
        TipoNo no;
        no = criaNovoNo(item);
        fseek(arquivo, 0, SEEK_SET); // Aponta para o início do arquivo
        fwrite(&no, sizeof(TipoNo), 1, arquivo); // Realiza inserção no início do arquivo
        atualizaTransferencias_antes(analise, 1); 
        return 1;

    } else {
        TipoNo no;
        TipoNo raiz;
        long desloc;
        int posNoPai = 0;
        no = criaNovoNo(item); // Cria o novo nó a ser inserido

        fseek(arquivo, 0, SEEK_SET); // Retorna para o ponteiro para início do arquivo
        fread(&raiz, sizeof(TipoNo), 1, arquivo); // Lê a raiz
        atualizaTransferencias_antes(analise, 1); // // Transf ++

        while (1) { 
        // Procurar o item pai
        atualizaComparacoes_antes(analise, 1); // Comp + 1

        if (item->chave < raiz.item.chave) { // Insere à esquerda

            if (raiz.esq != -1) { //O nó contem filho a esquerda
                posNoPai = raiz.esq;
                desloc = raiz.esq * sizeof(TipoNo);

                fseek(arquivo, desloc, SEEK_SET); // Desaloca o ponteiro do arquivo para o filho a esquerda
                fread(&raiz, sizeof(TipoNo), 1, arquivo); // Lê o nó a esquerda para retornar o loop
                atualizaTransferencias_antes(analise, 1);

            } else {
                raiz.esq = pos;
                desloc = posNoPai * sizeof(TipoNo);
                fseek(arquivo, desloc, SEEK_SET); // Volta para a posicao do item pai
                fwrite(&raiz, sizeof(TipoNo), 1, arquivo); // Reescreve a linha do item pai
                atualizaTransferencias_antes(analise, 1);

                desloc = pos * sizeof(TipoNo);
                fseek(arquivo, desloc, SEEK_SET);
                fwrite(&no, sizeof(TipoNo), 1, arquivo); // Registra o nó no arquivo
                atualizaTransferencias_antes(analise, 1);
                return 1;
            }

        } else if (item->chave > raiz.item.chave) { //Insere à direita sem considerar itens iguais
            atualizaComparacoes_antes(analise, 1);

            if (raiz.dir != -1) { //O nó contem filho a direita
                posNoPai = raiz.dir;
                desloc = raiz.dir * sizeof(TipoNo);
                fseek(arquivo, desloc, SEEK_SET); // Desaloca o ponteiro do arquivo para o filho a direita
                fread(&raiz, sizeof(TipoNo), 1, arquivo); // Lê o nó a direita para retornar o loop
                atualizaTransferencias_antes(analise, 1);

            } else {
                atualizaComparacoes_antes(analise, 1); 
                raiz.dir = pos;
                desloc = posNoPai * sizeof(TipoNo);
                fseek(arquivo, desloc, SEEK_SET); // Volta para a posicao do item pai
                fwrite(&raiz, sizeof(TipoNo), 1, arquivo); // Reescreve a linha do item pai
                atualizaTransferencias_antes(analise, 1);

                desloc = pos * sizeof(TipoNo);
                fseek(arquivo, desloc, SEEK_SET);
                fwrite(&no, sizeof(TipoNo), 1, arquivo); //Registra o nó no arquivo
                atualizaTransferencias_antes(analise, 1);
                return 1;
            }
        } else { // Itens iguais
            return 0;
        }
        }
    }
    return 0;
}

int insercaoOrdenada(FILE *arquivo, TipoItem *item, int pos, Analise *analise) { // Função que realiza inserção de dados ordenados na árvore externa
    
    if (pos == 0) { //Caso a árvore esteja vazia
        TipoNo no;
        no = criaNovoNo(item);
        fseek(arquivo, 0, SEEK_SET);
        fwrite(&no, sizeof(TipoNo), 1, arquivo); // Insere
        atualizaTransferencias_antes(analise, 1);
        return 1;

    } else {
        TipoNo no;
        TipoNo raiz;
        long desloc;
        int posNoPai = (pos - 1);
        no = criaNovoNo(item); // Cria o novo nó a ser inserido

        desloc = posNoPai * sizeof(TipoNo);
        fseek(arquivo, desloc, SEEK_SET); // Retorna para a linha anterior
        fread(&raiz, sizeof(TipoNo), 1, arquivo); // Lê a raiz
        atualizaTransferencias_antes(analise, 1); // Transf ++

        atualizaComparacoes_antes(analise, 1); // Comp ++

        if (item->chave < raiz.item.chave && raiz.esq == -1) { // Insere à esquerda, não tem filho 
            raiz.esq = pos;
            desloc = posNoPai * sizeof(TipoNo);
            fseek(arquivo, desloc, SEEK_SET);            // Volta para a posicao do item pai
            fwrite(&raiz, sizeof(TipoNo), 1, arquivo); // Reescreve a linha do item pai
            atualizaTransferencias_antes(analise, 1);

            desloc = pos * sizeof(TipoNo);
            fseek(arquivo, desloc, SEEK_SET);
            fwrite(&no, sizeof(TipoNo), 1, arquivo); // Registra o nó no arquivo
            atualizaTransferencias_antes(analise, 1);
            return 1;

        } else if (item->chave > raiz.item.chave && raiz.dir == -1) { // Insere à direita, não tem filho, não consisera itens iguais
            atualizaComparacoes_antes(analise, 1);

            raiz.dir = pos;
            desloc = posNoPai * sizeof(TipoNo);
            fseek(arquivo, desloc, SEEK_SET); // Volta para a posicao do item pai
            fwrite(&raiz, sizeof(TipoNo), 1, arquivo); // Reescreve a linha do item pai
            atualizaTransferencias_antes(analise, 1);

            desloc = pos * sizeof(TipoNo);
            fseek(arquivo, desloc, SEEK_SET);
            fwrite(&no, sizeof(TipoNo), 1, arquivo); //Registra o nó no arquivo
            atualizaTransferencias_antes(analise, 1);
            return 1;

        } else { // Itens iguais
            atualizaComparacoes_antes(analise, 1);
            return 0;
        }
    }

    return 0;
}

int pesquisa(FILE *arquivo, TipoItem *itemPesq, Analise *analise) { // Função que realiza a busca no arquivo da árvore 
    
    TipoNo no;
    if ( !fread(&no, sizeof(TipoNo), 1, arquivo) ) {
        return 0;
    }

    long int desloc;
    int filhoEsq = 1, filhoDir = 1;

    while (1) {
        atualizaComparacoes_depois(analise, 1);
        if (itemPesq->chave < no.item.chave && filhoEsq != -1) {
            desloc = no.esq * sizeof(TipoNo);
            fseek(arquivo, desloc, SEEK_SET);
            fread(&no, sizeof(TipoNo), 1, arquivo); // Lê o filho a esquerda
            filhoEsq = no.esq;
            filhoDir = no.dir;
            atualizaTransferencias_depois(analise, 1);

        } else if (itemPesq->chave > no.item.chave && filhoDir != -1) {
            atualizaComparacoes_depois(analise, 1);
            desloc = no.dir * sizeof(TipoNo);
            fseek(arquivo, desloc, SEEK_SET);
            fread(&no, sizeof(TipoNo), 1, arquivo); // Lê o filho a direita
            filhoEsq = no.esq;
            filhoDir = no.dir;
            atualizaTransferencias_depois(analise, 1);

        } else if (itemPesq->chave == no.item.chave) { // Analisando folhas
            atualizaComparacoes_depois(analise, 1);
            *itemPesq = no.item;
            return 1;

        } else {
            atualizaComparacoes_depois(analise, 1);
            return 0;
        } 
    }
}

int arvoreBinariaExterna(TipoItem *itemP, Analise *analise, int situacao, int quantidade) { // Função que cria a árvore no arquivo
    
    TipoItem *item = criaRegistro(quantidade); // Cria o Dado
    FILE *arv = fopen("data_arv.bin", "w+b"); // Cria arquivo para leitura e escrita
    FILE *arq = fopen("data.bin", "rb"); // Abre o arquivo para leitura
    if (arv == NULL || arq == NULL) {
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    //Cria a árvore no aquivo
    int cont = 0;
    int inseriu;

    iniciaAnalise(analise); // Inicializa com 0
    iniciaContagemTempo(analise);

    if (situacao == 3) { // Caso os dados estejam aleatórios
        atualizaTransferencias_antes(analise, 1);
        while ( fread(item, sizeof(TipoItem), quantidade, arq) ) { //Pega n itens do arquivo
            atualizaTransferencias_antes(analise, 1);
            for (int i = 0; i < quantidade; i++) { //Percorre o array de n itens para inserir na arvore
                inseriu = insercao(arv, &item[i], cont, analise);
                if (!inseriu){
                    cont--; // Não foi possivel inserir, a posição no arv não fica vazia
                }
                cont++;
            }
        }
    }
    else { // Caso os dados estejam ordenados de forma crescente ou decrescente
        atualizaTransferencias_antes(analise, 1);
        while ( fread(item, sizeof(TipoItem), quantidade, arq) ) {  //Pega n itens do arquivo
            atualizaTransferencias_antes(analise, 1);
            for (int i = 0; i < quantidade; i++) {
                inseriu = insercaoOrdenada(arv, &item[i], cont, analise);
                if (!inseriu){
                    cont--; // Não foi possivel inserir, a posição no arv não fica vazia
                }
                cont++;
            }
        }
    }

    fclose(arv);
    fclose(arq);
    finalizaContagemTempo(analise);
    atualizaTempo_antes(analise); // Final - Inicial

    iniciaContagemTempo(analise);
    arv = fopen("data_arv.bin", "rb");
    int rtr = pesquisa(arv, itemP, analise);
    fclose(arv);
    finalizaContagemTempo(analise);
    atualizaTempo_depois(analise);
    return rtr;
}