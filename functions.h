#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estrutura de um nó de uma fila de prioridade, que mais tarde será usada
//para criar uma árvore binária
typedef struct node{
    void *item;
    struct node *next;
    int frequency;
    struct node *left;
    struct node *right;
}Node;

//Estrutura de uma fila de prioridade
typedef struct priorityQueue{
    Node *head;
}Queue;

//Estrutura de um elemento da tabela de frequências dos bytes
typedef struct element{
    int frequency;
    void *value;
}Element;

//Estrutura da tabela de frequências dos bytes
typedef struct hashTable{
    Element *table[256];
}HashTable;

//Cria uma fila de prioridades vazia
Queue *createHuffmanQueue(){
    //Aloca dinamicamente um ponteiro para uma nova fila de prioridades
    Queue *fila = (Queue*) malloc(sizeof(Queue));
    fila->head = NULL; //Define o início da fila como nulo
    return fila; //Retorna a fila
}

//Cria a tabela de frequências de elementos
HashTable *createHashTable(){
    //Aloca dinamicamente uma nova tabela
    HashTable *newHashTable = (HashTable*) malloc(sizeof(HashTable));

    //Passa por todos os elementos da tabela, definindo-os como nulo
    for(int i = 0; i < 256; i++){
        newHashTable->table[i] = NULL;
    }

    return newHashTable;
}

//Adiciona um novo item na tabela de frequências, atualizando sua respectiva frequência 
void put(HashTable *table, void *value){
    //Usa o valor do byte para criar o ídice a ser acessado na tabela
    int h = *(unsigned char*) value; 

    //Se o índice acessado for vaizo, adiciona o valor e define sua frequência como 1
    //Se o índice não for vazio, apenas incrementa a frequência do elemento naquele índice
    if(table->table[h] == NULL){
        //Aloca dinamicamente um novo elemento o adiciona no índice acessado na tabela
        table->table[h] = (Element*) malloc(sizeof(Element));
        //Define a frequência desse elemento como 1
        table->table[h]->frequency = 1;
        //Define o valor do elemento como a variável "value"
        table->table[h]->value = value;
    }
    else{
        //Incrementa a frequência do elemento
        table->table[h]->frequency++;
    }
}

//Verifica se uma fila de prioridade é vazia
int isEmpty(Queue *fila){
    return fila->head == NULL;
}

//Verifica se uma árvore de huffman é vazia
int isEmptyList(Node *head){
    return (head == NULL);
}

//Retorna o maior dentre de 2 número
int max(int a, int b){
    if(a > b) return a;
    else return b;
}

//Retorna o tamanho de um arquivo
long int fileSize(FILE *f){
    fseek(f, 0, SEEK_END); //Vai até o final do arquivo
    long int size = ftell(f); //Salva a posição do final do arquivo em "size"
    rewind(f); //Volta ao início do arquivo
    return size;
}

//Adiciona um item à fila de prioridade
void enqueue(Queue *fila, void *item, int frequency){
    //Aloca dinamicamente um novo nó
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->item = item; //Define o item do novo nó como "item"
    newNode->frequency = frequency; //Define a frequência do novo nó com "frequency"
    newNode->left = NULL; //Define a esquerda di novo nó como nulo
    newNode->right = NULL; //Define a direita di novo nó como nulo

    /*
    Se a fila estiver vazia ou a frequência do item a ser adicionado for menor
    que a frequência do primeiro nó da fila, adiciona o novo nó ao início da fila,
    se não, procura a posição apropriada para adicioná-lo
    */
    if(isEmpty(fila) || frequency < fila->head->frequency){
        //Define o next do novo nó como o primeiro nó da fila
        newNode->next = fila->head;
        //O início da fila passa a ser o novo nó
        fila->head = newNode;
    }
    else{
        //Cria um nó auxiliar que começa sendo igual ao primeiro nó da fila
        Node *current = fila->head;

        /*
        Enquanto o next de current for diferente de nulo e a frequência do nó
        seguinte ao current for menor que a frequência do nó a ser adicionado,
        current é atualizado para o nó seguinte a ele
        */
        while(current->next != NULL && current->next->frequency < frequency){
            current = current->next;
        }

        //O next do novo nó passa a ser o next de current
        newNode->next = current->next;
        //O next de current passa a ser o novo nó
        current->next = newNode;
    }
}

//Imprime na tela todos os elementos da tabela de frequências como caracteres
void printHashTable(HashTable *table){
    for(int i = 0; i < 256; i++){
        if(table->table[i] != NULL){
            unsigned char c = *(unsigned char*) table->table[i]->value;
            printf("%c %d\n", c, table->table[i]->frequency);
        }
    }
}

//Imprime todos os itens da fila de prioridade como caracteres
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

//Transforma a fila de prioridade na árvore binária de Huffman
Node *createBinaryHuffmanTree(Node *huffmanList){
    //Os processos seguintes ocorrem enquanto o next de "huffmanList" não for nulo
    while(huffmanList->next != NULL){
        //Cria uma variável do tipo char para armazenar o símbolo "\"
        char item = '\\';

        //Aloca dinamicamente um ponteiro para um char
        char *pItem = (char*) malloc(sizeof(char));

        //Faz o conteúdo apontado por pItem ser a variável "item"
        *pItem = item;

        //Aloca dinamicamente um novo nó
        Node *newNode = (Node*) malloc(sizeof(Node));

        /*
        Define a frequência do novo nó como a soma das frequências dos dois
        primeiros nós da fila de prioridade
        */
        newNode->frequency = huffmanList->frequency + huffmanList->next->frequency;

        //A esquerda do novo nó passa a ser o primeiro nó da fila
        newNode->left = huffmanList;

        //A direita do novo nó passa a ser o segundo nó da fila
        newNode->right = huffmanList->next;

        //Define o o item do novo nó como o pItem convertido para um ponteiro para void
        newNode->item = (void*) pItem;

        //Libera a memória de de pItem
        free(pItem);

        //huffmanList passa a ser o nó seguinte ao seu next
        huffmanList = huffmanList->next->next;

        //O nó seguinte à esquerda de huffmanList passa a ser nulo
        newNode->left->next = NULL; 
        //O nó seguinte à direita de huffmanList passa a ser nulo
        newNode->right->next = NULL;

        /*
        Se a fila estiver vazia ou a frequência do novo nó for menor ou igual 
        à frequência do primeiro nó de huffmanList, o novo nó passa a ser o início
        da fila, se não, procura-se a posição apropriada para adicioná-lo à fila
        */
        if(isEmptyList(huffmanList) || newNode->frequency <= huffmanList->frequency){
            //O next do novo nó passa a ser o primeiro nó da fila
            newNode->next = huffmanList;
            //O primeiro nó da fila passa a ser o novo nó
            huffmanList = newNode;
        }
        else{
            //Cria um nó auxiliar que começa sendo igual ao primeiro nó da fila
            Node *current = huffmanList;

            /*
            Enquanto o next de current for diferente de nulo e a frequência do nó
            seguinte ao current for menor que a frequência do nó a ser adicionado,
            current é atualizado para o nó seguinte a ele
            */
            while(current->next != NULL && current->next->frequency < newNode->frequency){
                current = current->next;
            }

            //O next do novo nó passa a ser o next de current
            newNode->next = current->next;
            //O next de current passa a ser o novo nó
            current->next = newNode;
        }
    }
    return huffmanList;
}

//Imprime a árvore de Huffman em pré-ordem
void printHuffmanTreePreOrder(Node *huffmanTree){
    if(!isEmptyList(huffmanTree)){
        char *p = (char*) huffmanTree->item;
        char c = *p;
        printf("%c ", c);
        printHuffmanTreePreOrder(huffmanTree->left);
        printHuffmanTreePreOrder(huffmanTree->right);
    }
}

//Calcula a altura da árvore
int height(Node *huffmanTree){
    if(isEmptyList(huffmanTree)){
        return -1;
    }
    else{
        return 1 + max(height(huffmanTree->left), height(huffmanTree->right));
    }
}

#endif //FUNCTIONS_H
