#include <stdio.h>
#include <stdlib.h>
#include "tree.h"


int main(){

        unsigned char *str;

        char arquivo[20];
        printf("qual o nome do arquivo para compactar? ");
        scanf("%s",arquivo);
        flush_in();
        
        int tam_arquivo = tamanhoArquivo(arquivo);
        str = lerArquivo(arquivo,&tam_arquivo);
        char **gloss;
        LinkedList lista;
        initLista(&lista);
    
        int options, max_options = 4, min_options = 1;
    
        int height;
    
        do {
            printf("\n ________________________________________________");
            printf("\n|                                                |");     
            printf("\n|       Escolha uma das seguintes opções:        |");
            printf("\n|________________________________________________|");
            printf("\n|                                                |");
            printf("\n| [1] Imprimir tabela                            |");
            printf("\n| [2] Imprimir lista                             |");
            printf("\n| [3] Gerar arvore                               |");
            printf("\n| [4] Gerar dicionario                           |");
            printf("\n| [5] Fechar programa                            |");
            printf("\n|________________________________________________|\n");
            scanf("%d", &options);
            
            switch(options){
                
                case 1:
                    
                    int *x = gerar_tabela(str);
                    imprimir_tabela(x);
    
    
                break;
                
                case 2:
                    
                    listar(&lista,x);
                    imprimir_lista(&lista);
    
                break;
               
                case 3:
                    
                    printf("\n ________________________________________________");
                    printf("\n|                                                |");
                    printf("\n|                     Arvore:                    |");
                    printf("\n|________________________________________________|");
                    printf("\n|                                                |");
                    gerar_arvore(&lista);
                    imprimir_arvore((&lista)->first, 0);
                    height = altura_arvore((&lista)->first);
                    printf("\n|                                                |");
                    printf("\n|                    altura: %d                  |", height-1);
                    printf("\n|________________________________________________|");
    
                break;
    
                case 4:
                    printf("\n ________________________________________________");
                    printf("\n|                                                |");
                    printf("\n|                   Glossario :                  |");
                    printf("\n|________________________________________________|");
                    printf("\n|                                                |");
                    char *txt = (char*)malloc(sizeof(char));
                    gloss = iniciar_glossario(height);
                    imprimir_glossario((&lista)->first, txt, height, gloss);
                    printf("\n|________________________________________________|");
    
                break;
    
            }
    
        }while(options <= max_options && options >= min_options);
        
        
        char *txt_cod = codificar(gloss,str); 
        printf("TEXTO CODIFICADO\n%s\n\n",txt_cod);
        
        char *txt_dec = decodificar(gloss,txt_cod, height);
        printf("\nTEXTO DECODIFICADO\n%s\n\n",txt_dec);
        
        compactar(gloss, txt_cod);


    return 0;
}
