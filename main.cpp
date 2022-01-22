#include <iostream>
using namespace std;

#define RED_BLACK_TREE

#if defined (RED_BLACK_TREE)
#include "user/RedBlackTree.h"
enum { RED, BLACK };
extern Tree* Nil;
extern Tree* root;

struct Tree
{
    Tree* pParent;
    Tree* pLeft;
    Tree* pRight;

    int data;
    int color;
};
#endif

int main()
{
#if defined (RED_BLACK_TREE)
    Nil = createRBNode(0);
    Nil->color = BLACK;

    root = createRBNode(20);
    root->color = BLACK;
    root->pLeft = Nil;
    root->pRight = Nil;

    insert_RB(root, createRBNode(15));
    insert_RB(root, createRBNode(3));
    insert_RB(root, createRBNode(12));
    insert_RB(root, createRBNode(5));
    insert_RB(root, createRBNode(11));
    insert_RB(root, createRBNode(6));
    insert_RB(root, createRBNode(40));
    insert_RB(root, createRBNode(25));
    insert_RB(root, createRBNode(18));

    //Tree* pRemoveTarget = remove_RB(root, 5);
    //free(pRemoveTarget);

    //pRemoveTarget = remove_RB(root, 6);
    //free(pRemoveTarget);

    //pRemoveTarget = remove_RB(root, 12);
    //free(pRemoveTarget);

    //pRemoveTarget = remove_RB(root, 25);
    //free(pRemoveTarget);

    //pRemoveTarget = remove_RB(root, 3);
    //free(pRemoveTarget);

    //pRemoveTarget = remove_RB(root, 11);
    //free(pRemoveTarget);

    //pRemoveTarget = remove_RB(root, 15);
    //free(pRemoveTarget);

    //pRemoveTarget = remove_RB(root, 18);
    //free(pRemoveTarget);

    //pRemoveTarget = remove_RB(root, 20);
    //free(pRemoveTarget);

    //pRemoveTarget = remove_RB(root, 40);
    //free(pRemoveTarget);

    if (root != Nil) {
        preorder(root);
        //inorder(root);
        //postorder(root);
    }
    else {
        printf("no data in tree\n");
    }

    if (root != Nil)
        destroy(root);

    free(Nil);
#endif
    return 0;
}