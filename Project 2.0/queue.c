#include "queue.h"


Queue *createHuffmanQueue(void); 
int isEmpty(Queue *fila);
void enqueue(Queue *fila, unsigned char item, int frequency);
void printQueue(Queue *fila);
