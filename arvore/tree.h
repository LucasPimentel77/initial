#ifndef TREE_H
#define TREE_H
#define TAMFALT 48

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
int altura_arvore(Node *raiz);
char** iniciar_glossario(int alt);
void imprimir_glossario(Node *no, char *txt, int alt, char **gloss);
char* codificar(char **gloss, unsigned char *txt);
void decodificar(char **gloss, unsigned char *txt, int tam);
void cria_linha_superior();
void cria_linha_inferior();
void cria_final_linha(int tam_linha, int tam_str);

#endif
