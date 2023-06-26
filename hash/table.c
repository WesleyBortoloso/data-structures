#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNode{
	struct sNode *next;
	struct sNode *prev;
	char name[100];
}Node;

typedef struct sBucket{
  struct sNode *head;
  struct sNode *tail;
  struct sBucket *next;
  struct sBucket *prev;
  int key;
  int size;
} Bucket;

typedef struct sHash{
	struct sBucket *head;
	struct sBucket *tail;
	int size;
	int key;
}Hash;


Hash *createHashTable();
Bucket *alocateBucketMemorie(int key);
Bucket *createBucket(int key);
Bucket *searchBucket(Hash *hash, int key);
Node *alocateNodeMemorie(char *name);
Node* createNode(char *name);
Node *createNode(char *name);
void insertNamesFromFile(Hash *hash);
void insertName(Hash *hash, char *name);
void insertNameInHashTable(Hash *hash, Bucket *bucket, int key, char *name);
void insertNameInBucket(Bucket *bucket, Node *pivot, char *name);
void listAllNames(Hash *hash);
void listNamesPerBucket(Hash *hash);
void listFirstCharOfNames(Hash *hash);
void ordinateBucket(Hash *hash, int ordinate_bucket);
int hashFunction(char *name);
int findName(Hash *hash, char *name);
int removeName(Hash *hash, char *name);

int main(){
  Hash* hashTable = createHashTable();
  char name[100];
  int option;
  int ordinate_bucket;
  
  while(option != 0) {
        printf("\nMENU\n");
        printf("1 - Inserir nomes com arquivo\n");
        printf("2 - Imprimir todos os nomes\n");
        printf("3 - Imprimir quantidade de nomes por bucket\n");
        printf("4 - Imprimir todas as primeiras letras dos nomes dos buckets\n");
        printf("5 - Pesquisar por nome\n");
        printf("6 - Remover nome\n");
        printf("7 - Inserir nome\n");
        printf("8 - Ordenar bucket\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                insertNamesFromFile(hashTable);
                break;
            case 2:
				        listAllNames(hashTable);
                break;
            case 3:
				        listNamesPerBucket(hashTable);
                break;
            case 4:
				        listFirstCharOfNames(hashTable);
                break;
            case 5:
              printf("\nInsira o nome para busca: ");
              scanf("%s", name);

              int result = findName(hashTable, name);
              if (result > 0) {
                printf("\n O nome está localizado no bucket: %d", result);
              } else {
                printf("\n Nome não encontrado(a)");
              }
              break;
            case 6:
              printf("\nInsira o nome para remoção: ");
              scanf("%s", name);

              int remove = removeName(hashTable, name);
              if (remove > 0) {
              	printf("\n O nome foi removido: %d", remove);
              } else {
              	printf("\n Nome não encontrado(a)");
              }
            break;
            case 7:
              printf("\nInsira o nome para inserção:\n");
              scanf("%s", name);

              insertName(hashTable, name);
              break;
            case 8:
              printf("\nInsira um bucket de 1 a 53 para ser ordenado:\n");
              scanf("%d", &ordinate_bucket);

              ordinateBucket(hashTable, ordinate_bucket);
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

void insertNamesFromFile(Hash *hashTable){
	char name[100];
	FILE *file = fopen("nomes.txt", "r");

	if (file == NULL){
    	printf("Arquivo não encontrado.\n");
  	}
  	else{
    	while(!feof(file)){    
			fgets(name, 100, file);
			name[strcspn(name, "\n")] = '\0';
			insertName(hashTable, name);
  		}
		printf("Nomes inseridos com sucesso!\n");
	}
}

void listAllNames(Hash *hashTable) {
  Bucket *bucket = hashTable->head;
  Node *node;
  int total =0;

  while (bucket != NULL){
	node = bucket->head;
	while(node != NULL){
		printf("%s\n", node->name);
		node = node->next;
	}
	total += bucket->size;
	bucket = bucket->next;
  }
  printf("Total de nomes: %i \n", total);
}

void listNamesPerBucket(Hash *hashTable){
  Bucket *bucket = hashTable->head;
  Node *node;

  printf("+----------------+-----------------+\n");
  printf("|     Chave      |    Quantidade   |\n");
  printf("+----------------+-----------------+\n");

  while (bucket != NULL){
	printf("|      %-6i    |      %-6i      |\n", bucket->key, bucket->size);
    bucket = bucket->next;
  }

  printf("+----------------+-----------------+\n");
}

int removeName(Hash *hash, char *name) {
    int key = hashFunction(name);
    Bucket *bucket = searchBucket(hash, key);

    if (bucket != NULL) {
        Node *node = bucket->head;

        while (node != NULL) {
            if (strcmp(node->name, name) == 0) {
                if (node->prev != NULL) {
                    node->prev->next = node->next;
                } else {
                    bucket->head = node->next;
                }

                if (node->next != NULL) {
                    node->next->prev = node->prev;
                } else {
                    bucket->tail = node->prev;
                }

                free(node);
                bucket->size--;

                return key;
            }

            node = node->next;
        }
    }

    return -1;
}

void listFirstCharOfNames(Hash *hashTable) {
  Bucket *bucket = hashTable->head;
  Node *node;

  while (bucket != NULL){
	node = bucket->head;
	printf("Chave: %i \n", bucket->key);

	while(node != NULL){
		printf("%c ", node->name[0]);
		node = node->next;
	}
	bucket = bucket->next;
  }
}

int hashFunction(char *name){
  int key = 0;
  for (int i=0; i<strlen(name); i++){
    key+= 5 * name[i];
  }
  return (key % 53);
}

void insertName(Hash *hashTable, char *name){
	int key = hashFunction(name);
	Bucket *bucket = searchBucket(hashTable, key);
	insertNameInHashTable(hashTable, bucket, key, name);
}

Bucket *createBucket(int key) {
  Bucket *bucket = (Bucket *)malloc(sizeof(Bucket));

  bucket->next = NULL;
  bucket->prev = NULL;
  bucket->key = key;
  bucket->size = 0;

  return bucket;
}

void insertNameInHashTable(Hash *hashTable, Bucket *bucket, int key, char *name){
  if (bucket == NULL) {
    bucket = createBucket(key);

    if (hashTable->size == 0) {
      hashTable->head = bucket;
      hashTable->tail = bucket;
    } else {
      bucket->next = hashTable->head;
      hashTable->head->prev = bucket;
      hashTable->head = bucket;
    }

    hashTable->size++;
  }

  insertNameInBucket(bucket, bucket->tail, name);
}

Node *createNode(char *name) {
  Node *node = (Node *)malloc(sizeof(Node));

  strcpy(node->name, name);
  node->next = NULL;
  node->prev = NULL;

  return node;
}

void insertNameInBucket(Bucket *bucket, Node *pivot, char *name) {
  Node *node = createNode(name);

  if ((pivot == NULL) && (bucket->size != 0)) {
    node->next = bucket->head;
    node->next->prev = node;
    bucket->head = node;

  } else if (bucket->size == 0) {
    bucket->head = node;
    bucket->tail = node;

  } else {
    node->next = pivot->next;
    node->prev = pivot;

    if (pivot->next == NULL) {
      bucket->tail = node;
    } else {
      pivot->next->prev = node;
    }

    pivot->next = node;
  }

  bucket->size++;
}

Bucket *searchBucket(Hash *hash, int key){
	Bucket *bucket = hash->head;

	while(bucket != NULL){
		if(key == bucket->key){
			return bucket;
		}
		bucket = bucket->next;
	}

	return NULL;
}

int findName(Hash *hash, char *name){
	Bucket *bucket = hash->head;
		
	while(bucket != NULL){
		Node *node = bucket->head;
		while (node != NULL) {
			if(strcmp(node->name, name) == 0){
			  return bucket->key;
			}
			node = node->next;
		}
		bucket = bucket->next;
	}
	return -1;
}

Hash* createHashTable(){
  Hash* hash = (Hash*)malloc(sizeof(Hash));
  hash->head = NULL;
  hash->tail = NULL;
  hash->size = 0;
  return hash;
}

Node *partition(Node *head, Node *tail) {
    Node *pivot = tail;
    Node *i = head->prev;

    for (Node *j = head; j != pivot; j = j->next) {
        if (strcmp(j->name, pivot->name) <= 0) {
            if (i == NULL) {
                i = head;
            } else {
                i = i->next;
            }
            char temp[100];
            strcpy(temp, i->name);
            strcpy(i->name, j->name);
            strcpy(j->name, temp);
        }
    }

    if (i == NULL) {
        i = head;
    } else {
        i = i->next;
    }
    char temp[100];
    strcpy(temp, i->name);
    strcpy(i->name, pivot->name);
    strcpy(pivot->name, temp);

    return i;
}

void quickSort(Node *head, Node *tail) {
    if (tail != NULL && head != tail && head != tail->next) {
        Node *pivot = partition(head, tail);
        quickSort(head, pivot->prev);
        quickSort(pivot->next, tail);
    }
}

void printBucket(Bucket *bucket) {
    Node *node = bucket->head;

    while (node != NULL) {
        printf("%s\n", node->name);
        node = node->next;
    }
}

void ordinateBucket(Hash *hash, int ordinate_bucket) {
    Bucket *bucket = searchBucket(hash, ordinate_bucket);

    if (bucket != NULL) {
        quickSort(bucket->head, bucket->tail);
        printf("Bucket %d ordenado.\n", ordinate_bucket);
        printf("Valores no bucket ordenado:\n");
        printBucket(bucket);
    } else {
        printf("Bucket não encontrado.\n");
    }
}
