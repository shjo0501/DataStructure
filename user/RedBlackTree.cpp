#include "user/RedBlackTree.h"
#include <iostream>
using namespace std;

enum { RED, BLACK };
struct Tree
{
    Tree* pParent;
    Tree* pLeft;
    Tree* pRight;

    int data;
    int color;
};

Tree* root;
Tree* Nil;

struct Tree* createRBNode(int data)
{
    Tree* pNode = (Tree*)malloc(sizeof(Tree));
    pNode->pParent = nullptr;
    pNode->pLeft = nullptr;
    pNode->pRight = nullptr;
    pNode->data = data;

    return pNode;
}

void rotate_left(Tree* pRoot)
{
    if (pRoot == nullptr || pRoot->pRight == nullptr)
        return;

    Tree* pRootOrg = pRoot;
    Tree* pParent = nullptr;
    Tree* pLeftFromRootOrg = nullptr;
    Tree* pRightFromRootLeft = nullptr;

    if (pRoot->pLeft != Nil)
        pLeftFromRootOrg = pRoot->pLeft;

    if (pRoot->pRight->pLeft != Nil)
        pRightFromRootLeft = pRoot->pRight->pLeft;

    if (pRootOrg->pParent)
        pParent = pRootOrg->pParent;

    if (pParent) {
        pRoot->pParent = pParent;

        if (pParent->pLeft == pRoot) {
            pRoot = pRoot->pRight;
            pRoot->pParent = pParent;
            pParent->pLeft = pRoot;
        }
        else {
            pRoot = pRoot->pRight;
            pRoot->pParent = pParent;
            pRoot->pParent->pRight = pRoot;
        }
    }
    else {
        pRoot = pRoot->pRight;
        root = pRoot;
        root->pParent = nullptr;
    }

    pRoot->pLeft = pRootOrg;
    pRoot->pLeft->pParent = pRoot;

    if (pRightFromRootLeft) {
        pRoot->pLeft->pRight = pRightFromRootLeft;
        pRoot->pLeft->pRight->pParent = pRoot;
    }
    else {
        pRoot->pLeft->pRight = Nil;
    }
}

void rotate_right(Tree* pRoot)
{
    if (pRoot == nullptr || pRoot->pLeft == nullptr)
        return;

    Tree* pRootOrg = pRoot;
    Tree* pParent = nullptr;
    Tree* pRightFromRootOrg = nullptr;
    Tree* pRightFromRootLeft = nullptr;

    if (pRoot->pRight != Nil)
        pRightFromRootOrg = pRoot->pRight;

    if (pRoot->pLeft->pRight != Nil)
        pRightFromRootLeft = pRoot->pLeft->pRight;

    if (pRootOrg->pParent)
        pParent = pRootOrg->pParent;

    if (pParent) {
        pRoot->pParent = pParent;

        if (pParent->pLeft == pRoot) {
            pRoot = pRoot->pLeft;
            pRoot->pParent = pParent;
            pParent->pLeft = pRoot;

        }
        else {
            pRoot = pRoot->pLeft;
            pRoot->pParent = pParent;
            pRoot->pParent->pRight = pRoot;
        }
    }
    else {
        pRoot = pRoot->pLeft;
        root = pRoot;
        root->pParent = nullptr;
    }

    pRoot->pRight = pRootOrg;
    pRoot->pRight->pParent = pRoot;

    if (pRightFromRootLeft) {
        pRoot->pRight->pLeft = pRightFromRootLeft;
        pRoot->pRight->pLeft->pParent = pRoot;
    }
    else {
        pRoot->pRight->pLeft = Nil;
    }
}

void preorder(Tree* ptree)
{
    char c = ptree->color == RED ? 'R' : 'B';
    printf("[%d c: %c]", ptree->data, c);

    if (ptree->pLeft != Nil)
        preorder(ptree->pLeft);

    if (ptree->pRight != Nil)
        preorder(ptree->pRight);
}

void inorder(Tree* ptree)
{
    if (ptree->pLeft != Nil)
        inorder(ptree->pLeft);

    char c = ptree->color == RED ? 'R' : 'B';
    printf("[%d c: %c]", ptree->data, c);

    if (ptree->pRight != Nil)
        inorder(ptree->pRight);
}

void postorder(Tree* ptree)
{
    if (ptree->pLeft != Nil)
        postorder(ptree->pLeft);

    if (ptree->pRight != Nil)
        postorder(ptree->pRight);

    char c = ptree->color == RED ? 'R' : 'B';
    printf("[%d c: %c]", ptree->data, c);
}

void insert_BT(Tree* pTree, Tree* pNewNode)
{
    if (pTree->data > pNewNode->data)
    {
        if (pTree->pLeft != Nil)
            insert_BT(pTree->pLeft, pNewNode);
        else {
            pTree->pLeft = pNewNode;
            pNewNode->pParent = pTree;
        }
    }
    else if (pTree->data < pNewNode->data)
    {
        if (pTree->pRight != Nil)
            insert_BT(pTree->pRight, pNewNode);
        else {
            pTree->pRight = pNewNode;
            pNewNode->pParent = pTree;
        }
    }
}

void rebuild_RB_for_Insert(Tree* pTree)
{
    Tree* pCurTree = pTree;

    if (pCurTree->pParent == nullptr)
        return;
    if (pCurTree->pParent->pParent == nullptr)
        return;

    while (pCurTree != root && pCurTree->pParent->color == RED)
    {
        Tree* pUncle = nullptr;
        if (pCurTree->pParent->pParent->pLeft == pCurTree->pParent) {
            pUncle = pCurTree->pParent->pParent->pRight;

            int uncleColor = -1;

            if (pUncle != Nil) {
                // 1) 삼촌이 빨간색인 경우
                if (pUncle->color == RED) {
                    pCurTree->pParent->color = BLACK;
                    pUncle->color = BLACK;

                    if (pCurTree->pParent->pParent != root) {
                        pCurTree->pParent->pParent->color = RED;
                        pCurTree = pCurTree->pParent->pParent;
                    }
                }

                uncleColor = pUncle->color;
                continue;
            }

            // 2) 삼촌이 검은색이고
            if (pUncle == Nil || uncleColor == BLACK) {
                // 새로 입력된 노드가 부모의 왼쪽에 위치하는 경우
                if (pCurTree->pParent->pLeft == pCurTree) {
                    pCurTree->pParent->color = BLACK;
                    pCurTree->pParent->pParent->color = RED;
                    rotate_right(pCurTree->pParent->pParent);
                }
                // 새로 입력된 노드가 부모의 오른쪽에 위치하는 경우
                else {
                    pCurTree = pCurTree->pParent;
                    rotate_left(pCurTree);
                }
            }
        }
        else {
            pUncle = pCurTree->pParent->pParent->pLeft;

            Tree* pUncle = nullptr;
            if (pCurTree->pParent->pParent->pRight == pCurTree->pParent) {
                pUncle = pCurTree->pParent->pParent->pLeft;

                int uncleColor = -1;

                if (pUncle != Nil) {
                    // 1) 삼촌이 빨간색인 경우
                    if (pUncle->color == RED) {
                        pCurTree->pParent->color = BLACK;
                        pUncle->color = BLACK;

                        if (pCurTree->pParent->pParent != root) {
                            pCurTree->pParent->pParent->color = RED;
                            pCurTree = pCurTree->pParent->pParent;
                        }
                    }

                    uncleColor = pUncle->color;
                    continue;
                }

                // 2) 삼촌이 검은색이고
                if (pUncle == Nil || uncleColor == BLACK) {
                    // 새로 입력된 노드가 부모의 왼쪽에 위치하는 경우
                    if (pCurTree->pParent->pRight == pCurTree) {
                        pCurTree->pParent->color = BLACK;
                        pCurTree->pParent->pParent->color = RED;
                        rotate_left(pCurTree->pParent->pParent);
                    }
                    // 새로 입력된 노드가 부모의 오른쪽에 위치하는 경우
                    else {
                        pCurTree = pCurTree->pParent;
                        rotate_right(pCurTree);
                    }
                }
            }
        }
    }
}

void insert_RB(Tree* pTree, Tree* pNewNode)
{
    insert_BT(pTree, pNewNode);

    pNewNode->color = RED;
    pNewNode->pLeft = Nil;
    pNewNode->pRight = Nil;

    rebuild_RB_for_Insert(pNewNode);
}

Tree* search_BT(Tree* pTree, int data)
{
    if (pTree == Nil)
        return NULL;

    if (pTree->data > data)
    {
        if (pTree->pLeft)
            return search_BT(pTree->pLeft, data);
    }
    else if (pTree->data < data)
    {
        if (pTree->pRight)
            return search_BT(pTree->pRight, data);
    }
    else {
        return pTree;
    }

    return NULL;
}

Tree* findMinNode(Tree* pParent, Tree* pTree)
{
    Tree* pCur = pTree;

    while (pCur->pLeft != Nil) {
        pParent = pCur;
        pCur = pCur->pLeft;
    }

    return pCur;
}

void rebuild_RB_for_Remove(Tree* pSuccessor)
{
    Tree* pCurNode = pSuccessor;
    Tree* sibling = nullptr;

    while (pCurNode != root && pCurNode->color == BLACK) {
        if (pCurNode->pParent->pLeft == pCurNode) {
            sibling = pCurNode->pParent->pRight;

            // 1) 형제 노드가 빨간색인 경우 -> 형제 노드가 검은색이 나올 때 까지 시행된다.
            if (sibling->color == RED) {
                sibling->color = BLACK;
                sibling->pParent->color = RED;
                rotate_left(sibling->pParent);
                continue;
            }

            // 2) 형제 노드가 검은색인 경우
            else {
                // 2-1) 두 자식이 다 검은색인 경우
                if (sibling->pLeft->color == BLACK && sibling->pRight->color == BLACK) {
                    sibling->color = RED;
                    pCurNode = pCurNode->pParent;
                }

                else {
                    // 2-2) 오른쪽 자식이 빨간색인 경우
                    if (sibling->pLeft->color == RED) {
                        // 2-3) 형제 노드의 왼쪽 자식이 빨간색이고, 오른쪽 자식이 검은색인 경우
                        // 형제 노드를 빨간색으로 칠한다.
                        sibling->color = RED;

                        // 형재 노드의 왼쪽 자식을 검은색으로 칠한다.
                        sibling->pLeft->color = BLACK;
                        // 오른쪽으로 회전한다.
                        rotate_right(sibling);
                    }
                    else if (sibling->pRight->color == RED) {
                        // 2-3) 왼쪽 자식이 빨간색인 경우
                        // 이중 흑색노드의 부모의 색을 형제에게 전달한다.
                        sibling->color = pCurNode->pParent->color;

                        // 형제의 오른쪽 자식, 이중 흑색 노드의 부모의 색을 검은색으로 칠한다.
                        sibling->pRight->color = BLACK;
                        sibling->pParent->color = BLACK;

                        // 좌회전을 한다.
                        rotate_left(sibling->pParent);

                        // 이중 흑색 노드를 루트 노드로 변경한다.
                        pCurNode = root;
                    }
                }
            }
        }
        else {
            sibling = pSuccessor->pParent->pLeft;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                sibling->pParent->color = RED;
                rotate_right(sibling->pParent);
                continue;
            }

            // 2) 형제 노드가 검은색인 경우
            else {
                // 2-1) 두 자식이 다 검은색인 경우
                if (sibling->pRight->color == BLACK && sibling->pLeft->color == BLACK) {
                    sibling->color = RED;
                    pCurNode = pCurNode->pParent;
                }

                // 2-2) 형제 노드의 왼쪽 자식이 검은색이고, 오른쪽 자식이 빨간색인 경우
                else {
                    if (sibling->pRight->color == RED) {
                        // 형제 노드를 빨간색으로 칠한다.
                        sibling->color = RED;

                        // 형재 노드의 왼쪽 자식을 검은색으로 칠한다.
                        sibling->pRight->color = BLACK;

                        // 오른쪽으로 회전한다.
                        rotate_left(sibling);
                    }
                    else if (sibling->pLeft->color == RED) {
                        // 이중 흑색노드의 부모의 색을 형제에게 전달한다.
                        sibling->color = pCurNode->pParent->color;

                        // 형제의 오른쪽 자식, 이중 흑색 노드의 부모의 색을 검은색으로 칠한다.
                        sibling->pLeft->color = BLACK;
                        sibling->pParent->color = BLACK;

                        // 좌회전을 한다.
                        rotate_right(sibling->pParent);

                        // 이중 흑색 노드를 루트 노드로 변경한다.
                        pCurNode = root;
                    }
                }
            }
        }
    }
    pCurNode->color = BLACK;
}

Tree* remove_RB(Tree* pRoot, int data)
{
    Tree* pTarget = search_BT(pRoot, data);
    Tree* pSuccessor = nullptr;
    Tree* pRemoved = nullptr;

    if (pTarget == nullptr) {
        return nullptr;
    }

    if (pTarget->pLeft == Nil || pTarget->pRight == Nil) {
        pRemoved = pTarget;
    }

    if (pTarget->pLeft != Nil && pTarget->pRight != Nil) {
        pRemoved = findMinNode(pTarget, pTarget->pRight);
        pTarget->data = pRemoved->data;
    }

    if (pRemoved->pLeft != Nil) {
        pSuccessor = pRemoved->pLeft;
    }
    else {
        pSuccessor = pRemoved->pRight;
    }

    pSuccessor->pParent = pRemoved->pParent;

    if (pRemoved->pParent == nullptr) {
        root = pSuccessor;
    }
    else {
        if (pRemoved->pParent->pLeft == pRemoved) {
            pRemoved->pParent->pLeft = pSuccessor;
        }
        else {
            pRemoved->pParent->pRight = pSuccessor;
        }
    }

    if (pRemoved->color == BLACK) {
        rebuild_RB_for_Remove(pSuccessor);
    }

    return pRemoved;
}

void remove_node(Tree* node)
{
    if (node)
        free(node);
}

void destroy(Tree* pTree)
{
    if (pTree->pLeft != Nil)
        destroy(pTree->pLeft);

    if (pTree->pRight != Nil)
        destroy(pTree->pRight);

    free(pTree);
}

void printParent(Tree* pTree)
{
    Tree* pCur = pTree;
    Tree* pLocalParent = pTree;

    while (pCur) {
        printf("%d ", pCur->data);
        pCur = pCur->pParent;
    }
    printf("\n\n");
}

void printLeftChild(Tree* pTree)
{
    Tree* pCur = pTree;
    Tree* pLocalParent = pTree;

    while (pCur) {
        printf("%d ", pCur->data);
        pCur = pCur->pLeft;
    }
}