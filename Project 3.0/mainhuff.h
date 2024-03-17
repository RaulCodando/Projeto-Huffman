#ifndef MAINHUFF_H
#define MAINHUFF_H

#include "queue.h"
#include "mapbytes.h"
#include <string.h>

long int fileSize(FILE *f);
int compressFile();
int decompressFile();

#endif //MAINHUFF_H
