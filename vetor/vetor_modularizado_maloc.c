#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 10

void criaVetor(int *vetor);
void imprimeVetor(int *vetor);


int main()
{
    int *vetor = (int *) malloc(sizeof(int) * TAM);
    criaVetor(vetor);
    imprimeVetor(vetor);
    
    free(vetor);
}

void criaVetor(int *vetor){
    for(int i=0;i<TAM;i++){
        printf("Insira um valor para a posição %i: ", i);
        scanf("%d", &vetor[i]);
    }
}

void imprimeVetor(int *vetor){
    for(int i=0;i<TAM;i++){
        printf("%i, ", vetor[i]);
    }
}