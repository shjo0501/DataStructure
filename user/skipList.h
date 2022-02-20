//#define SKIP_LIST
#pragma once
#if defined (SKIP_LIST)
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <time.h>
#include <stdlib.h>
#define MAX_LEVEL 3

// Node struct�� key ������ ���� node�� ����ų ������ ������ ����˴ϴ�.
struct Node
{
    int key;
    struct Node** next;
};

// skipList ������
typedef struct _SkipList
{
    struct Node* head; // ù��° Node�� ����Ű�� head node
    int level;         // skipList�� ���� level ����
    float prob;        // skipList�� ���������� ���� �� �� �ִ� Ȯ�� (Ʃ�� ���Դϴ�.)
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