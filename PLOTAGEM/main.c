#include <stdio.h>
#include <stdlib.h>
#include "filaPrioridades.h"

int main() {
    int i;
    int iterationsWithHeap;
    PriorityQueue* pqWithHeap = createPriorityQueue();
    PriorityQueue* pqWithoutHeap = createPriorityQueue();

    // Inserção e impressão das iterações com e sem heap
    int heapWith[25000];
    int heapSizeWith = 0;
    

    for (i = 1; i <= 25000; ++i) {
        iterationsWithHeap = 0;
        insertHeap(heapWith, &heapSizeWith, i, &iterationsWithHeap);
        int iterationsWithoutHeap = insertWithoutHeap(pqWithoutHeap, i);
        printf("Elemento %d (com heap): %d iterações\n", i, iterationsWithHeap);
        printf("Elemento %d (sem heap): %d iterações\n", i, iterationsWithoutHeap);
        printf("\n");
    }

    // Liberando memória alocada
    freePriorityQueue(pqWithHeap);
    freePriorityQueue(pqWithoutHeap);

    return 0;
}
