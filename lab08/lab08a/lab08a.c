/* Nome: Gabriel Henriques Siqueira
 * RA: 155446
 * Laboratorio 08a -Amigos dos amigos */

#include<stdio.h>
#include<stdlib.h>

#define MAX 100

int main(){
    int totus,us,rel[MAX][MAX],i,j,a;
    int suginter[MAX],sug[MAX],numsug = 0,min;
    /* recebe o total de usuarios e o numero do usuario a ser analisado */
    scanf("%d %d",&totus,&us);
    /* recebe a matriz de relacionamentos */
    for(i = 0; i < totus; i++)
        for(j = 0; j < totus; j++){
            scanf("%d",&rel[i][j]);
        }
        
        /* encontra os amigos de usuario sendo analisado */
        for(a = 0; a < totus; a++){
            if(rel[us][a] && a != us){
                /* checa se o amigo do usuario analisado tem algum amigo que o 
                 * usuario sendo analisado nao tem */ 
                for(j = 0; j < totus; j++)
                    if(rel[us][j] != rel[a][j] && !(rel[us][j])){
                        /* guarda os sugestões ainda não encontradas */
                        for(i = 0; i < numsug && suginter[i] != j; i++);
                        if(i == numsug)
                            suginter[numsug++] = j;
                    }
            } 
        }
        
    /* encontra o menor valor de sugestao */
    min = suginter[0];
    for(i = 1; i < numsug; i++)
        if(suginter[i] < min)
            min = suginter[i];
    sug[0] = min;
    /* coloca em ordem crescente as sugestoes */
    for(j = 1; j < numsug; j++){
        min = totus;
        for(i = 0; i < numsug; i++)
            if(suginter[i] < min && suginter[i] > sug[j-1]){
                min = suginter[i];
            }
        sug[j] = min;
    }
        
    /* caso haja sugestao de novos amigos imprime essa sugestao*/
    if(numsug){
        printf("Sugestao de amigos:");
        for(i = 0; i < numsug; i++)
            printf(" %d",sug[i]);
        printf("\n");
    }else{
        printf("Sem sugestao de novos amigos\n");
    }
    return 0;
}
