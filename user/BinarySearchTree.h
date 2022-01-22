#pragma once
#include <iostream>
using namespace std;

struct Tree* createBTNode(int data);
void insert(Tree* pTree, Tree* pNewNode);
int search(Tree* ptree, int data);
void preorder(Tree* ptree);
void inorder(Tree* ptree);
void postorder(Tree* ptree);
Tree* findMinNode(Tree* pParent, Tree* pTree);
Tree* remove(Tree* pTree, Tree* pParent, int data);
void destroy(Tree* pTree);
void remove_node(Tree* pTree);