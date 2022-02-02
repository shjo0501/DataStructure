#define B_TREE
#if defined (B_TREE)
#include "BTree.h"
#include <iostream>
#include <algorithm>
using namespace std;
//https://www.cs.usfca.edu/~galles/visualization/BTree.html

// BTree Property
const int T = 4;
const int MAX = 2 * T - 1;

struct BTreeNode
{
    int keys[MAX];
    int n;
    bool leafNode;

    BTreeNode* pChild[MAX + 1];
};

BTreeNode* createEmptyNode(bool leafNode)
{
    BTreeNode* pNode = (BTreeNode*)malloc(sizeof(BTreeNode));

    pNode->n = 0;
    pNode->leafNode = leafNode;
    memset(pNode->keys, 0, sizeof(pNode->keys));
    memset(pNode->pChild, 0, sizeof(pNode->pChild));

    return pNode;
}

BTreeNode* root = nullptr;

void splitNode(int index, BTreeNode* pTree, BTreeNode* pParent)
{
    // 새로운 노드는 pTree 노드와 같은 레벨에 위치하게 된다. pTree가 leaf라면 pNodeZ도 leaf가 되고, leaf가 아니라면 pNodeZ도 leaf 아니게 된다.
    BTreeNode* pNodeZ = createEmptyNode(pTree->leafNode);
    pNodeZ->n = T - 1;
    // 1) 새로운 노드(pNodeZ)가 부모가 되고, 오른쪽 key 값엔 median을 중심으로 오른쪽 값들을 저장시킨다. // 왼쪽엔 기존에 연결되어 있던 것을 사용한다.
    for (int k = 0; k < T - 1; k++) {
        pNodeZ->keys[k] = pTree->keys[k + T];
    }

    // 2) 만일에 leafNode가 아니라면
    if (pTree->leafNode == false) {
        // 새로운 부모에 기존의 오른쪽 child만 연결 시킨다. // 왼쪽엔 기존에 연결되어 있던 것을 사용한다.
        for (int k = 0; k < T; k++)
            pNodeZ->pChild[k] = pTree->pChild[k + T];
    }

    // [예시]
    // Parent엔 기존의 key 값이 있었고 기존의 pChild이 있는 상황에서 분할된 median 노드가 추가되면 child 값의 순서를 재정렬 할 필요가 있다. (자식에서 분할된 노드가 올라올 때 왼쪽에서 온거면 자식의 median은 부모 보다 값이 작다.)
    // 가령 key가 17이 있고 pChild[0]->key 13 14 15, pChild[1]->key엔 20이 있다면 14가 새로올라와서 parent는 14, 17이 된다. 하지만 이때 pChild[1]->key가 20이므로 옆으로 땡겨야한다.
    for (int j = pParent->n; j >= index + 1; j--)
        pParent->pChild[j + 1] = pParent->pChild[j];

    // 2) 부모의 오른쪽 자식에 pNodeZ를 단다.
    pParent->pChild[index + 1] = pNodeZ;

    // 3) 분할된 노드의 수를 줄이기
    pTree->n = T - 1;

    // [예시] key의 경우도 17을 한칸 땡겨야한다.
    for (int j = pParent->n - 1; j >= index; j--)
        pParent->keys[j + 1] = pParent->keys[j];

    // 4) 부모에 medianKey 올리기
    pParent->keys[index] = pTree->keys[T - 1];
    pParent->n++;
}

void insert(int key)
{
    // 만약에 루트 노드가 null이라면
    if (root == nullptr) {
        // 빈 노드를 생성해서 key 값을 채운다.
        root = createEmptyNode(true);
        root->keys[root->n++] = key;
    }
    // 루트에 노드가 있다면
    else {
        int i = 0;
        while (root->keys[i] < key)
            i++;

        insertNode(root, i, nullptr, key);
    }
}

void insertNode(BTreeNode* pTree, int childIdx, BTreeNode* pParent, int key)
{
    int i = pTree->n - 1;

    if (pTree->leafNode == false) {
        // 탐색하려는 인덱스를 찾는다.
        while ((i >= 0) && key < pTree->keys[i])
            i--;

        // 탐색을 이어간다.
        insertNode(pTree->pChild[i + 1], (i + 1), pTree, key);
    }
    else {
        // 원래 key 값과 비교하여 작다면 옆으로 이동시키고, (작은게 들어가니 큰 값은 옆으로 미뤄저야 된다. 
        while (key < pTree->keys[i] && i >= 0) {
            pTree->keys[i + 1] = pTree->keys[i];
            i--;
        }
        // 정렬 순서에서 알맞는 인덱스가 갱신되니 그대로 넣는다.
        pTree->keys[i + 1] = key;
        pTree->n++;
    }

    if (pTree->n == 2 * T - 1) {
        if (pParent) {
            splitNode(childIdx, pTree, pParent);
        }
        else {
            BTreeNode* pNode = createEmptyNode(false);
            pNode->pChild[0] = root;

            splitNode(0, pTree, pNode);
            root = pNode;
        }
    }
}

void traverse(BTreeNode* pNode)
{
    int k = 0;
    for (k = 0; k < pNode->n; k++) {
        if (pNode->leafNode == false) {
            traverse(pNode->pChild[k]);
        }
        printf("%d ", pNode->keys[k]);
    }

    if (pNode->leafNode == false) {
        traverse(pNode->pChild[k]);
    }
}
#endif
