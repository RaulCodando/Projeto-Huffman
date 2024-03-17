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
        unsigned char item = '\\';

        //Aloca dinamicamente um ponteiro para um char
        unsigned char *pItem = (unsigned char*) malloc(sizeof(unsigned char));

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

//salva a árvore de Huffman em pré-ordem
void saveHuffmanTreePreOrder(Node *huffmanTree, unsigned char array[], int *i, int *treeSize){
    if(!isEmptyList(huffmanTree)){
        unsigned char c = *(unsigned char*) huffmanTree->item;
        if(huffmanTree->left == NULL && huffmanTree->right == NULL){
            if(c == '*' || c == '\\'){
                array[*i] = '\\';
                (*i)++;
                (*treeSize)++;
            }
            array[*i] = c;
        }
        else{
            array[*i] = '*';
        }
        
        (*i)++;
        (*treeSize)++;
        saveHuffmanTreePreOrder(huffmanTree->left, array, i, treeSize);
        saveHuffmanTreePreOrder(huffmanTree->right, array, i, treeSize);
    }
}

void printHuffmanTreePreOrder(Node *huffmanTree){
    if(!isEmptyList(huffmanTree)){
        unsigned char c = *(unsigned char*) huffmanTree->item;
        if(huffmanTree->left == NULL && huffmanTree->right == NULL){
            printf("%c ", c);
        }
        else{
            printf("* ");
        }
        printHuffmanTreePreOrder(huffmanTree->left);
        printHuffmanTreePreOrder(huffmanTree->right);
    }
}

Node *rebuildTree(unsigned char string[], int size, int *i, Node *tree){
    if(*i < size){
        unsigned char *item = (unsigned char*) malloc(sizeof(unsigned char));
        *item = string[*i];
        (*i)++;

        if(*item == '*'){
            tree = (Node*) malloc(sizeof(Node));
            tree->item = item;
            tree->left = NULL;
            tree->right = NULL;
            tree->left = rebuildTree(string, size, i, tree->left);
            tree->right = rebuildTree(string, size, i, tree->right);
        }
        else{
            if(*item == '\\'){
                (*i)++;
                *item = string[*i];
            }

            tree = (Node*) malloc(sizeof(Node));
            tree->item = item;
            tree->left = NULL;
            tree->right = NULL;
        }
    }

    return tree;
}


#endif //HUFFTREE_H
