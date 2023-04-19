#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 100


typedef struct sNode {
    struct sNode *next; 
    char value;
} Node;

typedef struct sStack {
    struct sNode *head;
    struct sNode *tail;
    int size;
} Stack;

Stack* createStack();
Node* createNode(char value);
void push(Stack* stack,char value);
char pop(Stack* stack);
char stackTop(Stack* stack);
void displayStack(Stack* stack);
void isBalanced(Stack*, char exp[]);

int main(){
   Stack* stack = createStack();
    //char exp[TAM]= "7+ {A} +- (B{CCCC}) {([M]T)U} ([{";
    //char exp[TAM]= "(A + B} )";
    //char exp[TAM]= "{[A + B] - [(C - D)]";
    //char exp[TAM]= "(A + B)-{C + D}-[F+ G]";
    //char exp[TAM]= "((H) * {([J + K])})";
    char exp[TAM]= "((((A))))";
   printf("%s\n",exp);
   isBalanced(stack,exp);
   displayStack(stack);
   free(stack);
}

Stack* createStack(){
    Stack* stack = (Stack*)malloc(sizeof(Stack));

    stack->head = NULL;
    stack->tail = NULL;
    stack->size = 0;
    return stack;
}

Node* createNode(char value){
    Node* node = (Node*)malloc(sizeof(Node));
    
    node->next = NULL;
    node->value = value;
    return node;
}

void displayStack(Stack* stack){
    Node* pivot = stack->head;
    if (stack->size < 0){
        printf("A pilha esta vazia!");
    }
    else{
        printf("Elementos restantes na pilha: ");
        while (pivot != NULL){
            printf("%c", pivot->value);
            pivot = pivot->next;
        }
        printf("\n");
    }
}


void isBalanced(Stack* stack,char exp[]){
    int i;
    char aux;
    for( i=0; i< TAM ; i++){ 
        switch (exp[i]){
            case '(':
            push(stack,'(');
            break;

            case '[':
            push(stack,'[');
            break;

            case '{':
            push(stack,'{');
            break;

            case ')':
            aux= stackTop(stack);
            if(aux=='('){
                pop(stack);
            }else{
                printf("\nExpressao invalida");
                exit(0);
            }
            break;

            case ']':
            aux= stackTop(stack);
            if(aux=='['){
                pop(stack);
            }else{
                printf("\nExpressao invalida");
                exit(0);
            }
            break;

            case '}':
            aux= stackTop(stack);
            if(aux=='{'){
                pop(stack);
            } else{
                printf("\nExpressao invalida");
                exit(0);
            }
            break;
        }
    }
    if(stack->size == 0){
        printf("\nExpressao valida!\n");
    } else{
        printf("\nExpressao invalida!\n");
    }

}


void push(Stack* stack,char value){
    Node* new = createNode(value);
    new->next = stack->head;
    stack->head = new;
    printf("Inserido:%c\n",stack->head->value);
    stack->size++;
}

char pop(Stack* stack){
    Node* removed = stack->head;
    char dado;
    if(stack->size == 0){
        printf("Fila esta vazia");
    }else{
        stack->head = removed->next;
        removed->next = NULL;
    }
    dado = removed->value;
    free(removed);
    stack->size--;
    printf("Excluido:%c\n",dado);
	return dado;
}

char stackTop(Stack* stack){
    char top;
    if(stack->size != 0){
        top = stack->head->value;
        return top;
    }else{
    	printf("A pilha esta vazia");
    	exit(0); 
	}
}