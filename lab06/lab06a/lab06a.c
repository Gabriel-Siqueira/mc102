/* Nome: Gabriel Henriques Siqueira
 * RA: 155446
 * Laboratorio 06a - Fruit Crush Saga - Part I */

#include<stdio.h>

#define LIN 50
#define COL 51

int main(){
    char tab[LIN][COL];
    int  lin,col,linjog,coljog,i,j,pont = 1;
    /* recebe os valores referentes ao tamanho do tabuleiro e
     * a posiçao da linha e da coluna da jogada*/
    scanf("%d %d %d %d ",&lin,&col,&linjog,&coljog);
    /* le os valores do tabuleiro*/
    for(i = 0; i < lin; i++)
        scanf("%s",tab[i]);
    
    /* encontra as posiçoes afetadas as troca por X e conta a pontuação*/
    /* checa as posiçoes abaixo da jogada na coluna da jogada*/
    for(i = linjog; tab[i][coljog-1] == tab[linjog-1][coljog-1]; i++){
        pont++;
        tab[i][coljog-1] = 'X';
    }
    /* checa as posiçoes acima da jogada na coluna da jogada*/
    for(i = (linjog - 2); tab[i][coljog-1] == tab[linjog-1][coljog-1]; i--){
        pont++;
        tab[i][coljog-1] = 'X';
    }
    /* checa as posiçoes a direita da jogada na linha da jogada*/
    for(j = coljog; tab[linjog-1][j] == tab[linjog-1][coljog-1]; j++){
        pont++;
        tab[linjog-1][j] = 'X';
    }
    /* checa as posiçoes a esquerda da jogada na linha da jogada*/
    for(j = (coljog -2); tab[linjog-1][j] == tab[linjog-1][coljog-1]; j--){
        pont++;
        tab[linjog-1][j] = 'X';
    }
    /*coloca X na posição da jogada*/
    tab[linjog-1][coljog-1] = 'X';
    
    /*imprime o tabuleiro com X no lugar das posiçoes afetadas*/
    printf("Score: %d\n",pont*pont);
    for(i = 0; i < lin; i++)
        printf("%s\n",tab[i]);
    return 0;

