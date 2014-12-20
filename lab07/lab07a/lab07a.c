/* Nome: Gabriel Henriques Siqueira
 * RA: 155446
 * Laboratorio 07a - The Voice - Blind Auditions */

#include<stdio.h>

#define MAX 100

void imprimetime(int time[MAX],int totmemtn){
    int i;
    if(totmemtn){
        for(i = 0; i < totmemtn; i++)
            printf(" %d",time[i]);
    }else{
        printf(" Nenhum participante");
    }
    printf("\n");
}

int main(){
    int numpar,time[4][MAX],infopar[8],totmemt[4],i,k;

    /* zera o indicador do total de membros de cada time*/
    for(i = 0; i < 4; i++)
        totmemt[i] = 0;
    
    /* recebe o numero de participantes*/
    scanf("%d",&numpar);
    
    /* verifica em que time ficou cada participante*/
    for(k = 1; k <= numpar; k++){
        /* recebe as informações do participante atual*/
        for(i = 0; i < 8; i++)
            scanf("%d",&infopar[i]);
        /* verifica se o treinador correspondente a primeira escolha do 
         * participante o escolheu*/ 
        if(infopar[infopar[4]-1])
            /* coloca o participante no time correspondende e incrementa o 
             * indicador do total de membros desse time*/
            time[infopar[4]-1][totmemt[infopar[4]-1]++] = k;
        /* verifica se o treinador correspondente a segunda escolha do 
         * participante o escolheu*/ 
        else if(infopar[infopar[5]-1])
            /* coloca o participante no time correspondende e incrementa o 
             * indicador do total de membros desse time*/
            time[infopar[5]-1][totmemt[infopar[5]-1]++] = k;
        /* verifica se o treinador correspondente a teceira escolha do 
         * participante o escolheu*/ 
        else if(infopar[infopar[6]-1])
            /* coloca o participante no time correspondende e incrementa o 
             * indicador do total de membros desse time*/
            time[infopar[6]-1][totmemt[infopar[6]-1]++] = k;
        /* verifica se o treinador correspondente a quarta escolha do 
         * participante o escolheu*/ 
        else if(infopar[infopar[7]-1])
            /* coloca o participante no time correspondende e incrementa o 
             * indicador do total de membros desse time*/
            time[infopar[7]-1][totmemt[infopar[7]-1]++] = k;
    }
    
    /* imprime os times*/
    printf("Time 1:");
    imprimetime(time[0],totmemt[0]);
    printf("Time 2:");
    imprimetime(time[1],totmemt[1]);
    printf("Time 3:");
    imprimetime(time[2],totmemt[2]);
    printf("Time 4:");
    imprimetime(time[3],totmemt[3]);
    
    return 0;
}