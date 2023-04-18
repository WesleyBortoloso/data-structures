#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 3

typedef struct{
    char nome[50];
    char cpf[12];
    int idade;
    float salario;
}Pessoa;

void criaVetor(Pessoa *vetor);
void imprimeVetor(Pessoa *vetor);

int main()
{
    Pessoa *vetor = (Pessoa *) malloc(sizeof(Pessoa) * TAM);
    criaVetor(vetor);
    imprimeVetor(vetor);
    
    free(vetor);
}

void criaVetor(Pessoa *vetor){
    for(int i=0;i<TAM;i++){
        printf("Insira um nome para a pessoa %i: ", i + 1);
        scanf("%s", vetor[i].nome);
        printf("Insira um cpf para a pessoa %i: ", i + 1);
        scanf("%s", vetor[i].cpf);
        printf("Insira uma idade para a pessoa %i: ", i + 1);
        scanf("%i", &vetor[i].idade);
        printf("Insira um salario para a pessoa %i: ", i + 1);
        scanf("%f", &vetor[i].salario);
    }
}

void imprimeVetor(Pessoa *vetor){
    for(int i=0;i<TAM;i++){
        printf("Nome da pessoa: %s \n", vetor[i].nome);
        printf("CPF da pessoa: %s \n", vetor[i].cpf);
        printf("Idade da pessoa: %i \n", vetor[i].idade);
        printf("Salario da pessoa: %f \n", vetor[i].salario);
        printf("\n");
    }
}