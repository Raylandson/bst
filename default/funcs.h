#ifndef FUNCS_H
#define FUNCS_H

typedef struct Node {
    int value;
    struct Node* right;
    struct Node* left;
} Node;

typedef Node* Tree;

int max(int a, int b);
Tree insert(Tree root, int value);
Tree removeBst(Tree root, int value);
Tree highestTree(Tree root);
void preOrder(Tree root);
void inOrder(Tree root);
void inOrderReverse(Tree root);
void posOrder(Tree root);
int treeHeight(Tree root);
int leafQuantity(Tree root);
void findValue(Tree root, int sValue);

#endif
