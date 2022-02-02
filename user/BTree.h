#pragma once
#define B_TREE
#if defined (B_TREE)
struct BTreeNode;
BTreeNode* createEmptyNode(bool leafNode);
void splitNode(int index, BTreeNode* pNode, BTreeNode* pParent);
void insertNode(BTreeNode* pNode, int childIdx, BTreeNode* pParent, int key);
void insert(int key);
void traverse(BTreeNode* pNode);
void remove(BTreeNode* pNode);
void search(BTreeNode* pNode);
#endif
