#include "grafo_heuristica.h"

#define FALSE 0
#define TRUE  1

//============================================================================== 
// Operadores para a lista de adjacencia de um grafo generico
// =============================================================================
void FLVazia(TipoLista *Lista) {
    Lista->Primeiro       = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo         = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
    Lista->flagAmigoUnico = 0; // Inicia toda a lista, fazendo com que ela seja de amigo unico
}

void Insere(TipoItem *novo, TipoLista *Lista) {
    Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo       = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = *novo;
    Lista->Ultimo->Prox = NULL;
}


//============================================================================== 
// Operadores para um tipo Grafo
// =============================================================================
void FGrafoVazio(TipoGrafo *Grafo) {
    int i;
    /*
     * Para cada posicao da lista de adjacencia do grafo, a partir da posicao 1 
     * ate o final da lista de adjacencia, aloca uma lista vazia
     */
    for(i = Grafo->Inicio; i < Grafo->Fim; i++) {
        FLVazia(&Grafo->ListaAdj[i]);
    }
}

void InsereAresta(int *vertice1, int *vertice2, TipoGrafo *Grafo) {
    TipoItem x;
    x.Vertice = *vertice2;
    Grafo->ListaAdj[*vertice1].flagAmigoUnico = 1; // Se inseriu-se uma nova aresta em uma lista, quer dizer que ela nao representa mais apenas um amigo, e sim, pelo menos 2
    Insere(&x, &Grafo->ListaAdj[*vertice1]);
}

void ImprimeGrafo(TipoGrafo *Grafo) {
    int i;  
    TipoApontador Aux;
    for (i = Grafo->Inicio; i < Grafo->Fim; i++) 
      { printf("%2d:", i);
        if (Grafo->ListaAdj[i].Primeiro != NULL) 
        { Aux = Grafo->ListaAdj[i].Primeiro->Prox;
          while (Aux != NULL) 
            { printf("%3d", Aux->Item.Vertice);
              Aux = Aux->Prox;
            }
        }
        putchar('\n');
      }
}

void SetaParametros(FILE *arquivo, TipoGrafo *Grafo) {
    /*
     * Armazena a quantidade de amigos(arestas) que o grafo(Zambis) possui e passa para 
     * a proxima linha
     */
    fscanf(arquivo, "%d", &Grafo->numAmigos);
    PassaParaProximaLinha(arquivo);
    
    /*
     * Cria um vetor (lista de adjacencia), inicializa inicio e fim para o grafo e
     * inicializa suas listas como vazia
     */
     Grafo->ListaAdj = (TipoLista *)malloc((Grafo->numAmigos + 1)* sizeof(TipoLista));
     Grafo->Inicio   = 1;
     Grafo->Fim      = Grafo->numAmigos + 1;
     FGrafoVazio(Grafo);
}

void SalvaAmizades(FILE *arquivo, TipoGrafo *Grafo) {
    int v1;
    fscanf(arquivo, "%d", &v1);  // Armazena o primeiro vertice, os quais tera uma lista de vertices conectadas
    char str[256];  // Cria uma string para armazenar todos os vertices que estarao conectados ao vertice1
    
    fgets(str, 256, arquivo); // Armazena os vertices adjacentes ao vertice1
    
    /*
     * Metodo para ler todos os vertices, e salva-los na lista de adjacentes ao vertice1
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
             * Insere todos os vertices armazenados em str na lista de adjacentes do vertice1.
             * Faz uma simetria de amizades, se v2 for inserido na lista de v1, logo v1 vai ser inserido na lista de v2
             */
            int v2 = atoi(pch);
            InsereAresta(&v1, &v2, Grafo);
            InsereAresta(&v2, &v1, Grafo);
        }
        pch = strtok (NULL, " ,.-"); // Passa para o proximo vertice adjacente, se ele existir
    }
}

int Heuristica(TipoGrafo *Grafo) {
    int i;
    int contador = 0;
    /*
     * Percorre todos os vertices do grafo
     */
    for(i = Grafo->Inicio; i < Grafo->Fim; i++) {
	
        /*
         * Se a lista tiver a flagAmigoUnico igual a zero, quer dizer que o vertice e amigo apenas de zambi, e nao possui outros amigos 
         * em comum, portanto, desaloca o vertice e coloca-o na solucao heuristica
         */
	if(Grafo->ListaAdj[i].flagAmigoUnico == 0) {
            
            /*
             * Entra para a solucao heuristica
             */
            //printf("\n\n-- %d --\n\n", i);
            contador++;
            
            free(Grafo->ListaAdj[i].Primeiro);  //printf("Liberei Grafo->ListaAdj[%d]\n", i);
            Grafo->ListaAdj[i].Primeiro = NULL;
        }
        /*
         * Verifica se a lista dos adjacentes de (i) não está vazia, se não estiver, processa
         */
        else if(Grafo->ListaAdj[i].Primeiro != NULL &&  Grafo->ListaAdj[Grafo->ListaAdj[i].Primeiro->Prox->Item.Vertice].Primeiro != NULL) {


            TipoApontador Aux;    // Conterá, a cada momento, um dos itens da lista de adjacentes de (i)
            TipoApontador AuxAnt; // Auxiliar que vai receber um elemento de (i) para desaloca-lo
            
            Aux = Grafo->ListaAdj[i].Primeiro->Prox; // Primeiro elemento da lista de adjacentes de (i)
            
            int arestaV; // Aresta que entrara na melhor solucao, junto com a aresta i
            
            /*
             * Descobre a arestaV da seguinte forma:
             * Se o primeiro elemento adjacente a (i), contem uma lista com nenhum elemento (o que significa que 
             * ela ja foi desalocada), passa para o proximo elemento e checa: Realiza esse procedimento ate 
             * achar uma aresta que possua uma lista que nao foi desalocada ainda
             */
            arestaV = Aux->Item.Vertice; // Atribui o valor da arestaV para o primeiro vertice adjacente a (i)
            TipoApontador AuxArestaV = Aux;
            while(Grafo->ListaAdj[arestaV].Primeiro == NULL) {
                AuxArestaV = AuxArestaV->Prox;
                arestaV = AuxArestaV->Item.Vertice;
            }
            
            /*
             * Entra para a solucao heuristica
             */
            //printf("\n\n-- %d --\n\n-- %d --\n\n", i, arestaV);
            contador++; // Para i
            contador++; // Para arestaV
            
            /*
             * Como ja se escolheu a arestaV, e necessario passar para o proximo elemento, para nao desalocar 
             * a lista de adjacentes de (arestaV)
             */
            Aux = Aux->Prox;
            
            /*
             * Percorre todos os elementos da lista de adjacentes de (i)
             */
            while(Aux != NULL) {
                AuxAnt = Aux;
                
                /*
                 * Libera toda a lista dos elementos adjacentes a Aux da lista de (i).
                 * Checa se a lista do grafo, na posicao Aux->Item.Vertice nao esta vazia, se nao estiver,
                 * libera todos os seus elementos e faz Aux->Primeiro apontar para null
                 */
                TipoApontador AuxLista;    // Vai conter a lista
                TipoApontador AuxListaAnt; // Auxiliar para desalocar
                if(Grafo->ListaAdj[Aux->Item.Vertice].Primeiro != NULL) {
                    AuxLista = Grafo->ListaAdj[Aux->Item.Vertice].Primeiro->Prox;
                    if(AuxLista != NULL) {
                        while(AuxLista != NULL) {
                            AuxListaAnt = AuxLista;
                            AuxLista = AuxLista->Prox;
                            //printf("Liberei %d da lista %d\n", AuxListaAnt->Item.Vertice, Aux->Item.Vertice);
                            free(AuxListaAnt);
                        }
                        free(Grafo->ListaAdj[Aux->Item.Vertice].Primeiro);  //printf("Liberei Grafo->ListaAdj[%d]\n", Aux->Item.Vertice);
                        Grafo->ListaAdj[Aux->Item.Vertice].Primeiro = NULL;
                    }
                }
                    
                //printf("Liberei %d da lista de %d\n", AuxAnt->Item.Vertice, i);
                
                /*
                 * Se o vertice que esta sendo analisado eh o ultimo da lista de adjacentes
                 */
                AuxArestaV->Prox = Aux->Prox;
                free(Aux);
                Aux = Aux->Prox;
            }
            
            TipoApontador AuxLista;           // Vai conter a lista dos adjacentes a (arestaV)
            TipoApontador AuxListaAnt;        // Auxiliar para desalocar
            TipoApontador AuxListaArestaV;    // Vai conter a lista de adjacentes de AuxLista
            TipoApontador AuxListaArestaVAnt; // Auxiliar para desalocar elementos da lista de adjacentes de AuxLista
            
            
            /*
             * Realiza o mesmo processo de desalocao para a (arestaV)
             */
            if(AuxArestaV != NULL) {
                
                AuxLista = Grafo->ListaAdj[arestaV].Primeiro->Prox; // Lista de adjacentes da (arestaV)
                /*
                 * Entra na lista de adjacentes da (arestaV)
                 */
                while(AuxLista != NULL) {
                    /*
                     * Entra na lista de adjacentes de cada item adjacente a (arestaV), se ela nao estiver vazia
                     */
                    if(Grafo->ListaAdj[AuxLista->Item.Vertice].Primeiro != NULL) {
                        AuxListaArestaV = Grafo->ListaAdj[AuxLista->Item.Vertice].Primeiro->Prox; // Pega o primeiro elemento adjacente a um elemento adjacente de (arestV)
                        while(AuxListaArestaV != NULL) {
                            AuxListaArestaVAnt = AuxListaArestaV;
                            //printf("Liberei %d da lista %d\n", AuxListaArestaVAnt->Item.Vertice, AuxLista->Item.Vertice);
                            AuxListaArestaV = AuxListaArestaV->Prox;
                            free(AuxListaArestaVAnt);
                            AuxListaArestaVAnt = NULL;
                        }
                        
                        free(Grafo->ListaAdj[AuxLista->Item.Vertice].Primeiro);  //printf("Liberei Grafo->ListaAdj[%d]\n\n", AuxLista->Item.Vertice);
                        Grafo->ListaAdj[AuxLista->Item.Vertice].Primeiro = NULL;

                        AuxListaAnt = AuxLista;
                        AuxLista = AuxLista->Prox;
                        //printf("Liberei %d da lista de %d\n", AuxListaAnt->Item.Vertice, arestaV);
                        free(AuxListaAnt);
                    
                    }
                    /*
                     * Se a lista do elemento em analise esta vazia, desaloca somente ele
                     */
                    else {                        
                        AuxListaAnt = AuxLista;
                        AuxLista = AuxLista->Prox;
                        //printf("Liberei %d da lista de %d\n", AuxListaAnt->Item.Vertice, arestaV);
                        free(AuxListaAnt);
                    }
                }
                free(Grafo->ListaAdj[arestaV].Primeiro);  //printf("Liberei Grafo->ListaAdj[%d]\n", arestaV);
                Grafo->ListaAdj[arestaV].Primeiro = NULL;
            }
        }
    }
    
    /*
     * Apos ter desalocado todos os vertices acessiveis diretamente, faz uma segunda varredura, verificando todos os vertices 
     * que ainda nao foram desalocados. Se os vertices ainda nao foram desalocados, desaloca sua lista de adjacente que coloca 
     * os vertice (i) na solucao heuristica
     */
    TipoApontador Aux;
    TipoApontador AuxAnt;
    for(i = Grafo->Inicio; i < Grafo->Fim; i++) {
        if(Grafo->ListaAdj[i].Primeiro != NULL) {
            Aux = Grafo->ListaAdj[i].Primeiro->Prox;
            while(Aux != NULL) {
                 AuxAnt = Aux;
                 Aux = Aux->Prox;
                 //printf("Liberei %d da lista de %d\n", AuxAnt->Item.Vertice, i);
                 free(AuxAnt);
            }
            /*
             * Entra para a solucao heuristica
             */
            //printf("\n\n-- %d --\n\n", i);
            contador++;
            free(Grafo->ListaAdj[i].Primeiro); //printf("Liberei Grafo->ListaAdj[%d]\n\n", i);
            Grafo->ListaAdj[i].Primeiro = NULL;
        }
    }
     
    /*
     * Desaloca o vetor de listas
     */
    free(Grafo->ListaAdj);
    
    return contador;
}