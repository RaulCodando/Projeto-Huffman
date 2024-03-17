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

    char aux[1000];
    char fileName[1000];

    int j = strlen(buffer) - 1;

    for(i = strlen(buffer) - 1; i >= 0; i--){
        if(buffer[i] != '\\'){
            fileName[j] = buffer[i];
            j--;
        }
        else if(buffer[i] == '\\') break;
    }

    fileName[strlen(buffer)] = '\0';

    int output = outputFile(encodedSize, treeCharacters, encodedFile, treeSize, fileName);

    free(encodedFile);
    free(huffmanTree);
    free(huffmanList);
    free(table);

    if(output == 1) return 1;

    rewind(f);

    //Fecha o arquivo "f"
    fclose(f);
    return 0;
}

int decompressFile(){
    FILE *f;

    char buffer[1000];
    unsigned short header;
    unsigned short trash = 0;
    unsigned short treeSize = 0;
    int index = 0;
    int binary[16] = {0};

    printf("Por favor, insira o caminho do arquivo que deseja descompactar: ");

    fgets(buffer, sizeof(buffer), stdin);

    buffer[strcspn(buffer, "\n")] = '\0';

    f = fopen(buffer, "rb");

    if(f == NULL){
        printf("\nErro ao abrir o arquivo.");
        return 1;
    }

    long int fSize = fileSize(f);

    fread(&header, sizeof(unsigned short), 1, f);

    int j = 2;
    for(int i = 15; i >= 13; i--){
        if(isHeaderSet(i, header)) trash = setHeader(j, trash);
        j--;
    }

    for(int i = 12; i >= 0; i--){
        if(isHeaderSet(i, header)) treeSize = setHeader(i, treeSize);
    }

    unsigned char tree[treeSize];

    for(int i = 0; i < treeSize; i++){
        fread(&tree[i], sizeof(unsigned char), 1, f);
    }

    Node *huffmanTree = rebuildTree(tree, treeSize, &index, NULL);
    Node *aux = huffmanTree;

    printHuffmanTreePreOrder(huffmanTree);

    printf("\n%d %d", trash, treeSize);

    for(int i = strlen(buffer) - 1; i >= 0; i--){
        if(buffer[i] == '.'){ 
            buffer[i] = '\0';
            break;
        }
    }

    char fileName[1000];
    strcpy(fileName, "decompressed");
    strcat(fileName, buffer);

    FILE *decompressedFile = fopen(fileName, "wb");

    if(decompressedFile == NULL){
        printf("\nErro ao criar arquivo descompactado.");
        return 1;
    }

    unsigned char byte;
    int i;
    int readBits = 0;

    while(fread(&byte, sizeof(unsigned char), 1, f)){
        long int position = ftell(f);

        for(i = 7; i >= 0; i--){
            if(isBitSet(i, byte)){
                aux = aux->right;
            }
            else{
                aux = aux->left;
            }

            readBits++;

            if(aux->left == NULL && aux->right == NULL){
                unsigned char *item = (unsigned char*) malloc(sizeof(unsigned char));
                item = (unsigned char*) aux->item;
                unsigned char c = *item;
                fwrite(item, sizeof(unsigned char), 1, decompressedFile);
                aux = huffmanTree;
            }

            if(position == fSize && (readBits + trash) % 8 == 0){
                break;
            }
        }

        if(position == fSize && (readBits + trash) % 8 == 0){
            break;
        }
    }

    fclose(f);
    fclose(decompressedFile);
    return 0;
}

#endif //MAINHUFF_H
