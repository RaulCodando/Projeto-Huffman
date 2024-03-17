#include "mapbytes.h"

int isBitSet(int i, unsigned char byte){
    unsigned char mask = 1 << i;
    return mask & byte;
}

unsigned char setBit(int i, unsigned char byte){
    unsigned char mask = 1 << i;
    return mask | byte;
}

int isHeaderSet(int i, unsigned short bytes){
    unsigned short mask = 1 << i;
    return mask & bytes;
}

short setHeader(int i, unsigned short bytes){
    unsigned short mask = 1 << i;
    return mask | bytes;
}

char **allocateMap(int columns){
    char **table;

    table = malloc(sizeof(char*) * 256);

    for(int i = 0; i < 256; i++){
        table[i] = calloc(columns, sizeof(char));
    }

    return table;
}

void createMap(char **table, Node *root, char *path, int columns, int *nodes){
    char left[columns];
    char right[columns];

    (*nodes)++;

    if(isEmptyList(root->left) && isEmptyList(root->right)){
        unsigned char i = *(unsigned char*) root->item;
        strcpy(table[i], path);
    }
    else{
        strcpy(left, path);
        strcpy(right, path);

        strcat(left, "0");
        strcat(right, "1");

        createMap(table, root->left, left, columns, nodes);
        createMap(table, root->right, right, columns, nodes);
    }
}

unsigned long long int encodedFileSize(char **table, unsigned char *symbols, long int strSize){
    unsigned long long int size = 0;
    int i = 0;

    while(i != strSize){
        size = size + strlen(table[symbols[i]]);
        i++;
    }
    
    return size + 1;
}

char *encodeFile(char **table, unsigned char *symbols, long int strSize, long int *outputSize){
    unsigned long long int size = encodedFileSize(table, symbols, strSize);
    *outputSize = size - 1;
    int i = 0;

    char *encodedFile = calloc(size, sizeof(char));
    char *aux = encodedFile;

    while(i != strSize){
        strcpy(aux, table[symbols[i]]);
        aux += strlen(table[symbols[i]]);
        i++;
    }

    return encodedFile;
}

int outputFile(long int size, unsigned char tree[], char *encodedFile, int nodes, char fileName[]){
    char string[1000];
    strcpy(string, fileName);
    strcat(string, ".huff");

    FILE *f = fopen(string, "wb");

    if(f == NULL){
        printf("\nErro ao criar arquivo compactado.");
        return 1;
    }

    int totalSize = (size - (size % 8)) + 8;
    int trash = totalSize - size;
    int totalBytes = totalSize / 8;
    unsigned short header = 0;

    for(int i = 12; i >= 0; i--){
        if(isHeaderSet(i, nodes)) header = setHeader(i, header);
    }

    int j = 2;

    for(int i = 15; i >= 13; i--){
        if(isHeaderSet(j, trash)) header = setHeader(i, header);
        j--;
    }

    fwrite(&header, sizeof(short), 1, f);

    for(int i = 0; i < nodes; i++){
        fwrite(&tree[i], sizeof(unsigned char), 1, f);
    }

    unsigned char byte = 0;
    j = 7;

    for(int i = 0; i < size; i++){
        if(encodedFile[i] == '1'){
            byte = setBit(j, byte);
        }

        j--;

        if(j < 0){
            j = 7;
            fwrite(&byte, sizeof(unsigned char), 1, f);
            byte = 0;
        }
    }
    if(j != 7){
        fwrite(&byte, sizeof(unsigned char), 1, f);
    }

    fclose(f);
}
