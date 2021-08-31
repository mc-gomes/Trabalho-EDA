#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main(){

    FILE *arquivoRef, *notas1, *notas2, *notas3, *notas4, *notas5;
    bool notaReview = true;
    char ch; // VARIAVEL QUE VAI LER CADA CARACTERE DO ARQUIVO COM AS NOTAS
    int tipoNota = 0;
    
    // LÊ O ARQUIVO COM AS REVIEWS
    arquivoRef = fopen("arquivo_reviews.csv", "r");

    // ARQUIVOS QUE SERÃO CRIADOS NO PRIMEIRO
    // MOMENTO EM QUE AS VARIÁVEIS FOREM CHAMADAS
    // E QUE RECEBERÃO CONTEÚDO PRA SER ESCRITO
    notas1 = fopen("notas1.txt", "w");
    notas2 = fopen("notas2.txt", "w");
    notas3 = fopen("notas3.txt", "w");
    notas4 = fopen("notas4.txt", "w");
    notas5 = fopen("notas5.txt", "w");

    
    while (!feof(arquivoRef)){
        /*
        ENQUANTO O ARQUIVO COM AS REVIEWS NÃO TERMINAR
        DE SER LIDO, O PROGRAMA VAI IDENTIFICANDO O TIPO DA NOTA
        */
        ch = fgetc(arquivoRef);

        if(notaReview){
            /*
            ENTRA NESSA CONDIÇÃO CASO ESTEJA LENDO QUAL O TIPO
            DA NOTA, QUE NO CASO É SEMPRE A PRIMEIRA COLUNA DO
            ARQUIVO DE REVIEWS (eu alterei pra ficasse dessa forma),
            E A SEPARAÇÃO ENTRE COLUNAS É MARCADA POR ';'
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
        A PARTIR DAQUI O COMPUTADOR VAI SEPARAR NOS ARQUIVOS
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
        DENTRO DO ARQUIVO DE REVIEWS CADA CONJUNTO DE
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

    // FECHANDO DE FORMA MAIS SEGURA CADA ARQUIVO QUE FOI ABERTO
    fclose(arquivoRef);
    fclose(notas1);
    fclose(notas2);
    fclose(notas3);
    fclose(notas4);
    fclose(notas5);

    return 0;
}
