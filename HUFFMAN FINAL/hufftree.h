#ifndef HUFFTREE_H
#define HUFFTREE_H

#include "queue.h"

/* A função isEmptyList(Node * head) verifica se a lista está vazia, ou seja, o ponteiro para o início da lista é nulo
 Retorna 1 se a lista estiver vazia e 0 caso contrário
 @param          head        ponteiro para o início da lista */
int isEmptyList(Node *head);

/* A função max(int a, int b) retorna o maior valor entre dois inteiros
 @param         a   primeiro inteiro
@param          b    segundo inteiro 
*/
int max(int a, int b);

//A função createBinaryHuffmanTree(Node * huffmanList) transforma uma fila de prioridade numa árvore
//Binária de Huffman e retorna a raiz da árvore
//@param     huffmanList primeiro nó da fila de prioridade
Node *createBinaryHuffmanTree(Node *huffmanList);

/* A função height(Node * huffmanTree) retorna a altura da árvore de Huffman
    @param         huffmanTree     raiz da árvore de Huffman 
*/
int height(Node *huffmanTree);

/*  A função saveHuffmanTreePreOrder(Node * huffmanTree, unsigned char array[], int *i, int *treeSize) salva a árvore de Huffman em pré-ordem
    @param         huffmanTree     raiz da árvore de Huffman
    @param         array           array de caracteres que armazenará a árvore
    @param         i               ponteiro para a posição atual do array
    @param         treeSize        ponteiro para o tamanho da árvore
*/
void saveHuffmanTreePreOrder(Node *huffmanTree, unsigned char array[], int *i, int *treeSize);
/*
A função printHuffmanTreePreOrder(Node * huffmanTree) imprime a árvore de Huffman em pré-ordem
    @param         huffmanTree     raiz da árvore de Huffman

*/
void printHuffmanTreePreOrder(Node *huffmanTree);

/* A função rebuildTree(unsigned char string[], int size, int *i, Node *tree) reconstrói a árvore de Huffman a partir de uma string
    @param         string      string que contém a árvore de Huffman
    @param         size        tamanho da string
    @param         i           ponteiro para a posição atual da string
    @param         tree        raiz da árvore de Huffman
 

*/
Node *rebuildTree(unsigned char string[], int size, int *i, Node *tree);

#endif //HUFFTREE_H
