#include <stdio.h>
#include <stdlib.h>

#define LEN 10

typedef struct {
  int valores[LEN];
  int qtde;
} heap;

int filho_esq(int pai) { 
    // fe = 2*i+1
    int fe = (2*pai) +1;
    return fe;
    }

int filho_dir(int pai) { 
    //fd = 2*i+2
    int fd = (2*pai) + 2;
    return fd;
    }

int pai(int filho) { 
    // p = (i-1)/2]
    int p = (filho-1)/2;
    return p;
    }

int ultimo_pai(heap *h) { 
    // up = [n/2]-1
    int up = (h->qtde/2)-1;
    return up;
}

void peneirar(heap *h, int pai) {
  // qual dos 3 é o maior se for o pai n faz nada, se não for o pai troca o valor e chama o peneirar

  int fd = filho_dir (pai);
  int fe = filho_esq(pai);

  int maior = pai;
  if(fd<h->qtde && h->valores[fd]>h->valores[maior]){
    maior = fd;
  }
  if(fe<h->qtde && h->valores[fe]>h->valores[maior]){
    maior = fe;
  }
  if(maior!=pai){
    int aux = h->valores[pai];
    h->valores[pai]=h->valores[maior];
    h->valores[maior]=aux;
    peneirar(h,maior);
  }
}

void mostrar(heap *h) {
    for(int i = 0; i< h->qtde; i++){
        printf("%d ",h->valores[i]);
    }
    printf("\n");
}

void construir(heap *h) {
  // ultimo pai ate a raiz e peneira todos
  int up = ultimo_pai(h);
  while (up != -1 ){
    peneirar(h, up);
    up --;
  }
}

void inserir(heap *h, int valor) {
  // primeira posição disponivel mais a esquerda (valor dentro da primeira posição disponivel); vai chamar o construir
  h->valores[h->qtde ++] = valor;

  //correto
  int p = pai(h->qtde-1);
  if(h->valores[p]<h->valores[h->qtde-1]){
    construir (h);
  }

  //fazer 
    //construir (h);
}

void remover(heap *h) {
    h->valores [0] = h->valores[h->qtde-1];
    h->qtde --;
    construir(h);

}

int main(void) {
  heap *h = malloc(sizeof(heap));
  int valor;
  h->qtde = 0;
  for (int i = 0; i < LEN; i++) {
    scanf("%d", &valor);
    inserir(h, valor);
    mostrar(h);
  }
  for (int i = 0; i < LEN; i++) {
    remover(h);
    mostrar(h);
  }

  return 0;
}