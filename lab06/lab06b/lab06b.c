/* Nome: Gabriel Henriques Siqueira
 * RA: 155446
 * Laboratorio 06b - Fruit Crush Saga - Part II */

#include<stdio.h>

#define LIN 50
#define COL 51

int main(){
    char tab[LIN][COL];
    int  lin,col,linjog,coljog,i,j,k,afetacima,afetabaixo,numfru,pont = 0;
    int  afetaesq,afetadir,numjog,ponttot = 0;
    /* recebe os valores referentes ao tamanho do tabuleiro e
     * o numero de jogadas*/
    scanf("%d %d %d ",&lin,&col,&numjog);
    /* le os valores do tabuleiro*/
    for(i = 0; i < lin; i++)
        scanf("%s",tab[i]);
    
    /* recebe o valor de cada jogada e efetua a jogada para cada valor*/
    while(numjog--){
        scanf("%d %d",&linjog,&coljog);
        
        /* não conta pontuaçao se a posiçao escolhida esta vazia*/
        if(tab[linjog-1][coljog-1] != '.'){
            
            /* encontra as posiçoes afetadas altera o tabuleiro e conta a 
            * pontuação*/
            
            /* efetua as açoes no tabuleiro menos na coluna da jogada*/
            /* checa as posiçoes a direita da jogada na linha da jogada*/
            for(j = coljog; (tab[linjog-1][j] == tab[linjog-1][coljog-1]) && (j 
            <= col); j++)
                pont++;
            /* marca a coluna da fruta afetada mais a direita*/
            afetadir = --j;
            /* checa as posiçoes a esquerda da jogada na linha da jogada*/
            for(j = (coljog - 2); (tab[linjog-1][j] == tab[linjog-1][coljog-1]) 
            && (j >= 0); j--)
                pont++;
            /* marca a coluna da fruta afetada mais a esquerda*/
            afetaesq = ++j;
            /* marca o numero de frutas a serem retiradas*/
            numfru = afetadir - (afetaesq - 1);
            /* retira as frutas afetadas na linha da jogada(menos a da jogada) 
e 
    marca o ponto*/  
            for(j = afetadir; j >= afetaesq; j--){
                if(j != coljog-1){
                    for(i = (linjog-1); i > 0; i--)
                        tab[i][j] = tab[i-1][j];
                    tab[0][j] = '.';
                }
            }
            
            /* efetua as açoes na coluna da jogada*/
            /* checa as posiçoes abaixo da jogada na coluna da jogada*/
            for(i = linjog; (tab[i][coljog-1] == tab[linjog-1][coljog-1]) && (i 
            <= lin); i++)
                pont++;
            /* marca a linha da fruta afetada mais abaixo*/
            afetabaixo = --i;
            /* checa as posiçoes acima da jogada na coluna da jogada*/
            for(i = (linjog - 2); (tab[i][coljog-1] == tab[linjog-1][coljog-1]) 
            && (i >= 0); i--)
                pont++;
            /* marca a linha da fruta afetada mais acima*/
            afetacima = ++i;
            /* marca o numero de frutas a serem retiradas*/
            numfru = afetabaixo - (afetacima - 1);
            /* retira as frutas afetadas da coluna da jogada*/
            for(i = afetabaixo, k = (afetacima - 1);k >= 0; i--,k--){
                tab[i][coljog - 1] = tab[k][coljog - 1];
            }
            /* coloca ponto onde não ha frutas*/
            for(i = 0; i < numfru ;i++){
                tab[i][coljog - 1] = '.';
            }
            /* conta pontuação da posição da jogada e soma a pontuaçao da 
             * jogada a pontuação total*/
            pont++;
            ponttot += pont*pont;
            pont = 0;
        }
    }
   
    /*imprime a pontuação total e o tabuleiro alterado*/
    printf("Score: %d\n",ponttot);
    for(i = 0; i < lin; i++)
        printf("%s\n",tab[i]);
    return 0;
}
