#ifndef HUFFTREE_H
#define HUFFTREE_H

#include "queue.h"

//Verifica se uma árvore de huffman é vazia
int isEmptyList(Node *head){
    return (head == NULL);
}

//Retorna o maior dentre de 2 número
int max(int a, int b){
    if(a > b) return a;
    else return b;
}

//Transforma a fila de prioridade na árvore binária de Huffman
Node *createBinaryHuffmanTree(Node *huffmanList){
    //Os processos seguintes ocorrem enquanto o next de "huffmanList" não for nulo
    while(huffmanList->next != NULL){
        //Cria uma variável do tipo char para armazenar o símbolo "\"
        char item = '\\';

        //Aloca dinamicamente um ponteiro para um char
        char *pItem = (char*) malloc(sizeof(char));

        //Faz o conteúdo apontado por pItem ser a variável "item"
        *pItem = item;

        //Aloca dinamicamente um novo nó
        Node *newNode = (Node*) malloc(sizeof(Node));

        /*
        Define a frequência do novo nó como a soma das frequências dos dois
        primeiros nós da fila de prioridade
        */
        newNode->frequency = huffmanList->frequency + huffmanList->next->frequency;

        //A esquerda do novo nó passa a ser o primeiro nó da fila
        newNode->left = huffmanList;

        //A direita do novo nó passa a ser o segundo nó da fila
        newNode->right = huffmanList->next;

        //Define o o item do novo nó como o pItem convertido para um ponteiro para void
        newNode->item = (void*) pItem;

        //Libera a memória de de pItem
        free(pItem);

        //huffmanList passa a ser o nó seguinte ao seu next
        huffmanList = huffmanList->next->next;

        //O nó seguinte à esquerda de huffmanList passa a ser nulo
        newNode->left->next = NULL; 
        //O nó seguinte à direita de huffmanList passa a ser nulo
        newNode->right->next = NULL;

        /*
        Se a fila estiver vazia ou a frequência do novo nó for menor ou igual 
        à frequência do primeiro nó de huffmanList, o novo nó passa a ser o início
        da fila, se não, procura-se a posição apropriada para adicioná-lo à fila
        */
        if(isEmptyList(huffmanList) || newNode->frequency <= huffmanList->frequency){
            //O next do novo nó passa a ser o primeiro nó da fila
            newNode->next = huffmanList;
            //O primeiro nó da fila passa a ser o novo nó
            huffmanList = newNode;
        }
        else{
            //Cria um nó auxiliar que começa sendo igual ao primeiro nó da fila
            Node *current = huffmanList;

            /*
            Enquanto o next de current for diferente de nulo e a frequência do nó
            seguinte ao current for menor que a frequência do nó a ser adicionado,
            current é atualizado para o nó seguinte a ele
            */
            while(current->next != NULL && current->next->frequency < newNode->frequency){
                current = current->next;
            }

            //O next do novo nó passa a ser o next de current
            newNode->next = current->next;
            //O next de current passa a ser o novo nó
            current->next = newNode;
        }
    }
    return huffmanList;
}

//Calcula a altura da árvore
int height(Node *huffmanTree){
    if(isEmptyList(huffmanTree)){
        return -1;
    }
    else{
        return 1 + max(height(huffmanTree->left), height(huffmanTree->right));
    }
}

//Imprime a árvore de Huffman em pré-ordem
void printHuffmanTreePreOrder(Node *huffmanTree){
    if(!isEmptyList(huffmanTree)){
        char *p = (char*) huffmanTree->item;
        char c = *p;
        printf("%c ", c);
        printHuffmanTreePreOrder(huffmanTree->left);
        printHuffmanTreePreOrder(huffmanTree->right);
    }
}

#endif //HUFFTREE_H
