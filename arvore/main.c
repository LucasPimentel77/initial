#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(){
    unsigned char *str = "naquela mesa ele sentava sempre";
    LinkedList lista;
    initLista(&lista);

    int *x = gerar_tabela(str);
    imprimir_tabela(x);

    listar(&lista,x);
    imprimir_lista(&lista);

    gerar_arvore(&lista);
    printf("\n arvore montada:\n\n");
    imprimir_arvore((&lista)->first, 0);

    int height = altura_arvore((&lista)->first);
    printf("altura: %d\n\n", height);


    char *txt = (char*)malloc(height*sizeof(char));
    char **gloss = iniciar_glossario(height);
    imprimir_glossario((&lista)->first, txt, height, gloss);
    
    char *txt_cod = codificar(gloss,str); 
    printf("texto codificado\n%s\n",txt_cod);
    
    decodificar(gloss,txt_cod, height);

    return 0;
}
