/* Nome: Gabriel Henriques Siqueira
 * RA: 155446
 * Laboratorio 07b - Modern Word Search */

#include<stdio.h>

#define PALAVRA 26 
#define LIN 50
#define COL 51

/* descobre qual caracter especial pode ser usado '#'(se for vogal) ou '%'(se 
 * for consoante)*/
char vogoucon(char letra){
    if(letra == 'a' || letra == 'e' || letra == 'i' || letra == 'o' ||     
        letra == 'u')
        return '#';
    else
        return '%';
}

/* verifica se o caracter equivale a letra */
int carcorr(int i, int j, int k, char caresp, char tab[][COL], char palavra[]){
    return tab[i][j] == palavra[k] || tab[i][j] == '_' || tab[i][j] == caresp;
}

int main(){
    int  lin,col,ocor = 0,i,j,k,l;
    char palavra[PALAVRA],tab[LIN][COL],res[LIN][COL],caresp;
    /* recebe o numero de linhas e colunas do caça palavras e a palavra a ser 
     * encontrada*/
    scanf("%d %d %s",&lin,&col,palavra);
    /* recebe o tabuleiro do caça palvras*/
    for(i = 0; i < lin; i++)
        scanf("%s",tab[i]);
    /* inicia a matriz do resultado com '.' para posteriormente colocar as 
     * palavras destacadas*/
    for(i = 0; i < lin; i++){
        res[i][col] = '\0';
        for(j = 0; j < col; j++)
            res[i][j] = '.';
    }
    
    /* procura as ocorrencias da palavra as conta e destaca as palavras*/
    for(i = 0; i < lin; i++)
        for(j = 0; j < col; j++){
            /* encontra a primeira letra ou um caracter especial que pode 
             * substuitui-la*/
            caresp = vogoucon(palavra[0]);
            if ( carcorr(i,j,0,caresp,tab,palavra) ){
                /* verifica se os demais caracteres na horizontal compoe a 
                 * palavra*/
                caresp = vogoucon(palavra[1]);
                for( k = 1;( (j+k) < col ) && (palavra[k] != '\0') &&
                    carcorr(i,j+k,k,caresp,tab,palavra); k++){
                    caresp = vogoucon(palavra[k+1]);
                }
                if (palavra[k] == '\0'){
                    /* destaca a palavra */
                    for( l = 0; palavra[l] != '\0'; l++ )
                        res[i][j + l] = tab[i][j + l];
                    ocor++;
                }
                /* verifica se os demais caracteres na vertical compoe a 
                 * palavra*/
                caresp = vogoucon(palavra[1]);
                for( k = 1; ( (i+k) < lin ) && (palavra[k] != '\0') &&
                carcorr(i+k,j,k,caresp,tab,palavra); k++){
                    caresp = vogoucon(palavra[k+1]);
                }
                if (palavra[k] == '\0'){
                    /* destaca a palavra */
                    for( l = 0; palavra[l] != '\0'; l++ )
                        res[i + l][j] = tab[i + l][j];
                    ocor++;
                }
                /* verifica se os demais caracteres na diagonal compoe 
                 * a palavra*/
                caresp = vogoucon(palavra[1]);
                for( k = 1;( (j+k) < col && (i+k) < lin ) && (palavra[k] != 
                '\0') && carcorr(i+k,j+k,k,caresp,tab,palavra); k++){
                    caresp = vogoucon(palavra[k+1]);
                }
                if (palavra[k] == '\0'){
                /* destaca a palavra */
                for( l = 0; palavra[l] != '\0'; l++ )
                    res[i + l][j + l] = tab[i + l][j + l];
                ocor++;
                }
            }
        }
        
        /* imprime o numero de ocorrencias*/
        printf("%s %d\n",palavra,ocor);
        /* imprime as ocorrencias destacadas*/
        for(i = 0; i < lin; i++)
            printf("%s\n",res[i]);
        
        return 0;
}