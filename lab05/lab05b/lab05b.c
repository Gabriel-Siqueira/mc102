/* Nome: Gabriel Henriques Siqueira
 * RA: 155446
 * Laboratorio 05b - Killing the Messenger */

#include<stdio.h>

#define MAXR 101

#define MAXO 26

int main(){
    int r,o,i,j,k,silenciado = 0;
    char rna[MAXR],oli[MAXO],aux;
    /*recebe a quantidade de bases nitrogenadas
     * no RNAm e no oligonucleotideo */
    scanf("%d %d",&r,&o);
    /*recebe as bases nitrogenadas do
     * RNAm e do oligonucleotideo*/
    scanf("%s %s",rna,oli);

    /*ajusta o aligonucleotideo para ele ser lido no sentdo correto*/
    for( i = 0; i < o/2; i++){
        aux = oli[o - 1 - i];
        oli[o - 1 - i] = oli[i];
        oli[i] = aux;
    }
    
    /*Troca as bases nitrogenadas do oligonucleotideo pelas complementates*/
    for( i = 0; i < o; i++){
        if( oli[i] == 'A'){
            oli[i] = 'U';
        }else if( oli[i] == 'U'){
            oli[i] = 'A';
        }else if( oli[i] == 'C'){
            oli[i] = 'G';
        }else{
            oli[i] = 'C';
        }
    }
    
    /*encontra se existir os trechos onde uma base nitrogenada
     * do RNAm é complementar a primeira base nitrogenada do oligonucleotídeio*/
    for(j = 0; j < (r -o +1) && !silenciado; j++){
        if(rna[j] == oli[0]){
            k = j++;
            /*Checa se as demais bases nitrogenadas são complementares*/
            for(i = 1; (i < o-1) && (oli[i] == rna[j]); i++, j++);
            if(oli[i] == rna[j])
                silenciado = 1;
            j = k;
        }
    }
    
    /*Avisa se o oligonucleotideo foi ou não silenciado, se foi
    * indica o posição onde isso ocorreu*/
    if(silenciado)
        printf("Silenciado em %d\n",k + 1);
    else
        printf("Nao silenciado\n");
    return 0;
}

