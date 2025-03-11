#include <stdio.h>


#define LEN 100

typedef struct {
	char data[LEN];
	int head;
	int tail;
	int qtde;
} Queue;

void enqueue(Queue *queue, char caracter) {
    if (queue-> qtde == LEN){ //verifica se esta cheia
        return;
    }
    queue-> data[queue->tail++]=caracter; //se não estiver eu coloco no final
    queue->qtde++;

}

int dequeue(Queue *queue) {
    if (queue->qtde==0){ //se nao consigo tirar da fila
        return 0;
    }
    char valor = queue-> data[queue-> head ++];
    queue->qtde--;
    return valor;
}

void show(Queue *queue) {
    for(int i = queue-> head; i< queue->tail; i++){
        printf("%c",queue->data[i]);
    }
}

void start_queue(Queue *queue) {
    queue->head = 0;
    queue->tail = 0;
    queue->qtde = 0;
}

int is_empty(Queue * q){
    return q->qtde ==0;
}

int main(void) {
    char s[LEN];
    fgets(s, sizeof(s), stdin);
    Queue queue; //cria fila
    Queue nova_fila; //cria fila

    
    start_queue(&queue); // inicializa
    start_queue(&nova_fila);

    for (int i = 0; s[i] != '\0'; i++) { //caracter a caracter
        enqueue(&queue, s[i]); //implementa
    }
     
    // implementar
    for (int i = 0; s[i] != '\0'; i++) { //caracter a caracter
        if(s[i]=='('){
            enqueue(&nova_fila, s[i]);
        }
        if(s[i]==')'){ 
            if (is_empty(&nova_fila)){
                printf("incorreto") //se nao consigo tirar da fila
                return 0;
            }
            else{
                dequeue(&nova_fila);
            }
            
        
        }

        dequeue(&queue);
        show(&queue);
    }
    
    
    if(dequeue(&nova_fila)== 0){
        printf("correto");
    }
    else{
        printf("incorreto");
    }

    

    return 0;
} //faz duas filas ai uma vazia vai colocar os parenteses qnd eles aparecem na fila acima

