#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

typedef struct sNode{
    int value;
    struct sNode *next;
}Node;

typedef struct sList{
    struct sNode *head;
    struct sNode *tail;
    int size;
}List;

List* createList();
Node* createNode();
int insertInList(Node*, List*);
int removeFromList(List*);
void printList(List*);
Node* searchInList(List*); 

int main()
{
    List *list = createList();
    int removed, value, option;
    Node* node;
    
    
    while(1) {
        printf("\nMENU\n");
        printf("1 - Inserir elemento na lista\n");
        printf("2 - Remover elemento da lista\n");
        printf("3 - Procurar elemento na lista\n");
        printf("4 - Exibir lista\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                insertInList(NULL, list);
                break;
            case 2:
                value = removeFromList(list);
                if (value == -1) {
                    printf("Lista vazia.\n");
                } else if (value == 0) {
                    printf("Elemento nao encontrado.\n");
                } else {
                    printf("Elemento %d removido da lista.\n", value);
                }
                break;
            case 3:
                node = searchInList(list);
                if (node == NULL) {
                    printf("Elemento nao encontrado.\n");
                } else {
                    printf("Elemento %d encontrado na lista.\n", node->value);
                }
                break;
            case 4:
                printList(list);
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


List* createList(){
    List* list = (List*) malloc(sizeof(List));
    list -> head = NULL;
    list -> tail = NULL;
    list -> size = 0;
    
    return list;
}

Node* createNode(int value){
    Node* node;
    node = (Node*)malloc(sizeof(Node));
    
    node -> next = NULL;
    node -> value = value;
    
    return node;
}

int insertInList(Node* pivot, List* list){
    Node* new;
    int value;
    printf("Insira um valor para o novo elemento: ");
    scanf("%i", &value);

    new = createNode(value);
    
    if(pivot == NULL){
        if(list->size == 0){
            list->tail = new;
        }
        new->next = list->head;
        list->head = new;
    }else {
        if(pivot->next == NULL){
            list->tail = new;
        }
        new->next = pivot->next;
        pivot->next = new;
    }
    list->size++;
    return list->size;
}

int removeFromList(List* list){
    int value;
    Node* current = list ->head;
    Node* pivot = NULL;
    
    printf("Insira um valor para remover da lista: ");
    scanf("%i", &value);
    
    if(list->size == 0){
        return -1; 
    }

    while (current != NULL && current->value != value) {
        pivot = current;
        current = current->next;
    }

    if (current != NULL) {
        if (pivot == NULL) {
            list->head = current->next;
        } else {
            pivot->next = current->next;
        }

        if (current == list->tail) {
            list->tail = pivot;
        }

        list->size--;
        free(current);
        return value;
    }
    
}

void printList(List* list){
    Node* node;
    node = list->head;
    
    while(node != NULL){
        printf("%i -> ",node->value);
        node = node->next;
    }
  printf("NULL\n");
}

Node* searchInList(List* list){
    int value;
    Node* node;
    node = list->head;
    
    printf("Insira um valor para verificar se existe na lista: ");
    scanf("%i", &value);

    while(node != NULL){
        if(node->value == value){
            return node;
        }
        node = node->next;
    }
    return NULL;
}


