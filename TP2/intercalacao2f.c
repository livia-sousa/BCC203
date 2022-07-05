#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "intercalacao2f.h"

enum tipoFita {
    Entrada,
    Saida
};

typedef enum tipoFita Fita;

const char *intercalacaoSPS(char *nomearquivo, int n, Analise *analisePrimeiraFase, Analise *analiseSegundaFase) {
    printf("entra aqui");
    TipoHeap heap;
    heap_constroiHeap(&heap, N);

    const char *fitasEntrada[20] = { // Arquivos fitas de entrada
        "fitas/in/fita01.txt",
        "fitas/in/fita02.txt",
        "fitas/in/fita03.txt",
        "fitas/in/fita04.txt",
        "fitas/in/fita05.txt",
        "fitas/in/fita06.txt",
        "fitas/in/fita07.txt",
        "fitas/in/fita08.txt",
        "fitas/in/fita09.txt",
        "fitas/in/fita10.txt",
        "fitas/in/fita11.txt",
        "fitas/in/fita12.txt",
        "fitas/in/fita13.txt",
        "fitas/in/fita14.txt",
        "fitas/in/fita15.txt",
        "fitas/in/fita16.txt",
        "fitas/in/fita17.txt",
        "fitas/in/fita18.txt",
        "fitas/in/fita19.txt",
        "fitas/in/fita20.txt",
    };

    const char *fitasSaida[20] = { // Arquivos fitas de saída
        "fitas/out/fita21.txt",
        "fitas/out/fita22.txt",
        "fitas/out/fita23.txt",
        "fitas/out/fita24.txt",
        "fitas/out/fita25.txt",
        "fitas/out/fita26.txt",
        "fitas/out/fita27.txt",
        "fitas/out/fita28.txt",
        "fitas/out/fita29.txt",
        "fitas/out/fita30.txt",
        "fitas/out/fita31.txt",
        "fitas/out/fita32.txt",
        "fitas/out/fita33.txt",
        "fitas/out/fita34.txt",
        "fitas/out/fita35.txt",
        "fitas/out/fita36.txt",
        "fitas/out/fita37.txt",
        "fitas/out/fita38.txt",
        "fitas/out/fita39.txt",
        "fitas/out/fita40.txt",
    };

    FILE *arq;

    for (int i = 0; i < N; i++) { // Cria as fitas limpas de entrada
        arq = fopen(fitasEntrada[i], "wt");
        fclose(arq);
    }

    for (int i = 0; i < N; i++) { // Cria as fitas limpas de saída
        arq = fopen(fitasSaida[i], "wt");
        fclose(arq);
    }

    // Cada posição do array representa quantos blocos cada fita têm
    int nBlocos[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int qtdeBlocos = 0; // Recebe a soma da quantidade total de blocos

    // Fase 1
    iniciaAnalise(analisePrimeiraFase);
    iniciaContagemTempo(analisePrimeiraFase);

    // Gera os primeiros blocos ordenados
    geracaoBlocosOrdenados(nomearquivo, &heap, fitasEntrada, nBlocos, n, analisePrimeiraFase);

    finalizaContagemTempo(analisePrimeiraFase);
    atualizaTempo(analisePrimeiraFase);

    for (int i = 0; i < N; i++) { // Soma os blocos em cada fita para obter o total de blocos e zera o array nBlocos
        qtdeBlocos += nBlocos[i];
        nBlocos[i] = 0;
    }

    FILE *arqs[20];
    int qualFita = 1;
    Fita intercala = Entrada;
    printf("chega aqui");

    // Fase 2
    iniciaAnalise(analiseSegundaFase);
    iniciaContagemTempo(analiseSegundaFase);
    while (qtdeBlocos > 1) {
        qtdeBlocos = 0;
        if (intercala == Entrada) { // Ler da entrada e escrever na saída

            for (int i = 0; i < N; i++) { // Limpando fitasSaida
                arq = fopen(fitasSaida[i], "wt");
                fclose(arq);
            }

            for (int i = 0; i < N; i++){ // Abre todos os arquivos de entrada para a leitura
                arqs[i] = fopen(fitasEntrada[i], "r");
            }
            qualFita = 0;

            intercalacao(&heap, arqs, fitasSaida, nBlocos, &qualFita, analiseSegundaFase);

            intercala = Saida;

        } else if (intercala == Saida) { // Ler da saída e escrever na entrada

            for (int i = 0; i < N; i++) { // Limpando fitasEntrada
                arq = fopen(fitasEntrada[i], "wt");
                fclose(arq);
            }

            for (int i = 0; i < N; i++) { // Abre todos os arquivos de saída os arquivos para a leitura
                arqs[i] = fopen(fitasSaida[i], "r");
            }
            qualFita = 0;

            intercalacao(&heap, arqs, fitasEntrada, nBlocos, &qualFita, analiseSegundaFase);

            intercala = Entrada;
        }

        for (int i = 0; i < N; i++) { // Fecha todos os arquivos abertos
            fclose(arqs[i]);
        }
        
        for (int i = 0; i < N; i++) { // Soma os blocos em cada fita para obter o total de blocos e zera o array nBlocos
          qtdeBlocos += nBlocos[i];
          nBlocos[i] = 0;
        }

    }

    finalizaContagemTempo(analiseSegundaFase);
    atualizaTempo(analiseSegundaFase);

    if (intercala == Entrada) { // Ler da entrada e escrever na saída
        for (int i = 0; i < N; i++) { // Limpando fitasSaida
            arq = fopen(fitasSaida[i], "wt");
            fclose(arq);
        }
    }

    heap_destroyHeap(&heap); // Libera a memória do heap

    //Retorna o nome da fita em que o arquivo ordenado está salvo
    if (intercala == Entrada){
        return fitasEntrada[qualFita - 1];
    } else {
        return fitasSaida[qualFita - 1];
    }

}

void geracaoBlocosOrdenados(char *nomearquivo, TipoHeap *heap, const char *fitasEntrada[], int nBlocos[], int n, Analise *analise) {
    
    Registro dado;
    int indexFita = 0;
    FILE *in = fopen(nomearquivo, "r");
    if (in == NULL) {
        printf("⚠️ - Erro na abertura do arquivo de entrada!\n");
        exit(1);
    }

    while (n > 0 && fscanf(in, "%s %lf %2[A-Z] %49[A-Z Ã Â À Á Õ Ó Ô Ç Ì Ê É ' -] %29[A-Z Ã Â À Á Õ Ó Ô Ç Ì Ê É ' -]\n", dado.inscricao, &dado.nota, dado.estado, dado.cidade, dado.curso) != EOF) {
        atualizaTransferencias(analise, 1);
        insereRegistro(heap, fitasEntrada, nBlocos, &indexFita, dado, analise);
        n -= 1;
    }
    fclose(in);

    if (heap_hasFullMarked(heap)) { // Desmarca os elementos do heap caso todos estejam marcados
        indexFita = indexFita != (N - 1) ? indexFita + 1 : 0; // Altera a fita para a escrita
        heap_reset(heap);
        nBlocos[indexFita] += 1; //Atualização da quantidade de blocos da fita
    }

    FILE *arq = fopen(fitasEntrada[indexFita], "a+");

    while (heap->tam > 0) { // Remove os elementos restantes no heap e escreve no arquivo

        TipoItem tmp = heap_remove(heap, analise);
        atualizaTransferencias(analise, 1);
        fprintf(arq, "%s %lf %s %s %s\n", tmp.chave.inscricao, tmp.chave.nota, tmp.chave.estado, tmp.chave.cidade, tmp.chave.curso);

        if (heap->nMarked == heap->tam && heap->tam > 0) { // Verifica se tudo está marcado
            atualizaTransferencias(analise, 1);
            fprintf(arq, "%c\n", '\0'); // Indica o final de um bloco
            fclose(arq);
            nBlocos[indexFita] += 1;
            indexFita = indexFita != (N - 1) ? indexFita + 1 : 0;
            arq = fopen(fitasEntrada[indexFita], "a+");
            heap_reset(heap); // Reseta todos os dados marcados para não marcados
        }

    }

    atualizaTransferencias(analise, 1);
    fprintf(arq, "%c\n", '\0'); // Fim do bloco
    fclose(arq);

}

void intercalacao(TipoHeap *heap, FILE *fitaRead[], const char *fitaWrite[], int nBlocos[], int *indexFita, Analise *analise) {
    
    FILE *fita;
    FILE *fitaPai;
    Registro dado;
    TipoItem min;
    int totalBlocosFinalizados = 0;
    int blocoEFinalizado[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int fitasAtivas[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int nFitasAtivas = 0, i = 0, j = 0;

    // Preenchimento do heap com os dados do arquivo
    while (!heap_isFull(heap)) { // Preenche o heap intercalando as fitas

        if (fscanf(fitaRead[i], "%s", dado.inscricao) != EOF) {
            atualizaTransferencias(analise, 1);

            if (strcmp(dado.inscricao, "\0")) { // Se não for o fim do bloco
                atualizaTransferencias(analise, 1);
                fscanf(fitaRead[i], "%lf %2[A-Z a-z] %49[A-Z Ã Â À Á Õ Ó Ô Ç Ì Ê É ' -] %29[A-Z Ã Â À Á Õ Ó Ô Ç Ì Ê É ' -]", &dado.nota, dado.estado, dado.cidade, dado.curso);
                heap_addReg(heap, dado, false, i + 1, analise);
                fitasAtivas[i] = 1;
                j += fitasAtivas[i];
            }

        }

        if (i == (N - 1) && !heap_isFull(heap) && j == 0) { // É verdadeiro quando não há dados para serem lidos
            break;
        }

        if (i < (N - 1)) { // Incrementa para a proxima fita
            i++;

        } else { // Reseta o para o inicio das fitas 
            i = 0;
            j = 0;
        }

    }

    for (int i = 0; i < N; i++) { // Conta a quantidade de fitas ativas ( que estão sendo lidas )
        nFitasAtivas += fitasAtivas[i];
    }

    while (totalBlocosFinalizados < nFitasAtivas || !heap_isEmpty(heap)) {
        min = heap_minValue(heap);

        if (blocoEFinalizado[min.fitaIndicator - 1]) { // Se na fita não há mais itens no bloco
            TipoItem tmp = heap_remove(heap, analise); // Remove o item do heap
            fita = fopen(fitaWrite[*indexFita], "a+");
            atualizaTransferencias(analise, 1);
            fprintf(fita, "%s %lf %s %s %s\n", tmp.chave.inscricao, tmp.chave.nota, tmp.chave.estado, tmp.chave.cidade, tmp.chave.curso);
            fclose(fita);

        } else { // Se há mais dados da mesma fita e do mesmo bloco para adicionar no heap
            fitaPai = fitaRead[min.fitaIndicator - 1];
            atualizaTransferencias(analise, 1);
            fscanf(fitaPai, "%s ", dado.inscricao);

            if (!strcmp(dado.inscricao, "\0")) { // Se for o final de um bloco
                totalBlocosFinalizados += 1;
                blocoEFinalizado[min.fitaIndicator - 1] = 1; // Indica que o bloco em n foi finalizado
                TipoItem tmp = heap_remove(heap, analise); // Remove o íltimo item dessa fita do heap
                fita = fopen(fitaWrite[*indexFita], "a+");
                atualizaTransferencias(analise, 1);
                fprintf(fita, "%s %lf %s %s %s\n", tmp.chave.inscricao, tmp.chave.nota, tmp.chave.estado, tmp.chave.cidade, tmp.chave.curso);
                fclose(fita);

            } else { // Se ainda não é o fim do bloco
                atualizaTransferencias(analise, 1);
                fscanf(fitaPai, "%lf %2[A-Z a-z] %49[A-Z Ã Â À Á Õ Ó Ô Ç Ì Ê É ' -] %29[A-Z Ã Â À Á Õ Ó Ô Ç Ì Ê É ' -]", &dado.nota, dado.estado, dado.cidade, dado.curso);
                TipoItem tmp = heap_organize(heap, dado, false, min.fitaIndicator, analise);
                fita = fopen(fitaWrite[*indexFita], "a+");
                atualizaTransferencias(analise, 1);
                fprintf(fita, "%s %lf %s %s %s\n", tmp.chave.inscricao, tmp.chave.nota, tmp.chave.estado, tmp.chave.cidade, tmp.chave.curso);
                fclose(fita);
            }
        }
    }

    if (nFitasAtivas == 0) { // Caso não tenha nenhum bloco para intercalar, termina a função
        return;

    } else if (totalBlocosFinalizados == nFitasAtivas) { // Chamada recursiva para os blocos restantes
        nBlocos[*indexFita] += 1;
        fita = fopen(fitaWrite[*indexFita], "a+"); // Escrita para indicar o fim do bloco
        atualizaTransferencias(analise, 1);
        fprintf(fita, "%c\n", '\0'); // Fim do bloco
        fclose(fita);

        *indexFita = *indexFita != (N - 1) ? *indexFita + 1 : 0; // Incrementa o indicador da fita ou reseta para 0
        intercalacao(heap, fitaRead, fitaWrite, nBlocos, indexFita, analise);
    }
}

void insereRegistro(TipoHeap *heap, const char *fitasEntrada[], int nBlocos[], int *indexFita, TipoChave dado, Analise *analise) {
    
    FILE *arq;

    if (!heap_isFull(heap)) {
        heap_addReg(heap, dado, false, -1, analise);

    } else {

        if (heap_hasFullMarked(heap)) { // Se o heap estiver com todos os itens marcados
            arq = fopen(fitasEntrada[*indexFita], "a+");
            atualizaTransferencias(analise, 1);
            fprintf(arq, "%c\n", '\0'); // Final do bloco
            fclose(arq);
            nBlocos[*indexFita] += 1;
            *indexFita = *indexFita != (N - 1) ? *indexFita + 1 : 0; // Incrementa o indicador da fita ou reseta para 0
            heap_reset(heap); // Altera todos os itens marcados para não marcados
        }
        atualizaComparacoes(analise, 1);

        // Se o dado que está "entrando" no heap for menor que o dado que "saiu", ele deve ser marcado, indicando que ele é maior que os não marcados.
        if (dado.nota < heap_minValue(heap).chave.nota) { // Se o novo valor for menor
            TipoItem tmp = heap_organize(heap, dado, true, -1, analise);
            arq = fopen(fitasEntrada[*indexFita], "a+");
            atualizaTransferencias(analise, 1);
            fprintf(arq, "%s %lf %s %s %s\n", tmp.chave.inscricao, tmp.chave.nota, tmp.chave.estado, tmp.chave.cidade, tmp.chave.curso);
            fclose(arq);

        } else { // Se o novo valor é maior
            TipoItem tmp = heap_organize(heap, dado, false, -1, analise);
            arq = fopen(fitasEntrada[*indexFita], "a+");
            atualizaTransferencias(analise, 1);
            fprintf(arq, "%s %lf %s %s %s\n", tmp.chave.inscricao, tmp.chave.nota, tmp.chave.estado, tmp.chave.cidade, tmp.chave.curso);
            fclose(arq);
        }
    }
}