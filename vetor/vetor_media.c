#include <stdio.h>
#define TAM 5

int main()
{
    int vet[TAM], j;
    int soma = 0;
    int media = 0;
    
    for(j=0;j<TAM;j++){
        printf("Digite um valor para a posição vet[%i]:", j);
        scanf("%i", &vet[j]);
    }
    
    for (j=0;  j < TAM;  j++){
	    printf("%i, ", vet[j]);
    }
    
    for (j=0; j < TAM; j++){
        soma = vet[j] + soma;
    }
    
    media = soma / TAM;
    printf("\nA média das somas é: %i\n", media);
    
    for (j=0; j < TAM; j++){
        if(vet[j] > media){
            printf("%i, ", vet[j]);
        }
    }
    
}
