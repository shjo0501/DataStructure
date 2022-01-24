//#define AVL_TREE
#if defined (AVL_TREE)
#include "AVLTree.h"
#include <iostream>
#include <algorithm>
using namespace std;

// https://www.cs.usfca.edu/~galles/visualization/AVLtree.html

struct Tree
{
    Tree* pLeft;
    Tree* pRight;
    int height;
    int key;
};

Tree* root;

struct Tree* createAVLNode(int data)
{
    Tree* pNode = (Tree*)malloc(sizeof(Tree));
    pNode->pLeft = nullptr;
    pNode->pRight = nullptr;
    pNode->height = 1;
    pNode->key = data;

    return pNode;
}

int max(int n0, int n1)
{
    if (n0 < n1) return n1;
    else         return n0;
}

int height(Tree* pNode)
{
    if (pNode == nullptr)
        return 0;
    else
        return pNode->height;
}

int getBalance(Tree* pNode)
{
    if (pNode == nullptr)
        return 0;
    else
        return height(pNode->pLeft) - height(pNode->pRight);
}

Tree* rotate_left(Tree* pRoot)
{
    if (pRoot->pRight == nullptr) {
        return pRoot;
    }

    Tree* pY  = pRoot->pRight;
    Tree* pT2 = pRoot->pRight->pLeft;
    Tree* pZ  = pRoot;

    pY->pLeft = pZ;
    pZ->pRight = pT2;

    pZ->height = 1 + max(height(pZ->pLeft), height(pZ->pRight));
    pY->height = 1 + max(height(pY->pLeft), height(pY->pRight));

    return pY;
}

Tree* rotate_right(Tree* pRoot)
{
    if (pRoot->pLeft == nullptr) {
        return pRoot;
    }

    Tree* pY  = pRoot->pLeft;
    Tree* pT2 = pRoot->pLeft->pRight;
    Tree* pZ  = pRoot;

    pY->pRight = pZ;
    pZ->pLeft = pT2;

    pZ->height = 1 + max(height(pZ->pLeft), height(pZ->pRight));
    pY->height = 1 + max(height(pY->pLeft), height(pY->pRight));

    return pY;
}

Tree* rebalance(Tree* pTree, int key)
{
    int balanceFactor = getBalance(pTree);

    // LL case
    if (balanceFactor > 1 && key < pTree->pLeft->key) {
        return rotate_right(pTree);
    }

    // RR case
    if (balanceFactor < -1 && key > pTree->pRight->key) {
        return rotate_left(pTree);
    }

    // LR case
    if (balanceFactor > 1 && key > pTree->pLeft->key) {

        pTree->pLeft = rotate_left(pTree->pLeft);
        return rotate_right(pTree);
    }

    // RL case
    if (balanceFactor < -1 && key < pTree->pRight->key) {
        pTree->pRight = rotate_right(pTree->pRight);
        return rotate_left(pTree);
    }

    return pTree;
}

Tree* insertAVL(Tree* pTree, Tree* pNewNode)
{
    if (pTree == nullptr) {
        return pNewNode;
    }

    if (pTree->key > pNewNode->key) {
        pTree->pLeft = insertAVL(pTree->pLeft, pNewNode);
    }
    else if (pTree->key < pNewNode->key) {
        pTree->pRight = insertAVL(pTree->pRight, pNewNode);
    }
    else {
        return pTree;
    }

    pTree->height = 1 + max(height(pTree->pLeft), height(pTree->pRight));

    pTree = rebalance(pTree, pNewNode->key);

    return pTree;
}

int search(Tree* pTree, int data)
{
    if (pTree->key > data)
    {
        if (pTree->pLeft)
            return search(pTree->pLeft, data);
    }
    else if (pTree->key < data)
    {
        if (pTree->pRight)
            return search(pTree->pRight, data);
    }
    else {
        return data;
    }

    return -1;
}

void preorder(Tree* pTree)
{
    printf("[%d h: %d] ", pTree->key, pTree->height);

    if (pTree->pLeft)
        preorder(pTree->pLeft);

    if (pTree->pRight)
        preorder(pTree->pRight);
}

void inorder(Tree* pTree)
{
    if (pTree->pLeft)
        inorder(pTree->pLeft);

    printf("[%d h: %d] ", pTree->key, pTree->height);

    if (pTree->pRight)
        inorder(pTree->pRight);
}

void postorder(Tree* pTree)
{
    if (pTree->pLeft)
        postorder(pTree->pLeft);

    if (pTree->pRight)
        postorder(pTree->pRight);

    printf("[%d h: %d] ", pTree->key, pTree->height);
}

Tree* findMinNode(Tree* pParent, Tree* pTree)
{
    Tree* pCur = pTree;

    while (pCur->pLeft) {
        pParent = pCur;
        pCur = pCur->pLeft;
    }

    return pCur;
}

Tree* remove(Tree* pTree, Tree* pParent, int data)
{
    Tree* pRemove = nullptr;
    if (pTree) {
        if (pTree->key > data)
        {
            if (pTree->pLeft)
                remove(pTree->pLeft, pTree, data);
        }
        else if (pTree->key < data)
        {
            if (pTree->pRight)
                remove(pTree->pRight, pTree, data);
        }
        else {
            if (pTree->pLeft == nullptr && pTree->pRight == nullptr) {
                // 현재 노드를 삭제하고 부모가 갖는 left or right에 해당하는 곳엔 nullptr 추가

                if (root == pTree) {
                    root = nullptr;
                }
                else {
                    if (pParent->pLeft == pTree) {
                        pParent->pLeft = nullptr;
                    }
                    else {
                        pParent->pRight = nullptr;
                    }
                }

                pRemove = pTree;
            }
            else if (pTree->pLeft == nullptr || pTree->pRight == nullptr) {
                // 현재 노드를 삭제하고 자식을 부모의 left or right에 해당하는 곳에 추가.
                Tree* pNode = nullptr;
                if (pTree->pLeft) {
                    pNode = pTree->pLeft;
                }
                else {
                    pNode = pTree->pRight;
                }

                if (root == pTree) {
                    root = pNode;
                }
                else {
                    if (pParent->pLeft == pTree) {
                        pParent->pLeft = pNode;
                    }
                    else {
                        pParent->pRight = pNode;
                    }
                }

                pRemove = pTree;
            }
            else if (pTree->pLeft && pTree->pRight) {
                // 1) 오른쪽 트리의 최소 자식을 찾는다.
                Tree* pMinNode = findMinNode(pTree, pTree->pRight);
                pRemove = remove(pTree, nullptr, pMinNode->key);
                pTree->key = pMinNode->key;
            }
        }
    }

    if (pTree == nullptr) {
        return pTree;
    }

    pTree->height = 1 + max(height(pTree->pLeft), height(pTree->pRight));
    int balanceFactor = getBalance(pTree);

#if 1
    //// LL case
    //if (balanceFactor > 1 && getBalance(pTree->pLeft) >= 0) {
    //    return rotate_right(pTree);
    //}

    //// LR case
    //if (balanceFactor > 1 && getBalance(pTree->pRight) < 0) {

    //    pTree->pLeft = rotate_left(pTree->pLeft);
    //    return rotate_right(pTree);
    //}


    //// RR case
    //if (balanceFactor < -1 && getBalance(pTree->pRight) <= 0) {
    //    return rotate_left(pTree);
    //}

    //// RL case
    //if (balanceFactor < -1 && getBalance(pTree->pLeft) > 0) {
    //    pTree->pRight = rotate_right(pTree->pRight);
    //    return rotate_left(pTree);
    //}
#elif 1 // my code what's difference
    // LL case
    if (balanceFactor > 1 && getBalance(pTree->pLeft) >= 1) {
        return rotate_right(pTree);
    }

    // LR case
    if (balanceFactor > 1 && getBalance(pTree->pRight)  <= -1) {

        pTree->pLeft = rotate_left(pTree->pLeft);
        return rotate_right(pTree);
    }


    // RR case
    if (balanceFactor < -1 && getBalance(pTree->pRight) <= -1) {
        return rotate_left(pTree);
    }

    // RL case
    if (balanceFactor < -1 && getBalance(pTree->pLeft) >= 1) {
        pTree->pRight = rotate_right(pTree->pRight);
        return rotate_left(pTree);
    }
#endif
    return pRemove;
}

void destroy(Tree* pTree)
{
    if (pTree->pLeft)
        destroy(pTree->pLeft);

    if (pTree->pRight)
        destroy(pTree->pRight);

    free(pTree);
}

void remove_node(Tree* pTree)
{
    if (pTree)
        free(pTree);
}
#endif