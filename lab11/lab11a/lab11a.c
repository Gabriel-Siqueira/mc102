/* Nome: Gabriel Henriques Siqueira
 * RA: 155446
 * Laboratorio 11a - Copa do Mundo */

#include<stdio.h>
#include<string.h>

/* total de frupos */
#define TOT_G 8
/* numero de times por grupo */
#define TIMES_PG 4

/* guarda informaçoes de cada time */
struct Time{
    char nome[16];
    int pontos;
    int gols_marcados;
    int gols_sofridos;
};
typedef struct Time Time;

/* atualiza informações dos times */
void atu_info(Time grupos[][TIMES_PG], int i, int time1, int time2, int 
golst1, int golst2){
    /* atualiza numero de gols marcados e sofridos */
    grupos[i][time1].gols_marcados += golst1;
    grupos[i][time2].gols_marcados += golst2;
    grupos[i][time1].gols_sofridos += golst2;
    grupos[i][time2].gols_sofridos += golst1;
    /* atualiza pontuaçao */
    if(golst1 > golst2)
        grupos[i][time1].pontos += 3;
    else if (golst1 < golst2)
        grupos[i][time2].pontos += 3;
    else{
        grupos[i][time1].pontos++;
        grupos[i][time2].pontos++;
    }
}

/* troca de lugar duas variaveis do tipo Time */
void troca_Time(Time *t1, Time *t2){
    Time aux = *t1;
    *t1 = *t2;
    *t2 = aux;
}

/* ordena times de cada grupo de acordo com a classificaçao */
void ordena(Time grupos[]){
    int i,j,max;
    for(i = 0; i < TIMES_PG-1; i++){
        max = i;
        /* acha melhor colocado */
        for(j = i+1; j < TIMES_PG; j++){
            /* compara pontuaçao */
            if(grupos[j].pontos > grupos[max].pontos){
                max = j;
            /* se empatar compara o saldo de gols */
            }else if(grupos[j].pontos == grupos[max].pontos){
                if(grupos[j].gols_marcados - grupos[j].gols_sofridos > 
                grupos[max].gols_marcados - grupos[max].gols_sofridos){
                    max = j;
                /* se empatar compara os gols marcados */
                }else if(grupos[j].gols_marcados - grupos[j].gols_sofridos ==
                      grupos[max].gols_marcados - grupos[max].gols_sofridos){
                    if(grupos[j].gols_marcados > grupos[max].gols_marcados){
                        max = j;
                    /* se empatar desempata por ordem alfabetica */
                    }else if(grupos[j].gols_marcados == 
                        grupos[max].gols_marcados){
                        if(strcmp(grupos[j].nome,grupos[max].nome) < 0){
                            max = j;
                        }
                    }
            }
            }
        }
        /* troca de lugar duas variaveis do tipo Time */
        troca_Time(&grupos[i],&grupos[max]);
    }
}

int main(){
    int  i,j,k,golst1,golst2,time1,time2;
    Time grupos[TOT_G][TIMES_PG];
    char time_nome[16];
    /* zera informações dos times */
    for(i = 0; i < TOT_G; i++)
        for(j = 0; j < TIMES_PG; j++){
            grupos[i][j].pontos = 0;
            grupos[i][j].gols_marcados = 0;
            grupos[i][j].gols_sofridos = 0;
        }
        
    /* le informaçoes de cada partida e atualiza informaçoes dos times */
    for(i = 0; i < TOT_G; i++){
        /* Primeira vez que os nomes dos times aparecem */
        for(j = 0; j < TIMES_PG; j += 2){
            /* le os nomes e o placar */
            scanf("%s %d x %d %s",grupos[i][j].nome, &golst1,&golst2, 
            grupos[i][j+1].nome);
            /* atualiza informações dos times */
            atu_info(grupos,i,j,j+1,golst1,golst2);
        }
        
        /* depois que os nomes ja sao conhecidos */
        for(k = 0; k < 4; k++){
            /* acha primeiro time que que participou da partida */
            scanf("%s",time_nome);
            for(j = 0; strcmp(time_nome,grupos[i][j].nome); j++);
            time1 = j; 
            /* le placar */
            scanf("%d x %d",&golst1,&golst2);
            /* acha segundo time que que participou da partida */
            scanf("%s",time_nome);
            for(j = 0; strcmp(time_nome,grupos[i][j].nome); j++);
            time2 = j;
            /* atualiza informações dos times */
            atu_info(grupos,i,time1,time2,golst1,golst2);   
        }
    }
   
    /* imprime times de cada grupo de forma ordenada e suas informaçoes */
    for(i = 0; i < TOT_G; i++){
        printf("Grupo %c:\n",i+'A');
        /* ordena times de cada grupo de acordo com a classificaçao */
        ordena(grupos[i]);
        /* imprime informaçoes de cada time */
        for(j = 0; j < TIMES_PG; j++){
            printf("%-15s %3d %3d %3d %3d\n", grupos[i][j].nome, 
            grupos[i][j].pontos, grupos[i][j].gols_marcados, 
            grupos[i][j].gols_sofridos, 
            grupos[i][j].gols_marcados - grupos[i][j].gols_sofridos);
        }
        printf("\n");
    }
    
    /* define jogos das oitavas de final e os imprime*/
    printf("Oitavas de final:\n");
    for(i = 0; i < 8; i += 2){
        printf("%15s x %s\n", grupos[i][0].nome, grupos[i+1][1].nome);
        printf("%15s x %s\n", grupos[i+1][0].nome, grupos[i][1].nome);
    }
    return 0;
}
