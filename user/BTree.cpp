#define B_TREE
#if defined (B_TREE)
#include "BTree.h"
#include <iostream>
#include <algorithm>
using namespace std;
//https://www.cs.usfca.edu/~galles/visualization/BTree.html

// BTree Property
int t = 2;

struct BTreeNode
{
#define MAX 32

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
    // leaf flag가 전달되는 방식 고민 필요
    BTreeNode* pNodeZ = createEmptyNode(pTree->leafNode);
    pNodeZ->n = t - 1;
    // 1) 새로운 노드(pNodeZ)가 부모가 되고, 오른쪽 key 값엔 median을 중심으로 오른쪽 값들을 저장시킨다. // 왼쪽엔 기존에 연결되어 있던 것을 사용한다.
    for (int k = 0; k < t - 1; k++) {
        pNodeZ->keys[k] = pTree->keys[k + t];
    }

    // 2) 만일에 leafNode가 아니라면
    if (pTree->leafNode == false) {
        // 새로운 부모에 기존의 오른쪽 child만 연결 시킨다. // 왼쪽엔 기존에 연결되어 있던 것을 사용한다.
        for (int k = 0; k < t; k++)
            pNodeZ->pChild[k] = pTree->pChild[k + t];
    }

    // [예시]
    // Parent엔 기존의 key 값이 있었고 기존의 pChild이 있는 상황에서 분할된 median 노드가 추가되면 child 값의 순서를 재정렬 할 필요가 있다. (자식에서 분할된 노드가 올라올 때 왼쪽에서 온거면 자식의 median은 부모 보다 값이 작다.)
    // 가령 key가 17이 있고 pChild[0]->key 13 14 15, pChild[1]->key엔 20이 있다면 14가 새로올라와서 parent는 14, 17이 된다. 하지만 이때 pChild[1]->key가 20이므로 옆으로 땡겨야한다.
    for (int j = pParent->n; j >= index + 1; j--)
        pParent->pChild[j + 1] = pParent->pChild[j];

    // 2) 부모의 오른쪽 자식에 pNodeZ를 단다.
    pParent->pChild[index + 1] = pNodeZ;

    // 3) 분할된 노드의 수를 줄이기
    pTree->n = t - 1;

    // [예시] key의 경우도 17을 한칸 땡겨야한다.
    for (int j = pParent->n - 1; j >= index; j--)
        pParent->keys[j + 1] = pParent->keys[j];

    // 4) 부모에 medianKey 올리기
    pParent->keys[index] = pTree->keys[t - 1];
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
        // 루트 노드에 여유 공간이 없을 경우
        if (root->n == 2 * t - 1) {
            BTreeNode* pNode = createEmptyNode(false);
            pNode->pChild[0] = root;
            splitNode(0, root, pNode);

            // Median Key 값만 새로 올라왔으니, 새롭게 할당된 노드엔 키가 하나다.
            int i = 0;
            if (pNode->keys[0] < key)
                i++;

            // 새로운 root 노드를 기준으로 탐색을 진행한다.
            insertNode(pNode->pChild[i], key);
            root = pNode;
        }
        else {
            insertNode(root, key);
        }
    }
}

void insertNode(BTreeNode* pTree, int key)
{
    int i = pTree->n - 1;

    if (pTree->leafNode == false) {
        // 탐색하려는 인덱스를 찾는다.
        while ((i >= 0) && key < pTree->keys[i]) 
            i--;

        // 탐색하는 노드마다 여유가 없다면 미리 분할한다.
        // 1) 탐색하려는 노드의 자식이 여유가 없다면
        if (pTree->pChild[i + 1]->n == 2 * t - 1) {
            // 2) 탐색하려는 인덱스를 기준으로 분할한다.
            splitNode(i + 1, pTree->pChild[i + 1], pTree);

            // 3) 분할을 한 후, key 값이 탐색하려던 노드의 key 값 보다 더 적어진다면, 인덱스를 한칸 이동시킨다. (원래는 key가 제일 작아서 0번 이었느나, 새로들어온게 더 작아져 버리니 인덱스 갱신을 시켜야된다.
            if (pTree->keys[i + 1] < key)
                i++;
        }

        // 분할이 끝났으니, 탐색을 이어간다.
        insertNode(pTree->pChild[i + 1], key);
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