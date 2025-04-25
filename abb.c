void in_order(raiz){
    if (raiz == NULL){
        return;
    }
    in_order(raiz->esq);
    printf("%d", raiz->valor);
    in_order(raiz->dir);
}