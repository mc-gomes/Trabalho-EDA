#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include "libManipulacao.h"

void menu(){
    printf("----------------------\n");
    printf("\tMenu\n");
    printf("1- Ler arquivo base\n");
    printf("2- Gerar vocabulário\n");
    printf("3- Sair\n");
}

int main(int argc, const char * argv[]){
    setlocale(LC_ALL, "Portuguese");

    FILE *arquivoRef;
    char  nomeArquivo[30];

    int opcao = 0;

    do{
        menu();
        printf(">> ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            // LÊ O ARQUIVO INFORMADO PELO USUARIO
            printf("Arquivo disponível: arquivo_reviews.csv\n");
            printf("Informe o nome do arquivo (com a extensão): ");
            scanf("%s", nomeArquivo);
            arquivoRef = fopen(nomeArquivo, "r");
            if(arquivoRef == NULL){
                printf("ERRO: Não foi possível abrir o arquivo!\n");
                return 0;
            }
            else{
                separaPorNota(arquivoRef);
                printf("\nArquivos gerados com sucesso! Pronto para gerar vocabulário.\n\n");
                fclose(arquivoRef);
            }
            break;
        case 2:
            separaPalavra("nota1.txt");
            separaPalavra("nota2.txt");
            separaPalavra("nota3.txt");
            separaPalavra("nota4.txt");
            separaPalavra("nota5.txt");

            criaCorpoText("N1semRep.txt");
            criaCorpoText("N2semRep.txt");
            criaCorpoText("N3semRep.txt");
            criaCorpoText("N4semRep.txt");
            criaCorpoText("N5semRep.txt");

            printf("\nVocabulário criado com sucesso!\n");

            break;
        case 3:
            printf("Programa encerrado!\n");
            break;
        default:
            printf("Opção inválida!\n\n");
            break;
        }
    } while (opcao != 3);
    
    return 0;
}
