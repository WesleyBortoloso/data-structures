#include <stdio.h>
#include <string.h>

typedef struct{
    int matricula;
    char nome[40];
    char cpf[40];
    int idade;
}Aluno;

Aluno aluno1;

int main()
{
    aluno1.matricula = 12345;
    aluno1.idade = 16;
    strcpy(aluno1.nome, "Joao");
    strcpy(aluno1.cpf, "12345678911");

    printf("%s \n", aluno1.nome);
    printf("%i \n", aluno1.matricula);
    printf("%s \n", aluno1.cpf);
    printf("%i \n", aluno1.idade);
    
}