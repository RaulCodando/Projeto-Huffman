#ifndef MAPBYTES_H
#define MAPBYTES_H

#include "hufftree.h"
#include <string.h>

/*  
A função isBitSet(int i, unsigned char byte) verifica se o i-ésimo bit de um byte está setado
    @param         i       posição do bit
    @param         byte    byte a ser verificado
 */

int isBitSet(int i, unsigned char byte);

/*
A função setBit(int i, unsigned char byte) seta o i-ésimo bit de um byte
    @param         i       posição do bit
    @param         byte    byte a ser modificado
 

*/
unsigned char setBit(int i, unsigned char byte);

/*
A função isHeaderSet(int i, unsigned short bytes) verifica se o i-ésimo bit de um short está setado
    @param         i       posição do bit
    @param         bytes   short a ser verificado
 
*/
int isHeaderSet(int i, unsigned short bytes);

/*
A função setHeader(int i, unsigned short bytes) seta o i-ésimo bit de um short
    @param         i       posição do bit
    @param         bytes   short a ser modificado
*/
short setHeader(int i, unsigned short bytes);

/*
A função allocateMap(int columns) aloca memória para uma tabela de mapeamento
    @param         columns     número de colunas da tabela

*/
char **allocateMap(int columns);

/*
A função createMap(char **table, Node *root, char *path, int columns, int *nodes) cria uma tabela de mapeamento
    @param         table       tabela de mapeamento
    @param         root        raiz da árvore de Huffman
    @param         path        caminho atual
    @param         columns     número de colunas da tabela
    @param         nodes       número de nós da árvore

*/
void createMap(char **table, Node *root, char *path, int columns, int *nodes);

/*
A função encodedFileSize(char **table, unsigned char *symbols, long int strSize) calcula o tamanho da string do símbolos codificados
    @param         table       tabela de mapeamento
    @param         symbols     string contendo os símbolos do arquivo
    @param         strSize     tamanho da string

*/
unsigned long long int encodedFileSize(char **table, unsigned char *symbols, long int strSize);

/* 
A função encodeFile(char **table, unsigned char *symbols, long int strSize, long int *outputSize) codifica um arquivo
    @param         table       tabela de mapeamento
    @param         symbols     símbolos do arquivo
    @param         strSize     tamanho do arquivo
    @param         outputSize  ponteiro para o tamanho do arquivo codificado
*/
char *encodeFile(char **table, unsigned char *symbols, long int strSize, long int *outputSize);

/* 
A função outputFile(long int size, unsigned char tree[], char *encodedFile, int nodes, char fileName[]) cria um arquivo de saída
    @param         size            tamanho do arquivo
    @param         tree            árvore de Huffman
    @param         encodedFile     arquivo codificado
    @param         nodes           tamnho da árvore
    @param         fileName        nome do arquivo
*/
int outputFile(long int size, unsigned char tree[], char *encodedFile, int nodes, char fileName[]);

#endif //MAPBYTES_H
