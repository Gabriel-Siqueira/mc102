/* Nome: Gabriel Henriques Siqueira
 * RA: 155446
 * Laboratorio 08b - Processamento de imagens */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Definindo tamanho maximo das imagens */
#define MAX_TAM 400

/* Le uma imagem em formato PGM a partir da entrada padrao.
 * Retorna 1 se a leitura for realmente de um arquivo PGM
 * e 0 caso contrario.
 * VOCE NAO DEVE ALTERAR ESTA FUNCAO                       */
int ler_pgm(int img[][MAX_TAM], int *W, int *H, int *MaxV,
            int *F, double *Px, double *Py) {
    char nome_formato[3];
    char c;
    int i,j;

    /* Le o formato da imagem. P2 indica o formato PGM */
    scanf("%s ", nome_formato);
    if (strcmp(nome_formato, "P2") != 0)
        return 0;

    /* Le o '#', que indica um comentario, e os numeros indicando
    * o filtro e o parametro, se houver */
    scanf("%[#]c", &c);
    scanf("%d", F);
    if (*F == 4) {
        scanf("%lf %lf", Px, Py);
    } 
 
    /* Le dimensoes e intensidade maxima da imagem */
    scanf("%d", W);
    scanf("%d", H);
    scanf("%d", MaxV);
 
    /* Le o valor de cada pixel da imagem */
    for (i = 0; i < (*H); i++) {
        for (j = 0; j < (*W); j++) {
            scanf("%d", &img[i][j]);
        }
    }

    return 1;
}

/* Escreve a imagem em formato pgm na saida padrao 
 * VOCE NAO DEVE ALTERAR ESTA FUNCAO               */
void escrever_pgm(int img[][MAX_TAM], int W, int H, int MaxV) {
    int i, j;

    /* Escreve os atributos da imagem */
    /* Tipo da imagem: P2 significa pgm*/
    printf("P2\n");
    /* Dimensoes e intensidade maxima da imagem */
    printf("%d %d %d\n", W, H, MaxV);

    /* Escreve os pixels da imagem */
    for (i = 0; i < H; i++) {
        printf("%d", img[i][0]);
        for (j = 1; j < W; j++) {
            printf(" %d", img[i][j]);
        }
        printf("\n");
    }
}

/* Negativo */
void negativo(int img[][MAX_TAM], int W, int H, int MaxV) {
    int i,j;
    /* inverte as intencidades das cores */
    for(i = 0; i < H; i++)
        for(j = 0; j < W; j++)
            img[i][j] = MaxV - img[i][j];
}

/* Rotacao de 180 graus */
void rotacao180(int img[][MAX_TAM], int W, int H) {
    int i,j,aux;
    /* efetua a rotação em todas as linhas exceto a do meio caso tenha uma 
     * quantidade impar de linhas*/
    for(i = 0; i < H/2; i++){
        for(j = 0; j < W; j++){
            aux = img[i][j];
            img[i][j] = img[(H-1)-i][(W-1)-j];
            img[(H-1)-i][(W-1)-j] = aux;
        }
    }
    /* rotaciona a do meio se tiver uma quantidade impar de linhas*/
    if(H%2){
        for(j = 0; j < W/2; j++){
            aux = img[H/2][j];
            img[H/2][j] = img[H/2][(W-1)-j];
            img[H/2][(W-1)-j] = aux;
        }
    }
}

/* Deteccao de bordas */
void detectaBorda(int img[][MAX_TAM], int W, int H, int MaxV) {
    int i,j,*vsalva,aux1,aux2;
    /* cria dois vetores auxiliares */
    vsalva = malloc(W * sizeof(int));
    
    /* prepara o vetor auxiliar com a primeira linha da imagem */
    for(j = 0; j < W; j++){
        vsalva[j] = img[0][j];
        aux2 = img[0][W-2];
    }
    /* encontra os novos valores de intencidade */
    for(i = 1; i < H-1; i++){
        /* salva o ultimo e o penultimo valor da linha anterior e o primeiro 
         * valor da linha atual pois eles serao utilisados */
        vsalva[W-2] = aux2;
        vsalva[W-1] = img[i-1][W-1];
        aux2 = img[i][0];  
        for(j = 1; j < W-1; j++){
            aux1 = ( vsalva[j-1]*(-1) + vsalva[j]*(-4) + vsalva[j+1]*(-1) + 
            aux2*(-4) + img[i][j]*(20) + img[i][j+1]*(-4) + img[i+1][j-1]*(-1) 
            + img[i+1][j]*(-4) + img[i+1][j+1]*(-1) );
            /* salva os valores que ainda serao usados */
            vsalva[j-1] = aux2;
            aux2 = img[i][j];
            /* muda os valores de intencidade fora do intervalo de 0 ao valor 
             * maximo e coloca o valor da nova intencidade na matriz da imagem*/
            if(aux1 < 0)
                img[i][j] = 0;
            else if(aux1 > MaxV)
                img[i][j] = MaxV;
            else
                img[i][j] = aux1;
        }
    }
    
    /* libera os vetores auxiliares */   
    free(vsalva);
}

/* Cisalhamento */
void cisalhamento(int img[][MAX_TAM], int W, int H, double Px, double Py) {  
    int i,j,**img2;
    /* cria uma matriz auxiliar */
    img2 = malloc(H * sizeof(int *));
    for(i = 0; i < H; i++)
        img2[i] = malloc(W * sizeof(int));
    /* inicia a matriz auxiliar com valores -1 para indicar onde ainda nao ha 
     * valor trasverido */
    for(i = 0; i < H; i++)
        for(j = 0; j < W; j++)
            img2[i][j] = -1;
    
    /* trasfere os pixels para a nova posição*/
    for(i = 0; i < H; i++)
        for(j = 0; j < W; j++){
            if( (i + (int)(Py * j)) < H && (j + (int)(Px * i)) < W )
                img2[i + (int)(Py * j)][j + (int)(Px * i)] = img[i][j];
        }
    
    /* copia os valores da matriz auxiliar */
    for(i = 0; i < H; i++)
        for(j = 0; j < W; j++){
            /* caso ainda não tenha valor coloca-se zero*/
            if(img2[i][j] == -1)
                img[i][j] = 0;
            else
                img[i][j] = img2[i][j];
        }
    
    /* libera a matriz auxiliar */    
    for(i = 0; i < H; i++)
        free(img2[i]);
    free(img2);
}


/* VOCE NAO DEVE ALTERAR A FUNCAO PRINCIPAL */
int main() {
    /* Matriz que armazena os pixels da imagem */
    int img[MAX_TAM][MAX_TAM]; 
    /* Atributos da imagem */
    int W, H, MaxV;
    /* Identificador do filtro a ser utilizado */
    int F;
    /* Parametro a ser passado para o cisalhamento */
    double Px, Py;

    /* Le a imagem */
    if (ler_pgm(img, &W, &H, &MaxV, &F, &Px, &Py) != 1) {
        printf("Error: nao foi possivel ler a imagem\n");
        return 0;
    }
 
    /* Seleciona o filtro */
    switch (F) {
        case 1:
            negativo(img, W, H, MaxV);
            break;
        case 2:
            rotacao180(img, W, H);
            break;
        case 3:
            detectaBorda(img, W, H, MaxV);
            break;
        case 4:
            cisalhamento(img, W, H, Px, Py);
            break;
    }

    /* Escreve a imagem */
    escrever_pgm(img, W, H, MaxV);

    return 0;
}