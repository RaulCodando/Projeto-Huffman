#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    void *item;
    struct node *next;
    void * frequency;
    struct node *left;
    struct node *right;
}Node;

typedef struct priorityQueue{
    Node *head;
}Queue;

Queue *createHuffmanQueue();
int isEmpty(Queue *fila);
void enqueue(Queue *fila, unsigned char item, int frequency);
void printQueue(Queue *fila);

#endif //QUEUE_H
