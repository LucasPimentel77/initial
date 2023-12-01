#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

void flush_in() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}

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

char *lerArquivo(const char *nomeArquivo, int *tamanho){
        
    FILE *arquivo = fopen(nomeArquivo, "r");
    
        if (arquivo == NULL) {
            fprintf(stderr, "Não foi possível abrir o arquivo %s\n", nomeArquivo);
            return NULL;
        }
    
        fseek(arquivo, 0, SEEK_END);
        *tamanho = ftell(arquivo);
        fseek(arquivo, 0, SEEK_SET);
    
        char *conteudo = (char *)malloc(*tamanho + 1);
    
        if (conteudo == NULL) {
            fprintf(stderr, "Erro ao alocar memória\n");
            fclose(arquivo);
            return NULL;
        }
    
        fread(conteudo, 1, *tamanho, arquivo);
        conteudo[*tamanho] = '\0';
    
       // fclose(arquivo);
    
        return conteudo;    
}

int tamanhoArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", nomeArquivo);
        return -1; // Valor de erro
    }

    fseek(arquivo, 0, SEEK_END);
    int tamanho = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    fclose(arquivo);

    return tamanho;
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
    char** gloss = calloc(256,sizeof(char*));
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

char* decodificar(char **gloss, unsigned char *txt, int tam){
    int i=0, j, k1=0, k2=0;
    char *concat = calloc(tam,sizeof(char));
    char *decodificado = calloc(strlen(txt),sizeof(char));
    while(txt[i]){
        concat[k1] = txt[i];
        k1++;
        concat[k1] = '\0';
        j = procura_no_glossario(gloss,concat);
        if(j >= 0){
            decodificado[k2] = j;
            strcpy(concat,"\0");
            k1=0;
            k2++;
        }
        i++;
    }
    decodificado[k2] = '\0';
    return decodificado;
}

char* converter_bytes(unsigned char *txt){
    int i;
    while(strlen(txt)%8 != 0){
        txt[strlen(txt)] = '0';
    }
    txt[strlen(txt)] = '\0';
    return txt;
}

int converter_decimal(const char *binario) {
    int decimal = 0;
    int base = 1;
    int tamanho = 0;

    while (binario[tamanho] != '\0') {
        tamanho++;
    }

    for (int i = tamanho - 1; i >= 0; i--) {
        if (binario[i] == '1') {
            decimal += base;
        }
        base *= 2;
    }

    return decimal;
}

void compactar(char **gloss, unsigned char *txt){
    int i, j=0, crt;
    char concat[256] = "zip_.txt", cat[9];
 
    FILE *compactado = fopen(concat, "w");
    
    if (compactado == NULL) {
            fprintf(stderr, "erro ao abrir o arquivo %s\n", concat);
            return;
    }
    for(int i=0; i<256; i++){
        if(strlen(gloss[i]) != 0){
            fprintf(compactado,"%c:%s;", i, gloss[i]);
        }
    }
    fprintf(compactado,"//\n%d\n",tamanho_string(gloss,txt));
    
    strcpy(txt,converter_bytes(txt));
    
    while(txt[j]){
        for(int k=0; k<8; k++){
            cat[k] = txt[j+k];
        }
           cat[8] = '\0';
        
        crt = converter_decimal(cat);
        fprintf(compactado,"%c",(char)crt);
        j+=8;    
    }
    printf("\n foi gerado um arquivo compactado com o nome %s\n",concat);
}

