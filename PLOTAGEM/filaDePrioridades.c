#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 25000

// Estrutura de nó para a fila de prioridade sem heap
typedef struct Node {
    int value;
    struct Node* next;
} Node;

// Função para criar um novo nó
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Função para inserir um novo nó na fila de prioridade sem heap
void insertNode(Node** head, int value) {
    Node* newNode = createNode(value);
    if (*head == NULL || (*head)->value < value) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL && current->next->value >= value) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Função para encontrar um número na fila de prioridade sem heap
int findNumber(Node* head, int target) {
    while (head != NULL) {
        if (head->value == target) {
            return 1; // O número foi encontrado
        }
        head = head->next;
    }
    return 0; // O número não foi encontrado
}

// Função para liberar a memória alocada para os nós da fila de prioridade sem heap
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Função para criar e inicializar um heap de inteiros
void initializeHeap(int heap[], int n) {
    for (int i = 0; i < n; i++) {
        heap[i] = -1; // Inicializamos com -1 para representar que o heap está vazio
    }
}

// Função para inserir um elemento no heap
void insertHeap(int heap[], int* size, int value) {
    int i = *size;
    *size = *size + 1;
    while (i > 0 && value > heap[(i - 1) / 2]) {
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap[i] = value;
}

// Função para remover o elemento máximo do heap
int removeMax(int heap[], int* size) {
    if (*size == 0) return -1; // Heap vazio
    int max = heap[0];
    *size = *size - 1;
    int x = heap[*size];
    int i = 0;
    int j = 1;
    while (j < *size) {
        if (j + 1 < *size && heap[j + 1] > heap[j]) j = j + 1;
        if (x >= heap[j]) break;
        heap[i] = heap[j];
        i = j;
        j = 2 * j + 1;
    }
    heap[i] = x;
    return max;
}

// Função para encontrar um número no heap
int findNumberHeap(int heap[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (heap[i] == target) {
            return 1; // O número foi encontrado
        }
    }
    return 0; // O número não foi encontrado
}

// Função principal
int main() {
    srand(time(NULL));

    // Abrir o arquivo "numeros.txt" para leitura
    FILE *file;
    file = fopen("numeros.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Preencher a fila de prioridade com números do arquivo para sem heap
    Node* head = NULL;
    int number;
    while (fscanf(file, "%d", &number) != EOF) {
        insertNode(&head, number);
    }

    // Fechar o arquivo
    fclose(file);

    // Preencher o heap com números do arquivo
    int heap[MAX_SIZE];
    int heapSize = 0;
    file = fopen("numeros.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    initializeHeap(heap, MAX_SIZE);
    while (fscanf(file, "%d", &number) != EOF) {
        insertHeap(heap, &heapSize, number);
    }
    fclose(file);

    // Procurar os números de 1 a 100 na fila de prioridade sem heap e com heap
    for (int i = 1; i <= 5000; i++) {
        clock_t start1 = clock();
        int found1 = findNumber(head, i);
        clock_t end1 = clock();
        double timeSpent1 = (double)(end1 - start1) / CLOCKS_PER_SEC;

        clock_t start2 = clock();
        int found2 = findNumberHeap(heap, heapSize, i);
        clock_t end2 = clock();
        double timeSpent2 = (double)(end2 - start2) / CLOCKS_PER_SEC;

        printf("Número %d:\n", i);
        if (found1) {
            printf("Sem heap - Número encontrado - Tempo: %f segundos.\n", timeSpent1);
        } else {
            printf("Sem heap - Número não encontrado - Tempo: %f segundos.\n", timeSpent1);
        }

        if (found2) {
            printf("Com heap - Número encontrado - Tempo: %f segundos.\n", timeSpent2);
        } else {
            printf("Com heap - Número não encontrado - Tempo: %f segundos.\n", timeSpent2);
        }
    }

    // Liberar a memória alocada para a fila de prioridade sem heap
    freeList(head);

    return 0;
}



