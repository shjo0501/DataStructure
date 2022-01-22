#include "Deque.h"
#include <iostream>
using namespace std;

deque::deque() : head(0), tail(0)
{
    memset(dataArray, 0, sizeof(dataArray));
}

deque::~deque() {}

void deque::push_front(ElementData data)
{
    if (full())
    {
        printf("deque is full\n");
        return;
    }
    dataArray[head] = data;
    head = (head + MAX_SIZE - 1) % MAX_SIZE;
}

void deque::push_back(ElementData data)
{
    if (full())
    {
        printf("deque is full\n");
        return;
    }
    tail = (tail + 1) % MAX_SIZE;
    dataArray[tail] = data;
}

bool deque::empty()
{
    return head == tail;
}

bool deque::full()
{
    return ((tail + 1) % MAX_SIZE) == head;
}

void deque::pop_front()
{
    if (deque::empty())
    {
        printf("deque is empty\n");
        return;
    }

    head = (head + 1) % MAX_SIZE;
}

void deque::pop_back()
{
    if (empty())
    {
        printf("deque is empty\n");
        return;
    }

    tail = (tail + MAX_SIZE - 1) % MAX_SIZE;
}

ElementData deque::front()
{
    return dataArray[(head + 1) % MAX_SIZE];
}

ElementData deque::back()
{
    return dataArray[tail];
}

void deque::print()
{
    int h = head, t = tail;
    while (h != t)
    {
        h = (h + 1) % MAX_SIZE;
        printf("%d ", dataArray[h].data);
    }
    printf("\n");
}