#include <stdio.h>
#include <stdlib.h>
#include "src/unity.h"
#include "mainhuff.h"

void setUp(){};

void tearDown(){};

void INSERT_NODES () {
    Queue *fila = createHuffmanQueue();
    int freq[6] = {1, 2, 3, 4, 5, 6};
    unsigned char item[6] = {'f', 'e', 'd', 'c', 'b', 'a'};

    for(int i = 0; i < 6; i++){
        enqueue(fila, item[i], freq[i]);
    }
    
    Node *huffmanTree = createBinaryHuffmanTree(fila->head);
    TEST_ASSERT_EQUAL (4, height(huffmanTree));
}

int main(void){
    UNITY_BEGIN();

    RUN_TEST(INSERT_NODES);
    //teste_huff_tree();

    return UNITY_END();

}
