#ifndef FUNCS_H
#define FUNCS_H

typedef enum { RED, 
  BLACK,
  DOUBLE_BLACK 
} Color;

typedef struct Node {
    int value;
    Color color;
    struct Node* right;
    struct Node* left;
    struct Node* father;

} Node;

typedef Node* Tree;
typedef Tree* MainTree;
Tree father(Tree root);
Tree sibling(Tree root);
Tree uncle(Tree root);
Tree grandFather(Tree root);
int rightChild(Tree root);
Color color(Tree root);


int max(int a, int b);
void insert(MainTree root, int value);
void removeBst(MainTree root, int value);
Tree highestTree(Tree root);

void simpleRightRotation(Tree root, MainTree mainRoot);
void doubleRightRotation(Tree root, MainTree mainRoot);
void simpleLeftRotation(Tree root, MainTree mainRoot);
void doubleLeftRotation(Tree root, MainTree mainRoot);

void preOrder(Tree root);
int treeHeight(Tree root);

#endif
