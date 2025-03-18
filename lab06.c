#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
	int valor;
	struct Celula *proximo;
	struct Celula *anterior;
} Celula;

typedef struct {
	Celula *head;
	Celula *tail;
	int qtde;
} Queue;

Celula *cria_celula(int valor){
	Celula *celula = malloc(sizeof(Celula));
	celula->proximo = NULL;
	celula->anterior = NULL;
	celula->valor = valor;

	return celula;
}

Queue *cria_queue(){
	Queue *queue = malloc(sizeof(Queue));
	queue->head = NULL;
	queue->tail = NULL;
	queue->qtde = 0;

	return queue;
}

void enqueue(Queue *queue, int valor){
    Celula *nova = cria_celula(valor);
    if(queue->qtde==0){
        queue->head=nova;
    }else{
        queue->tail->proximo=nova;
        nova->anterior=queue->tail;
    }
    queue->tail=nova;
    queue->qtde++;
}

int dequeue(Queue *queue){
    if(queue->qtde == 0){
        return -1;
    }
    Celula *liberar = queue->head;
    int valor = queue ->head->valor;
    if(queue->qtde ==1){

        queue->head = NULL;
        queue->tail = NULL;
    }else{
        queue->head->proximo->anterior = NULL;
        queue->head = queue->head->proximo;
    }
    queue->qtde--;
    free(liberar);
    return valor;
}

void show(Queue *queue){
    Celula *atual = queue->head;
        while(atual != NULL){
            printf("%d ", atual->valor);
            atual= atual->proximo;
        } 
}

void show_invertido(Queue *queue){
	Celula *atual = queue->tail;
        while(atual != NULL){
            printf("%d ", atual->valor);
            atual= atual->anterior;
        }
}

int main(void) {
	Queue *qnum1 = cria_queue();
	Queue *qnum2 = cria_queue();
	Queue *res = cria_queue();
	
	char num1[100];
	char num2[100];
	fgets(num1, sizeof(num1), stdin); //moodle vai dae
	fgets(num2, sizeof(num2), stdin);

	int i = 0; //intera os cara e pega cada um dos numeros e coloca em uma fila correspondente
	while(num1[i] != '\n'){		
		enqueue(qnum1, (int)(num1[i]) - 48);
		enqueue(qnum2, (int)(num2[i]) - 48);
		i++;
	}

    Celula *n1 = qnum1->tail;
    Celula *n2 = qnum2->tail;
    int carry = 0;
    int total = 0;
    
    while(n1 != NULL){
        total = n1->valor + n2-> valor + carry;
    
        if (total>9){
            total = total-10;
            carry = 1;
        }
        else{
            carry = 0;
        }
    
    
        n1 = n1->anterior;
        n2 = n2-> anterior;
        enqueue(res,total);
    }
    
    if(carry==1){
        enqueue(res,carry);
    }
    show_invertido(res);	
}
//interar do final para o começo, pega os valores da posição e soma os caras e pega o resto para somar na proximna interação
//ai imprime invertido isso