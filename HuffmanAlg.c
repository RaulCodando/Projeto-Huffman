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

int compareBytes(void *item1, void *item2){
    return (*(unsigned char*) item1 == *((unsigned char*) item2));
}

int isEmpty(Node *head){
    return (head == NULL);
}

int isIntheList(Node *head, void *item, int (*compareBytes) (void*, void*)){
    while(head != NULL){
        if((*compareBytes)(item, head->item)) return 1;
        head = head->next;
    }
    return 0;
}

Node *addElements(Node *head, void *item, int (*compareBytes) (void*, void*)){
    Node *newNode = (Node*) malloc(sizeof(Node));
    Node *start = head;

    if(isEmpty(head) || !isIntheList(head,item,compareBytes)){
        newNode->item = item;
        newNode->frequency = 1;
        newNode->next = head;
        return newNode;
    }
    
    while(head != NULL){
        if((*compareBytes)(item,head->item)){
            head->frequency++;
            break;
        }
        head = head->next;
    }

    return start;
}

void printHuffmanList(Node *head){
    while(head != NULL){
        void *item = head->item;
        printf("%c", item);
        printf("%d", head->frequency);
        head = head->next;
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

    for(int i = 0; i < nomeTamanho; i++){
        printf("%c", nome[i]);
    }
    
    f = fopen(nome, "rb");

    if(f == NULL){
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    int (*compareBytes) (void*, void*);
    return 0;
}
