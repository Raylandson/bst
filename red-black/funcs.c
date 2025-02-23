#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"


void insert(MainTree root, int value){
    // caso base
    //if(root == NULL) return root;
    printf("adding value %d\n", value);
    Tree aux = *root;
    Tree fatherAux = aux;
    while(aux != NULL){
      fatherAux = aux;
      if(aux->value > value){
        aux = aux->left;
      } else if(aux->value < value){
        aux = aux->right;
      } else if(aux->value == value){
        return;
      }
    }
    //creating new node
    Tree newNode = (Tree)malloc(sizeof(Node));
    newNode->value = value;
    newNode->color = RED;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->father = fatherAux;
    if (newNode->father == NULL){
      *root = newNode;
      newNode->color = BLACK;
      //printf("new node father null\n");
      return;
    }
    if(fatherAux->value > value){
      fatherAux->left = newNode;
    } else{
      fatherAux->right = newNode;
    }
    
    aux = newNode;
    while(color(father(aux)) == RED && color(aux) == RED){
      //case no 1, recoloring
      if(color(uncle(aux)) == RED){
        printf("recolorindo\n");
        uncle(aux)->color = BLACK;
        father(aux)->color = BLACK;
        if(grandFather(aux) != NULL) grandFather(aux)->color = RED;
        aux = grandFather(aux);
        continue;
      }
      //case no 2, simple rotation
      if (color(uncle(aux)) == BLACK){
        //simple left rotation
        if(rightChild(aux) && rightChild(father(aux))){
          printf("simple left rotation\n");

          simpleLeftRotation(aux, root);

          father(aux)->color = BLACK;
          sibling(aux)->color = RED;
          break;
        }
        //double left rotation
        if(!rightChild(aux) && rightChild(father(aux))){
          printf("double left rotation\n");
          Tree gf = grandFather(aux);
          doubleLeftRotation(aux, root);
          aux->color = BLACK;
          gf->color = RED;
          break;
        }
        

        if(!rightChild(aux) && !rightChild(father(aux))){
          printf("simple right rotation\n");

          simpleRightRotation(aux, root);
          father(aux)->color = BLACK;
          sibling(aux)->color = RED;
          break;
        }

        if(rightChild(aux) && !rightChild(father(aux))){
          printf("double right rotation\n");
          Tree gf = grandFather(aux);
          doubleRightRotation(aux, root);
          aux->color = BLACK;
          gf->color = RED;
          break;
        }

      }
    }  
    
    (*root)->color = BLACK;
}

void removeBst(MainTree root, int value){
}

Color color(Tree root){
  if(root == NULL || root->color == BLACK) return BLACK;
  if(root->color == RED) return RED;
  return DOUBLE_BLACK;
}


Tree father(Tree root) {
    if (root == NULL) {
        return NULL;
    }
    return root->father;
}

Tree grandFather(Tree root) {
    if (root == NULL) {
        return NULL; 
    }
    return father(father(root));
}

Tree uncle(Tree root) {
    if (root == NULL) {
        return NULL; 
    }
    Tree f = father(root);
    Tree gf = grandFather(root);
    if (gf == NULL) {
        return NULL;
    }
    if (f == gf->left) {
        return gf->right;
    } else {
        return gf->left;
    }
}

Tree sibling(Tree root) {
    if (root == NULL) {
        return NULL;
    }
    Tree f = father(root);
    if (f == NULL) {
        return NULL;
    }
    if (root == f->left) {
        return f->right;
    } else {
        return f->left;
    }
}

int rightChild(Tree root){
  if(father(root) == NULL || root == NULL) return 0;
  return (father(root)->right == root);
}


/*
x
/   \
y     t3
/   \
t1    t2

y
/    \
t1     x 
/   \
t2   t3

*/
//calcula os nos

void simpleRightRotation(Tree root, MainTree mainRoot){
    Tree nodeFa = father(root);
    Tree nodeGf = grandFather(root);
    Tree gfFather = father(nodeGf);
    // Tree nodeSi = sibling(root);
    
    if(nodeFa == NULL || nodeGf == NULL) return;
    
    if(gfFather != NULL){
      if(rightChild(nodeGf)){
        gfFather->right = nodeFa;
      } else{
        gfFather->left = nodeFa;
      }
    } else {
      *mainRoot = nodeFa;
    }
    
    Tree nodeFaRight = nodeFa->right;
    nodeFa->right = nodeGf;

    nodeGf->father = nodeFa;

    nodeFa->father = gfFather;
    // nodeGf->left = nodeSi;
    nodeGf->left = nodeFaRight; 
    // if(nodeSi != NULL) nodeSi->father = nodeGf;
    
    if (nodeFaRight != NULL) {
      nodeFaRight->father = nodeGf;
    }

    return;
}

void doubleRightRotation(Tree root, MainTree mainRoot){
    /*
            x -2
          /   \
        y +1   t4
      /   \
    t1     v
          / \
         t2  t3     
    
          x
         / \
       v    t4
      / \
    y     t3
   /  \
t1    t2

        v
      /   \  
    y       x
  /  \     /  \
t1   t2   t3   t4  
    */
    Tree nodeFa = father(root);
    Tree nodeGf = grandFather(root);
    Tree gfFather = father(nodeGf);

    if(nodeFa == NULL || nodeGf == NULL) return;

    
    if(gfFather != NULL){
      if(rightChild(nodeGf)){
        gfFather->right = root;
      } else{
        gfFather->left = root;
      }
    } else{
      *mainRoot = root;
    }

    Tree root_left = root->left;
    Tree root_right = root->right;

    root->left = nodeFa;
    root->right = nodeGf;
    
    root->father = gfFather;

    nodeFa->father = root;
    nodeFa->right = root_right;

    if (root_right != NULL) root_right->father = nodeFa;
    
    nodeGf->father = root;
    nodeGf->left = root_left;
    if (root_left != NULL) root_left->father = nodeGf;
}

void simpleLeftRotation(Tree root, MainTree mainRoot) {
  Tree nodeFa = father(root);
  Tree nodeGf = grandFather(root);
  Tree nodeSi = sibling(root);

  if(nodeFa == NULL || nodeGf == NULL) return;

  Tree gfFather = father(nodeGf);

  //se for nulo, então é a raiz
  if(gfFather != NULL){
    if(rightChild(nodeGf)){
      gfFather->right = nodeFa;
    } else{
      gfFather->left = nodeFa;
    }
  } else {
    *mainRoot = nodeFa;
  }

  nodeFa->left = nodeGf;
  nodeGf->father = nodeFa;
  nodeFa->father = gfFather;
  nodeGf->right = nodeSi;
  if(nodeSi != NULL) nodeSi->father = nodeGf; 
}



void doubleLeftRotation(Tree root, MainTree mainRoot){
  Tree nodeFa = father(root);
  Tree nodeGf = grandFather(root);
  Tree gfFather = father(nodeGf);

  if(nodeFa == NULL || nodeGf == NULL) return;

  
  if(gfFather != NULL){
    if(rightChild(nodeGf)){
      gfFather->right = root;
    } else{
      gfFather->left = root;
    }
  } else{
    *mainRoot = root;
  }

  Tree root_left = root->left;
  Tree root_right = root->right;
  
  root->left = nodeGf;
  root->right = nodeFa;
  
  root->father = gfFather;
  nodeFa->father = root;
  nodeFa->left = root_right;
  if (root_right != NULL) root_right->father = nodeFa;
  
  nodeGf->father = root;
  nodeGf->right = root_left;
  if (root_left != NULL) root_left->father = nodeGf;
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
    if(color(root) == RED) printf("\033[31m[%d]\n\033[0m", root->value);
    else printf("\033[30m[%d]\n\033[0m", root->value); 
    preOrder(root->left);
    preOrder(root->right);
}

int max(int a, int b){
    if(a > b) return a;
    return b;
}
