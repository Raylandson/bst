#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

int main(int argc, char * argv[]) {
    //Declarar uma variável do tipo árvore e inicializar como uma árvore vazia
    Tree arvore = NULL;
    
    //Usando um While true para fazer um menu com switch
    while(1) {
        int opcao;
        int valor, aux, aux2;
        scanf("%d", &opcao);
        switch(opcao) {
            //Inserir
            case 1:
                scanf("%d", &valor);
                arvore = insert(arvore, valor, &aux);
                break;
            case 2:
            //Pre-order
                preOrder(arvore); 
                printf("\n");
                break;
           case 3:
           //Remover
                scanf("%d", &valor);
                arvore = removeBst(arvore, valor, &aux2);
                break;
            case 99:
            //Sair
                exit(0);
        }    
    }
 }