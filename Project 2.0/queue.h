#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

//Estrutura de um nó de uma fila de prioridade, que mais tarde será usada
//para criar uma árvore binária
typedef struct node{
    void *item;
    struct node *next;
    void * frequency;
    struct node *left;
    struct node *right;
}Node;

//Estrutura de uma fila de prioridade
typedef struct priorityQueue{
    Node *head;
}Queue;

//Cria uma fila de prioridades vazia
Queue *createHuffmanQueue(){
    //Aloca dinamicamente um ponteiro para uma nova fila de prioridades
    Queue *fila = (Queue*) malloc(sizeof(Queue));
    fila->head = NULL; //Define o início da fila como nulo
    return fila; //Retorna a fila
}

//Verifica se uma fila de prioridade é vazia
int isEmpty(Queue *fila){
    return fila->head == NULL;
}

//Adiciona um item à fila de prioridade
void enqueue(Queue *fila, unsigned char item, int frequency){
    //Aloca dinamicamente um novo nó
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->item = malloc(sizeof(unsigned char)); //Define o item do novo nó como "item"
    newNode->frequency = malloc(sizeof(int)); //Define a frequência do novo nó como "frequency"
    *(unsigned char*) newNode->item = item;
    
     *(int*)newNode->frequency = frequency; //Define a frequência do novo nó com "frequency"
    newNode->left = NULL; //Define a esquerda di novo nó como nulo
    newNode->right = NULL; //Define a direita di novo nó como nulo

    /*
    Se a fila estiver vazia ou a frequência do item a ser adicionado for menor
    que a frequência do primeiro nó da fila, adiciona o novo nó ao início da fila,
    se não, procura a posição apropriada para adicioná-lo
    */
    if(isEmpty(fila) || frequency <= *(int*)fila->head->frequency){
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
        while(current->next != NULL && *(int*)current->next->frequency < frequency){
            current = current->next;
        }

        //O next do novo nó passa a ser o next de current
        newNode->next = current->next;
        //O next de current passa a ser o novo nó
        current->next = newNode;
    }
}

//Imprime todos os itens da fila de prioridade como caracteres
void printQueue(Queue *fila){
    Node *aux = fila->head;
    int num = 0;

    while(aux != NULL){
        num += *(int*)aux->frequency;
        unsigned char c = *(unsigned char*) aux->item;
        printf("%c\n", c);
        aux = aux->next;
    }
    printf("%d\n", num);
}

#endif //QUEUE_H
