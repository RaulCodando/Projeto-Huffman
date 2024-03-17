#ifndef HUFFTREE_H
#define HUFFTREE_H

#include "queue.h"

int isEmptyList(Node *head);
int max(int a, int b);
Node *createBinaryHuffmanTree(Node *huffmanList);
int height(Node *huffmanTree);
void saveHuffmanTreePreOrder(Node *huffmanTree, unsigned char array[], int *i, int *treeSize);
void printHuffmanTreePreOrder(Node *huffmanTree);
Node *rebuildTree(unsigned char string[], int size, int *i, Node *tree);

#endif //HUFFTREE_H
