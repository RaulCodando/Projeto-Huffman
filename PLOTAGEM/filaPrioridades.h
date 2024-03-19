#ifndef FILAPRIORIDADES_H
#define FILAPRIORIDADES_H

#include <stdio.h>
#include <stdlib.h>

// Estrutura de nó para a fila de prioridades
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Estrutura da fila de prioridades
typedef struct PriorityQueue {
    Node* front;
} PriorityQueue;

// Função para criar um novo nó
Node* createNode(int data);

// Função para criar uma nova fila de prioridades
PriorityQueue* createPriorityQueue();

// Função para inserir um elemento na fila de prioridades usando heap
void insertHeap(int heap[], int* size, int value, int* iterations);

// Função para inserir um elemento na fila de prioridades sem heap
int insertWithoutHeap(PriorityQueue* pq, int data);

// Função para liberar a memória alocada para a fila de prioridades
void freePriorityQueue(PriorityQueue* pq);

#endif /* FILAPRIORIDADES_H */
