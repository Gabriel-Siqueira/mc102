/* Nome: Gabriel Henriques Siqueira
 * RA: 155446
 * Laboratorio 04b - Semanada */

#include<stdio.h>

#define MAX 100

int main(){

    int dig, aretirar, maior, posmaior, valmin, valmax;
    int i, j, k=0, num[MAX], res[MAX-1];
    
    /*recebe os valores referentes ao numero de digitos
     *e a quantidade de digitos que devem ser retirados*/ 
    scanf("%d %d",&dig,&aretirar);
    /*recebe os digitos*/
    for(i = 0; i < dig; i++){
        scanf("%d",&num[i]);
    }
    
    /*define o valor maximo e minimo do entervalo em que 
     * se pode procurar pelo maior numero*/
    valmax = aretirar;
    valmin = 0;
    
    /*seleciona o maior numero do intervalo permitido
     * ateh selecionar a quantidade de  numeros necessaria*/ 
    for(j = 0; j < (dig - aretirar); j++){
        maior = num[valmin];
        posmaior = valmin;
        for(i = (valmin + 1); i <= valmax; i++){
            /*quando encontra um numero maior salva o numero e sua posição*/
            if(num[i] > maior){
                maior = num[i];
                posmaior = i;
            }
        }
        /*redefine o intervalo para procura do maior numero*/
        valmin = posmaior + 1;
        valmax++;
        /*salva o maior numero encontrado*/
        res[k++] = maior;
    }
    
    /*imprime o maior valor*/
    printf("Maior valor: ");
    for(i = 0; i < k; i++){
        printf("%d",res[i]);
    } 
    printf("\n");
    return 0;
}
