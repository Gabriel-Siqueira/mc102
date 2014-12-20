/***********************************************************
 * Autor: Gabriel Henriques Siqueira
 * RA:    155446
 * Laboratorio 14a: Gerenciador de memória
 *
 ***********************************************************/

#include<stdio.h>

/* aloca memoria retorna 0 se a alocacao se memoria acobou 1 se continua*/
int aloca_mem(int *situacao, int livre){
    /* guarda o comando recebido I, D ou # */
    char comando;
    /* recebe o comando */
    scanf(" %c",&comando);
    /* se acabaram os pedidos de alocacao */
    if(comando == '#')
        return 0;
    else if(*situacao == 1 || *situacao == -1){
        *situacao = -1;
        return 0;
    }
    /* se essa parte da memoria foi completamente alocada */
    else if(comando == 'I'){
        /* se ainda tem parte da memoria livre com o mesmo tamanho */
        if(livre)
            return 1;
        /* se nao a mais memoria livre com o mesmo tamanho */
        else{
            *situacao = 1;
            return aloca_mem(situacao,0);
        }
        /* se essa parte da memoria foi parcialmente alocada */
    }else{
        /* aloca primeira metade de matade ainda disponivel */
        *situacao = 0;
        if(aloca_mem(situacao,1)){
            /* aloca segunda metade de matade ainda disponivel */
            /* se ainda tem mais partes da memoria livre */
            if(livre)
                return aloca_mem(situacao,1);
            /* se nao a mais partes da memoria livre */
            else
                return aloca_mem(situacao,0);
        } else
            return 0;
    }
}

int main(){
    /* guarda situacao da alocacao de memoria 1 se foi completamente alocada, 0 
     * se foi parcialmente alocada, -1 se eh uma alocacao invalida*/
    int situacao = 0;
    /* aloca memoria*/
    aloca_mem(&situacao,0);
    /* se foi completamente alocada */
    if(situacao == 1)
        printf("Alocacao total\n");
    /* se foi parcialmente alocada */
    else if(situacao == 0)
        printf("Alocacao parcial\n");
    /* se foi uma alocacao invalida */
    else if(situacao == -1)
        printf("Alocacao invalida\n");
    return 0;
}