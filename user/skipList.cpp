//#define SKIP_LIST
#if defined (SKIP_LIST)
#include "skipList.h"
SkipList skipList;

// ��带 �Ҵ��ϰ�, �ʱ�ȭ�ϰ� �� ��� ������ �ʱ�ȭ �ϴ� �����Դϴ�.
struct Node* allocNode(int key, int targetLevel)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    memset(newNode, 0, sizeof(newNode));
    newNode->key = key;

    newNode->next = (struct Node**)malloc((targetLevel + 1) * sizeof(struct Node*));
    memset(newNode->next, 0, (targetLevel + 1) * sizeof(newNode->next));

    return newNode;
}

// �Ҵ�� ��带 �����ϴ� �����Դϴ�.
// ���� ���� 0�� ������ ��� ��带 �����ϰ� �ֱ� ������ 0�� ������ �����ϸ� ��� ��忡 ���� �޸������� ��ų �� �ֽ��ϴ�.
void destroyAllNode()
{
    struct Node* curNode = NULL;
    struct Node* tempNode = NULL;
    struct Node** temppNode = NULL;

    curNode = skipList.head->next[0];
    while (curNode != NULL) {
        // ���� ��带 �����ع�����, ���� ���� �̵� �� �� ���� ������ ���� node�� �ּ� �� tempNode�� �����մϴ�.
        tempNode = curNode;
        temppNode = curNode->next;
        curNode = curNode->next[0];
        free(tempNode);
        free(temppNode);
    }
}

// skipList�� ���� �ʱ�ȭ �����Դϴ�.
void init()
{
    srand((unsigned int)time(NULL));
    skipList.head = allocNode(-1, MAX_LEVEL); // Ȯ��(=rand())���� ������ ���� time
    skipList.level = 0;    // head�� ���⼭ �Ҵ��ϰ�,
    skipList.prob = 0.45f; // ���� ������ �������� Ȯ���� ���⼭ �����մϴ�. (=Ʃ�� ��)
}

// skipList�� �޸𸮸� �����ϴ� �����Դϴ�.
void deinit()
{
    destroyAllNode();
}

// ������ Ȯ�� ��(skipList.prob)�� �������� level ���� ���˴ϴ�.
// Ȯ���� ������ ���� ������ �� Ȯ���� �������ϴ�.
int getRandeomLevel()
{
    int level = 0;
    while (((float)rand() / RAND_MAX) < skipList.prob && level < MAX_LEVEL)
        level++;

    return level;
}

// ��带 �����ϴ� �����Դϴ�.
void insertNode(int key)
{
    struct Node* curNode = skipList.head;
    struct Node* update[MAX_LEVEL + 1] = { 0 };
    struct Node* newNode = NULL;
    int randomLevel = 0;
    int k = 0;

    // ��ŵ����Ʈ�� ���� ����(express line)���� ���� ������ ��� ���Ḯ��Ʈ�� ���� �Ʒ��� ������ �����մϴ�.
    for (k = skipList.level; k >= 0; k--)
    {
        // ���� �Էµ� key�� ����� ����Ʈ���� ���ĵ� ������ ���ڸ��� ã�� �� �� �ְԲ� write�� �� ��ġ�� ����մϴ�. 
        while (curNode->next[k] != NULL && curNode->next[k]->key < key)
            curNode = curNode->next[k];

        update[k] = curNode; // update�� ��� ������ ���ؼ� ������Ʈ �Ǿߵ� ��ġ(write �ؾߵ�) ��ġ�� �˰��ֽ��ϴ�.
    }

    // ������ 0 level �ش� �Ǵ� curNode�� wrtie�� �ؾߵ� ��ġ�� ���� ��ġ���� ������ �ֱ� ������ �� ������ �̵� �ؾ� �մϴ�. 
    curNode = curNode->next[0];

    // 0 level node�� ���� �Է°��� NULL �̰ų�(����ְų�) �ٸ� key ���� �ִٸ� key�� ���� �����ؾߵǴ� ��Ȳ�Դϴ�.
    if (curNode == NULL || curNode->key != key) {
        // random level�� ����ϰ�,
        randomLevel = getRandeomLevel();

        // skipList�� ���� ���� ���� ���� ũ�ٸ� ������ �ٽ� ���� �մϴ�.
        if (randomLevel > skipList.level) {
            // update�� �迭�� ������Ʈ�� ���� ��ŭ �þ ���̱� ������ head�� �߰��� �ʱ�ȭ�� �մϴ�.
            for (k = skipList.level + 1; k < randomLevel + 1; k++)
                update[k] = skipList.head;

            skipList.level = randomLevel;
        }

        // randomLevel ��ŭ�� next pointer�� ����Ű�� Ű�� key ���� ���ο� ���� �Ҵ��մϴ�.
        newNode = allocNode(key, randomLevel);

        // ���� �Ҵ�� ��带 �Ҵ������� ��� ������ ���ؼ� ������ �ִ� ���Ḯ��Ʈ�� ����� �մϴ�.
        // update�� ���ο� ��尡 write�� ��ġ�� �˰� �ֱ� ������ �� �ּҸ� �������� ��ϸ� ���ָ� �˴ϴ�.
        for (k = 0; k < randomLevel + 1; k++)
        {
            newNode->next[k] = update[k]->next[k]; //  ���ο� ����� ���� ��ġ�� write �� node�� ���� �ּҸ�
            update[k]->next[k] = newNode;          //  ���� ���(write)�� ��ġ�� ���ο� ��带 �����մϴ�.
        }
    }
}

// ������ ��� ������ ���ؼ� ��ϵ� Ű�� �ִٸ� ã�� �Լ��Դϴ�.
void searchKey(int key)
{
    struct Node* current = skipList.head;
    int k = 0;

    // ���� ������ ���� express line�� ������ �Ǿ��ֱ� ������, ���� ��� ���� �˻��� �մϴ�.
    for (k = skipList.level; k >= 0; k--) {
        // ���� ��� ���� ���� ������ �̵��ϸ鼭 ���ǿ� ������ ��带 ã���ϴ�.
        while (current->next[k] && current->next[k]->key < key) {
            current = current->next[k];
        }
    }
    // ������ 0 level �ش� �Ǵ� curNode�� wrtie�� �ؾߵ� ��ġ�� ���� ��ġ���� ������ �ֱ� ������ �� ������ �̵� �ؾ� �մϴ�. 
    current = current->next[0];

    // Ű�� ã�Ҵٸ� ����� �մϴ�.
    if (current->key == key) {
        printf("found %d\n", key);
    }
    else {
        printf("not found\n");
    }
}
// ����� ����Ʈ�� ��ȸ�ϸ鼭 ��� ������ ��ũ�� ����Ʈ�� ����ϴ� �Լ��Դϴ�.
void printAllNode()
{
    struct Node* curNode = NULL;
    int k = 0;
    printf("########[skipList]########\n");
    for (k = 0; k < skipList.level + 1; k++)
    {
        curNode = skipList.head->next[k];
        printf("[level: %d] ", k);
        while (curNode != NULL) {
            printf("%d ", curNode->key);
            curNode = curNode->next[k];
        }
        printf("\n");
    }
}

// �ش� key�� ��ũ�帮��Ʈ�� �����ϴ��� Ȯ���Ͽ� �����Ѵٸ� �ش� key�� �����ϴ� ����Դϴ�.
struct Node* deleteNode(int key)
{
    struct Node* update[MAX_LEVEL + 1] = { 0 };
    struct Node* curNode = skipList.head;
    struct Node* remove = NULL;
    int k = 0;

    // Ž���� ������ searchKey �˰����� �����ϰ� ��� �� ��,
    for (k = skipList.level; k >= 0; k--) {
        while (curNode->next[k] && curNode->next[k]->key < key) {
            curNode = curNode->next[k];
        }

        update[k] = curNode;
    }

    curNode = curNode->next[0];

    // �ش�Ǵ� key���
    if (curNode != NULL && curNode->key == key) {
        // ������ node�� remove�� ����Ű���� �մϴ�.
        remove = curNode;

        // �׷� ���� ���� ���� ���� ��ȸ�ϸ鼭 �ش� key�� �����ϰ� �ִٸ� 
        for (k = 0; k <= skipList.level; k++)
        {
            // ���࿡ ���� ������ ������ ������ ��带 �������� �ʴ´ٸ�, ���� ���� �Ӹ� �ƴ϶� ���� �������� ������ key�� ���ٴ� ���̱� ������, �������� Ż���մϴ�. 
            if (update[k]->next[k] != curNode)
                break;

            // ������ ��带 �ǳ� �ٰ� �� �����ϵ��� ��ũ�� ����Ʈ�� �����ϴ� �����Դϴ�.
            update[k]->next[k] = curNode->next[k];
        }

        // ���࿡ head�� ����Ű�� key ������ �ƹ��͵� ���ٸ� level�� �ش�Ǵ� �ڵ尡 ���ٴ� ���̹Ƿ� ������ ����ϴ�.
        while (skipList.level > 0 && skipList.head->next[skipList.level] == 0)
            skipList.level--;
    }

    // ������ �ּҸ� ��ȯ�մϴ�.
    return remove;
}

void destroyNode(struct Node* remove)
{
    if (remove)
    {
        free(remove->next);
        free(remove);
    }
}
#endif