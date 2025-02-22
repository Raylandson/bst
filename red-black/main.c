#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

int main(int argc, char * argv[]) {
    //Declarar uma variável do tipo árvore e inicializar como uma árvore vazia
    Tree arvore = NULL;
    insert(&arvore, 25);
    preOrder(arvore);
    insert(&arvore, 22);
    preOrder(arvore);
    insert(&arvore, 23);
    preOrder(arvore);
    
    //Usando um While true para fazer um menu com switch
    return 0;
    while(1) {
        int opcao;
        int valor;
        scanf("%d", &opcao);
        switch(opcao) {
            //Inserir
            case 1:
                scanf("%d", &valor);
                insert(&arvore, valor);
                break;
            case 2:
            //Pre-order
                preOrder(arvore); 
                printf("\n");
                break;
           case 3:
           //Remover
                scanf("%d", &valor);
                removeBst(&arvore, valor);
                break;
            case 99:
            //Sair
                exit(0);
        }    
    }
 }
