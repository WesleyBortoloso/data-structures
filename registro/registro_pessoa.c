#include <stdio.h>
#include <string.h>

typedef struct{
    char nome[50];
    char cpf[11];
    char data_de_nascimento[20];
}Pessoa;

Pessoa pessoa1;

int main()
{
    strcpy(pessoa1.nome, "Joao");
    strcpy(pessoa1.cpf, "12345678911");
    strcpy(pessoa1.data_de_nascimento, "05/03/02");
    
    printf("%s \n", pessoa1.nome);
    printf("%s \n", pessoa1.cpf);
    printf("%s \n", pessoa1.data_de_nascimento);
    
}