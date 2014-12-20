/***********************************************************
 * Autor: Gabriel Henriques Siqueira
 * RA:    155446
 * Laboratorio 15b: DON'T PANIC - Part II
 *
 ***********************************************************/

#include<stdio.h>
#include<stdlib.h>

/* Permutacao guarda o elemeto da permutacao e se ha ou nao breakpoint */
struct Permutacao {
    int elemento;
    int breakpoint;
};
typedef struct Permutacao Permutacao;

void imprime(Permutacao *per, int tam_per){
    int i;
    /* imprime proxima permutacao */
    printf("(");
    for(i = 0; i <= tam_per; i++) 
        printf("%d ",per[i].elemento);
    printf("%d",per[tam_per+1].elemento);
    printf(")\n");
}

/* acha breakpoints e limitante inferior*/
int acha_breakpoints(Permutacao *per,int tam_per){
    int i,inferior = 0;
    /* procura por breakpoints */
    for(i = 1; i <= tam_per; i++)
        /* se for um breakpoint */
        if(per[i+1].elemento - per[i].elemento != 1){
            per[i].breakpoint = 1;
            /* verifica se eh o limitante inferior */
            if(per[i].elemento > inferior)
                inferior = per[i].elemento;
        }else
            per[i].breakpoint = 0;
        return inferior;
}

/*verifica se a permutacao esta ordenada*/
int ordenada(Permutacao *per,int tam_per){
    int i;
    /* procura por breakpoints */
    for(i = 0; i <= tam_per && (per[i+1].elemento - per[i].elemento == 1); i++);
    if(i <= tam_per)
        return 0;
    else
        return 1;
}

/* acha transposicões de prefixo que removem breakpoints */

/* quando almentando strip com procimo elemento */
void acha_transp1(Permutacao *per, int *indice1,int *indice2){
    int i,j;
    /* acha ultimo elemento da strip */
    for(i = 1; !per[i].breakpoint; i++);
    /* acha elemento que remove breakpoint */
    for(j = i+1; per[j].elemento != per[i].elemento + 1; j++);
    *indice1 = i+1;
    *indice2 = j;
}

/* quando almentando strip com elemento anterior */
void acha_transp2(Permutacao *per, int tam_per,int *indice1,int *indice2){
    int i;
    /* acha elemento anterior da strip */
    for(i = 0; per[i].elemento != per[1].elemento - 1; i++);
    *indice2 = i+1;
    /* acha primeiro breakpoint da strip */
    for(i = 1; !per[i].breakpoint; i++);
    *indice1 = i+1;
    /* se tiver uma transposicao que remove 2 breakpoints usa ela*/
    for(i = i; i < *indice2; i++)
        if(per[i].elemento == per[*indice2].elemento - 1)
            *indice1 = i+1;
}

/* acha transposicao de perfixo mais leve */
int acha_maisleve(int t1_indice2, int t2_indice2){
    /* nao ha transposicao 2 */
    if(t2_indice2 == 1)
        return 1;
    else if(t2_indice2 <= t1_indice2)
        /* transposicao 2 deve ser realisada */
        return 2;
    else
        /* transposicao 1 deve ser realisada */
        return 1;
}

/* realiza transposicao de prefixo */
void transp(Permutacao *per, int indice1,int indice2){
    int i,j;
    Permutacao *aux;
    aux = malloc((indice1-1) * sizeof(Permutacao));
    for(i = 1; i < indice1; i++)
        aux[i-1] = per[i];
    for(i = 1; i <= indice2-indice1; i++)
        per[i] = per[i + indice1-1];
    for(i = indice2-indice1+1, j = 0; i < indice2; i++, j++)
        per[i] = aux[j];
    free(aux);
}

int acha_superior(Permutacao *per,int tam_per){
    /* indices da transposicao que aumenta a strip com o proximo elemento */
    int t1_indice1,t1_indice2;
    /* indices da transposicao que aumenta a strip com o elemento anterior */
    int t2_indice1,t2_indice2;
    /* idica qual a transposicao mais leve */
    int remove;
    /* peso total de todas as transposicoes */
    int peso = 0;
    
    /* ateh a permutacao estar ordenada */
    while(!ordenada(per,tam_per)){
        /* acha transposicao de prefixo que removem breakpoint no caso onde: */
        
        /* aumenta a strip com o proximo elemento */
        acha_transp1(per,&t1_indice1,&t1_indice2);
        
        /* aumenta a strip com o elemento anterior */
        acha_transp2(per,tam_per,&t2_indice1,&t2_indice2);
        
        /* acha transposicao de perfixo mais leve */
        remove = acha_maisleve(t1_indice2,t2_indice2);

        /* se a primeira transposicao for a mais leve */
        if(remove == 1){
            /* indica que nao tem mais o breakpoint que sera removido */
            per[t1_indice1-1].breakpoint = 0;
        
            /* soma ao peso total o peso da transposicao que sera realizada */
            peso += t1_indice2 - 1;

            /* realiza transposicao de prefixo */
            transp(per, t1_indice1, t1_indice2);
            
        /* se a segunda transposicao for a mais leve */    
        }else{
            /* indica que nao tem mais o breakpoint que sera removido */
            per[t2_indice2-1].breakpoint = 0;
            /* se remover 2 breakpoints indica que nao tem o outro tambem */
            if(per[t2_indice1-1].elemento == per[t2_indice2].elemento-1)
                per[t2_indice1-1].breakpoint = 0;
            
            /* soma ao peso total o peso da transposicao que sera realizada */
            peso += t2_indice2 - 1;
            
            /* realiza transposicao de prefixo */
            transp(per, t2_indice1, t2_indice2);
        }
    }
    return peso;
}

/* acha peso minimo para ordenacao */
int acha_peso_minimo(Permutacao *per,int tam_per,int superior,int peso){
    /* indices das transposicoes */
    int indice1,indice2;
    /* limitante inferior */
    int inferior;
    
    /* se ja estiver ordenada */
    if(ordenada(per,tam_per)){
        return 0;
    }else{
        /* encontra limitante inferior */
        inferior = acha_breakpoints(per, tam_per);
        /* se com essa permutacao puder chegar ao peso minimo */
        if(peso + inferior <= superior){
            /* gera todos os possiveis indices 2 */
            for(indice2 = 3; indice2 <= tam_per+1; indice2++){
                peso += indice2 - 1;
                /* verifica se o peso nao ultrapassa a limitante superior ou o 
                 * peso minimo*/
                if(peso <= superior)
                    /* gera todos os possiveis indices 1 para cada indice 2 */
                    for(indice1 = 2; indice1 < indice2; indice1++){
                        /* realisa trasposicao */
                        transp(per, indice1, indice2);
                        /* continua a ordenacao */
                        return indice2 + acha_peso_minimo(per,tam_per, 
                        superior,peso);
                        /* desfaz trasposicao */
                        transp(per, (indice2-indice1+1), indice2);
                    }
                peso -= indice2 - 1;
            }
        }
    }
}
                      
int main(){
    /* para o vetor que guardara a permutacao */
    Permutacao *per;
    /* tamanho da permutacao */
    int tam_per;
    /* limitante superior e inferior */
    int superior, inferior;
    /* peso minimo */
    int peso_min = 0;
    /* variavel para controle do loop */
    int i;
    /* para o vetor auxiliar */
    Permutacao *aux;
    
    /* le o tamanho da permutacao */
    scanf("%d",&tam_per);
    /* cria um vetor para guardar a permutacao */
    per = malloc((tam_per + 2) * sizeof(Permutacao));
    
    /* le os elementos da permutacao */
    per[0].elemento = 0;
    per[tam_per + 1].elemento = tam_per+1;
    for(i = 1; i <= tam_per; i++)
        scanf("%d",&per[i].elemento);
    
    /* cria vetor auxiliar */
    aux = malloc((tam_per+2) * sizeof(Permutacao));
    
    /* coloca elementos no vetor auxiliar */
    for(i = 0; i <= tam_per+1; i++)
        aux[i].elemento = per[i].elemento;
    
    /* acha breakpoints e limitante inferior */
    inferior = acha_breakpoints(aux, tam_per);
    
    /* acha limitante superior */
    superior = acha_superior(aux, tam_per);
    
    /* libera vetor */
    free(aux);
    
    /* se os limitantes superior e inferior coincidirem ja eh o peso minimo */
    if(superior == inferior)
        peso_min = superior;
    else
        /* acha peso minimo */
        peso_min = acha_peso_minimo(per,tam_per,superior,0);
    
    /* imprime limitante inferior */
    printf("Limitante inferior: %d\n",inferior);
    /* imprime peso minimo */
    printf("Peso: %d\n",peso_min);
    /* imprime limitante superior */
    printf("Limitante superior: %d\n",superior);
    
    /* lebera vetor da permutacao */
    free(per);
    return 0;
}