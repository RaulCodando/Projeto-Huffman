#include "mainhuff.h"

int main(){
    char input[100];
    while(1){
        printf("\n");
        printf("==============================================\n");
        printf("Por favor, digite abaixo o que deseja realizar\n");
        printf("==============================================\n");
        printf("\n");
        printf("--> Comprimir arquivo\n");
        printf("--> Descomprimir arquivo\n");
        printf("--> Fechar o programa\n");
        printf("\n");
        printf("==============================================\n");
        printf("\n>>> ");

        int inputValido = 1;

        do{
            scanf("%s", &input);

            if(input[0] == 'F' || input[0] == 'f') break;
            else if(input[0] == 'C' || input[0] == 'c'){
                inputValido = 1;
                getchar();

                if(compressFile() == 1) return 1;

                printf("\n===============================================================\n");
                printf("O arquivo foi compactado. Deseja continuar usando o programa?\n");
                printf("===============================================================\n");
                printf("\nDigite SIM para prosseguir");
                printf("Digite qualquer outra entrada para sair");
                printf("\n>>> ");
                scanf("%s", &input);

                if(input[0] != 'S' && input[0] != 's'){
                    input[0] = 'F';
                    break;
                }
            }
            else if(input[0] == 'D' || input[0] == 'd'){
                inputValido = 1;
                getchar();
                if(decompressFile() == 1) return 1;
            }
            else{ 
                inputValido = 0;
                printf("Por favor, digite uma entrada valida\n");
                printf("\n>>> ");
            }
        }while(inputValido == 0);

        if(input[0] == 'F' || input[0] == 'f') break;
    }
    
    return 0;
}
