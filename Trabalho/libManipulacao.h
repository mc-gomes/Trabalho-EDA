#ifndef LIBMANIPULACAO_H
#define LIBMANIPULACAO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*  Essa função verfica se a variável recebida como parâmetro
    é igual a algum caractere que marca final de palavra,
    dentre os caracteres especificados.*/
int finalDePalavra(char pcar);

/*  Essa função analisa se 'plv' se repete dentro
    do arquivo em que ela está (no caso 'filep').*/
int analisaRepeticao(FILE *filep, char plv[], long int posic);

/*  No contexto do trabalho, essa função lê o
    arquivo .csv com a base de dados e cria os arquivos
    separados pelas notas.*/
void separaPorNota(FILE *arquivoReferencia);

/*  Essa função recebe o nome de um arquivo de notas específico,
    para que o mesmo possa ser lido e que cada uma de suas palavras
    seja colocada em uma linha de outro arquivo '.txt'.*/
void separaPalavra(char nomeArquivo[]);

/*  Essa função recebe o arquivo que foi manipulado
    pela função 'separaPalavra' e coloca as palavras
    desse arquivo em outro, sem nenhuma repetição.*/
void palavraUnica(FILE *frepetido, char nome_arq[]);

/*  Função que gera o vocabulário com as palavras de
    todos os arquivos de notas, sem nenhuma repetição.*/
void criaCorpoText(char nome_arq[]);


#endif