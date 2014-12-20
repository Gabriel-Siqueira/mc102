/* Laboratorio 14b - Whiteworse
 * Autor: Gabriel Henriques Siqueira ra: 155446
 * e-mail: gabriel._gabriel@hotmail.com
 */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Tamanho maximo do nome do titular */
#define MAXNOME 21
/* Tamanho maximo do nome dos arquivos de entrada/saida */
#define MAXNOMEARQ 101
/* Numero maximo de contas */
#define MAXCONTAS 20
/* Numero maximo de transacoes */
#define MAXTRANS 40
/* Valor da taxa de deposito em conta com saldo negativo */
#define TAXA 5.00

/* Conta
 * ag = numero da agencia
 * cc = numero da conta corrente
 * titular = Nome do titular da conta
 * saldo = Saldo da conta
 */
struct Conta {
    int ag;
    int cc;
    char titular[MAXNOME];
    double saldo;
};

typedef struct Conta Conta;

/* Transacao
 * tipo - 'D' para Depositos e 'S' para Saques
 * ag - Numero da agencia
 * cc - Numero da conta corrente
 * valor - Valor da operacao
 */
struct Transacao {
    char tipo;
    int ag;
    int cc;
    double valor;
};

typedef struct Transacao Transacao;

/* le informacoes dos arquivos */
Conta* le_arquivo1(char *nomeArqConta, int *quant_cont){
    FILE *arq_conta;
    Conta *contas;
    
    /* abre arquivo */
    arq_conta = fopen(nomeArqConta,"rb");
    
    /* se o arquivo tiver sido aberto com sucesso */
    if(arq_conta){
        /* recebe quatidade de contas */
        fread(quant_cont, sizeof(int),1,arq_conta);
        /* cria vetor para as contas */
        contas = malloc(*quant_cont * sizeof(Conta));
        /* recebe informacoes das contas */
        fread(contas, sizeof(Conta),*quant_cont,arq_conta);
        
        /* fecha o arquivo */
        fclose(arq_conta);
    }
    return contas;
}

Transacao* le_arquivo2(char *nomeArqTrans, int *quant_trans){
    FILE *arq_trans;
    Transacao *transacoes;
    
    /* abre arquivo */
    arq_trans = fopen(nomeArqTrans,"rb");
    
    /* se o arquivo tiver sido aberto com sucesso */
    if(arq_trans){
        /* recebe quatidade de transacoes */
        fread(quant_trans, sizeof(int),1,arq_trans);
        /* cria vetor para as transacoes */
        transacoes = malloc(*quant_trans * sizeof(Transacao));
        /* recebe informacoes das transacoes */
        fread(transacoes, sizeof(Transacao),*quant_trans,arq_trans);
        
        /* fecha o arquivo */
        fclose(arq_trans);
    }
    return transacoes;
}
        
/* acha a conta onde a transacao sera realisada */
int busca_conta(Conta *contas, int quant_cont, int qual_ag, int qual_cc) {
    int i;
    for (i = 0; i < quant_cont; i++) {
        if (contas[i].ag == qual_ag)
            if(contas[i].cc == qual_cc)
                return i;
        }
        return -1;
} 
 
/* executa transacoes */
void ex_tras(Conta *contas,Transacao *transacoes,int quant_cont,
     int quant_trans){
    int qual_conta,valida,i;
    
    for(i = 0; i < quant_trans; i++){
        /* acha a conta onde a transacao sera realisada */
        qual_conta = busca_conta(contas, quant_cont, transacoes[i].ag, 
        transacoes[i].cc);
        /* verifica se a conta foi encontrada */
        if(qual_conta != -1){
            /* verifica qual sera a transacao */
            if(transacoes[i].tipo == 'S'){
                /* verifica se o saque pode ser realisado */
                if(contas[qual_conta].saldo > 0 && (contas[qual_conta].saldo - 
                transacoes[i].valor) >= -100.0){
                    valida = 1;
                    /* realisa o saque */
                    contas[qual_conta].saldo -= transacoes[i].valor;
                    /* verifica se havera taxa de abertura de credito */
                    if(contas[qual_conta].saldo < 0)
                        contas[qual_conta].saldo -= 5.0;
                }else
                    valida = 0;
            }else{
                /* realisa o deposito */
                contas[qual_conta].saldo += transacoes[i].valor;
                valida = 1;
            }
            /* se for uma transacao valida */
            if(valida)
                /* inprime transacao */
                printf("T%d: %c %d %d %.2f\n",i,transacoes[i].tipo, 
                transacoes[i].ag,transacoes[i].cc,transacoes[i].valor);
        }
    }
}

/* escreve no arquivo de saida */
void escreve_arquivo(char *nomeArqSaida, Conta *contas, int quant_cont){
    FILE *arq_saida;
    
    /* abre arquivo */
    arq_saida = fopen(nomeArqSaida,"wb");
    
    /* se o arquivo tiver sido aberto com sucesso */
    if(arq_saida){
        /* escreve quatidade de contas */
        fwrite(&quant_cont, sizeof(int),1,arq_saida);
        /* escreve informacoes das contas */
        fwrite(contas, sizeof(Conta),quant_cont,arq_saida);
   
        /* fecha o arquivo */
        fclose(arq_saida);
    }
}
 
int main(int argc, char **argv) {
    /* Nome do arquivo binario com as contas */
    char nomeArqConta[MAXNOMEARQ];
    /* Nome do arquivo binario com as transacoes */
    char nomeArqTrans[MAXNOMEARQ];
    /* Nome do arquivo binario de saida */
    char nomeArqSaida[MAXNOMEARQ];
    /* informacoes contas */
    Conta *contas;
    /* informacoes das transacoes */
    Transacao *transacoes;
    /* quantidade de contas */
    int quant_cont;
    /* quantidade de transacoes */
    int quant_trans;
    
    /* Obtendo o nome dos arquivos */
    strcpy(nomeArqConta, argv[1]);
    strcpy(nomeArqTrans, argv[2]);
    strcpy(nomeArqSaida, argv[3]);
    
    /* le informacoes dos arquivos */
    contas = le_arquivo1(nomeArqConta,&quant_cont);
    transacoes =  le_arquivo2(nomeArqTrans,&quant_trans);
    
    /* executa transacoes */
    ex_tras(contas, transacoes, quant_cont, quant_trans);
    
    /* escre no arquivo de saida */
    escreve_arquivo(nomeArqSaida, contas, quant_cont);
    /* libera vetores */
    free(contas);
    free(transacoes);
    return 0;
}
