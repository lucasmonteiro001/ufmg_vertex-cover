#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: FILE *AbreArquivo(char *nome_arquivo, char *modo_leitura);
Função:    Abre o arquivo no modo especificado
Entrada:   @ nome_arquivo: uma string que contém o local e o nome do arquivo
           @ modo_leitura: uma string informando qual vai ser o modo para abrir o arquivo (ex: "r")
Saída:     Retorna um ponteiro para o arquivo
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
FILE *AbreArquivo(char *nome_arquivo, char *modo_leitura);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void FechaArquivo(FILE *arquivo);
Função:    Fecha o arquivo passado como parâmetro
Entrada:   @ arquivo: arquivo que será fechado
Saída:     Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void FechaArquivo(FILE *arquivo);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void PassaParaProximaLinha(FILE *arquivo)
Função:    Para o cursor para a proxima linha
Entrada:   @ arquivo
Saída:     Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void PassaParaProximaLinha(FILE *arquivo);

#endif // IO_H_INCLUDED
