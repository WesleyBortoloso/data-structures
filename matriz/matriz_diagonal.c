#include <stdio.h>
#define COL 5
#define LIN 5

int main()
{
    int mat[LIN][COL], l,c;
    int soma = 0;
    int media = 0;
    
    for(l=0;l<LIN;l++){
        for(c=0;c<COL; c++){
            printf("Digite um valor para a posição mat[%i][%i]:", l,c);
            scanf("%i", &mat[l][c]);
        }
    }
    
    for(l=0;l<LIN;l++){
        for(c=0;c<COL; c++){
            printf("%d, ", mat[l][c]);
        }
        printf("\n");
    }
    
    for(l=0;l<LIN;l++){
        for(c=0;c<COL; c++){
            soma = mat[l][c] + soma;
        }
    }
    
    media = soma / (COL * LIN);
    printf("\nA média das somas é: %i\n", media);
    
    for(l=0;l<LIN;l++){
        for(c=0;c<COL; c++){
            if(l == c){
                if(mat[l][c] > media){
                    printf("%i, ", mat[l][c]);
                }
            }
        }
    }
    
}
