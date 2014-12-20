/***********************************************************
 * Autor: Gabriel Henriques Siqueira
 * RA:    155446
 * Laboratorio 12a: CUT++
 *
 ***********************************************************/
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NOMEARQ 101
#define MAX_CAMPO   501

/* Prototipo das funcoes utilizadas pela main */
void gera_csv_reduzido(char fnamein[], char fnameout[]);

int main(int argc, char *argv[]) {
    char fnamein[MAX_NOMEARQ], fnameout[MAX_NOMEARQ];

    strcpy(fnamein, argv[1]);
    strcpy(fnameout, argv[2]);

    gera_csv_reduzido(fnamein, fnameout);

    return 0;
}

void gera_csv_reduzido(char fnamein[], char fnameout[]){
    FILE *arqin,*arqout;
    char teste,**mat_aux;
    int  num_cam = 1,num_cam_ped,*cam_ped;
    int  i,j,fim;
    
    /* abre arquivo de entrada para leitura */
    arqin = fopen(fnamein, "r");
    /* abre arquivo de saida para escrita */
    arqout = fopen(fnameout, "w");
    
    /* verivica se os arquivos foram abertos com sucesso */
    if(arqin && arqout){
        /* recebe numero de campo pedidos */
        scanf("%d",&num_cam_ped);
        /* cria vator para guardar os numeros dos campos pedidos */
        cam_ped = malloc(num_cam_ped * sizeof(int));
        /* recebe numeros dos campos pedidos */
        for(i = 0; i < num_cam_ped; i++)
            scanf("%d",&cam_ped[i]);
        /* descobre o numero de campos */
        do{
            fscanf(arqin,"%c",&teste);
            if(teste == ',')
                num_cam++;
        }while(teste != '\n');
        /* vota para o começo do arquivo */
        rewind(arqin);
        /* cria matriz para guardar cada linha da entrada */
        mat_aux = malloc(num_cam * sizeof(char*));
        for(i = 0; i < num_cam; i++)
            mat_aux[i] = malloc(MAX_CAMPO * sizeof(char));
        
        /* le primeiro caracter do arquivo*/
            fscanf(arqin,"%c",&teste);
        /* ateh acabar o arquivo */
        do{
            printf("EOF\n");
            /* guarda linha atual na matriz */
            for(j = 0; j < num_cam; j++){
                /* coloca na matriz o primeiro caracter da linha */
                mat_aux[j][0] = teste;
                i = 1;
                /* ateh acabar a leitura do campo */
                do{
                    fscanf(arqin,"%c",&mat_aux[j][i++]);
                }while(mat_aux[j][i-1] != ',' && mat_aux[j][i-1] != '\n');
                /* para testar se o arquivo acabou */
                fim = fscanf(arqin,"%c",&teste);
                    printf("EOF\n");
                /* indica fim da string correspondente ao campo */
                mat_aux[j][i-1] = '\0';
            }
            /* escreve no arquivo de saida a informação da linha atual 
             * correspondente aos campos pedidos */
            for(j = 0; j < num_cam_ped; j++){
                fprintf(arqout,"%s",mat_aux[cam_ped[j] - 1]);
                if(j != num_cam_ped - 1)
                    fprintf(arqout,",");
            }
            fprintf(arqout,"\n");
        }while(fim != EOF);   
        /* libera matriz e vetor utilizado */
        free(cam_ped);
        for(i = 0; i < num_cam; i++)
            free(mat_aux[i]);
        free(mat_aux);
    }
   
    /* fecha arquivos abertos */
    if(arqin)
        fclose(arqin);
    if(arqout)
        fclose(arqout);
}