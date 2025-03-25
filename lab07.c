#include <stdio.h>
#include <stdlib.h>

int resultado = 1; 

typedef struct Cell {
  struct Cell *anterior;
  struct Cell *proximo;
  char valor;
} Cell;

typedef struct {
  Cell *top;
  int qtde;
} Stack;

Cell *start_cell(char valor) {
  Cell *nova = malloc(sizeof(Cell));
  nova->anterior = NULL;
  nova->proximo = NULL;
  nova->valor = valor;
  return nova;
}

Stack *start_stack() {
  Stack *stack = malloc(sizeof(Stack));
  stack->qtde = 0;
  stack->top = NULL;
  return stack;
}

void push(Stack *stack, char valor) {
  Cell *nova = start_cell(valor);
  if (stack->qtde != 0) {
    nova->proximo = stack->top;
    stack->top->anterior = nova;
  }
  stack->top = nova;
  stack->qtde++;
}

char pop(Stack *stack) {
  if (stack->qtde > 0) {
    char valor = stack->top->valor;
    Cell *top = stack->top;
    stack->top = stack->top->proximo;
    if (stack->top != NULL)
      stack->top->anterior = NULL;
    stack->qtde--;
    free(top);
    return valor;
  } else {
    return 'x';
  }
}

int main(void) {
    Stack *stack = start_stack();
    int cont_par = 0;
    int cont_col = 0;
    int cont_cha = 0;
  
    char expr[100];
    fgets(expr, sizeof(expr), stdin);

    for(int i=0; expr[i] != '\0';i++){
        if(expr[i] == '{'){
            push(stack,expr[i]);
            cont_cha ++;
        }

        if(expr[i] == '[' && cont_cha > 0){
            push(stack,expr[i]);
            cont_col ++;
        } else if(cont_cha == 0){
            resultado = 0;
        }

        if(expr[i] == '(' && cont_col > 0){
            push(stack,expr[i]);
            cont_par ++;
        }else if(cont_cha == 0 && cont_col==0){
            resultado = 0;
        }
    }

    for(int i=0; expr[i]!= '\0';i++){
        if(expr[i] == ')' && cont_par > 0 ){
            pop(stack);
            cont_par --;
        } else if(expr[i] == ')' && cont_par == 0){
            resultado = 0;
        }

        if(expr[i] == ']' && cont_col > 0){
            pop(stack);
            cont_col --;
        } else if(expr[i] == ']' && cont_col == 0){
            resultado = 0;
        }

        if(expr[i] == '}' && cont_cha > 0){
            pop(stack);
            cont_cha --;
        }else if(expr[i] == '}' && cont_cha == 0 && cont_par == 0 && cont_col == 0 ){
            resultado = 0;
        }
    }

    if(resultado==1){
        printf("correto");
    }else{
        printf("incorreto");
    }


    return 0;
}

//a bem formada tudo que abre fecha, tem parenteses, cochetes e chaves
// so precisa da main, ja tem a pilha e a string, oq é para fazer, 1 verifica irtera na string e verifica cada caracter, faz um laço e le cada um dos elemsntos cada elemento de abertura poe na pilha stack, ve fechamento tira da pilha o de abertura, faz 3 contadores um p parentes, um colchetes, e um chaves. 
//qnd ve um de abertura incrementa e qnd for fechamento decrementa, o colchete precisa de um parentes e as chaves precisa do colchetes(precisa ser 0)
//int correto seta com 1 e se nos casos tiver errado seta com 0