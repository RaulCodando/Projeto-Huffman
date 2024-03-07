#ifndef MAPBYTES_H
#define MAPBYTES_H

#include "hufftree.h"
#include <string.h>

char **allocateMap(int columns){
    char **table;

    table = malloc(sizeof(char*) * 256);

    for(int i = 0; i < 256; i++){
        table[i] = calloc(columns, sizeof(char));
    }

    return table;
}

void createMap(char **table, Node *root, char *path, int columns){
    char left[columns];
    char right[columns];

    if(isEmptyList(root->left) && isEmptyList(root->right)){
        unsigned char i = *(unsigned char*) root->item;
        strcpy(table[i], path);
    }
    else{
        strcpy(left, path);
        strcpy(right, path);

        strcat(left, "0");
        strcat(right, "1");

        createMap(table, root->left, left, columns);
        createMap(table, root->right, right, columns);
    }
}

void printMap(char **table){
    for(int i = 0; i < 256; i++){
        if(strlen(table[i]) > 0){
            printf("%c: %s\n", i, table[i]);
        }
    }
}

#endif //MAPBYTES_H
