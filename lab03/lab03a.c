/* Nome: Gabriel Henriques Siqueira
 * RA: 155446
 * Laboratorio 03a - Composição de senha */

#include<stdio.h>

int main(){
    char nota;
    double compasso = 0;
    int digito = 0,fim = 0;
   
    do{
        do{
            
/*entrada do caracter*/
            scanf("%c",&nota);
            
/*checa se o caracter e uma das letras que representa as notas*/
            if (nota == 'A'){
                compasso += 1;
                digito += 1;
            }
            else if (nota == 'B'){
                compasso += 0.5;
                digito += 1;
            }
            else if (nota == 'C'){
                compasso += 0.25;
                digito += 1;
            }
            else if (nota == 'D'){
                compasso += 0.125;
                digito += 1;
            }
            else if (nota == 'E'){
                compasso += 0.0625;
                digito += 1;
            }
            else if (nota == 'F'){
                compasso += 0.03125;
                digito += 1;
            }
            else if (nota == 'G'){
                compasso +=0.015625;
                digito += 1;
            }
            else if (nota == 'H'){
                compasso += 0.0078125;
                digito += 1;
            }
            
/*checa se a leitura terminou*/
            else if (nota == '*'){
                fim = 1;
            }
        }while(nota != '\n');
        
/*checa se o compasso é valido*/       
        if (compasso != 1)
           digito = 0;
        
/*imprime o digito da senha*/
        if (!fim)
            printf("%d",digito);
        compasso = 0;
        digito = 0;
    }while(!fim);
    printf("\n");
    return 0;
}
