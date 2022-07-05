#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "geradorArq.h"
#include "heap.h"
#include "intercalacao2f.h"
#include "quickSortExterno.h"

void printfTXT(char *arquivo, int n);

void convertBinToTxt();

int main(int argc, char *argv[]){

    char nomearquivo[30];
    int metodo;
    int quantidade;
    int situacao;
    char imprime = 0;
    char finalfile[100];

    strcpy(nomearquivo, argv[1]);
    metodo = atoi(argv[2]);
    quantidade = atoi(argv[3]);
    situacao = atoi(argv[4]);

    if (argc == 6 && !strcmp(argv[5], "[-P]")) {
      imprime = 1;
    }

    geradorArq(quantidade, situacao);

    printf("🗂️  Arquivo gerado!\n\n");
    convertBinToTxt();
    FILE *novo, *velho;
    novo = fopen("entrada.txt", "w");
    velho = fopen("provaoFinal.txt", "r");
    if (novo == NULL || velho == NULL){
        printf("Arquivo não pode ser aberto\n");
        exit(1);
    }
    char caracter;
    while((caracter = fgetc(velho)) != EOF ) {
        fprintf(novo, "%c", caracter);
    }
    strcpy(nomearquivo, "entrada.txt");

    // Iniciando análise
    Analise analisePrimeiraFase, analiseSegundaFase, analise;

    // <Método>
    // --> Intercalação balanceada de vários caminhos (2f fitas) utilizando método de ordenação interna apresentado em "Estrutura de Dados I"
    if (metodo == 1) {
        //Método Luiz

    // --> Intercalação balanceada de vários caminhos (2f fitas) utilizando a técnica de seleção por substituição apresentada em "Estrutura de Dados II". 
    } else if (metodo == 2){
        printf("chega aqui");
        strcpy(finalfile, intercalacaoSPS(nomearquivo, quantidade, &analisePrimeiraFase, &analiseSegundaFase));
    
    // --> QuickSort Externo
    } else if (metodo == 3) {
        ordenacaoQuickSortExterno(quantidade, &analise);
        convertBinToTxt();
        strcpy(finalfile, "provaoFinal.txt");
    }

    if (imprime) { // [-P]
        printf("📢 Imprimindo os dados dos alunos a serem ordenados e o resultado da ordenação:\n");
        printf("\n 📁 Arquivo de entrada:\n\n");
        printfTXT(nomearquivo, quantidade);
        printf("\n 📂 Arquivo de saída [Ordenado]:\n\n");
        printfTXT(finalfile, quantidade);
    }

    if (metodo == 1) {
          printf("\n1️⃣ - Intercalação balanceada de vários caminhos com\n");
    } else if (metodo == 2) {
          printf("\n2️⃣ - Intercalação balanceada de vários caminhos ( Seleção por substituição )\n");
    }  else {
          printf("\n3️⃣ - Quicksort externo\n");
    }

    // <Situação>
    if (situacao == 1) { 
        printf("⤴️ - Ordenado ascendentemente pelas notas\n");
    } else if (situacao == 2) {
        printf("⤵️ - Ordenado descendentemente pelas notas\n");
    } else {
        printf("🔀 - Desordenado aleatoriamente pelas notas\n");
    }
    
    if (metodo == 3) {
        printf("Análise QuickSort externo:\n");
        imprimirAnalise(&analise);
    } else {
        printf("Análise geração dos blocos [Fase 1]:\n");
        imprimirAnalise(&analisePrimeiraFase);
        printf("Análise geração dos blocos [Fase 2]:\n");
        imprimirAnalise(&analiseSegundaFase);
    }
    return 0;
}
void printfTXT(char *arquivo, int n) {
    Registro dado;
    FILE *arq = fopen(arquivo, "r");
    while (n > 0 && fscanf(arq, "%s %lf %2[A-Z] %49[A-Z Ã Â À Á Õ Ó Ò Ô Ç Ì Í Ê É ' -] %29[A-Z -A--Z -M Ã Â À Á Õ Ó Ô Ç Ì Í Ê É ' -]\n", dado.inscricao, &dado.nota, dado.estado, dado.cidade, dado.curso) != EOF) {
        printf("%s %lf %s %s %s\n", dado.inscricao, dado.nota, dado.estado, dado.cidade, dado.curso);
        n--;
    }
}

// Função que converte arquivo binário para txt
void convertBinToTxt() {
    TipoChave dado;
    FILE *arqTxt = fopen("provaoFinal.txt", "w");
    FILE *arqBin = fopen("teste.bin", "rb");

    fread(&dado, sizeof(TipoChave), 1, arqBin);

    while (!feof(arqBin)) {
        fprintf(arqTxt, "%s %lf %s %s %s\n", dado.inscricao, dado.nota, dado.estado, dado.cidade, dado.curso);
        fread(&dado, sizeof(TipoChave), 1, arqBin);
    }

    fclose(arqTxt);
    fclose(arqBin);
}