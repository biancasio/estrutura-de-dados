#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
    int valor;
    struct Celula *proximo;
} Celula;

typedef struct {
    Celula *primeiro;
    int qtd;
} LDE;

Celula *criar_celula(int valor){
    Celula *nova = malloc(sizeof(Celula));
    nova->proximo = NULL;
    nova->valor = valor;
    return nova;
}

//Celula *apagar_celula(int scan){
// Celula *apag = malloc(sizeof(Celula));
   // apag->proximo = NULL;
    //apag->scan = scan;
    //return apag;
//}

LDE *criar_lista(){
    LDE *lista = malloc(sizeof(LDE));
    lista->primeiro = NULL;
    lista->qtd = 0;
    return lista;
}

void inserir(LDE *lista, int valor){
    Celula *nova = criar_celula(valor);
    Celula *anterior = NULL;
    Celula *atual = lista->primeiro;
    while(atual != NULL && atual->valor < nova->valor){
        anterior = atual;
        atual = atual->proximo;
    }
    if(anterior == NULL){
        lista->primeiro = nova;
    } else {
        anterior->proximo = nova;
    }
    nova->proximo = atual;
    lista->qtd++;
}

void remover(LDE *lista, int valor) {
    //free(atual)
    Celula *anterior = NULL;
    Celula *atual = lista->primeiro;
    while(atual != NULL && atual->valor != valor){
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL){
        return;
    }
    if(anterior == NULL){ //anterior nulo significa que o meu atual existe
        lista->primeiro = atual->proximo; //remover no inicio
    
    } else{ //
        anterior->proximo = atual->proximo; //remover no meio e no fim

    }lista -> qtd --; //decrementa a qntd 
    free(atual); //remove

}

void mostrar(LDE *lista){
    Celula *atual = lista->primeiro;
    while(atual != NULL){
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

int main(){
    LDE *lista = criar_lista();
    int num;
    for(int i = 0; i < 10; i++){
        scanf("%d", &num);
        inserir(lista, num);
        mostrar(lista);
    }
    for(int i = 0; i < 10; i++){
        scanf("%d", &num);
        remover(lista, num);
        mostrar(lista);
    }
    return 0;
}