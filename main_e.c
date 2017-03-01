#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "grafo_otimo.h"

int main(int argc, char** argv) {
    
    FILE *arqEntrada = AbreArquivo(argv[1], "r");
    FILE *arqSaida   = AbreArquivo(argv[2], "w");
    FILE *arqCombinacoes = AbreArquivo("combinacoes.txt", "w+");
    
    int NumInstancias = 0; // Numero de instancias para o qual o programa será executado    
    TipoGrafoO GrafoO;     // Grafo que será trabalhado
    
    /*
     * Le do arquivo o numero de instancias e passa para a proxima linha
     */
    fscanf(arqEntrada, "%d", &NumInstancias);
    PassaParaProximaLinha(arqEntrada);
        
    /*
     * Percorre o arquivo para executar todas as instancias
     */
    while(NumInstancias-- > 0) {
        /*
         * Seta os parametros e faz as inicializacoes necessarias para o grafo
         */
        SetaParametrosO(arqEntrada, &GrafoO);
        
        /*
         * Cria uma matriz de adjacencia para o grafo
         */
        GrafoO.mAdj = CriaMatrizAdjQuadrada(GrafoO.fim);
        
        /*
         * Cria um vetor do tamanho do número de vértices + 1.
         * Esse vetor será usado para verificar o caminho ótimo.
         */
        GrafoO.vetorVertices = CriaVetorVertices(GrafoO.numAmigos + 1);
             
        
        /*
         * Enquanto nao terminar de ler todos os amigos(vertices) do grafo em questao
         */
        int numAmigos = GrafoO.numAmigos;
        while(numAmigos-- > 0) {
            SalvaAmizadesO(arqEntrada, &GrafoO);
        }
        
        /*
         * Salva todas as combinações possíveis de um conjunto de (1, 2 ... Grafo.numAmigos + 1) em um arquivo
         */
        int i,j;
        for(i = 1; i < (1 << GrafoO.numAmigos); i++) {
            for(j = 0; j < GrafoO.numAmigos; j++) {
                if ((1 << j) & i) {
                    fprintf(arqCombinacoes, "%d ", j + 1);
                }
            }
            fprintf(arqCombinacoes, "\n");
        }
        
        /*
         * Volta o cursor do arquivo de combinações para o começo, para fazer a leitura
         */
        fseek(arqCombinacoes, 0, SEEK_SET);

        int combinacoes_possiveis = 2;
        int comb_aux = GrafoO.numAmigos;
        int minimo = 777777777;
        
        /*
         * Descobre quantas combinacoes de conjuntos sao possiveis realizando-se a seguinte conta:
         * 2 ^ n, onde n representa o numero de amigos
         */
        while(comb_aux -- > 1)
            combinacoes_possiveis *= 2;
        
        /*
         * Realiza n combinacoes_possiveis, buscando o menor numero de vertices que conectam todos os vertices do grafo.
         */
        while(combinacoes_possiveis -- > 1)
            DescobreMenorCobertura(arqCombinacoes, &GrafoO, &minimo);
        
        /*
         * Desaloca tudo o que foi alocado para GrafoO
         */
        LiberaGrafoO(&GrafoO);
        
        //printf("Ótima = %d\n", minimo);                
        //printf("___________________________________\n\n");
        
        /*
         * Fecha o arquivo de combinações, se for usa-lo novamente ele vai ser reaberto no if de baixo
         */
        FechaArquivo(arqCombinacoes);
        
        /*
         * Imprime no arquivo de saida, conforme descrito na especificacao do trabalho
         */
        fprintf(arqSaida, "%d", minimo);
        if(NumInstancias + 1 > 0) {
            fprintf(arqSaida, "\n");
            if(NumInstancias + 1 > 1) arqCombinacoes = AbreArquivo("combinacoes.txt", "w+");
        }
        
    }
    
    /*
     * Fecha os arquivos de entrada, saida e o de combinacoes possiveis
     */
    FechaArquivo(arqEntrada);
    FechaArquivo(arqSaida);
    
    return (EXIT_SUCCESS);
}

