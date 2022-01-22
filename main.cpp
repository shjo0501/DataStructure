// #define RED_BLACK_TREE
// #define BINARY_SEARH_TREE
#if defined (BINARY_SEARH_TREE)
#include "BinarySearchTree.h"
#include <iostream>
using namespace std;

struct Tree
{
    Tree* pLeft;
    Tree* pRight;
    int data;
};

extern Tree* root;

int main()
{
    root = createBTNode(50);

    Tree* pNode = createBTNode(40);
    insert(root, createBTNode(60));
    insert(root, createBTNode(25));
    insert(root, createBTNode(30));
    insert(root, createBTNode(55));
    insert(root, createBTNode(70));
    insert(root, createBTNode(12));
    insert(root, createBTNode(27));

    Tree* pTarget = nullptr;
    pTarget = remove(root, nullptr, 60);
    remove_node(pTarget);

    pTarget = remove(root, nullptr, 50);
    remove_node(pTarget);

    pTarget = remove(root, nullptr, 55);
    remove_node(pTarget);

    pTarget = remove(root, nullptr, 70);
    remove_node(pTarget);

    pTarget = remove(root, nullptr, 40);
    remove_node(pTarget);

    pTarget = remove(root, nullptr, 25);
    remove_node(pTarget);

    pTarget = remove(root, nullptr, 27);
    remove_node(pTarget);

    pTarget = remove(root, nullptr, 12);
    remove_node(pTarget);

    pTarget = remove(root, nullptr, 30);
    remove_node(pTarget);

    if (root) {
        preorder(root);
        //inorder(root);
        //postorder(root);
    }
    else {
        printf("no data in tree\n");
    }

    if (root) {
        destroy(root);
    }

    return 0;
}
#endif

#if defined (RED_BLACK_TREE)
#include <iostream>
using namespace std;

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

int main()
{
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

    return 0;
}
#endif