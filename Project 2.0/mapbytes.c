#include "mapbytes.h"

int isBitSet(int i, unsigned char byte);
unsigned char setBit(int i, unsigned char byte);
int isHeaderSet(int i, int bytes);
short setHeader(int i, unsigned short bytes);
char **allocateMap(int columns);
void createMap(char **table, Node *root, char *path, int columns, int *nodes);
void printMap(unsigned char **table);
unsigned long long int encodedFileSize(char **table, unsigned char *symbols, long int strSize);
char *encodeFile(char **table, unsigned char *symbols, long int strSize, long int *outputSize);
void writeTestOutputFile(char *encodedFile);
int outputFile(long int size, unsigned char tree[], char *encodedFile, int nodes);
