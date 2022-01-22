#if defined (BINARY_SEARH_TREE)
#include <iostream>
using namespace std;

struct Tree
{
    Tree* pLeft;
    Tree* pRight;
    int data;
};

Tree* root;

struct Tree* createBTNode(int data)
{
    Tree* pNode = (Tree*)malloc(sizeof(Tree));
    pNode->pLeft = nullptr;
    pNode->pRight = nullptr;
    pNode->data = data;

    return pNode;
}

void insert(Tree* pTree, Tree* pNewNode)
{
    if (pTree->data > pNewNode->data)
    {
        if (pTree->pLeft)
            insert(pTree->pLeft, pNewNode);
        else
            pTree->pLeft = pNewNode;

    }
    else if (pTree->data < pNewNode->data)
    {
        if (pTree->pRight)
            insert(pTree->pRight, pNewNode);
        else
            pTree->pRight = pNewNode;
    }
}

int search(Tree* ptree, int data)
{
    if (ptree->data > data)
    {
        if (ptree->pLeft)
            return search(ptree->pLeft, data);
    }
    else if (ptree->data < data)
    {
        if (ptree->pRight)
            return search(ptree->pRight, data);
    }
    else {
        return data;
    }

    return -1;
}

void preorder(Tree* ptree)
{
    printf("%d ", ptree->data);

    if (ptree->pLeft)
        preorder(ptree->pLeft);

    if (ptree->pRight)
        preorder(ptree->pRight);
}

void inorder(Tree* ptree)
{
    if (ptree->pLeft)
        inorder(ptree->pLeft);

    printf("%d ", ptree->data);

    if (ptree->pRight)
        inorder(ptree->pRight);
}

void postorder(Tree* ptree)
{
    if (ptree->pLeft)
        postorder(ptree->pLeft);

    if (ptree->pRight)
        postorder(ptree->pRight);

    printf("%d ", ptree->data);
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
        if (pTree->data > data)
        {
            if (pTree->pLeft)
                remove(pTree->pLeft, pTree, data);
        }
        else if (pTree->data < data)
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
                pRemove = remove(pTree, nullptr, pMinNode->data);
                pTree->data = pMinNode->data;
            }
        }
    }

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