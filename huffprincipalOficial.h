#ifndef MAINHUFF_H
#define MAINHUFF_H

#include "table.h"
#include "queue.h"
#include "mapbytes.h"
#include <string.h>

//Retorna o tamanho de um arquivo
long int fileSize(FILE *f){
    fseek(f, 0, SEEK_END); //Vai até o final do arquivo
    long int size = ftell(f); //Salva a posição do final do arquivo em "size"
    rewind(f); //Volta ao início do arquivo
    return size;
}

int compressFile(){
    Queue *huffmanList = createHuffmanQueue(); //Cria uma fila de prioridade
    HashTable *table = createHashTable(); //Cria uma tabela vazia
    char **mappedBytes;
    FILE *f; //Declara o arquivo "f"

    printf("Por favor, insira o caminho do arquivo que deseja compactar: ");

    //Cria o buffer onde será armazenado o caminho do arquivo escolhido pelo usuário
    char buffer[1000];
    
    //Lê o caminho do arquivo pela entrada padrão e o armazena no buffer
    fgets(buffer, sizeof(buffer), stdin);

    //Substitui a quebra de linha no final pelo caractere de término de string
    buffer[strcspn(buffer, "\n")] = '\0';

    /*
    Abre o arquivo cujo caminho está armazenado no buffer 
    em modo de leitura de bytes
    */
    f = fopen(buffer, "rb");

    /*
    Se houver algum problema na abertura do arquivo ou ele não existir,
    encerra o programa
    */
    if(f == NULL){
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    //Calcula e armazena o tamanho do arquivo
    long int fSize = fileSize(f);

    //Passa por cada byte do arquivo, adicionando-o à tabela de frequências
    for(int i = 0; i < fSize; i++){
        // Aloca dinamicamente um ponteiro para void
        void *byteP = malloc(sizeof(unsigned char));

        // Lê um byte e o armazena como um inteiro
        fread(byteP, sizeof(unsigned char), 1, f);

        // Adiciona o ponteiro para void à tabela, atualizando sua frequência
        put(table, byteP);
    }

    //Passa por todos os elementos não nulos da tabela adicionando-os à fila de prioridade
    for(int i = 0; i < 256; i++){
        if(table->table[i] != NULL){
            enqueue(huffmanList, table->table[i]->value, table->table[i]->frequency);
        }
    }

    printQueue(huffmanList);

    //Cria a árvore de Huffman usando a fila contendo os bytes do arquivo
    Node *huffmanTree = createBinaryHuffmanTree(huffmanList->head);

    printHuffmanTreePreOrder(huffmanTree);

    int columns = height(huffmanTree) + 1;

    printf("\n");

    mappedBytes = allocateMap(columns);

    createMap(mappedBytes, huffmanTree, "", columns);

    printMap(mappedBytes);

    //Fecha o arquivo "f"
    fclose(f);
    return 0;
}

int decompressFile(){
    return 0;
}

#endif //MAINHUFF_H
