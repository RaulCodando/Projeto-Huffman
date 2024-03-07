#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>

//Estrutura de um elemento da tabela de frequências dos bytes
typedef struct element{
    int frequency;
    void *value;
}Element;

//Estrutura da tabela de frequências dos bytes
typedef struct hashTable{
    Element *table[256];
}HashTable;

//Cria a tabela de frequências de elementos
HashTable *createHashTable(){
    //Aloca dinamicamente uma nova tabela
    HashTable *newHashTable = (HashTable*) malloc(sizeof(HashTable));

    //Passa por todos os elementos da tabela, definindo-os como nulo
    for(int i = 0; i < 256; i++){
        newHashTable->table[i] = NULL;
    }

    return newHashTable;
}

//Adiciona um novo item na tabela de frequências, atualizando sua respectiva frequência 
void put(HashTable *table, void *value){
    //Usa o valor do byte para criar o ídice a ser acessado na tabela
    int h = *(unsigned char*) value; 

    //Se o índice acessado for vaizo, adiciona o valor e define sua frequência como 1
    //Se o índice não for vazio, apenas incrementa a frequência do elemento naquele índice
    if(table->table[h] == NULL){
        //Aloca dinamicamente um novo elemento o adiciona no índice acessado na tabela
        table->table[h] = (Element*) malloc(sizeof(Element));
        //Define a frequência desse elemento como 1
        table->table[h]->frequency = 1;
        //Define o valor do elemento como a variável "value"
        table->table[h]->value = value;
    }
    else{
        //Incrementa a frequência do elemento
        table->table[h]->frequency++;
    }
}

#endif //TABLE_H
