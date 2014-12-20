/* Nome: Gabriel Henriques Siqueira
 * RA: 155446
 * Laboratorio 09b - Concurso Público para Professor da UNICAMP */

#include<stdio.h>
#include<stdlib.h>

#define MEMBROS 5

double* cal_media(int cand, double **notas);
void print_medias(int cand, double *medias);
int** acha_preferencias(int cand, double **notas);
void print_preferencias(int cand, int **preferencias);
int acha_preferido(int **preferencias, int cand, double *medias, int *votos);
void classificacao(int **preferencias, int cand, double *medias,double **notas);
void troca_int(int *a, int *b);
void troca_double(double *a, double *b);
void selectionsort(double *vet1,int *vet2, int tam);

int main(){
    int    i,j,cand,**preferencias;
    double **notas,*medias;
    /* recebe o numero de candidatos */
    scanf("%d",&cand);
    /* cria a matriz que guardara as notas */
    notas = malloc(MEMBROS * sizeof(double *));
    for(i = 0; i < MEMBROS; i++)
        notas[i] = malloc(cand * sizeof(double));
    /* recebe as notas de cada candidato */
    for(i = 0; i < MEMBROS; i++)
        for(j = 0; j < cand; j++)
            scanf("%lf",&notas[i][j]);
  
    /* calcula e imprime as medias */
    medias = cal_media(cand,notas);
    print_medias(cand,medias);
    printf("\n");
    
    /* encontra e imprime as preferencias */
    preferencias = acha_preferencias(cand,notas);
    print_preferencias(cand,preferencias);
    printf("\n");
    
    /* descobre e imprime a classificaçao */
    classificacao(preferencias,cand,medias,notas);
    
    /* libera vetores e matrizes utilizados */
    for(i = 0; i < MEMBROS; i++)
        free(preferencias[i]);
    free(preferencias);
    for(i = 0; i < MEMBROS; i++)
        free(notas[i]);
    free(notas);
    free(medias);
    
    return 0;
}

/* calcula as medias */
double* cal_media(int cand, double **notas){
    int i,j;
    double *medias;
    /* cria vetor para guardar as medias e o zera */
    medias = malloc(cand * sizeof(double));
    for(i = 0; i < cand; i++)
        medias[i] = 0;
    /* calcula as medias de cada nota */
    for(j = 0; j < cand; j++){
        for(i = 0; i < MEMBROS; i++)
            medias[j] += notas[i][j];
        medias[j] /= MEMBROS;
    }
    return medias;
}

/* imprime as medias */
void print_medias(int cand, double *medias){ 
    int i;
    printf("Nota Media:");
    for(i = 0; i < cand; i++)
        printf(" %.1f",medias[i]);
    printf("\n");
}

/* encontra as preferencias */
int** acha_preferencias(int cand, double **notas){
    int **preferencias,i,j;
    /* cria matriz para guardar as preferencias */
    preferencias = malloc(MEMBROS * sizeof(int *));
    for(i = 0; i < MEMBROS; i++)
        preferencias[i] = malloc(cand * sizeof(int));
    
    for(i = 0; i < MEMBROS; i++){
        /* coloca o numero dos candidatos na matriz de preferencias na 
         * mesma ordem da matriz de notas */
        for(j = 0; j < cand; j++)
           preferencias[i][j] = j;
        /* ordena esta linha de candidatos das matrizes de notas e de 
        preferencias por nota (começando da mais alta) */
        selectionsort(notas[i], preferencias[i], cand);
    }
    return preferencias;
}

/* imprime as preferencias*/
void print_preferencias(int cand, int **preferencias){
    int i,j;
    printf("Preferencia:\n"); 
    for(i = 0; i < MEMBROS; i++){
        printf("Membro %d:",i + 1);
        for(j = 0; j < cand; j++)
            printf(" %d",preferencias[i][j] + 1);
        printf("\n");
    }
}

/* descobre e imprime a classificaçao */
void classificacao(int **preferencias, int cand, double *medias,double **notas){
    int *votos,preferido,k,i,j;
    /* cria vetor para guardar o numero de votos */
    votos = malloc(cand * sizeof(int));
    
    printf("Classificacao:");
    /* descobre e imprime o primeiro colocado */
    preferido = acha_preferido(preferencias,cand,medias,votos);
    printf(" %d",preferido);

    /* descobre e imprime demais colocados*/
    for(k = 1; k < cand; k++){
        /* remove as informações do ultimo candidato que foi classificado*/
        for(i = 0; i < MEMBROS; i++)
            for(j = 0; j < cand; j++)
                if(preferencias[i][j] == preferido-1)
                    notas[i][j] = -1;
        /* reordena a preferencia */
        for(i = 0; i < MEMBROS; i++)
            selectionsort(notas[i],preferencias[i],cand);
        /* encontra novo preferido */
        preferido = acha_preferido(preferencias,cand,medias,votos);
        printf(" %d",preferido);
    }
    printf("\n");
    free(votos);
}

int acha_preferido(int **preferencias, int cand, double *medias, int *votos){
    int preferido,i;
    /*inicia vetor dos votos*/
    for(i = 0; i < cand; i++)
        votos[i] = 0;
    /* conta o numero de votos(1 voto para o preferido de 
     * cada membro) de cada candidato */
    for(i = 0; i < MEMBROS; i++)
        votos[preferencias[i][0]]++;
    /* encontra o mais votado */
    preferido = 0;
    for(i = 1; i < cand; i++)
        if(votos[i] > votos[preferido])
            preferido = i;
        /* se empatar decide pela media */
        else if(votos[i] == votos[preferido])
            if(medias[i] > medias[preferido])
               preferido = i;
return preferido+1;
}
    
/* troca dois inteiros */
void troca_int(int *a, int *b) {
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

/* troca dois doubles */
void troca_double(double *a, double *b) {
    double aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

/* ordena os candidatos por nota(preferencia) */
void selectionsort(double *vet1, int *vet2, int tam){
    int i,inicio,maior;
    for(inicio = 0; inicio < tam; inicio++){
        maior = inicio;
        for(i = inicio+1; i < tam; i++){
            if(vet1[i] > vet1[maior])
                maior = i;
            /* em caso de empate o primeiro candidato a se inscrever fica na 
             * frente*/
            if(vet1[i] == vet1[maior] && vet2[i] < vet2[maior])
                maior = i;
        }
        troca_double(&vet1[maior], &vet1[inicio]);
        troca_int(&vet2[maior], &vet2[inicio]);
    }
}