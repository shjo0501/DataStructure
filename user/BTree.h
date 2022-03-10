#pragma once
#define B_TREE
#if defined (B_TREE)
struct BTreeNode;
BTreeNode* createEmptyNode(bool leafNode);
void splitNode(int index, BTreeNode* pNode, BTreeNode* pParent);
void insertNode(BTreeNode* pNode, int childIdx, BTreeNode* pParent, int key);
void insert(int key);
void traverse(BTreeNode* pNode);
void search(int key);
BTreeNode* searchNode(BTreeNode* pTree, int key);
void remove(int key);
#endif
