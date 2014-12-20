#include<stdio.h>
#include<stdlib.h>

/* maximo de caracteres por linha mais '\n' e '\0'*/
#define MAXC 502
/* numero de letras do alfabeto*/
#define NUML 26

/* quarda letras e a frequencia com que elas aparecem no texto */
struct Letra {
    char letra;
    int  freq;
};
typedef struct Letra Letra;

/* conta a frequencia de cada letra*/
void  contafreq(char **texto, int lin, Letra *letras){
    int i,j;
    for(i = 0; i < lin; i++){
        for(j = 0; texto[i][j] != '\0'; j++){
            /* se for minuscula */
            if(texto[i][j] >= 'a' && texto[i][j] <= 'z' )
                letras[texto[i][j] - 97].freq++;
            /* se for maiuscula */
            if(texto[i][j] >= 'A' && texto[i][j] <= 'Z' )
                letras[texto[i][j] - 65].freq++;
        }
    }
}

/* troca dois registros de letras de lugar */
void troca_Letra(Letra *a, Letra *b){
    Letra aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

/* ordena as letras por ordem decrescente de frequencias*/
void ordena_letras(Letra *letras){
    int i,j,max;
    for(i = 0; i < NUML; i++){
        max = i;
        for(j = i+1; j < NUML; j++)
            if(letras[max].freq < letras[j].freq)
                max = j;
            /* se as frequencias forem iguais a maior eh a lexicograficamente 
             * maior */
            else if(letras[max].freq == letras[j].freq)
                if(letras[max].letra < letras[j].letra)
                    max = j;
                troca_Letra(&letras[i],&letras[max]);
    }
}

int acha_letra(Letra *letras, char letra){
    int i;
    for(i = 0; i < NUML; i++){
        if(letras[i].letra == letra)
            return i;
    }
    return -1;
}

/* criptografa o texto */
void cript(char **texto, int lin, Letra *letras){
    int i,j,letra_pos;
    for(i = 0; i < lin; i++)
        for(j = 0; texto[i][j] != '\0'; j++){
            /* se for uma letra minuscula */
            if(texto[i][j] >= 'a' && texto[i][j] <= 'z' ){
                /* encontra a posição da letra */
                letra_pos = acha_letra(letras,texto[i][j]);
                /* se aposição for impar troca a letra com a anterior(mais 
                 * frequente) */
                if(letra_pos%2)
                    texto[i][j] = letras[letra_pos-1].letra;
                /* se aposição for par troca a letra com a procima(menos 
                 * frequente) */
                else
                    texto[i][j] = letras[letra_pos+1].letra;
            }
            /* se for uma letra maiuscula */
            else if(texto[i][j] >= 'A' && texto[i][j] <= 'Z' ){
                /* encontra a posição da letra */
                letra_pos = acha_letra(letras,(texto[i][j] + 32));
                /* se aposição for impar troca a letra com a anterior(mais 
                 * frequente) */
                if(letra_pos%2)
                    texto[i][j] = (letras[letra_pos-1].letra - 32);
                /* se aposição for par troca a letra com a procima(menos 
                 * frequente) */
                else
                    texto[i][j] = (letras[letra_pos+1].letra - 32);
            }
        }
}

int main(){
    char  **texto,l;
    int   lin,i;
    Letra letras[NUML];
    
    /* recebe o numero de linhas */
    scanf("%d\n",&lin);
    /* aloca matriz para guardar o texto que sera criptografado */
    texto = malloc(lin * sizeof(char*));
    for(i = 0; i < lin; i++)
        texto[i] = malloc(MAXC * sizeof(char));
    /* le o texto que sera criptografado */
    for(i = 0; i < lin; i++)
        fgets(texto[i],MAXC,stdin);
    /* inicia o vetor das letras */
    for(i = 0 ,l = 'a'; i < NUML; i++, l++){
        letras[i].letra = l;
        letras[i].freq = 0;
    }
    
    /* conta a frequencia de cada letra*/
    contafreq(texto,lin,letras);
    /* ordena as letras */
    ordena_letras(letras);
    /* criptografa o texto */
    cript(texto,lin,letras);
    
    /* imprime texto criptografado */
    for(i = 0; i < lin; i++)
        printf("%s",texto[i]);
    /* libera vetor do texto */
    for(i = 0; i < lin; i++)
        free(texto[i]);
    free(texto);
    return 0;
}
    