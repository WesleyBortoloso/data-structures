#include <stdio.h>
#include <stdlib.h>

typedef struct sNode{
    int value;
    struct sNode *next;
    struct sNode *prev;
}Node;

typedef struct sQueue{
    struct sNode *front;
    struct sNode *rear;
    int size;
}Queue;


Queue* createQueue();
Node* createNode(int value);
void insertInQueue(Queue*);
int removeFromQueue(Queue*);
void printQueue(Queue*);
int empty(Queue*);

int main()
{
    Queue *queue = createQueue();
    int removed, value, option;
    Node* node;

    while(1) {
        printf("\nMENU\n");
        printf("1 - Inserir elemento na fila\n");
        printf("2 - Remover elemento da fila\n");
        printf("3 - Exibir fila\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                insertInQueue(queue);
                break;
            case 2:
                value = removeFromQueue(queue);
                if (value == -1) {
                    printf("Fila vazia.\n");
                }  else {
                    printf("Elemento %d removido da fila.\n", value);
                }
                break;
            case 3:
                printQueue(queue);
                break;
            case 0:
                printf("Encerrando programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }
}

Queue* createQueue(){
    Queue* queue = (Queue*) malloc(sizeof(Queue));

    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

Node* createNode(int value){
    Node* node;
    node = (Node*)malloc(sizeof(Node));
    
    node ->next = NULL;
    node->prev = NULL;
    node ->value = value;
    
    return node;
}

void insertInQueue(Queue* queue){
    Node* new;
    int value;
    printf("Insira um valor para o novo elemento: ");
    scanf("%i", &value);

    new = createNode(value);

    if((queue->front == NULL)&&(queue->rear == NULL)){
        queue->front = new;
        queue->rear = new;
    }else{
        new->prev = queue->rear;
        queue->rear->next = new;
        queue->rear = new;
    }
    queue->size++;
}

int empty(Queue* queue){
	if(queue->front > queue->rear){
    return 1;
  }else{
    return 0;
  }
}

int removeFromQueue(Queue* queue){
    if(empty(queue) == 1){
        return -1;
    }

    int value;
    Node* pivot = queue->front;
    queue->front = queue->front->next;
    value = pivot->value;
    
    free(pivot);
    queue->size--;
    return value;
}

void printQueue(Queue* queue){
    Node* pivot = queue->front;
    printf("Queue: ");
    for(int i = 0; i < queue->size; i++){
        printf("%i ", pivot->value);
        pivot = pivot->next;
    }
    printf("\n");
}
