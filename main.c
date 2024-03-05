#include "functions.h"

int main(){
    Queue *huffmanList = createHuffmanQueue(); //Cria uma fila de prioridade
    HashTable *table = createHashTable(); //Cria uma tabela vazia
    FILE *f; //Declara o arquivo "f"

    printf("Por favor, insira o nome do arquivo que deseja compactar: ");

    //Cria o buffer onde será armazenado o nome do arquivo escolhido pelo usuário
    char buffer[100];
    
    //Lê o nome do arquivo pela entrada padrão e o armazena no buffer
    fgets(buffer, sizeof(buffer), stdin);

    //Calcula o tamanho da string lida
    int nomeTamanho = strlen(buffer)-1;

    //Cria um array de caracteres com o tamanho da string lida
    char nome[nomeTamanho];

    //Transfere os caracteres do buffer para o novo array
    for(int i = 0; i < nomeTamanho; i++){
        nome[i] = buffer[i];
    }

    /*
    Abre o arquivo cujo nome está armazenado no array "nome" 
    em modo de leitura de bytes
    */
    f = fopen(nome, "rb");

    //Calcula e armazena o tamanho do arquivo
    long int fSize = fileSize(f);

    /*
    Se houver algum problema na abertura do arquivo ou ele for vazio,
    encerra o programa
    */
    if(f == NULL || fSize == 0){
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    //Passa por cada byte do arquivo, adicionando-o à tabela de frequências
    for(int i = 0; i < fSize; i++){
        //Lê um byte e o armazena como um inteiro
        int byte = fgetc(f);

        //Aloca dinamicamente um ponteiro para void
        void *byteP = malloc(sizeof(unsigned char));

        /*
        O byte que foi guardado como um inteiro é convertido em um unsigned char
        e passa a ser o contúdo apontado pelo ponteiro para void
        */
        *((unsigned char*)byteP) = (unsigned char)byte;

        //Adiciona o ponteiro para void à tabela, atualizando sua frequência
        put(table, byteP);
    }

    //Passa por todos os elementos não nulos da tabela adicionando-os à fila de prioridade
    for(int i = 0; i < 256; i++){
        if(table->table[i] != NULL){
            enqueue(huffmanList, table->table[i]->value, table->table[i]->frequency);
        }
    }

    //Imprime a fila
    printQueue(huffmanList);

    //Cria a árvore de Huffman usando a fila contendo os bytes do arquivo
    Node *huffmanTree = createBinaryHuffmanTree(huffmanList->head);

    //Imprime a árvore em pré-ordem
    printHuffmanTreePreOrder(huffmanTree);

    //Fecha o arquivo "f"
    fclose(f);
    return 0;
}
