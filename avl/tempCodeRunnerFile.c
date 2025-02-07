#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

int main(){
    Tree myTree = NULL;
    myTree = insert(myTree, 1);

    preOrder(myTree);

    return 0;
}