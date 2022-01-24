//#define AVL_TREE
#pragma once
#if defined (AVL_TREE)
#include <iostream>
using namespace std;

struct Tree* createAVLNode(int key);
Tree* insertAVL(Tree* pTree, Tree* pNewNode);
int search(Tree* pTree, int key);
void preorder(Tree* pTree);
void inorder(Tree* pTree);
void postorder(Tree* pTree);
Tree* findMinNode(Tree* pParent, Tree* pTree);
Tree* remove(Tree* pTree, Tree* pParent, int key);
Tree* rotate_left(Tree* pRoot);
Tree* rotate_right(Tree* pRoot);
Tree* rebalance(Tree* pTree, int key);
void destroy(Tree* pTree);
void remove_node(Tree* pTree);
#endif