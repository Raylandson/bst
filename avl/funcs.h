#ifndef FUNCS_H
#define FUNCS_H

typedef struct Node {
    int value;
    int bf;
    struct Node* right;
    struct Node* left;

} Node;

typedef Node* Tree;

int max(int a, int b);
Tree insert(Tree root, int value, int *grew);
Tree removeBst(Tree root, int value, int *diminuiu);
Tree highestTree(Tree root);
Tree rightRotation(Tree root);
Tree leftRotation(Tree root);
Tree simpleRightRotation(Tree root);
Tree doubleRightRotation(Tree root);
Tree simpleLeftRotation(Tree root);
Tree doubleLeftRotation(Tree root);

void preOrder(Tree root);
void inOrder(Tree root);
void inOrderReverse(Tree root);
void posOrder(Tree root);
int treeHeight(Tree root);
int totalNodes(Tree root);
void findValue(Tree root, int sValue, int *found);

#endif