#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

Tree insert(Tree root, int nValue){
    // caso base
    if(root == NULL){
        Tree newRoot = (Tree)malloc(sizeof(Node));
        newRoot->left = NULL;
        newRoot->right = NULL;
        newRoot->bf = 0;
        newRoot->value = nValue;
        return newRoot;
    }

    //procura de onde colocar
    if(nValue > root->value){
        root->right = insert(root->right, nValue);
    } else if (nValue < root->value){
        root->left = insert(root->left, nValue);
    }else {
        return root;
    }
        
}

Tree removeBst(Tree root, int rValue){
    //caso base
    if(root == NULL) return root;
    
    //achou
    if (rValue == root->value){
        //sem filhos
        if(root->left == NULL && root->right == NULL){
            free(root);
            root = NULL;
            return root;
        }
        //filho direito
        if(root->left == NULL && root->right != NULL){
            Tree aux = root->right;
            free(root);
            return aux;
        }
        //filho esquerdo      
        if(root->left != NULL && root->right == NULL){
            Tree aux = root->left;
            free(root);
            return aux;
        }
        //dois filhos
        root->value = highestTree(root->left)->value;
        root->left = removeBst(root->left, root->value);
        return root;
    }
    //nao achou
    if(rValue > root->value){
        root->right = removeBst(root->right, rValue);
    } else{
        root->left = removeBst(root->left, rValue);
    }
    return root;
}


Tree highestTree(Tree root){
    if(root == NULL) return NULL;
    
    if(root->right != NULL){
        return highestTree(root->right);
    }
    return root;
}


void preOrder(Tree root){
    if (root == NULL) return;
    printf("[%d]", root->value);
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Tree root){
    if(root == NULL) return;
    inOrder(root->left);
    printf("[%d]", root->value);
    inOrder(root->right);
}

void inOrderReverse(Tree root){
    if(root == NULL) return;
    inOrderReverse(root->right);
    printf("[%d]", root->value);
    inOrderReverse(root->left);
}

void posOrder(Tree root){
    if (root == NULL) return;
    posOrder(root->left);
    posOrder(root->right);
    printf("[%d]", root->value);
}


int max(int a, int b){
    if(a > b) return a;
    return b;
}


int treeHeight(Tree root){
    if(root == NULL) return 0;

    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);

    return max(leftHeight, rightHeight) + 1;
}

int leafQuantity(Tree root){
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;

    int l = leafQuantity(root->left);
    int r = leafQuantity(root->right);
    
    return l + r;
}

void findValue2(Tree root, int sValue){
    Tree auxRoot = root;
    // find the value
    while (1)
    {
        if (auxRoot == NULL) return;
        
        if(auxRoot->value > sValue){
            auxRoot = auxRoot->left;
        } else if (auxRoot->value < sValue){
            auxRoot = auxRoot->right;
        } else{
            break;
        }
    }
    Tree auxRoot = root;
    
    while(auxRoot != NULL){
        printf("[%d]", auxRoot->value);
        if(auxRoot->value > sValue){
            auxRoot = auxRoot->left;
        } else{
            auxRoot = auxRoot->right;
        }
    }

}
