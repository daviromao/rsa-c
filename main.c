#include <stdio.h>
#include "libs/rsa.c"

void menu(){
    printf("1 - Criar chaves publica\n");
    printf("2 - Criptografar\n");
    printf("3 - Descriptografar\n");
    printf("4 - Sair\n\n");
    printf("Digite a opcao desejada: ");
    int opcao;
    scanf("%d", &opcao);
    scanf("%*c");

    switch(opcao){
        case 1:
            generate_public_key();
            break;
        case 2:
            encrypt();
            break;
        case 3:
            decrypt();
            break;
        case 4:
            return;
            break;
        default:
            printf("Opcao invalida\n");
            break;
    }

}

int main(){
    menu();
    return 0;
}