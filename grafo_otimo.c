#include "grafo_otimo.h"

void SetaParametrosO(FILE *arquivo, TipoGrafoO *Grafo) {
    /*
     * Armazena a quantidade de amigos(arestas) que o grafo(Zambis) possui e passa para 
     * a proxima linha
     */
    fscanf(arquivo, "%d", &Grafo->numAmigos);
    PassaParaProximaLinha(arquivo);
    
    /*
     * Inicializa os parametros do grafo
     */
    Grafo->inicio = 1;
    Grafo->fim    = Grafo->numAmigos + 1;
}

TipoMatrizAdj CriaMatrizAdjQuadrada(int dimensao) {
    TipoMatrizAdj matriz;
    
    matriz = (TipoMatrizAdj)malloc(dimensao * sizeof(short *)); // Aloca as linhas da matriz
    
    int i = 0, j = 0;
    
    /*
     * Aloca as colunas da matriz
     */
    for(i = 0; i < dimensao; i++) {
        matriz[i] = (short *)malloc(dimensao * sizeof(short));
    }
    
    /*
     * Inicializa todas as posições da matriz com 0
     */
    for(i = 0; i < dimensao; i++) {
        for(j = 0; j < dimensao; j++) {
            matriz[i][j] = 0;
        }
    }
    
    return matriz;
}

void ConectaVertices(int v1, int v2, TipoGrafoO *Grafo) {
    /*
     * Dado que a matriz de adjacencia de um grafo e simetrica, se v1 liga v2, logo v2 liga v1, e feita essa ligacao 
     * com os dois comandos abaixo
     */
    Grafo->mAdj[v1][v2] = 1;
    Grafo->mAdj[v2][v1] = 1;
}

void SalvaAmizadesO(FILE *arquivo, TipoGrafoO *Grafo) {
    int v1;        // Primeiro vertice que sera lido em cada linha
    char str[256]; // Cria uma string para armazenar todos os vertices que estarao conectados ao vertice1
    
    /*
     * Armazena o primeiro vertice
     */
    fscanf(arquivo, "%d", &v1);
    
    /*
     * Armazena os vertices adjacentes ao vertice1
     */
    fgets(str, 256, arquivo);
    
    /*
     * Metodo para ler todos os vertices de uma linha e salvar suas conexoes
     */
    char * pch;
    pch = strtok (str," ,.-");
    /*
     * Le todos os vertices que estao na string, um a um
     */
    while (pch != NULL)
    {
        /*
         * Se existir vertices que sao adjacentes ao vertice1
         */
        if(atoi(pch) != 0) {
            /*
             * Faz uma simetria de amizades, se v2 estiver ligado em v1 na matriz de adj., a reciproca e verdadeira
             */
            int v2 = atoi(pch);
            ConectaVertices(v1, v2, Grafo);
        }
        pch = strtok (NULL, " ,.-"); // Passa para o proximo vertice adjacente, se ele existir
    }
}

void ImprimeGrafoO(TipoGrafoO *Grafo) {
    int i, j;
    for (i = Grafo->inicio; i < Grafo->fim; i++) {
        printf("%2d:", i);
        for (j = Grafo->inicio; j < Grafo->fim; j++) {
            printf("%4d", Grafo->mAdj[i][j]);
        }
        putchar('\n');
    }
}

short *CriaVetorVertices(int tamanho) {
    
    /*
     * Cria um vetor de (short) com tamanho (tamanho)
     */
    short *vetor = (short *)malloc(tamanho * sizeof(short));
    
    int i = 0;
    
    /*
     * Inicializa todas as posicoes do vetor com 0
     */
    for(i = 0; i < tamanho; i++)
        vetor[i] = 0;
    
    return vetor;
}

short VerificaCobertura(TipoGrafoO *Grafo) {
    int i = 0;   // Auxiliar
    short x = 1; // Variavel que comeca como VERDADEIRO
    
    /*
     * Verifica se todos os valores no (vetorVertices) estao igual a 1, o que indica
     * que todos os vertices estao cobertos por um subconjunto
     */
    for(i = Grafo->inicio; i < Grafo->fim; i++)
        x = x & Grafo->vetorVertices[i];
    
    return x;
}

void DescobreMenorCobertura(FILE *arqCombinacoes, TipoGrafoO *Grafo, int *minimo) {
    int i;
    int aux;
    int contador = 0; // Contara o numero minimo de vertices necessarios para cobrir todo o grafo
    
    char str[256];  // Cria uma string para armazenar todos os vertices que estarao conectados ao vertice1
    
    fgets(str, 256, arqCombinacoes); // Armazena os vertices adjacentes ao vertice1
    
    //printf("\nVertices = %s", str);
    
    /*
     * Metodo para ler todos os vertices, e salva-los na lista de adjacentes ao vertice1
     */
    char * pch;
    pch = strtok (str," ,.-");
    /*
     * Le todos os vertices que estao na string, um a um.
     * Faz a analise da seguinte forma: Pega todos os vertices que estao na string e verifica todos os vertices que 
     * eles conectam. Se ele conecta 1 vertice x, vetorVertice[x] e marcado como 1.
     * Apos realizar esse processo para todos os vertices, verifica se todos os elemetos do vetorVertices estao com 
     * o valor 1. Se sim, indica que todos os vertices foram cobertos, se nao, indica que pelo menos um vertice nao foi coberto
     */
    while (pch != NULL)
    {
        aux = atoi(pch); // Vertice lido do arquivo
        
        /*
         * i, a cada interacao, fica igual a um vertice do grafo. Logo, i vai assumir todos os vertices
         */
        for(i = Grafo->inicio; i < Grafo->fim; i++) {
            /*
             * Verifica se i != aux. Se sim, verifica se aux e i estao conectados no vertice, se sim, marca a posicao i
             * do vetorVertices como 1
             */
            if(i != aux) {
                if(Grafo->mAdj[aux][i] == 1)
                    Grafo->vetorVertices[i] = 1;
            }
            /*
             * Se i == aux, significa que o vertice e conectado com ele mesmo e, entao, seta-se 1 no vetorVertices na posicao i
             */
            else
                Grafo->vetorVertices[i] = 1;
        }
        contador++;
        pch = strtok (NULL, " ,.-"); // Passa para o proximo vertice adjacente, se ele existir
    }
    contador--;
    
    /*
     * Verifica se todos os vertices do grafo foram cobertos
     */
    //printf("%d\n", VerificaCobertura(Grafo));
    if(VerificaCobertura(Grafo) == 1) {
        //printf("Minimo: = %d\n\n", contador);
        if(contador < *minimo)
                *minimo = contador;
    }
    
    /*
     * Apos a interacao para uma linha, zera o vetorVertices novamente, para que se possa executar o algoritmo para uma proxima linha
     */
    for(i = Grafo->inicio; i < Grafo->fim; i++) {
        Grafo->vetorVertices[i] = 0;
    }
    
    contador = 0;
}

void LiberaGrafoO(TipoGrafoO *Grafo) {
    int i;
    
    /*
     * Libera as colunas da matriz de adjacencia do grafo
     */
    for(i = 0; i < Grafo->fim; i++) {
        free(Grafo->mAdj[i]);
    }
    /*
     * Libera o vetor alocado para mAdj(linhas)
     */
    free(Grafo->mAdj);
    /*
     * Libera o vetor de vertices
     */
    free(Grafo->vetorVertices);
}