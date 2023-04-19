#include <stdio.h>
#include <stdlib.h>
#define QUEUE 5

typedef struct sCar{
    int license;
    int changes;
    struct sCar *next;
    struct sCar *prev;
}Car;

typedef struct sPark{
    struct sCar *front;
    struct sCar *rear;
    int size;
}Park;


Park* createPark();
Car* searchInPark(Park*, int license);
Car* createCar(int license);
void insertCar(Park*, Park*);
void insertWaitingCar(Park*, int license);
void insertCarInWait(Park*, int license);
int removeCar(Park*, Park*);
void printPark(Park*, Park*);
int empty(Park*);

int main()
{
    Park* park = createPark();
    Park* waitPark = createPark();
    int removed, value, option;
    Car* car;

    while(1) {
        printf("\nMENU\n");
        printf("1 - Inserir carro no estacionamento\n");
        printf("2 - Remover carro do estacionamento\n");
        printf("3 - Exibir estacionamento\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                insertCar(park, waitPark);
                break;
            case 2:
                value = removeCar(park, waitPark);
                if (value == -1) {
                    printf("Estacionamento vazio.\n");
                }  else {
                    printf("Carro %d removido do estacionamento.\n", value);
                }
                break;
            case 3:
                printPark(park, waitPark);
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

void printPark(Park* park, Park* waitPark){
    Car* pivotPark = park->front;
    printf("Estacionamento: ");
    for(int i = 0; i < park->size; i++){
        printf("%i ", pivotPark->license);
        pivotPark = pivotPark->next;
    }
    printf("\n");
    
    Car* pivotWaitPark = waitPark->front;
    printf("Lista de espera estacionamento: ");
    for(int i = 0; i < waitPark->size; i++){
        printf("%i ", pivotWaitPark->license);
        pivotWaitPark = pivotWaitPark->next;
    }
    printf("\n");
}

Park* createPark(){
    Park* park = (Park*)malloc(sizeof(Park));
    park->front = NULL;
    park->rear = NULL;
    park->size = 0;
    return park;
}

Car* createCar(int license){
    Car* car = (Car*)malloc(sizeof(Car));
    
    car ->next = NULL;
    car->prev = NULL;
    car ->license = license;
    car->changes = 0;
    
    return car;
}

void insertCar(Park* park, Park* waitPark){
	int license;
    printf("Insira um valor para a placa do novo carro: ");
    scanf("%i", &license);

	Car* new = createCar(license);
	
	if(park->size < QUEUE){
		if(park->front == NULL){
			park->front = new;
			park->rear = new;	
		}else{
			new->prev = park->rear;
			park->rear->next = new;
			park->rear = new;
		}
        printf("Carro estacionado: %i\n",license);
        park->size++;
    }else{
        printf("Carro adicionado a lista de espera: %i\n",license);
        insertCarInWait(waitPark, license);
    }
}

void insertWaitingCar(Park* park, int license){

	Car* new = createCar(license);
	
	if(park->size < QUEUE){
		if(park->front == NULL){
			park->front = new;
			park->rear = new;	
		}else{
			new->prev = park->rear;
			park->rear->next = new;
			park->rear = new;
		}
        printf("Carro estacionado: %i\n",license);
        park->size++;
	}
}

void insertCarInWait(Park* waitPark,int license){
    Car* new = createCar(license);
    if(waitPark->rear == NULL){
			waitPark->front = new;
			waitPark->rear = new;
		}else{
			new->prev = waitPark->rear;
			waitPark->rear->next = new;
			waitPark->rear = new;	
		}
        waitPark->size++;
}

Car* searchInPark(Park* park, int license){
    Car* car;
    car = park->front;

    while(car != NULL){
        if(car->license == license){
            return car;
        }
        car = car->next;
    }
    return NULL;
}

int removeCar(Park* park, Park* waitPark){
    int license;
    printf("Insira um valor para a placa do carro que deve ser removido: ");
    scanf("%i", &license);

    Car* car = searchInPark(park, license);
    if(car != NULL){
        if(car == park->front){
            park->front = car->next;
            if(park->front != NULL){
                park->front->prev = NULL;
            }
        }else if(car == park->rear){
            park->rear = car->prev;
            if(park->rear != NULL){
                park->rear->next = NULL;
            }
        }else{
            car->prev->next = car->next;
            car->next->prev = car->prev;
        }
        park->size--;
        printf("Carro %d removido do estacionamento.\n", license);

        if(waitPark->size > 0){
            int waitLicense = waitPark->front->license;
            Car* waitCar = createCar(waitLicense);
            waitPark->front = waitPark->front->next;
            if(waitPark->front == NULL){
                waitPark->rear = NULL;
            }else{
                waitPark->front->prev = NULL;
            }
            waitPark->size--;
            insertWaitingCar(park, waitLicense);
            printf("Carro %d adicionado do estacionamento.\n", waitLicense);
        }
        return license;
    }else{
        printf("Carro %d nao encontrado no estacionamento.\n", license);
        return -1;
    }
}