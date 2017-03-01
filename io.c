#include "io.h"

FILE *AbreArquivo(char *nome_arquivo, char *modo) {
    FILE *arquivo;

    if(!(arquivo = fopen(nome_arquivo, modo))) {
        printf("\nErro ao abrir o arquivo\n");
        exit(0);
    }

    return arquivo;
}

void FechaArquivo(FILE *arquivo) {

    fclose(arquivo);
}

void PassaParaProximaLinha(FILE *arquivo) {
    fseek(arquivo, 1, SEEK_CUR);
}
