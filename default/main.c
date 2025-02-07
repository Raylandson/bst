#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

int main(int argc, char * argv[]) {
    //Declarar uma variável do tipo árvore e inicializar como uma árvore vazia
    Tree arvore = NULL;
    
    //Usando um While true para fazer um menu com switch
    while(1) {
        int opcao;
        int valor, aux;
        scanf("%d", &opcao);
        switch(opcao) {
            //Inserir
            case 1:
                scanf("%d", &valor);
                arvore = insert(arvore, valor);
                break;
            case 2:
            //Pre-order
                preOrder(arvore); 
                printf("\n");
                break;
            case 3:
            //inorder
                inOrder(arvore);
                printf("\n");
                break;
            case 4:
            //posorder
                posOrder(arvore);
                printf("\n");
                break;
            case 5:
            //inorder
                inOrderReverse(arvore);
                printf("\n");
                break;
            case 6:
            //height
                printf("%d", treeHeight(arvore));
                printf("\n");
                break;
            case 7:
            //height
                printf("%d", leafQuantity(arvore));
                printf("\n");
                break;
            case 8:
            //height
                scanf("%d", &valor);
                findValue(arvore, valor);
                printf("\n");
                break;
            case 9:
            //Remover
                scanf("%d", &valor);
                arvore = removeBst(arvore, valor);
                break;
            case 99:
            //Sair
                exit(0);
                break;
        }    
    }
 }
