#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

Tree insert(Tree root, int nValue, int *grew){
    // caso base
    if(root == NULL){
        Tree newRoot = (Tree)malloc(sizeof(Node));
        newRoot->left = NULL;
        newRoot->right = NULL;
        newRoot->bf = 0;
        newRoot->value = nValue;
        *grew = 1;
        return newRoot;
    }

    //procura de onde colocar
    if(nValue > root->value){
        root->right = insert(root->right, nValue, grew);
        //calcular fator de balancos
        //cresceu
        if (*grew){
            if(root->bf == -1){
                root->bf += 1;
                *grew = 0;
                return root;
            }
            if(root->bf == 0){
                root->bf += 1;
                *grew = 1;
                return root;
            }
            if(root->bf == 1){
                //ativar rotacao
                *grew = 0;
                if(root->right->bf >= 0){
                    //simples a esquerda
                    return simpleLeftRotation(root);
                }
                //rotacao dupla esquerda
                return doubleLeftRotation(root);
            }
        }
    
    
    } else if (nValue < root->value){
        root->left = insert(root->left, nValue, grew);
        //calcular fator de balancos

        if(*grew){
            if(root->bf == 1){
                root->bf = 0;
                *grew = 0;
                return root;
            }
            if(root->bf == 0){
                root->bf = -1;
                *grew = 1;
                return root;
            }
            if(root->bf == -1){
                //desbalanceada
                *grew = 0;

                if(root->left->bf <= 0){
                    //simples direita
                    return simpleRightRotation(root);
                }

                //rotacao dupla direita

                return doubleRightRotation(root);
            }

        }
    }
    return root;
        
}

Tree removeBst(Tree root, int rValue, int *diminuiu){
    //caso base
    if(root == NULL) return root;
    
    //achou
    if (rValue == root->value){
        //sem filhos
        if(root->left == NULL && root->right == NULL){
            //printf("root: %d ", root->value);
            //printf("sem filho, diminuiu\n");
            *diminuiu = 1;
            free(root);
            root = NULL;
            return root;
        }
        //filho direito
        if(root->left == NULL && root->right != NULL){
            //printf("root: %d ", root->value);
            //printf("1 filho dir, diminuiu\n");
            *diminuiu = 1;
            Tree aux = root->right;
            free(root);
            return aux;
        }
        //filho esquerdo      
        if(root->left != NULL && root->right == NULL){
            //printf("root: %d ", root->value);
            //printf("1 filho esq, diminuiu\n");
            *diminuiu = 1;
            Tree aux = root->left;
            free(root);
            return aux;
        }
        //dois filhos
        //printf("root: %d ", root->value);
        //printf("2 filhos, nao diminuiu\n");
        *diminuiu = 0;
        int higher_value = highestTree(root->left)->value;
        root->value = higher_value;
        //printf("removendo duplicada %d\n", higher_value);
        root->left = removeBst(root->left, higher_value, diminuiu);
        //atualizar os balancea mentos
        //printf("remove left: %d root: %d ", rValue, root->value);
        if(root->right != NULL){
            //printf("root->left: %d", root->right->value);
        }
        //printf("\n");
        //printf("diminuiu: %d\n", *diminuiu);
        if (*diminuiu){
            switch (root->bf)
            {
            case 0:
                root->bf = 1;
                *diminuiu = 0;

                //printf("case bf: 0 root: %d\n", root->value);
                break;
            case 1:
                *diminuiu = 0;
                if (root->right->bf == -1){
                    return doubleLeftRotation(root);
                }

                return simpleLeftRotation(root);
            
            case -1:
                root->bf = 0;
                *diminuiu = 1;
                //printf("case bf: -1 root: %d\n", root->value);
                break;
            }
        }
        //printf("root bf e root value: %d %d\n", root->bf, root->value);
        return root;

    }
    //nao achou
    else if(rValue > root->value){
        root->right = removeBst(root->right, rValue, diminuiu);
        
        ////printf("remove right: %d root: %d ", rValue, root->value);
        if(root->right != NULL){
            ////printf("root->right: %d", root->right->value);
        }
        //printf("\n");
        //printf("diminuiu: %d\n", *diminuiu);
        //atualizar os balancea mentos
        if (*diminuiu){
            switch (root->bf)
            {
            case 0:
                root->bf = -1;
                //printf("bf -1 %d\n", root->value);
                *diminuiu = 0;
                break;
            case 1:
                root->bf = 0;
                *diminuiu = 1;
                break;
            case -1:
                *diminuiu = 0;
                if (root->left->bf == 1){
                    return doubleRightRotation(root);
                }
                
                //printf("simple right\n");
                return simpleRightRotation(root);
            }
        }

    } else if(rValue < root->value){
        root->left = removeBst(root->left, rValue, diminuiu);
        //atualizar os balancea mentos
        //printf("remove left: %d root: %d ", rValue, root->value);
        if(root->right != NULL){
            //printf("root->left: %d", root->right->value);
        }
        //printf("\n");
        //printf("diminuiu: %d\n", *diminuiu);
        if (*diminuiu){
            switch (root->bf)
            {
            case 0:
                root->bf = 1;
                *diminuiu = 0;

                //printf("case bf: 0 root: %d\n", root->value);
                break;
            case 1:
                *diminuiu = 0;
                if (root->right->bf == -1){
                    return doubleLeftRotation(root);
                }

                return simpleLeftRotation(root);
            
            case -1:
                root->bf = 0;
                *diminuiu = 1;
                //printf("case bf: -1 root: %d\n", root->value);
                break;
            }
        }
    }
    //sem duplicata
    return root;
}


Tree simpleRightRotation(Tree root){
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
    Tree x = root;
    Tree y = root->left;
    Tree t2 = y->right;
    Tree t3 = x->right;

    //rotaciona
    y->right = x;
    x->left = t2;

    //atualizar bf
    if(x->bf == -1){
        x->bf = 0;
        y->bf = 0;
    } else{
        //caso x->bf == 0
        x->bf = -1;
        y->bf = 1;
    }
    
    if(t3 == NULL && t2 != NULL){
        x->bf = -1;
        y->bf = 1;
    }

    //printf("bfs x: %d y: %d\n", x->bf, y->bf);
    //printf("values x: %d y: %d\n", x->value, y->value);

    return y;
}

Tree doubleRightRotation(Tree root){
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
    Tree x = root;
    Tree y = root->left;
    Tree v = y->right;
    Tree t2 = v->left;
    Tree t3 = v->right;


    y->right = t2;
    x->left = t3;
    v->left = y;
    v->right = x;
    // 3 casos
    if(v->bf == 0){
        y->bf = 0;
        x->bf = 0;
        v->bf = 0;
    } else if(v->bf == 1){
        y->bf = -1;
        x->bf = 0;
        v->bf = 0;
    } else{
        //v->bf == -1
        y->bf = 0;
        x->bf = 1;
        v->bf = 0;
    }

    return v;
}

Tree simpleLeftRotation(Tree root){
    /*
        
             z
           /   \
         t2     y
               / \
              t1  t3
       
             y
          /    \
        z        t3
      /   \
    t2    t1
    */

    Tree z = root;
    Tree y = root->right;
    Tree t1 = y->left;
    Tree t2 = z->left;
    Tree t3 = y->right;

    y->left = z;
    z->right = t1;

    //atualizar bf

    if(z->bf == 1){
        z->bf = 0;
        y->bf = 0;
    } else{
        //z->bf == 0
        z->bf = 1;
        y->bf = -1;
    }
    if(t2 == NULL && t1 != NULL){
        z->bf = 1;
        y->bf = -1;
    }

   return y;
}


Tree doubleLeftRotation(Tree root){
   Tree x = root;
   Tree y = x->right;
   Tree v = y->left;

   Tree t2 = v->left;
   Tree t3 = v->right;

   x->right = t2;
   y->left = t3;
   v->left = x;
   v->right = y;

   if(v->bf == 0){
        x->bf = 0;
        y->bf = 0;
   } else if(v->bf == 1){
        x->bf = -1;
        y->bf = 0;
   } else{
    //v->bf == -1
        x->bf = 0;
        y->bf = 1;
   }
    v->bf = 0;
    return v;
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
    printf("[%d %d]", root->value, root->bf);
    preOrder(root->left);
    preOrder(root->right);
}

int max(int a, int b){
    if(a > b) return a;
    return b;
}
