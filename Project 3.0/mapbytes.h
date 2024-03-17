#ifndef MAPBYTES_H
#define MAPBYTES_H

#include "hufftree.h"
#include <string.h>

int isBitSet(int i, unsigned char byte);
unsigned char setBit(int i, unsigned char byte);
int isHeaderSet(int i, unsigned short bytes);
short setHeader(int i, unsigned short bytes);
char **allocateMap(int columns);
void createMap(char **table, Node *root, char *path, int columns, int *nodes);
unsigned long long int encodedFileSize(char **table, unsigned char *symbols, long int strSize);
char *encodeFile(char **table, unsigned char *symbols, long int strSize, long int *outputSize);
int outputFile(long int size, unsigned char tree[], char *encodedFile, int nodes, char fileName[]);

#endif //MAPBYTES_H
