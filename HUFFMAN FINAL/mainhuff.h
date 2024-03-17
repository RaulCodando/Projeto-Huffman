#ifndef MAINHUFF_H
#define MAINHUFF_H

#include "queue.h"
#include "mapbytes.h"
#include <string.h>

/* A função fileSize(FILE *f) retorna o tamanho do arquivo
    @param         f       ponteiro para o arquivo
*/
long int fileSize(FILE *f);

/* A função compressFile() comprime um arquivo
    Retorna 0 se o arquivo foi comprimido com sucesso e 1 caso contrário
*/
int compressFile();

/* A função decompressFile() descomprime um arquivo
    Retorna 0 se o arquivo foi descomprimido com sucesso e 1 caso contrário
*/
int decompressFile();

#endif //MAINHUFF_H
