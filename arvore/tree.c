#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

void cria_linha_superior() {
    printf("\n ________________________________________________");
    printf("\n|                                                |");
}

void cria_linha_inferior() {
    printf("\n|________________________________________________|");
}

void cria_final_linha(int tam_linha, int tam_str) {
    int falt;
    while(tam_str < tam_linha) {
        printf("%c", 32);
        tam_str++;
    }
    printf("|");
}

int* gerar_tabela(unsigned char *str) {
    int i, tam = strlen((char*)str);
    int *tab = (int*)calloc(256, sizeof(int));

    for (i = 0; i < tam; i++) {
        tab[str[i]]++;
    }

    return tab;
}

void imprimir_tabela(int *tab) {
    int z;
    cria_linha_superior();
    printf("\n|            tabela de frequencia:               |");
    cria_linha_inferior();
    printf("\n|                                                |");
    printf("\n| ASCII | Caracter -> quantidade                 |");
    cria_linha_inferior();
    printf("\n|                                                |");
    for (int i = 0; i < 256; i++) {
        if (tab[i] != 0) {
            if(i>100) {
                printf("\n|  %d  |  '%c' -> %d",i , i, tab[i]);
                z=18;
            } else {
                printf("\n|  %d   |  '%c' -> %d",i , i, tab[i]);
                z=18;
            }
            cria_final_linha(TAMFALT, z);
        }
    }
    cria_linha_inferior();
    
    return;
}

void initLista(LinkedList *lista){
    lista->size = 0;
    lista->first = NULL;
}

void inserir_ordenado(LinkedList *lista, Node *novo){

        if(lista->size==0){
            novo->next = NULL;
            lista->first = novo;
        }else if(novo->freq < lista->first->freq){
            novo->next = lista->first;
            lista->first = novo;
        }else{
            Node *aux = lista->first;
            while(aux->next  && novo->freq >= aux->next->freq )
                aux = aux->next;
            novo->next = aux->next;
            aux->next = novo;
        }
        lista->size++;
}

Node* remove_inicio(LinkedList *lista){
    if(lista->size == 0){
        printf("nao e possivel remover lista vazia\n");
        return NULL;
    }
    Node *aux = lista->first;
    //free(&aux);
    lista->first = lista->first->next;
    aux->next = NULL;
    lista->size--;
    return aux;
} 

void listar(LinkedList *lista, int *tab){
    int i;
    for(i=0; i<256; i++)
        if(tab[i] > 0){
            Node *no = (Node *)malloc(sizeof(Node));
            no->caractere = i;
            no->freq = tab[i];
            no->left = NULL;
            no->right = NULL;
            inserir_ordenado(lista,no);
        }
}

void imprimir_lista(LinkedList *lista){
    if(lista->size == 0)
        printf("lista vazia!");
    cria_linha_superior();
    printf("\n|         lista de caracteres ordenados:         |");
    cria_linha_inferior();
    printf("\n|                                                |");
    Node *aux = lista->first;
    while(aux){
        printf("\n|        caractere: '%c' -> frequencia: %d         |",aux->caractere, aux->freq);
        aux=aux->next;
    }
    cria_linha_inferior();
}

void gerar_arvore(LinkedList *lista){

    while(lista->size >1){
        Node *T = (Node *)malloc(sizeof(Node));
        T->left = remove_inicio(lista);
        T->right = remove_inicio(lista);
        T->freq = T->left->freq + T->right->freq;
        T->caractere = '-';
        T->next = NULL;
        inserir_ordenado(lista,T);
    }
}

void imprimir_arvore(Node *no, int size){
    int z = 10;
    if(no->left == NULL && no->right == NULL){
        printf("\n|          ");
        for(int i=1; i<size; i++) {
            printf(" |");
        }
        printf("'%c' size:%d", no->caractere,size);
        cria_final_linha(TAMFALT-size-8, z+size);
    }
    else{
        imprimir_arvore(no->left, size + 1);
        imprimir_arvore(no->right, size + 1);
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int altura_arvore(Node *raiz) {
    if (raiz == NULL) {
        return 0;
    } else {
        int esquerda = altura_arvore(raiz->left);
        int direita = altura_arvore(raiz->right);
        return 1 + max(esquerda, direita);
    }
}

char** iniciar_glossario(int alt){
    int i;
    char** gloss = malloc(256 * sizeof(char*));
    for(i=0; i<256; i++){
        gloss[i] = calloc(alt,sizeof(char));
    }
    return gloss;
}

void imprimir_glossario(Node *no, char *txt, int alt, char** gloss){
    char dir[alt], esq[alt];
    int z;
    if(no->left == NULL && no->right == NULL){
        printf("\n|                   '%c' = %s", no->caractere, txt);
        z = strlen(txt);
        cria_final_linha(TAMFALT, z+25);
        strcpy(gloss[no->caractere],txt);
    }
    else{
        strcpy(esq,txt);
        strcpy(dir,txt);

        strcat(esq,"0");
        strcat(dir,"1");

        imprimir_glossario(no->left, esq, alt, gloss);
        imprimir_glossario(no->right, dir, alt, gloss);
    }
} 

int tamanho_string(char **gloss, unsigned char *txt){
    int i = 0, tam = 0;
    while(txt[i]){
        tam = tam + strlen(gloss[txt[i]]);
        i++;
    }
    return tam + 1;
}
char* codificar(char **gloss, unsigned char *txt){
    int i;
    char *codificado = calloc(tamanho_string(gloss,txt),sizeof(char));
    for(i=0; i<strlen(txt); i++){
        strcat(codificado,gloss[txt[i]]);
    }
    return codificado;
}
int procura_no_glossario(char **gloss, char *txt){
    int i;
    for(i=0; i<256; i++){
        if(strcmp(gloss[i],txt) == 0)
            return i;
    }
    return -1;
}

 decodificar(char **gloss, unsigned char *txt, int tam){
    int i=0, j, k=0;
    char *concat = calloc(tam,sizeof(char));
    while(txt[i]){
        concat[k] = txt[i];
        k++;
        concat[k] = '\0';
        j = procura_no_glossario(gloss,concat);
        if(j >= 0){
            printf("%c",(char)j);
            strcpy(concat,"\0");
            k=0;
        }
        i++;
    }
}
