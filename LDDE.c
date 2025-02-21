#include <stdio.h>
#include <stdlib.h>

//ESTRUTURA
typedef struct Celula{
    struct Celula *anterior;
    struct Celula *proximo;
    int valor;
} Celula;

typedef struct {
    Celula *primeiro;
    int qtd;
} LDDE;

//ENTRADAS
Celula *criar_celula(int valor){
    Celula *novo = malloc(sizeof(Celula)); //espaço de memoria alocado
    novo->anterior = NULL;
    novo->proximo = NULL;
    novo->valor = valor;
    return novo;
}

LDDE *criar_lista(){
    LDDE *lista = malloc(sizeof(LDDE));
    lista->primeiro = NULL;
    lista->qtd = 0;
    return lista;
}

//Celulapara valor
void inserir(LDDE *lista, int valor){
    Celula *novo = criar_celula(valor);
    Celula *anterior = NULL;
    Celula *atual = lista->primeiro;
    //posição de inserção
    while(atual != NULL && atual-> valor < novo->valor){
        anterior = atual;
        atual = atual->proximo;
    }

    //Inserir no INICIO:
    if(anterior == NULL){
        lista->primeiro = novo;
        if(atual!= NULL){
            novo ->proximo = atual;
            atual->anterior = novo;
        }
    }else if(atual == NULL){ //Inserir no FINAL
        anterior->proximo = novo;
        novo->anterior= anterior;
    }else { //inserir no MEIO
        anterior->proximo=novo;
        novo->anterior = anterior;
        novo ->proximo = atual;
        atual->anterior = novo; 
    }
    lista-> qtd ++; //incrementação da quantidade
}
