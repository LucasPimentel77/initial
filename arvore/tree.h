#ifndef TREE_H
#define TREE_H

typedef struct Node{
    int freq;
    unsigned char caractere;
    struct Node *next;
    struct Node *left;
    struct Node *right;
}Node;

typedef struct LinkedList{
    Node *first;
    int size;
}LinkedList;

int* gerar_tabela(unsigned char *str);
void imprimir_tabela(int *tab);
void initLista(LinkedList *lista);
void inserir_ordenado(LinkedList *lista, Node *novo);
Node* remove_inicio(LinkedList *lista);
void listar(LinkedList *lista, int *tab);
void imprimir_lista(LinkedList *lista);
void gerar_arvore(LinkedList *lista);
void imprimir_arvore(Node *no, int size);
void gerar_dicionario(Node *no, char *txt, int alt);
int altura_arvore(Node *raiz);

#endif
