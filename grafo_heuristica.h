#ifndef GRAFO_H
#define	GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"

typedef struct TipoItem {
    int Vertice; // Identificacao do amigo (vertice)
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
    TipoItem Item;      // Item que vai conter um vertice
    TipoApontador Prox; // Apontador para um proximo elemento do TipoCelula
} TipoCelula;

typedef struct TipoLista {
    TipoApontador Primeiro; // Apontador para o primeiro elemento da lista
    TipoApontador Ultimo;   // Apontador para o ultimo elemento da lista
    int flagAmigoUnico;     // Indica se o amigo(vertice) e amigo so de Zambis
} TipoLista;

typedef struct TipoGrafo {
    int numAmigos;       // Quantidade de amigos que Zambi possui
    int Inicio;          // Posicao inicial da lista de adjacencia do grafo, em todos os casos sera 1
    int Fim;             // Ultima posicao da lista de adjacencia do grafo
    TipoLista *ListaAdj; // Lista de adjacencia que representa as relacoes de amizade
} TipoGrafo;

/*
 * Pressuposto: toda lista de adjacencia de um grafo tera a quantidade do seu numero de vertices + 1, o acrescimo de + 1 facilita a 
 * indexacao dos vertices, visto que os mesmos comecam com identificacao = 1, 2 ...
 */

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void FLVazia(TipoLista *Lista)
Função:    Faz uma lista vaia
Entrada:   @ Lista: // Lista que sera alocada
Saída:     Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void FLVazia(TipoLista *Lista);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void Insere(TipoItem *novo, TipoLista *Lista)
Função:    Insere um novo elemento na lista
Entrada:   @ novo:  // Elemento que sera adicionado na lista
           @ Lista: // Lista que contera o novo elemento
Saída:     Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void Insere(TipoItem *novo, TipoLista *Lista);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void FGrafoVazio(TipoGrafo *Grafo)
Função:    Cria uma grafo vazio (utiliza um dos parametros do grafo para cria-lo)
Entrada:   @ Grafo: // Grafo que sera criado
Saída:     Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void FGrafoVazio(TipoGrafo *Grafo);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void InsereAresta(int *vertice1, int *vertice2, TipoGrafo *Grafo)
Função:    Insere uma aresta na lista do vertice1, a aresta e o identificacao do vertice2
Entrada:   @ vertice1: // Vertice que sera indexado na lista do grafo
           @ vertice2: // Vertice que sera inserido na lista do vertice1
           @ Grafo:    // Grafo que contem os vertices
Saída:     Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void InsereAresta(int *vertice1, int *vertice2, TipoGrafo *Grafo);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void LiberaGrafo(TipoGrafo *Grafo)
Função:    Libera o grafo, desaloca tudo o que foi alocado
Entrada:   @ Grafo: // Grafo que sera liberado da memoria
Saída:     Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void LiberaGrafo(TipoGrafo *Grafo);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void ImprimeGrafo(TipoGrafo *Grafo)
Função:    Imprime o grafo, com seus vertices e sua lista de adjacentes
Entrada:   @ Grafo: // Grafo que vai ser impresso
Saída:     Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void ImprimeGrafo(TipoGrafo *Grafo);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void SetaParametros(FILE *arquivo, TipoGrafo *Grafo)
Função:    Atribui valores para os atributos do grafo e inicializa sua lista de adjacencia
Entrada:   @ arquivo: // Arquivo que contem os parametros do grafo
           @ Grafo:   // Grafo que sera atualizado
Saída:     Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void SetaParametros(FILE *arquivo, TipoGrafo *Grafo);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void SalvaAmizades(FILE *arquivo, TipoGrafo *Grafo)
Função:    Salva as relacoes de amizade (conexao) entre os amigos (vertices)
Entrada:   @ arquivo: // Arquivo que contem as conexoes entre os amigos (vertices)
           @ Grafo:   // Grafo que contem as informacoes de amizades
Saída:     Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void SalvaAmizades(FILE *arquivo, TipoGrafo *Grafo);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: int Heuristica(TipoGrafo *Grafo)
Função:    Heuristica baseada na cobertura de vertices que retorna o numero minino de amigos que precisam ser chamados para se chamar todos os amigos
Entrada:   @ Grafo: // Grafo que representa todas as relacoes de amizade
Saída:     Menor número de vértices que cobrem o grafo, segunda a heurística implementada
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int Heuristica(TipoGrafo *Grafo);

#endif	/* GRAFO_H */

