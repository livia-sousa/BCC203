#include <string.h>
#include "geradorArq.h"
#include "registro.h"

int geradorArq(int tam, int sit) {
    int i;
    Registro reg;
    FILE *Arq, *Saida;
	
    Saida = fopen ("teste.bin", "w+b");
    if(Saida == NULL) {
        printf("Não foi possivel criar o arquivo.");
        return FALSE;
    }
	
    //Geracao arquivo binario com os dados do PROVAO.txt
    switch(sit) {
        case 1: {
			Arq = fopen("PROVAO_ORDENADO.txt","r");
			if(Arq == NULL) {
				return FALSE;
			}
            for(i = 0; i < tam; i++) {
				fscanf(Arq,"%s %lf %s ", reg.inscricao, &reg.nota, reg.estado);
				fgets(reg.cidade, 50, Arq);
				fscanf(Arq, " %[A-Z a-z]\n", reg.curso);
				fwrite(&reg, sizeof(Registro), 1, Saida);
			}
            break;
        }
        case 2: {
			Arq = fopen("PROVAO_DECRESCENTE.txt","r");
			if(Arq == NULL) {
				return FALSE;
			}
            for(i = 0; i < tam; i++) {
				fscanf(Arq,"%s %lf %s ", reg.inscricao, &reg.nota, reg.estado);
				fgets(reg.cidade, 50, Arq);
				fscanf(Arq," %[A-Z a-z]\n",reg.curso);
				fwrite(&reg, sizeof(Registro), 1, Saida);
			}
            break;
        }
        case 3: {
			Arq = fopen("PROVAO.txt","r");
			if(Arq == NULL) {
				return FALSE;
			}
			for(i = 0; i < tam; i++) {
				fscanf(Arq, "%s %lf %s ", reg.inscricao, &reg.nota, reg.estado);
				fgets(reg.cidade, 50, Arq);
				fscanf(Arq, "  %[A-Z a-z]\n", reg.curso);
				fwrite(&reg, sizeof(Registro), 1, Saida);
			}
            break;
        }
    }
	
    fclose(Saida);
    fclose(Arq);
    return TRUE;
}