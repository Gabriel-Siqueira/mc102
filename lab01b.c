/* Nome: Gabriel Henriques Siqueira
 * RA: 155446
 * Laboratorio 01b - notas do vestubular */

#include<stdio.h>

#define MEDIA NP = ((( N - M) * 100) / DP) + 500;

int main()
{   
    int    A,NMO;
    double Pcg,Pin,Ppo,Pma,Pch,Pcn,Ncg,Mcg,DPcg,Nin,Min,DPin,Npo,Mpo,DPpo;
    double Nma,Mma,DPma,Nch,Mch,DPch,Ncn,Mcn,DPcn,NPcg,NF,DP,N,M,NP;
    double NPin,NPpo,NPma,NPch,NPcn;
    /*Recebendo A=(codigo de area do curso de primeira opçao)
    NMO=(nota media de opçao)
    Pi=(pesos)
    Ncg,Mcg,DPch=(nota,media e desvio padrao referente a
    conhecimentos gerais)*/ 
    scanf("%d %d",&A,&NMO);
    scanf("%lf %lf %lf %lf %lf %lf",&Pcg,&Pin,&Ppo,&Pma,&Pch,&Pcn);
    scanf("%lf %lf %lf",&Ncg,&Mcg,&DPcg);
    /*Calculando nota padronisada de primeira fase*/
    DP = DPcg;
    N  = Ncg;
    M  = Mcg;
    MEDIA
    NPcg = NP;
    /*checando se o candidato passou*/
    if(NPcg >= 550)
    {   
        /*informações acerca das demais provas*/
        scanf(" %lf %lf %lf",&Nin,&Min,&DPin);
        scanf(" %lf %lf %lf",&Npo,&Mpo,&DPpo);
        scanf(" %lf %lf %lf",&Nma,&Mma,&DPma);
        scanf(" %lf %lf %lf",&Nch,&Mch,&DPch);
        scanf(" %lf %lf %lf",&Ncn,&Mcn,&DPcn);
        /*Calculando notas padronisadas de primeira fasee nota final*/
        DP = DPin;
        N  = Nin;
        M  = Min;
        MEDIA
        NPin = NP;
        DP = DPpo;
        N  = Npo;
        M  = Mpo;
        MEDIA
        NPpo = NP;
        DP = DPma;
        N  = Nma;
        M  = Mma;
        MEDIA
        NPma = NP;
        DP = DPch;
        N  = Nch;
        M  = Mch;
        MEDIA
        NPch = NP;
        DP = DPcn;
        N  = Ncn;
        M  = Mcn;
        MEDIA
        NPcn = NP;
        NF = ( NPcg*Pcg + NPin*Pin + NPpo*Ppo + NPma*Pma + NPch*Pch + NPcn*Pcn) / (Pcg + Pin + Ppo + Pma + Pch + Pcn);
        /*imprimindo notas e grupo*/   
        printf("Primeira Fase: %.1f\n",NPcg);
        printf("Segunda Fase: %.1f\n",NF);
        if (((A == 1) && ( NPma >= NMO ) && ( NPcn >= NMO )) || (( A==2 ) && ( NPpo >= NMO ) && ( NPch >= NMO )) || ((A == 3) && ( NPcn >= NMO )))
            printf("Grupo 1\n");
        else
            printf("Grupo 2\n");   
    } 
    else
        printf("Primeira Fase: %.1f\n",NPcg);
    return 0;
}
