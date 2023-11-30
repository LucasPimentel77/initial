#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int* gerar_tabela(unsigned char *str) {
    int i, tam = strlen((char*)str);
    int *tab = (int*)calloc(256, sizeof(int));

    for (i = 0; i < tam; i++) {
        tab[str[i]]++;
    }

    return tab;
}

void imprimir_tabela(int *tab) {
    printf("\ntabela de frequencia\n\n");
    for (int i = 0; i < 256; i++) {
        if (tab[i] != 0)
            printf("%d:'%c' -> %d\n",i , i, tab[i]);
    }
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
    printf("\nlista de caracteres ordenados!\n\n");
    Node *aux = lista->first;
    while(aux){
        printf("caractere: %c -> frequencia: %d\n",aux->caractere, aux->freq);
        aux=aux->next;
    }
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
    if(no->left == NULL && no->right == NULL){
        for(int i=1; i<size; i++)
            printf(" | ");
        printf("'%c'  size:%d\n", no->caractere,size);

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
void gerar_dicionario(Node *no, char *txt, int alt){
    char dir[alt], esq[alt];
    if(no->left == NULL && no->right == NULL){
        printf("'%c' = %s \n", no->caractere, txt);
    }
    else{
        strcpy(esq,txt);
        strcpy(dir,txt);

        strcat(esq,"0");
        strcat(dir,"1");

        gerar_dicionario(no->left, esq);
        gerar_dicionario(no->right, dir);
    }
} 
