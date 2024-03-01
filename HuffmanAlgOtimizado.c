#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    void *item;
    struct node *next;
    int frequency;
    struct node *left;
    struct node *right;
}Node;

typedef struct priorityQueue{
    Node *head;
}Queue;

typedef struct element{
    int frequency;
    void *value;
}Element;

typedef struct hashTable{
    Element *table[256];
}HashTable;

Queue *createHuffmanQueue(){
    Queue *fila = (Queue*) malloc(sizeof(Queue));
    fila->head = NULL;
    return fila;
}

HashTable *createHashTable(){
    HashTable *newHashTable = (HashTable*) malloc(sizeof(HashTable));

    for(int i = 0; i < 256; i++){
        newHashTable->table[i] = NULL;
    }

    return newHashTable;
}

void put(HashTable *table, void *value){
    int h = *(unsigned char*) value;

    if(table->table[h] == NULL){
        table->table[h] = (Element*) malloc(sizeof(Element));
        table->table[h]->frequency = 1;
        table->table[h]->value = value;
    }
    else{
        table->table[h]->frequency++;
    }
}

int isEmpty(Queue *fila){
    return fila->head == NULL;
}

int isEmptyList(Node *head){
    return (head == NULL);
}

int max(int a, int b){
    if(a > b) return a;
    else return b;
}

long int fileSize(FILE *f){
    fseek(f, 0, SEEK_END);
    long int size = ftell(f);
    rewind(f);
    return size;
}

int compareBytes(void *item1, void *item2){
    return *(unsigned char*)item1 == *(unsigned char*)item2;
}

void enqueue(Queue *fila, void *item, int frequency){
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->item = item;
    newNode->frequency = frequency;
    newNode->left = NULL;
    newNode->right = NULL;

    if(isEmpty(fila) || frequency < fila->head->frequency){
        newNode->next = fila->head;
        fila->head = newNode;
    }
    else{
        Node *current = fila->head;

        while(current->next != NULL && current->next->frequency < frequency){
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }
}

void printHashTable(HashTable *table){
    for(int i = 0; i < 256; i++){
        if(table->table[i] != NULL){
            unsigned char c = *(unsigned char*) table->table[i]->value;
            printf("%c %d\n", c, table->table[i]->frequency);
        }
    }
}

void printQueue(Queue *fila){
    Node *aux = fila->head;
    int num = 0;

    while(aux != NULL){
        num += aux->frequency;
        unsigned char c = *(unsigned char*) aux->item;
        printf("%c\n", c);
        aux = aux->next;
    }
    printf("%d\n", num);
}

Node *createBinaryHuffmanTree(Node *huffmanList){
    while(huffmanList->next != NULL){
        char item = '\\';
        char *pItem = (char*) malloc(sizeof(char));
        *pItem = item;
        Node *newNode = (Node*) malloc(sizeof(Node));
        newNode->frequency = huffmanList->frequency + huffmanList->next->frequency;
        newNode->left = huffmanList;
        newNode->right = huffmanList->next;
        newNode->item = (void*) pItem;
        free(pItem);

        huffmanList = huffmanList->next->next;
    
        newNode->left->next = NULL;
        newNode->right->next = NULL;

        if(isEmptyList(huffmanList) || newNode->frequency <= huffmanList->frequency){
            newNode->next = huffmanList;
            huffmanList = newNode;
        }
        else{
            Node *current = huffmanList;

            while(current->next != NULL && current->next->frequency < newNode->frequency){
                current = current->next;
            }

            newNode->next = current->next;
            current->next = newNode;
        }
    }
    return huffmanList;
}

void printHuffmanTreePreOrder(Node *huffmanTree){
    if(!isEmptyList(huffmanTree)){
        char *p = (char*) huffmanTree->item;
        char c = *p;
        printf("%c ", c);
        printHuffmanTreePreOrder(huffmanTree->left);
        printHuffmanTreePreOrder(huffmanTree->right);
    }
}

int height(Node *huffmanTree){
    if(isEmptyList(huffmanTree)){
        return -1;
    }
    else{
        return 1 + max(height(huffmanTree->left), height(huffmanTree->right));
    }
}

int main(){
    Queue *huffmanList = createHuffmanQueue();
    HashTable *table = createHashTable();
    int (*equalsItem) (void*, void*) = compareBytes;
    FILE *f;

    printf("Por favor, insira o nome do arquivo que deseja compactar: ");

    char buffer[100];
    
    fgets(buffer, sizeof(buffer), stdin);
    int nomeTamanho = strlen(buffer)-1;
    char nome[nomeTamanho];

    for(int i = 0; i < nomeTamanho; i++){
        nome[i] = buffer[i];
    }

    f = fopen(nome, "rb");
    long int fSize = fileSize(f);

    if(f == NULL || fSize == 0){
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    for(int i = 0; i < fSize; i++){
        int byte = fgetc(f);
        void *byteP = malloc(sizeof(unsigned char));
        *((unsigned char*)byteP) = (unsigned char)byte;
        put(table, byteP);
    }

    for(int i = 0; i < 256; i++){
        if(table->table[i] != NULL){
            enqueue(huffmanList, table->table[i]->value, table->table[i]->frequency);
        }
    }

    printQueue(huffmanList);

    Node *huffmanTree = createBinaryHuffmanTree(huffmanList->head);

    printHuffmanTreePreOrder(huffmanTree);
    fclose(f);
    return 0;
}
