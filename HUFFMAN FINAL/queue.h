#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
/*
    o struct Node é uma estrutura que representa um nó de uma árvore de Huffman
    ou de uma fila de prioridade ordenada pelas frequências Conforme solicitado, 
    os itens que não fazem parte da estrutura estão em formato void*.

*/
typedef struct node{
    void *item;
    struct node *next;
    void * frequency;
    struct node *left;
    struct node *right;
}Node;

/*
    o struct Queue é uma estrutura que representa uma fila de prioridade
*/
typedef struct priorityQueue{
    Node *head;
}Queue;

/*
    A função *createHuffmanQueue() cria uma fila de prioridade vazia
    Retorna um ponteiro para a fila de prioridade criada
*/
Queue *createHuffmanQueue();

/*
    A função isEmpty(Queue *fila) verifica se a fila de prioridade está vazia
    Retorna 1 se a fila estiver vazia e 0 caso contrário
    @param         fila        ponteiro para a fila de prioridade

*/
int isEmpty(Queue *fila);

/*
    A função enqueue(Queue *fila, unsigned char item, int frequency) insere um item na fila de prioridade
    @param         fila        ponteiro para a fila de prioridade
    @param         item        item a ser inserido
    @param         frequency   frequência do item
*/
void enqueue(Queue *fila, unsigned char item, int frequency);
/*
    A função printQueue(Queue *fila) imprime a fila de prioridade
    @param         fila        ponteiro para a fila de prioridade
*/
void printQueue(Queue *fila);

#endif //QUEUE_H
