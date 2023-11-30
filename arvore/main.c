#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(){
    unsigned char *str = "eu ja sofri por amar assim";
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


    char *txt = (char*)malloc(sizeof(char));
    gerar_dicionario((&lista)->first, txt, height);

    free(x);
    return 0;
}
