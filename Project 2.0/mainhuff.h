#ifndef MAINHUFF_H
#define MAINHUFF_H

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
    FILE *f; //Declara o arquivo "f"

    char **table;
    char *encodedFile;

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
    unsigned char *symbols = (unsigned char*) malloc(fSize * sizeof(unsigned char) + 1);
    int frequency[256] = {0};
    int byte;
    long int i = 0;

    //Passa por cada byte do arquivo, adicionando-o à tabela de frequências
    while((byte = fgetc(f)) != EOF){
        frequency[byte]++;
        symbols[i] = byte;
        i++;
    }

    symbols[i] = '\0';

    //Passa por todos os elementos não nulos da tabela adicionando-os à fila de prioridade
    for(int j = 0; j < 256; j++){
        int maior = 0;
        if(frequency[j] != 0){
            enqueue(huffmanList, j, frequency[j]);
        }
    }

    //Cria a árvore de Huffman usando a fila contendo os bytes do arquivo
    Node *huffmanTree = createBinaryHuffmanTree(huffmanList->head);

    printHuffmanTreePreOrder(huffmanTree);

    int columns = height(huffmanTree) + 1;
    int nodes = 0;
    int treeSize = 0;
    int index = 0;

    table = allocateMap(columns);

    createMap(table, huffmanTree, "", columns, &nodes);
    unsigned char treeCharacters[2 * nodes];
    saveHuffmanTreePreOrder(huffmanTree, treeCharacters, &index, &treeSize);

    long int encodedSize;

    encodedFile = encodeFile(table, symbols, i, &encodedSize);

    free(symbols);

    outputFile(encodedSize, treeCharacters, encodedFile, treeSize);

    free(encodedFile);

    rewind(f);

    //Fecha o arquivo "f"
    fclose(f);
    return 0;
}

int decompressFile(){
    return 0;
}

#endif //MAINHUFF_H
