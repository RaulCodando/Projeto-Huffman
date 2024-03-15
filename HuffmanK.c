#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ASCII 256


typedef struct node
{
    int Frequency;
    void * Character;
    struct node *left;
    struct node *right;
    struct node *next;
} Node;

typedef struct list
{
    Node *start;
    int size;
} List;

void createList (List *list)
{
    list->start = NULL;
    list->size = 0;
}

Node * removeonstart (List * list)
{
    Node * aux = NULL;
    if (list->start != NULL)
    {
        aux = list->start;
        list->start = aux->next;
        aux->next = NULL;
        list->size--;
    }

    return aux;
}
void ordered_Insert (List * list, Node * node)
{

    Node * aux;

    if (list->start == NULL)
    {
        list->start = node;
    }
    else if (node->Frequency <= list->start->Frequency)
    {
        node->next = list->start;
        list->start = node;
    }
    else {
        aux = list->start;
        while (aux->next && aux->next->Frequency <= node->Frequency)
        {

            aux = aux->next;
        
        }
                    node->next = aux->next;
            aux->next = node;
    }
        list->size++;
}

void FillList (unsigned int table[], List * list)
{
    int c;
    Node * new;
    for ( c = 0; c < ASCII; c++)
    {

        if (table[c] > 0)
        {
            new = malloc(sizeof(Node));
            new->Character = calloc(1, sizeof(char));
            if (new != NULL)
            {
                
                *(char*)new->Character = c;
                new->Frequency = table[c];
                new->left = NULL;
                new->right = NULL;
                new->next = NULL;
            ordered_Insert(list, new);
            }
        else {
            printf ("\nMALLOC ERROR :)\n PLEASE CHECK YOUR CODE AGAIN\n");
            break;
 
        }

        }
    }
}

void printList (List * list)
{
    Node * aux = list->start;
    while (aux)
    {
        printf ("\n Lista Ordenada: Size: %d\n",list->size);
        printf (" Character: %c Frequency: %d", *(char*)aux->Character, aux->Frequency);
        aux = aux->next;

    }
}


void countFrequency (FILE *file, int Frequency[])
{
    int c;
    while ((c = fgetc(file)) != EOF)
    {
        Frequency[c]++;
    }
}

void printFrequency (int Frequency[])
{
      for (int c = 0; c < ASCII; c++)
    {   
        if (Frequency[c] != 0)
        printf ("Frequência de %c: %d\n", c, Frequency[c]);
    }
}

// ------------------------------------------- TREE -----------------------------

Node * mkTree (List * list)
{
    Node *first, *second, *new;
    while (list->size > 1)
    {
        first = removeonstart(list);
        second = removeonstart(list);
        new = malloc(sizeof(Node));

        if (new)
        {
            new->Character = calloc(1, sizeof(char));
            *(char*)new->Character = '*'; // EDIT LATER, PLACEHOLD CHARACTER
            new->Frequency = first->Frequency + second->Frequency;
            new->left = first;
            new->right = second;
            new->next = NULL;

            ordered_Insert(list, new);
        }
        else {
            printf ("\n PLEASE CHECK YOUR CODE AGAIN -> TREE ERROR!\n");
            break;
        }
    }
    return list->start;
}

void printTree (Node * root, int size)
{
    if (root->left == NULL && root->right == NULL)
    {
        printf ("Leafchar: %c Height: %d\n", *(char*)root->Character, size);
    }
    else {
        printTree(root->left, size + 1);
        printTree(root->right, size + 1);
    }
}
int TreeHeight (Node * root){

        int left, right;
        if (root == NULL)
        {
            return -1;
        }
        else {
            left = TreeHeight(root->left) + 1;
            right = TreeHeight(root->right) + 1;
            if (left > right)
            {
                return left;
            }
            else {
                return right;
            }
        }
}
 // ------------------------------------------- DICTIONARY -----------------------------
char ** allocate_Dictionary (int rows)
{
    char ** dictionary;
    int c;
    dictionary = malloc(sizeof(char*) * ASCII);
    for (c = 0; c < ASCII; c++)
    {
        dictionary[c] = calloc(rows,sizeof(char));
    } 
    return dictionary;
}

void Generate_Dictionary (char ** dictionary, Node * root, char * path, int rows)
{

    char left[rows], right[rows];

    if (root->left == NULL && root->right == NULL)
    {
        strcpy (dictionary[*(int*)root->Character], path);
    }
    else {

        strcpy(left, path);
        strcpy(right, path);
        
        strcat(left, "0");
        strcat(right, "1");

        Generate_Dictionary(dictionary, root->left, left, rows);
        Generate_Dictionary(dictionary, root->right, right, rows);

    }
}

void Print_Dictionary (char ** dictionary)
    {
        int c;
        printf ("\n--- DICTIONARY ---\n");
        for (c = 0; c < ASCII; c++)
        {
           if (strlen(dictionary[c]) > 0)
           {
               printf ("Character: %c Code: %s\n", c, dictionary[c]);
           }
        }
    }
// ------------------------------------------- ENCODE -----------------------------
int get_String_Size (char ** dictionary, FILE *file)
{
    rewind(file);
    int c;
    int size = 0;
    while ((c = fgetc(file)) != EOF)
    {
        if(c >= 0 && c < 256) 
            size += strlen(dictionary[c]);
    }

    rewind(file);
    return size + 1;
}

char * encode (char ** dictionary, FILE * file)
{
    int c;
    int size = get_String_Size(dictionary, file);
    char * encoded = calloc(size, sizeof(char));
    char * current_position = encoded;
    if(encoded == NULL)
    {
        printf("\nMemory allocation failed -> ENCONDING ERROR\n");
        return NULL;
    }
    while ((c = fgetc(file)) != EOF)
    {
        if(c >= 0 && c < 256) 
        {
            strcpy(current_position, dictionary[c]);
            current_position += strlen(dictionary[c]);
        }
    }
    return encoded;
}







// ------------------------------------------- DECODE -----------------------------



// ------------------------------------------- MAIN -----------------------------
int main ()
{
FILE *file = NULL;
int Frequency[ASCII] = {0};
int rows;
char ** dictionary;
char *encoded, *decoded;
Node * tree;

    printf ("Por favor, insira o nome do arquivo.\n");
    do {
  unsigned  char filename[100];
    scanf (" %s", filename);
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("\nInsira um arquivo válido!\n");
    }
} while (file == NULL);
    printf ("arquivo aberto com sucesso!\n");
    // CONTA TEMPO CONTA TEMPO
        clock_t start, end;


        start = clock();


    // CONTA TEMPO CONTA TEMPO
    countFrequency(file, Frequency);
    printFrequency(Frequency); // Remover mais tarde
    printf ("--------------------------------\n");

    List list;
    createList(&list);
    FillList(Frequency, &list);
    printList(&list);  // Remover mais tarde
    printf ("\n--------------------------------\n");
   
    tree = mkTree(&list);
    printTree(tree, 0);
    
    rows = TreeHeight(tree) + 1;

    dictionary = allocate_Dictionary(rows);
    Generate_Dictionary(dictionary, tree, "", rows);
    Print_Dictionary(dictionary);
   encoded = encode(dictionary, file);
  /*  FILE * output =fopen("output.txt","w"); NÃO USAR EM ARQUIVOS GRANDES KKKKKKKKKKKKKKKKKKKKKKKKKKK
    fprintf(output,"%s",encoded); */
    end = clock();
    printf ("Tempo de execução: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
