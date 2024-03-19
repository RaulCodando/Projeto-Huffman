#include "filaPrioridades.h"

// Função para criar um novo nó
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Erro: Não foi possível alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

// Função para criar uma nova fila de prioridades
PriorityQueue* createPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (pq == NULL) {
        printf("Erro: Não foi possível alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    pq->front = NULL;
    return pq;
}

// Função para inserir um elemento na fila de prioridades usando heap
void insertHeap(int heap[], int* size, int value, int* iterations) {
    int i = *size;
    *size = *size + 1;
    while (i > 0 && value > heap[(i - 1) / 2]) {
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
        (*iterations)++;
    }
    heap[i] = value;
}

// Função para inserir um elemento na fila de prioridades sem heap
int insertWithoutHeap(PriorityQueue* pq, int data) {
    int iterations = 0;
    Node* newNode = createNode(data);
    if (pq->front == NULL || data < pq->front->data) {
        newNode->next = pq->front;
        pq->front = newNode;
        iterations++;
    } else {
        Node* prev = NULL;
        Node* current = pq->front;
        while (current != NULL && data >= current->data) {
            prev = current;
            current = current->next;
            iterations++;
        }
        newNode->next = prev->next;
        prev->next = newNode;
        iterations++;
    }
    return iterations;
}

// Função para liberar a memória alocada para a fila de prioridades
void freePriorityQueue(PriorityQueue* pq) {
    Node* current = pq->front;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(pq);
}
