//#define RED_BLACK_TREE
#pragma once
#if defined (RED_BLACK_TREE)
#include "user/RedBlackTree.h"
struct Tree* createRBNode(int data);
void rotate_left(Tree* pRoot);
void rotate_right(Tree* pRoot);
void preorder(Tree* ptree);
void inorder(Tree* ptree);
void postorder(Tree* ptree);
void insert_BT(Tree* pTree, Tree* pNewNode);
void rebuild_RB_for_Insert(Tree* pTree);
void insert_RB(Tree* pTree, Tree* pNewNode);
Tree* search_BT(Tree* pTree, int data);
Tree* findMinNode(Tree* pParent, Tree* pTree);
void rebuild_RB_for_Remove(Tree* pSuccessor);
Tree* remove_RB(Tree* pRoot, int data);
void remove_node(Tree* node);
void destroy(Tree* pTree);
void printParent(Tree* pTree);
void printLeftChild(Tree* pTree);
#endif