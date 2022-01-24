//#define DEQUE
#pragma once
#if defined (DEQUE)
struct ElementData
{
    int data;
    
    ElementData() {}
    ~ElementData() {}
    ElementData(int _data) :data(_data) {}
};

class deque {
private:
#define MAX_SIZE 16
    ElementData dataArray[MAX_SIZE];
    int head, tail;

public:
    deque();
    ~deque();

    void push_front(ElementData data);
    void push_back(ElementData data);
    bool empty();
    bool full();
    void pop_front();
    void pop_back();
    ElementData front();
    ElementData back();
    void print();
};
#endif