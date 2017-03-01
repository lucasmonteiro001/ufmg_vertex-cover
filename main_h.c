#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "grafo_heuristica.h"

int main(int argc, char** argv) {
    
    /*
     * Abertura dos arquivos de entrada e saida
     */
    FILE *arqEntrada = AbreArquivo(argv[1], "r");
    FILE *arqSaida   = AbreArquivo(argv[2], "w");
    
    int NumInstancias = 0; // Numero de instancias para o qual o programa será executado    
    TipoGrafo GrafoH;      // Grafo que será trabalhado
    
    /*
     * Le do arquivo o numero de instancias que o programa sera executado e passa para a proxima linha
     */
    fscanf(arqEntrada, "%d", &NumInstancias);
    PassaParaProximaLinha(arqEntrada);
    
    /*
     * Percorre todo o arquivo, executando quantas instancias existam
     */
    while(NumInstancias-- > 0) {
        /*
         * Seta os parametros e faz as inicializacoes necessarias para o grafo
         */
        SetaParametros(arqEntrada, &GrafoH);
        
        /*
         * Le todos os vertices do grafo e realiza suas conexoes
         */
        int numAmigos = GrafoH.numAmigos;
        while(numAmigos-- > 0) {
            SalvaAmizades(arqEntrada, &GrafoH);
        }
        
        /*
         * Heuristica() retorna ate 2x o numero minimo de vertices necessarios para que se realize a Cobertura de Vertices
         */
        int minimo = Heuristica(&GrafoH);
        
        /*
         * Imprime no arquivo de saida, conforme descrito na especificacao do trabalho
         */
        fprintf(arqSaida, "%d", minimo);
        if(NumInstancias + 1 > 0) fprintf(arqSaida, "\n");
                
    }
   
    /*
     * Fecha os arquivos de entrada e saida
     */
    FechaArquivo(arqEntrada);
    FechaArquivo(arqSaida);
    
    return (EXIT_SUCCESS);
}

