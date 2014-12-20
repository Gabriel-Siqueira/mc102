#include<stdio.h>
#include<stdlib.h>

/* Permutacao guarda o elemeto da permutacao e  os valores dos indices para 
 * transposcao de prefixo que retira o breakpoint breakpoint indica se ha 
 * ou nao breakpoint */
struct Permutacao {
    int elemento; 
    int indice1;
    int indice2;
    int breakpoint;
};
typedef struct Permutacao Permutacao;

void imprime(Permutacao *per, int tam_per){
/* imprime proxima permutacao */
printf("(");
for(i = 1; i < tam_per; i++) 
    printf("%d ",per[i].elemento);
printf("%d",per[tam_per].elemento);
printf(")\n");
}

/* acha breakpoints */
void acha_breakpoints(Permutacao *per,int tam_per){
    int i;
    /* procura por breakpoints */
    for(i = 1; i <= tam_per; i++)
        /* se for um breakpoint */
        if(per[i+1].elemento - per[i].elemento != 1)
            per[i].breakpoint = 1;
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

/* almentando strip com procimo elemento */
void acha_trasp1(Permutacao *per,int tam_per){
    int i,j;
    for(i = 0; i <= tam_per; i++)
        /* se for um breakpoint */
        if(per[i].breakpoint){
            /* acha procimo elemento da strip */
            for(j = i+1; j <= tam_per && 
            (per[j].elemento != per[i].elemento + 1); j++);
               if(j <= tam_per){
                   per[i].indice1 = i+1;
                   per[i].indice2 = j;
               }else{
                   /* se o breakpoint nao puder ser removido zera indice1 */
                   per[i].indice1 = 0;
               }
        }
}

/* almentando strip com elemento anterior coloca indices da permutação no 
 * indice zero*/
void acha_trasp2(Permutacao *per,int tam_per){
   int i;
   /* acha elemento anterior da strip */
   for(i = 0; per[i].elemento != per[1].elemento - 1; i++);
   per[0].indice2 = i+1;
   /* acha primeiro breakpoint da strip */
   for(i = 1; !per[i].breakpoint; i++);
        if(i < per[0].indice2)
            per[0].indice1 = i+1;
        else
            per[0].indice1 = 0;
}

/* acha trasposicao de perfixo mais leve */
int acha_maisleve(Permutacao *per,int tam_per){
    int i,min;
    /* concidera mais leve a trasposicao que almenta strip com elemento 
     * anterior se existir*/
    if(per[0].indice1)
        min = 0;
    else{
        /* se nao acha um breakpoint que possa se retirado */
        for(i = 1; !per[i].breakpoint || !per[i].indice1; i++);
        /* e concidera a transposição que o retira a menor */
        min = i;
    }
    /* checa os demais breakpoints que podem ser removidos pela trasposicao */
    for(i = 1; i <= tam_per; i++)
        if(per[i].breakpoint && per[i].indice1)
            /* acha menor indice2 (trasposicao de perfixo mais leve) */
            if(per[min].indice2 > per[i].indice2)
                min = i;
    return min;
}

/* realiza trasposicao de prefixo */
void trasp(Permutacao *per, int indice1,int indice2){
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

int main(){
    Permutacao *per;
    int tam_per,i,remove,peso = 0;
    
    /* le o tamanho da permutacao*/
    scanf("%d",&tam_per);
    /* cria um vetor para guardar a permutacao */
    per = malloc((tam_per + 2) * sizeof(Permutacao));
    /* zera breakpoint */
    for(i = 0; i <= tam_per+1; i++){
        per[i].breakpoint = 0;
    }
    /* le os elementos da permutacao */
    per[0].elemento = 0;
    per[tam_per + 1].elemento = tam_per+1;
    for(i = 1; i <= tam_per; i++)
        scanf("%d",&per[i].elemento);
    /* imprime a permutacao inicial */
    printf("(");
    for(i = 1; i < tam_per; i++)
        printf("%d ",per[i].elemento);
    printf("%d",per[tam_per].elemento);
    printf(")\n");

    /* acha breakpoints */
    acha_breakpoints(per,tam_per);
    
    /* ateh a permutacao estar ordenada */
    while(!ordenada(per,tam_per)){ 
        /* acha transposicoes de prefixo que removem breakpoints no caso ande 
         * aumentamos a strip com o proximo elemento */
        acha_trasp1(per,tam_per);
        /* acha transposicoes de prefixo que removem breakpoints no caso ande 
         * aumentamos a strip com o elemento anterior */
        acha_trasp2(per,tam_per);
        /* acha trasposicao de perfixo mais leve */
        remove = acha_maisleve(per,tam_per);
        /* indica que não tem mais o breakpoint que sera removido */
        if(remove)
            per[remove].breakpoint = 0;
        else{
            per[per[0].indice2-1].breakpoint = 0;
            /* se remover 2 breakpoint indica que não tem o outro tambem */
            if(per[per[0].indice1-1].elemento == per[per[0].indice2].elemento-1)
                per[per[0].indice1-1].breakpoint = 0;
        }
        /* soma ao peso total o peso da transposição que sera realizada */
        peso += per[remove].indice2 - 1;
        /* realiza trasposicao de prefixo */ 
        trasp(per, per[remove].indice1, per[remove].indice2);
        /* imprime proxima permutacao */
        printf("(");
        for(i = 1; i < tam_per; i++) 
            printf("%d ",per[i].elemento);
        printf("%d",per[tam_per].elemento);
        printf(")\n");
    }
    
    /* imprime peso total */
    printf("Peso: %d\n",peso);
    free(per);
    return 0;
}