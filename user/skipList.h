//#define SKIP_LIST
#pragma once
#if defined (SKIP_LIST)
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <time.h>
#include <stdlib.h>
#define MAX_LEVEL 3

// Node struct엔 key 정보와 다음 node를 가리킬 포인터 변수만 저장됩니다.
struct Node
{
    int key;
    struct Node** next;
};

// skipList 정보엔
typedef struct _SkipList
{
    struct Node* head; // 첫번째 Node를 가리키는 head node
    int level;         // skipList의 현재 level 정보
    float prob;        // skipList의 상위레벨로 도달 할 수 있는 확률 (튜닝 값입니다.)
} SkipList;

struct Node* allocNode(int key, int targetLevel);
void destroyAllNode();
void init();
void deinit();
int getRandeomLevel();
void insertNode(int key);
void searchKey(int key);
void printAllNode();
struct Node* deleteNode(int key);
void destroyNode(struct Node* remove);
#endif