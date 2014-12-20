/* Nome: Gabriel Henriques Siqueira
 * RA: 155446
 * Laboratorio 13b - Fruit Crush Saga - Part III */

#include <stdio.h>
#include <stdlib.h>

int acha_afetadas(char **tab,int lin,int col,int lin_jog,int col_jog){
    int  pont = 1;
    char fruta;
    
    /* quarda tipo de fruta que deve ser afetada */
    fruta = tab[lin_jog-1][col_jog-1];
    /* indica posicao a ser eliminada */
    tab[lin_jog-1][col_jog-1] = 'x';
    
    /* verifica fruta a cima */
    if( (lin_jog > 1) && (fruta == tab[lin_jog-2][col_jog-1]) )
        pont += acha_afetadas(tab,lin,col,lin_jog - 1,col_jog);
    
    /* verifica fruta a direita */
    if( (col_jog < col) && (fruta == tab[lin_jog-1][col_jog]) )
        pont += acha_afetadas(tab,lin,col,lin_jog,col_jog + 1);

    /* verifica fruta a esquerda */
    if( (col_jog > 1) && (fruta == tab[lin_jog-1][col_jog-2]) )
        pont += acha_afetadas(tab,lin,col,lin_jog,col_jog - 1);
    
    /* verifica fruta a baixo */
    if( (lin_jog < lin) && (fruta == tab[lin_jog][col_jog-1]) )
        pont += acha_afetadas(tab,lin,col,lin_jog + 1,col_jog);  
  
    return pont;
}   

/* efetua as mudacas do efeito gravidade no tabuleiro */
void gravidade(char **tab, int lin, int col){
    int i,j,fim,in;
    /* acha posicoes a serem removidas */
    for(i = 0; i < lin; i++)
        for(j = 0; j < col; j++){
            if(tab[i][j] == 'x'){
                /* acha posicoes a serem removidas logo abaixo da encontrada */
                for(fim = i+1; fim < lin && tab[fim][j] == 'x'; fim++);
                /* remove frutas de in a fim */
                for(fim--,in = i - 1; in >= 0 && tab[in][j] != '*'; fim--,in--)
                    tab[fim][j] = tab[in][j];
                /* coloca pontos */
                while(fim >= 0 && tab[fim][j] != '*')
                    tab[fim--][j] = '.';
            }
        }
}
                  
/* realisa uma jogada alterando o tabuleiro e retornando a 
 * pontuacao */
int jogada(char **tab,int lin,int col){
    /* pontuacao da jogada */
    int pont;
    /* linha e coluna da jogada */
    int lin_jog,col_jog;
    
    /* recebe linha e coluna da jogada */
    scanf("%d %d",&lin_jog,&col_jog);
    
    /* não muda nada se a posicao da jogada esta vazia ou com 
    *bloco de gelo*/
    if(tab[lin_jog-1][col_jog-1] == '.' || 
        tab[lin_jog-1][col_jog-1] == '*')
        return 0;
    
    /* encontra as posicoes afetadas */
    pont = acha_afetadas(tab,lin,col,lin_jog,col_jog);
    
    /* altera o tabuleiro */
    gravidade(tab,lin,col);
    
    /* retorna pontuacao da jogada */
    return pont*pont;
}
                  
int main(){
    /* tabuleiro */
    char **tab;
    /* total de linhas e de colunas*/
    int  lin,col;
    /* variaveis para loop */
    int i;
    /* pontuacao e numero de jogadas*/
    int pont = 0,num_jog;
    
    /* recebe os valores referentes ao tamanho do tabuleiro e
    * o numero de jogadas*/
    scanf("%d %d %d ",&lin,&col,&num_jog);
    /* aloca matriz que representa o tabuleiro */
    tab = malloc(lin * sizeof(char*));
    for(i = 0; i < lin; i++)
        tab[i] = malloc((col+1) * sizeof(char));
    /* le os valores do tabuleiro*/
    for(i = 0; i < lin; i++)
        scanf("%s",tab[i]);
    
    /* efetua jogadas */
    while(num_jog--){
        pont += jogada(tab,lin,col);
    }
    
    /*imprime a pontuação total e o tabuleiro alterado*/
    printf("Score: %d\n",pont);
    for(i = 0; i < lin; i++)
        printf("%s\n",tab[i]);
    /* libera matriz */
    for(i = 0; i < lin; i++)
        free(tab[i]);
    free(tab);
    return 0;
}
