#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    void *item;
    struct node *next;
    int frequency;
    struct node *left;
    struct node *right;
    int size;
}Node;

int max(int a, int b){
    if(a > b) return a;
    else return b;
}

Node *createHuffmanLinkedList(){
    return NULL;
}

long int fileSize(FILE *f){
    fseek(f, 0, SEEK_END);
    long int size = ftell(f);
    rewind(f);
    return size;
}

int isEmpty(Node *head){
    return (head == NULL);
}

int compareBytes(void *item1, void *item2){
    return *(unsigned char*)item1 == *(unsigned char*)item2;
}

Node *addElements(Node *head, void *item, int (*compareBytes) (void*, void*)){
    if(isEmpty(head) || !compareBytes(head->item, item)){
        Node *newNode = (Node*) malloc(sizeof(Node));
        if(isEmpty(head)) newNode->size = 1;
        else newNode->size = head->size + 1;
        newNode->item = item;
        newNode->next = head;
        newNode->frequency = 1;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    else if(compareBytes(head->item, item)){
        head->frequency++;
        return head;
    }
}

void printHuffmanList(Node *head){
    int num = 0;

    while(head != NULL){
        num += head->frequency;
        void *p = head->item;
        unsigned char c = *(unsigned char*)p;
        printf("%c\n", c);
        head = head->next;
    }

    printf("%d\n", num);
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

Node *bubbleSortList(Node *lista, int tamanho) {
    if (tamanho <= 1) 
        return lista;

    Node *temp;

    for (int i = 0; i < tamanho - 1; i++) {
        Node *current = lista;
        Node *nextNode = lista->next;

        for (int j = 0; j < tamanho - 1 - i; j++) {
            if (current->frequency > nextNode->frequency) {
                if (current == lista) 
                    lista = nextNode;
                else { 
                    Node *prev = lista;
                    while (prev->next != current)
                        prev = prev->next;
                    prev->next = nextNode;
                }

                current->next = nextNode->next;
                nextNode->next = current;

                temp = current;
                current = nextNode;
                nextNode = temp;
            }
            current = current->next;
            nextNode = nextNode->next;
        }
    }
    return lista;
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

        if(isEmpty(huffmanList) || newNode->frequency <= huffmanList->frequency){
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
    if(!isEmpty(huffmanTree)){
        char *p = (char*) huffmanTree->item;
        char c = *p;
        printf("%c ", c);
        printHuffmanTreePreOrder(huffmanTree->left);
        printHuffmanTreePreOrder(huffmanTree->right);
    }
}

int height(Node *huffmanTree){
    if(isEmpty(huffmanTree)){
        return -1;
    }
    else{
        return 1 + max(height(huffmanTree->left), height(huffmanTree->right));
    }
}

int main(){
    Node *huffmanList = createHuffmanLinkedList();
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

    void **bytes = malloc(sizeof(void*)*fSize);

    for(int i = 0; i < fSize; i++){
        int byte = fgetc(f);
        void *byteP = malloc(sizeof(unsigned char));
        *((unsigned char*)byteP) = (unsigned char)byte;
        bytes[i] = byteP;
    }

    bubbleSort(bytes,fSize);

    for(int i = 0; i < fSize; i++){
        huffmanList = addElements(huffmanList, bytes[i], equalsItem);
    }

    int size = huffmanList->size;

    huffmanList = bubbleSortList(huffmanList, size);

    printHuffmanList(huffmanList);

    Node *huffmanTree = createBinaryHuffmanTree(huffmanList);

    printHuffmanTreePreOrder(huffmanTree);

    fclose(f);
    return 0;
}
