#include <stdlib.h>
#include <stdio.h>

//MODELO PARA UMA CELULA
typedef struct Celula { //o typedef serve para nomear a estrutura no final
    int valor;
    struct Celula *proximo; //se refere ao mesmo tipo de dado construido aq, ele vai ter um ponteiro para o proximo elemento da celula
} Celula;

typedef struct{
    Celula *primeiro; // ponteiro para o primeiro numero
    int qtd; // qtd de numeros na lista
} LDE; //esse é o nome

// cria a celula e me retorna o endereço
Celula *criar_celula(int valor){
    Celula *nova = malloc(sizeof(Celula)); //qnts bites esse tipo de dado precisa //ponteiro para o primeiro bite alocado
    nova->proximo = NULL;   //a setinha serve para chamar os membros
    nova->valor = valor;
    return nova;
}

//LISTA
LDE *criar_lista(){
    LDE *lista = malloc(sizeof(LDE));
    lista ->primeiro = NULL;
    lista -> qtd = 0;
    return lista;
}

void inserir(LDE *lista, int valor){
    Celula *nova = criar_celula(valor);
    if (lista->primeiro == NULL){
        lista->primeiro = nova;
        lista-> qtd++;
    }
    Celula *anterior = NULL;
    Celula *atual = lista->primeiro;
    while(atual!= NULL && atual->valor < nova->valor){
        anterior = atual;
        atual = atual->proximo;
    }
    if (anterior == NULL && atual!= NULL){
        nova->proximo = atual;
        lista->primeiro = nova;
    }
    if(anterior !=NULL && atual== NULL){
        anterior->proximo=nova;
    }
    if(anterior !=NULL && atual != NULL){
        anterior->proximo=nova;
        nova->proximo = atual;
    }
    lista ->qtd++;
}
void mostrar (LDE *lista){
    Celula *atual = lista->primeiro;
    while (atual != NULL){
        printf("%d", atual->valor);
        atual= atual->proximo;
    }
    printf("\n");
}
int main(){
    LDE *lista = criar_lista();
    for(int i = 10 ; i>0; i--);
    inserir(lista, i);
    mostrar(lista);
}