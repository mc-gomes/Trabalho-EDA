#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include "libManipulacao.h"

// No momento todas as funções estão aqui
// por causa de um problema com as bibliotecas


void menu(){
    printf("----------------------\n");
    printf("\tMenu\n");
    printf("1- Ler arquivo base\n");
    printf("2- Gerar vocabulário\n");
    printf("3- Sair\n");
}

int finalDePalavra(char pcar){
    // FUNÇÃO QUE VERIFICA SE HÁ ALGUM
    // MARCADOR DE FINAL DE PALAVRA
    int indx, pehfim = 0;
    char FIMPAL[8] = {' ', '.', ',', '-', ':', '/', '!', '?'};
    int TAMFIMPAL = 8;

    for (indx = 0; indx < TAMFIMPAL; indx++){
        if (pcar == FIMPAL[indx]){
            pehfim = 1;
            break;
        }
    }
    return pehfim;
}

int analisaRepeticao(FILE *filep, char plv[], long int posic){
    // FUNÇÃO QUE VAI ANALISAR SE UMA PALAVRA SE
    // REPETE DENTRO DO PRÓPRIO ARQUIVO
    fseek(filep, 0, SEEK_SET);
    int pos = ftell(filep);

    char plv2[50];

    while(fgets(plv2, 50, filep) != NULL && pos < posic){ 
        pos = ftell(filep);

        if(strcmp(plv, plv2) == 0){
            fseek(filep, (posic-pos)+(strlen(plv)-1), SEEK_CUR);
            return 1;
        }
    }

    return 0;
}

void separaPorNota(FILE *arquivoReferencia){
    FILE *notas1, *notas2, *notas3, *notas4, *notas5;
    bool notaReview = true;
    char ch; // VARIAVEL QUE VAI LER CADA CARACTERE DO ARQUIVO COM AS NOTAS
    int tipoNota = 0;

    // ARQUIVOS QUE SERÃO CRIADOS NO PRIMEIRO
    // MOMENTO EM QUE AS VARIÁVEIS FOREM CHAMADAS
    // E QUE RECEBERÃO CONTEÚDO PRA SER ESCRITO
    notas1 = fopen("nota1.txt", "w");
    notas2 = fopen("nota2.txt", "w");
    notas3 = fopen("nota3.txt", "w");
    notas4 = fopen("nota4.txt", "w");
    notas5 = fopen("nota5.txt", "w");


    while (!feof(arquivoReferencia)){
        /*
        ENQUANTO O ARQUIVO COM AS REVIEWS NÃO TERMINAR
        DE SER LIDO, O PROGRAMA VAI IDENTIFICANDO O TIPO DA NOTA.
        */
        ch = fgetc(arquivoReferencia);

        if(notaReview){
            /*
            ENTRA NESSA CONDIÇÃO CASO ESTEJA LENDO QUAL O VALOR
            DA NOTA, QUE NO CASO É SEMPRE O PRIMEIRO CARACTERE
            DE CADA LINHA ARQUIVO BASE DE REVIEWS.
            */
            if(ch == '1'){
                tipoNota = 1;
            }
            if(ch == '2'){
                tipoNota = 2;
            }
            if(ch == '3'){
                tipoNota = 3;
            }
            if(ch == '4'){
                tipoNota = 4;
            }
            if(ch == '5'){
                tipoNota = 5;
            }

            notaReview = false;
            /*
            O PROGR IDENTIFICA O TIPO DA NOTA E DESATIVA
            ESSA FLAG 'notaReview', PRA QUE AGORA O COMPUTADOR
            LEIA OS COMENTARIOS ASSOCIADOS AQUELA NOTA
            */
        }
        
        switch (tipoNota)
        {
        /*
        A PARTIR DAQUI O COMPUTADOR VAI INSERIR NOS ARQUIVOS
        RESPECTIVOS CADA CONJUNTO DE COMENTARIO ASSOCIADO A UMA NOTA
        */
        case 1:
            fputc(ch, notas1);
            if(ch == '\n'){
                notaReview = true;     
            }
            break;
        case 2:
            fputc(ch, notas2);
            if(ch == '\n'){
                notaReview = true;
            }
            break;
        case 3:
            fputc(ch, notas3);
            if(ch == '\n'){
                notaReview = true;
            }
            break;
        case 4:
            fputc(ch, notas4);
            if(ch == '\n'){
                notaReview = true;
            }
            break;
        case 5:
            fputc(ch, notas5);
            if(ch == '\n'){
                notaReview = true;
            }
            break;
        /*
        DENTRO DO ARQUIVO DE REVIEWS, CADA CONJUNTO DE
        COMENTÁRIOS ESTÁ EM UMA CÉLULA, E ESSA CÉLULA SÓ
        TERMINA COM QUEBRA DE LINHA, POR ISSO SEMPRE QUE
        ch == '\n' O COMPUTADOR TERMINOU DE LER UM CONJ
        DE COMENTÁRIOS E ASSIM PODE LER OUTROS, COM ISSO
        ATIVAMOS NOVAMENTE A FLAG 'notaReview'
        */

        default:
            break;
        }

    }

    fclose(notas1);
    fclose(notas2);
    fclose(notas3);
    fclose(notas4);
    fclose(notas5);
}

void separaPalavra(char nome_arq[]){
    // FUNÇÃO QUE LÊ O ARQUIVO COM AS REVIEWS
    // E COLOCA CADA PALAVRA EM UMA LINHA DE
    // OUTRO ARQUIVO
    FILE *fp, *plvs_repetidas;
    char ch;

    int notaRating = 1;
    int espaco = 0, undrsc = 0;
    int nova_pal = 0, comeca_num = 0, fim_num = 1;

    fp = fopen(nome_arq, "r");
    if(fp == NULL){
        printf("Não foi possível gerar vocabulário.\n* É preciso ler o arquivo base primeiro.*\n");
        printf("Encerrando programa.\n");
        exit(0);
    }

    // ANÁLISE PARA SABER QUAL ARQUIVO SERÁ CRIADO
    if(strcmp(nome_arq, "nota1.txt") == 0)
        plvs_repetidas = fopen("N1 repetidas.txt", "a+");
    else if(strcmp(nome_arq, "nota2.txt") == 0)
        plvs_repetidas = fopen("N2 repetidas.txt", "a+");
    else if(strcmp(nome_arq, "nota3.txt") == 0)
        plvs_repetidas = fopen("N3 repetidas.txt", "a+");
    else if(strcmp(nome_arq, "nota4.txt") == 0)
        plvs_repetidas = fopen("N4 repetidas.txt", "a+");
    else if(strcmp(nome_arq, "nota5.txt") == 0)
        plvs_repetidas = fopen("N5 repetidas.txt", "a+");
    

    // INÍCIO DA SEPARAÇÃO DE PALAVRAS
    while(!feof(fp)){
        ch = fgetc(fp);
        if(notaRating){
            notaRating = 0;
        }
        else{
            if(ch != ';'){
                if(ch == '\n')
                    notaRating = 1;
                if(ch == '_')
                    undrsc = 1;
                
                if(!undrsc){
                    if(!espaco){
                        if(comeca_num){
                            if(!finalDePalavra(ch)){
                                fim_num = 0;
                            }
                            else{
                                if(ch == ',')
                                    espaco = 1;
                                fim_num = 1;
                                nova_pal = 1;
                                comeca_num = 0;
                            }
                        }
                        if(nova_pal){
                            if(!isdigit(ch)){
                                if(finalDePalavra(ch)){
                                    if(fim_num == 0){
                                        ch ='\n';
                                        nova_pal = 1;
                                        fputc(ch, plvs_repetidas);
                                    }
                                }
                                else{
                                    fputc(ch, plvs_repetidas);
                                    nova_pal = 0;
                                    comeca_num = 0;
                                }
                            }
                            else{
                                comeca_num = 1;
                                nova_pal = 0;
                            }
                        }
                        else{
                            if(finalDePalavra(ch)){
                                if(ch == ',')
                                    espaco = 1;
                                ch = '\n';
                                fputc(ch, plvs_repetidas);
                                nova_pal = 1;
                            }
                            else{
                                if(fim_num == 1)
                                    fputc(ch, plvs_repetidas);
                            }
                        }
                    }
                    else{
                        if(!finalDePalavra(ch)){
                            if(!isdigit(ch)){
                                if(ch != '\n'){
                                    fputc(ch, plvs_repetidas);
                                    espaco = 0;
                                    nova_pal = 0;
                                }
                            }
                        }
                    }
                }
                else{
                    if(finalDePalavra(ch)){
                        ch = '\n';
                        fputc(ch, plvs_repetidas);
                        nova_pal = 1;
                        undrsc = 0;
                    }
                }
            }
        }
    }

    palavraUnica(plvs_repetidas, nome_arq);


    fclose(fp);
    fclose(plvs_repetidas);
}

void palavraUnica(FILE *frepetido, char nome_arq[]){
    // FUNÇÃO QUE RECEBE O ARQUIVO COM TODAS AS
    // PALAVRAS DE CADA REVIEW E AS COLOCA SEM REPETIÇÃO
    // EM OUTRO ARQUIVO
    FILE *plvs_sem_rep;
    char palavra[50];

    fseek(frepetido, 0, SEEK_SET);
    
    // ANÁLISE PARA SABER QUAL ARQUIVO SERÁ CRIADO
    if(strcmp(nome_arq, "nota1.txt") == 0)
        plvs_sem_rep = fopen("N1semRep.txt", "a+");
    else if(strcmp(nome_arq, "nota2.txt") == 0)
        plvs_sem_rep = fopen("N2semRep.txt", "a+");
    else if(strcmp(nome_arq, "nota3.txt") == 0)
        plvs_sem_rep = fopen("N3semRep.txt", "a+");
    else if(strcmp(nome_arq, "nota4.txt") == 0)
        plvs_sem_rep = fopen("N4semRep.txt", "a+");
    else if(strcmp(nome_arq, "nota5.txt") == 0)
        plvs_sem_rep = fopen("N5semRep.txt", "a+");


    long int posicao;

    while(!feof(frepetido)){
        posicao = ftell(frepetido);
        fgets(palavra, 50, frepetido);

        if((strlen(palavra) > 4)){

            int repete = analisaRepeticao(frepetido, palavra, posicao);

            if(!repete){
                fputs(palavra, plvs_sem_rep);
            }
        }
    
    }

    fclose(plvs_sem_rep);
}


void criaCorpoText(char nome_arq[]){
    // FUNÇÃO QUE CRIA O CORPO TEXTUAL
    // COM AS PALAVRAS DE TODAS AS REVIEWS

    FILE *fcorpo, *plvs_notas;
    char palavra1[50], palavra2[50], ch;


    fcorpo = fopen("Corpo Textual.txt", "a+");
    plvs_notas = fopen(nome_arq, "r");

    fseek(plvs_notas, 0 , SEEK_SET);

    int repetiu;

    while(!feof(plvs_notas)){
        repetiu = 0;
        fgets(palavra1, 50, plvs_notas);
        fseek(fcorpo, 0, SEEK_SET);
        while(!feof(fcorpo)){
            fgets(palavra2, 50, fcorpo);
            
            if(strcmp(palavra1, palavra2)==0){
                repetiu =1;
                break;
            }
        }
        if(!repetiu)
            fputs(palavra1, fcorpo);
    }

    fclose(fcorpo);
    fclose(plvs_notas);
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
            printf("nome: arquivo_reviews.csv\n");
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
