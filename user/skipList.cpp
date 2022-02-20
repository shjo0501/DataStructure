//#define SKIP_LIST
#if defined (SKIP_LIST)
#include "skipList.h"
SkipList skipList;

// 노드를 할당하고, 초기화하고 각 멤버 변수를 초기화 하는 과정입니다.
struct Node* allocNode(int key, int targetLevel)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    memset(newNode, 0, sizeof(newNode));
    newNode->key = key;

    newNode->next = (struct Node**)malloc((targetLevel + 1) * sizeof(struct Node*));
    memset(newNode->next, 0, (targetLevel + 1) * sizeof(newNode->next));

    return newNode;
}

// 할당된 노드를 해제하는 과정입니다.
// 가장 낮은 0번 레벨은 모든 노드를 포함하고 있기 때문에 0번 레벨만 삭제하면 모든 노드에 대해 메모리해제를 시킬 수 있습니다.
void destroyAllNode()
{
    struct Node* curNode = NULL;
    struct Node* tempNode = NULL;
    struct Node** temppNode = NULL;

    curNode = skipList.head->next[0];
    while (curNode != NULL) {
        // 현재 노드를 삭제해버리면, 다음 노드로 이동 할 수 없기 때문에 다음 node의 주소 값 tempNode에 저장합니다.
        tempNode = curNode;
        temppNode = curNode->next;
        curNode = curNode->next[0];
        free(tempNode);
        free(temppNode);
    }
}

// skipList를 위한 초기화 정보입니다.
void init()
{
    srand((unsigned int)time(NULL));
    skipList.head = allocNode(-1, MAX_LEVEL); // 확률(=rand())값을 얻어오기 위한 time
    skipList.level = 0;    // head를 여기서 할당하고,
    skipList.prob = 0.45f; // 상위 레벨로 가기위한 확률을 여기서 결정합니다. (=튜닝 값)
}

// skipList의 메모리를 해제하는 과정입니다.
void deinit()
{
    destroyAllNode();
}

// 설정한 확률 값(skipList.prob)을 바탕으로 level 값이 계산됩니다.
// 확률이 낮으면 상위 레벨로 갈 확률이 낮아집니다.
int getRandeomLevel()
{
    int level = 0;
    while (((float)rand() / RAND_MAX) < skipList.prob && level < MAX_LEVEL)
        level++;

    return level;
}

// 노드를 삽입하는 과정입니다.
void insertNode(int key)
{
    struct Node* curNode = skipList.head;
    struct Node* update[MAX_LEVEL + 1] = { 0 };
    struct Node* newNode = NULL;
    int randomLevel = 0;
    int k = 0;

    // 스킵리스트의 상위 레벨(express line)부터 하위 레벨의 모든 연결리스트에 대해 아래의 과정을 진행합니다.
    for (k = skipList.level; k >= 0; k--)
    {
        // 새로 입력된 key가 연결된 리스트에서 정렬된 순으로 제자리에 찾아 갈 수 있게끔 write를 될 위치를 계산합니다. 
        while (curNode->next[k] != NULL && curNode->next[k]->key < key)
            curNode = curNode->next[k];

        update[k] = curNode; // update는 모든 레별에 대해서 업데이트 되야될 위치(write 해야될) 위치를 알고있습니다.
    }

    // 하지만 0 level 해당 되는 curNode는 wrtie를 해야될 위치의 이전 위치값을 가지고 있기 때문에 한 스텝을 이동 해야 합니다. 
    curNode = curNode->next[0];

    // 0 level node에 대해 입력값이 NULL 이거나(비어있거나) 다른 key 값이 있다면 key를 새로 갱신해야되는 상황입니다.
    if (curNode == NULL || curNode->key != key) {
        // random level을 계산하고,
        randomLevel = getRandeomLevel();

        // skipList의 현재 상태 레벨 보다 크다면 레벨을 다시 설정 합니다.
        if (randomLevel > skipList.level) {
            // update가 배열이 업데이트된 레벨 만큼 늘어난 것이기 때문에 head를 추가로 초기화를 합니다.
            for (k = skipList.level + 1; k < randomLevel + 1; k++)
                update[k] = skipList.head;

            skipList.level = randomLevel;
        }

        // randomLevel 만큼의 next pointer를 가리키는 키와 key 값을 새로운 노드로 할당합니다.
        newNode = allocNode(key, randomLevel);

        // 새로 할당된 노드를 할당했으니 모든 레벨에 대해서 기존의 있던 연결리스트에 등록을 합니다.
        // update는 새로운 노드가 write될 위치를 알고 있기 때문에 그 주소를 기준으로 등록만 해주면 됩니다.
        for (k = 0; k < randomLevel + 1; k++)
        {
            newNode->next[k] = update[k]->next[k]; //  새로운 노드의 다음 위치엔 write 될 node의 다음 주소를
            update[k]->next[k] = newNode;          //  기존 노드(write)될 위치엔 새로운 노드를 연결합니다.
        }
    }
}

// 다음은 모든 레벨에 대해서 등록된 키가 있다면 찾는 함수입니다.
void searchKey(int key)
{
    struct Node* current = skipList.head;
    int k = 0;

    // 상위 레벨의 노드는 express line로 구성이 되어있기 때문에, 상위 노드 부터 검색을 합니다.
    for (k = skipList.level; k >= 0; k--) {
        // 상위 노드 부터 하위 레벨로 이동하면서 조건에 적합한 노드를 찾습니다.
        while (current->next[k] && current->next[k]->key < key) {
            current = current->next[k];
        }
    }
    // 하지만 0 level 해당 되는 curNode는 wrtie를 해야될 위치의 이전 위치값을 가지고 있기 때문에 한 스텝을 이동 해야 합니다. 
    current = current->next[0];

    // 키를 찾았다면 출력을 합니다.
    if (current->key == key) {
        printf("found %d\n", key);
    }
    else {
        printf("not found\n");
    }
}
// 연결된 리스트를 순회하면서 모든 레벨의 링크드 리스트를 출력하는 함수입니다.
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

// 해당 key가 링크드리스트에 존재하는지 확인하여 존재한다면 해당 key를 삭제하는 노드입니다.
struct Node* deleteNode(int key)
{
    struct Node* update[MAX_LEVEL + 1] = { 0 };
    struct Node* curNode = skipList.head;
    struct Node* remove = NULL;
    int k = 0;

    // 탐색은 기존의 searchKey 알고리즘을 동일하게 사용 한 후,
    for (k = skipList.level; k >= 0; k--) {
        while (curNode->next[k] && curNode->next[k]->key < key) {
            curNode = curNode->next[k];
        }

        update[k] = curNode;
    }

    curNode = curNode->next[0];

    // 해당되는 key라면
    if (curNode != NULL && curNode->key == key) {
        // 삭제될 node를 remove로 가리키도록 합니다.
        remove = curNode;

        // 그런 다음 하위 레벨 부터 순회하면서 해당 key를 포함하고 있다면 
        for (k = 0; k <= skipList.level; k++)
        {
            // 만약에 현재 레벨의 다음이 삭제할 노드를 포함하지 않는다면, 현제 레벨 뿐만 아니라 상위 레벨에도 삭제할 key가 없다는 뜻이기 때문에, 루프문을 탈출합니다. 
            if (update[k]->next[k] != curNode)
                break;

            // 삭제될 노드를 건너 뛰게 끔 연결하도록 링크드 리스트를 조정하는 과정입니다.
            update[k]->next[k] = curNode->next[k];
        }

        // 만약에 head가 가리키는 key 정보가 아무것도 없다면 level에 해당되는 코드가 없다는 뜻이므로 레벨을 낮춥니다.
        while (skipList.level > 0 && skipList.head->next[skipList.level] == 0)
            skipList.level--;
    }

    // 삭제될 주소를 반환합니다.
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