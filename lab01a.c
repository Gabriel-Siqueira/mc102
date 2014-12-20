/* Nome: Gabriel Henriques Siqueira
 * RA: 155446
 * Laboratorio 01 - Calculo de media das notas do semestre */

#include<stdio.h>
#include<math.h>

int main()
{   
    double p1,p2,p3,l,ma,mh,mg,p;
    /* recebe notas*/
    scanf("%lf %lf %lf %lf",&p1,&p2,&p3,&l);
    /* calcula as medias */
    p  = (3 * p1 + 3 * p2 + 4 * p3) / 10;
    ma = (p + l) / 2;
    mh = (2 * p * l) / (p + l);
    mg = sqrt(p * l);
    /* imprime resultados */
    printf("Media aritmetica: %.1f\nMedia harmonica: %.1f\n",ma,mh);
    printf("Media geometrica: %.1f\n",mg);
    return 0;
}