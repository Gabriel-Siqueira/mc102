/* Nome: Gabriel Henriques Siqueira
 * RA: 155446
 * Laboratorio 02b - Pedra - Papel - Tesoura - Lagarto - Spock */

#include<stdio.h>

int main(){
    int i,rod,jl,js,pl = 0,ps = 0;
/*recebe numero de rodadas (rod) e repete o o bloco do comando for para todas 
as rodadas*/
    scanf("%d",&rod);
    for(i = 1; i <= rod; i++){
/*caso de empate*/
        scanf("%d %d",&js,&jl);
        if (jl == js)
            printf("Empate\n");
        else{
/*todas as possibilidades com Leonard escolhentdo pedra exceto empate*/
            if (jl == 1){
                if(js == 2){
                    printf("Sheldon: Papel embrulha Pedra\n");
                    ps++;
                }else if(js == 3){
                    printf("Leonard: Pedra quebra Tesoura\n");
                    pl++;
                }else if(js == 4){
                    printf("Leonard: Pedra amassa Lagarto\n");
                    pl++;
                }else{
                    printf("Sheldon: Spock vaporiza Pedra\n");
                    ps++;
                }
/*todas as possibilidades com Leonard escolhentdo papel exceto empate*/
            }else if(jl == 2){
                if (js == 1){
                    printf("Leonard: Papel embrulha Pedra\n");
                    pl++;
                }else if(js == 3){
                    printf("Sheldon: Tesoura corta Papel\n");
                    ps++;
                }else if(js == 4){
                    printf("Sheldon: Lagarto come Papel\n");
                    ps++;
                }else{
                    printf("Leonard: Papel refuta Spock\n");
                    pl++;
                }
/*todas as possibilidades com Leonard escolhentdo tesoura exceto empate*/
            }else if(jl == 3){
                if (js == 1){
                    printf("Sheldon: Pedra quebra Tesoura\n");
                    ps++;
                }else if(js == 2){
                    printf("Leonard: Tesoura corta Papel\n");
                    pl++;
                }else if(js == 4){
                    printf("Leonard: Tesoura decepa Lagarto\n");
                    pl++;
                }else{
                    printf("Sheldon: Spock quebra Tesoura\n");
                    ps++;
                }
/*todas as possibilidades com Leonard escolhentdo lagarto exceto empate*/            
            }else if(jl == 4){
                if (js == 1){
                    printf("Sheldon: Pedra amassa Lagarto\n");
                    ps++;
                }else if(js == 2){
                    printf("Leonard: Lagarto come Papel\n");
                    pl++;
                }else if(js == 3){
                    printf("Sheldon: Tesoura decepa Lagarto\n");
                    ps++;
                }else{
                    printf("Leonard: Lagarto envenena Spock\n");
                    pl++;
                }
/*todas as possibilidades com Leonard escolhentdo spock exceto empate*/
            }else{
                if (js == 1){
                    printf("Leonard: Spock vaporiza Pedra\n");
                    pl++;
                }else if(js == 2){
                    printf("Sheldon: Papel refuta Spock\n");
                    ps++;
                }else if(js == 3){
                    printf("Leonard: Spock quebra Tesoura\n");
                    pl++;
                }else{
                    printf("Sheldon: Lagarto envenena Spock\n");
                    ps++;
                }
            }
        }
    }
/*placar*/    
    printf("Sheldon %d x %d Leonard\n",ps,pl);
    return 0;
}
