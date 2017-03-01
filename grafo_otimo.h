#ifndef GRAFO_OTIMO_H
#define	GRAFO_OTIMO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"

/*
 * Definicicao do tipo da matriz de adjacencia que representa o grafo.
 */
typedef short **TipoMatrizAdj;

/*
 * TipoGrafo que e usado para a definicao do grafo que vai ser representado por lista de adjacencia e 
 * usado para a solucao otima.
 */
typedef struct TipoGrafoO {
    TipoMatrizAdj mAdj;
    short* vetorVertices;
    int inicio;    // Inicio do grafo, que será a posicao 1
    int fim;       // Fim do grafo, que será a posicao[tamanho do grafo + 1]
    int numAmigos; // Numero de amigos (vertices)
} TipoGrafoO;

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void SetaParametrosO(FILE *arquivo, TipoGrafoO *Grafo)
Função:    Inicializa os parametros do grafo, conforme foram lidos do arquivo de de entrada
Entrada:   @ arquivo: // Arquivo de entrada que contém os parametros que inicilizarao o grafo
           @ Grafo:   // Grafo em questao
Saída:     Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void SetaParametrosO(FILE *arquivo, TipoGrafoO *Grafo);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: TipoMatrizAdj CriaMatrizAdjQuadrada(int dimensao)
Função:    Cria uma matriz quadrada, que representara a matriz de adjacencia de um grafo
Entrada:   @ dimensao: // Como sera criada uma matriz quadrada M, ela tera dimensao M[dimensao][dimensao]
Saída:     Retorna uma matriz de adjacencia
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
TipoMatrizAdj CriaMatrizAdjQuadrada(int dimensao);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void ConectaVertices(int v1, int v2, TipoGrafoO *Grafo)
Função:    Conecta os vertices v1 e v2 no Grafo, ligando v1 - v2 e v2 - v1
Entrada:   @ v1:    // Vertice que sera ligado
           @ v2:    // Vertice que sera ligado
           @ Grafo: // Grafo a qual pertencem os vertices
Saída:     Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void ConectaVertices(int v1, int v2, TipoGrafoO *Grafo);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void SalvaAmizadesO(FILE *arquivo, TipoGrafoO *Grafo)
Função:    Le todos os vertices e a quem estao conectados do arquivo de entrada e, entao, conecta-os no grafo
Entrada:   @ arquivo: // Arquivo de entrada de onde serao lidos os vertices e suas conexoes
           @ Grafo:   // Grafo em questao
Saída:     Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void SalvaAmizadesO(FILE *arquivo, TipoGrafoO *Grafo);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void ImprimeGrafoO(TipoGrafoO *Grafo)
Função:    Funcao auxiliar usada pelo aluno apenas para conferir se o grafo fora corretamente alocado e preenchido
Entrada:   @ Grafo: // Grafo em questao
Saída:     Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void ImprimeGrafoO(TipoGrafoO *Grafo);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: short *CriaVetorVertices(int tamanho)
Função:    Cria um vetor do tamanho do numero de vertices + 1
Entrada:   @ tamanho: // Quantidade de vertices que um dado grafo possui
Saída:     Retorna um vetor com a quantidade do numero de vertices + 1
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
short *CriaVetorVertices(int tamanho);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: short VerificaCobertura(TipoGrafoO *Grafo)
Função:    O grafo tem um vetor com o tamanho do numero de vertices + 1, o qual e alterado todas as vezes que verifica se um conjunto 
           de vertices conecta todos os outros. Logo, e feita uma verificacao desse vetor para saber se todos os vertices do grafo 
           sao conectados pelos vertices do conjunto
Entrada:   @ Grafo: // Grafo em questao
Saída:     Retorna 1 se o conjunto de vertices cobre todos os vertices e 0 se nao
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
short VerificaCobertura(TipoGrafoO *Grafo);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void DescobreMenorCobertura(FILE *arqCombinacoes, TipoGrafoO *Grafo, int *minimo)
Função:    Descobre o menor numero de vertices necessarios para se realizar a cobertura de todos os vertices do grafo
Entrada:   @ arqCombinacoes: // Arquivo criado pelo programa, o qual contem todas as possibilidades de conjunto entre todos os vertices
           @ Grafo:          // Grafo em questao
           @ minimo:         // Contem a quantidade minima de vertice para se realizar a cobertura otima
Saída:     Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void DescobreMenorCobertura(FILE *arqCombinacoes, TipoGrafoO *Grafo, int *minimo);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void LiberaGrafoO(TipoGrafoO *Grafo)
Função:    Desaloca tudo o que foi alocado para o TipoGrafoO
Entrada:   @ Grafo: // Grafo que tera seus elementos desalocados
Saída:     Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void LiberaGrafoO(TipoGrafoO *Grafo);

#endif	/* GRAFO_OTIMO_H */

