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

Node *createHuffmanLinkedList(){
    return NULL;
}

long int fileSize(FILE *f){
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    rewind(f);
    return size;
}

int isEmpty(Node *head){
    return (head == NULL);
}

Node *addElements(Node *head, void *item, int (*compareBytes) (void*, void*)){
    return NULL;
}

void printHuffmanList(Node *head){
}

void bubbleSort(void *array[], int size){
    for(int i = 0; i < size-1; i++){
        for(int j = 0; j < size-1-i; j++){
            if(*(unsigned char*)array[j] > *(unsigned char*)array[j+1]){
                void *aux = array[j];
                array[j] = array[j+1];
                array[j+1] = aux;
            }
        }
    }
}

int main(){
    Node *huffmanList = createHuffmanLinkedList();
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

    if(f == NULL){
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    void **bytes = malloc(sizeof(void)*fSize);

    for(int i = 0; i < fSize; i++){
        int byte = fgetc(f);
        printf("%c", byte);
        void *byteP = malloc(sizeof(unsigned char));
        *((unsigned char*)byteP) = (unsigned char)byte;
        bytes[i] = byteP;
    }

    bubbleSort(bytes,fSize);

    for(int i = 0; i < fSize; i++){
        void *p = bytes[i];
        unsigned char c = *(unsigned char*)p;
        peintf("%c \n", c);
    }

    fclose(f);
    return 0;
}
