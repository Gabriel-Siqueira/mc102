#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* registro que guardara as informaçoes de cada campo */
struct Article{
    char title[503];
    char author[503];
    char journal[103];
    int  volume;
    int  number;
    char pages[53];
    int  year;
    int  pos;
};
typedef struct Article Article;

/* recebe linha em branco e procima linha escrita as descarta */
void descarta_lin(){
    char lixo[161];
    /* retira linhas em branco */
    fgets(lixo,1,stdin);
    fgets(lixo,1,stdin);
    /* retira linha do label */
    scanf("%s",lixo);
}

/* le conteudo de um campo */
int le_campo(Article *entradas,int i){
    char teste;
    int j;
    scanf(" %c",&teste);
    /* se a entrada article tiver terminado */
    switch(teste){
        /* caso seja o campo title */
        case 't':
            /* acha onde o titulo começa */
            do{
                scanf("%c",&teste);
            }while(teste != '{');
            /* le o titulo */
            fgets(entradas[i].title,503,stdin);
            /* remove '}' e ',' */
            for(j = 0; entradas[i].title[j] != '}'; j++);
            entradas[i].title[j] = '\0';
            break;
        /* caso seja o campo author */
        case 'a':
            /* acha onde o nome do autor começa */
            do{
                scanf("%c",&teste);
            }while(teste != '{');
            /* le o nome do autor */
            fgets(entradas[i].author,503,stdin);
            /* remove '}' e ',' */
            for(j = 0; entradas[i].author[j] != '}'; j++);
            entradas[i].author[j] = '\0';
            break;
        /* caso seja o campo journal */
        case 'j':
            /* acha onde o nome da revista/periodico começa */
            do{
                scanf("%c",&teste);
            }while(teste != '{');
            /* le o nome da revista/periodico */
            fgets(entradas[i].journal,103,stdin);
            /* remove '}' e ',' */
            for(j = 0; entradas[i].journal[j] != '}'; j++);
            entradas[i].journal[j] = '\0';
            break;
        /* caso seja o campo volume */
        case 'v':
            /* le volume */
            scanf("olume = {%d},",&entradas[i].volume);
            break;
        /* caso seja o campo number */
        case 'n':
            /* le numero */
            scanf("umber = {%d},",&entradas[i].number);
            break;
        /* caso seja o campo pages */
        case 'p':
            /* acha onde o numero de paginas começa */
            do{
                scanf("%c",&teste);
            }while(teste != '{');
            /* le o numero de paginas */
            fgets(entradas[i].pages,53,stdin);
            /* remove '}' e ',' */
            for(j = 0; entradas[i].pages[j] != '}'; j++);
            entradas[i].pages[j] = '\0';
            break;
        /* caso seja o campo year */
        case 'y':
            /* le ano */
            scanf("ear = {%d},",&entradas[i].year);
            break;
        default:
            return 0;
    }
    return 1;
}

/* troca de posiçao duas variaveis do tipo Article */
void troca_Article(Article *a,Article *b){
    Article aux = *a;
    *a = *b;
    *b = aux;
}

/* organiza as entradas por ordem lexicografica do campo title*/
void ordena_ent(Article *entradas,int num_ent){
    int i,j,min;
    for(i = 0; i < num_ent-1; i++){
        min = i;
        for(j = i+1; j < num_ent; j++)
            /* encontra a lexicograficamente menor */
            if(strcmp(entradas[j].title,entradas[min].title) < 0)
                min = j;
            /* se empatar pega a que foi dada primeiro */
            else if(strcmp(entradas[j].title,entradas[min].title) == 0)
                if(entradas[j].pos < entradas[min].pos)
                    min = j;
        /* troca de posiçao duas variaveis do tipo Article */
        troca_Article(&entradas[i],&entradas[min]);
    }
}

int main(){
    int num_ent,i;
    Article *entradas;
    /* recebe o numero de entradas article que serao fornecidas */
    scanf("%% %d",&num_ent);
    /* cria vetor para guardar as entradas */
    entradas = malloc(num_ent * sizeof(Article));
    /* indica que campos que podem não ser usados nao sao usados*/
    for(i = 0; i < num_ent; i++){
        entradas[i].volume = -1;
        entradas[i].number = -1;
        entradas[i].pages[0] = 'n';
    }
    /* recebe cada entrada tipo article */
    for(i = 0; i < num_ent; i++){
        /* descarta linha em branco e linha do lebel*/
        descarta_lin();
        /* recebe o conteudo de cada campo */
        while(le_campo(entradas,i));
        /* marca posiçao em que a entrada foi fornecida */
        entradas[i].pos = i;
    }
   
    /* organiza as entradas*/
    ordena_ent(entradas,num_ent);
    
    /* imprime entradas formatadas */
    for(i = 0; i < num_ent; i++){
        printf("%s, %s, %s,",entradas[i].title,entradas[i].author,  
        entradas[i].journal); 
        /* se tiver informado o volume */
        if(entradas[i].volume != -1)
            printf(" %d,",entradas[i].volume);
        /* se tiver informado o numero */
        if(entradas[i].number != -1)
            printf(" %d,",entradas[i].number);
        /* se tiver informado as paginas */
        if(entradas[i].pages[0] != 'n')
            printf(" %s,",entradas[i].pages);
        printf(" %d.",entradas[i].year);
        printf("\n\n");
    }
        
    /* libera entradas*/
    free(entradas);
    return 0;
}