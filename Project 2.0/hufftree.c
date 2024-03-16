#include "hufftree.h"

//Verifica se uma árvore de huffman é vazia
int isEmptyList(Node *head);

//Retorna o maior dentre de 2 número
int max(int a, int b);

//Transforma a fila de prioridade na árvore binária de Huffman
Node *createBinaryHuffmanTree(Node *huffmanList);


//Calcula a altura da árvore
int height(Node *huffmanTree);

//salva a árvore de Huffman em pré-ordem
void saveHuffmanTreePreOrder(Node *huffmanTree, unsigned char array[], int *i, int *treeSize);

void printHuffmanTreePreOrder(Node *huffmanTree);



