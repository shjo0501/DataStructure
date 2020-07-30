#ifndef _LISTH
#define _LISTH
#include <malloc.h>

template <class T> class list
{
    private:
    struct node {
        T data;
        struct node* pNext;
        struct node* pPrev;
        node() :data(0), pNext(nullptr), pPrev(nullptr) {}
    };

    private:
        node* pHead;
        node* pTail;
        unsigned int size;

        node* allocateNode(T data)
        {
            node* n = (node*)malloc(sizeof(node));
            n->data = data;
            n->pNext = nullptr;
            n->pPrev = nullptr;

            return n;
        }

        void destroyAllNode()
        {
            if (pHead)
            {
                node* pCur = pHead;
                node* pTemp;
                while (pCur)
                {
                    pTemp = pCur->pNext;
                    free(pCur);
                    pCur = pTemp;
                }
            }
        }

    public:
        list<T>():pHead(nullptr), pTail(nullptr), size(0) {}
        ~list<T>() 
        {
            destroyAllNode();
        }

        void push(T data)
        {
            if (pHead)
            {
                pTail->pNext = allocateNode(data);
                pTail->pNext->pPrev = pTail;
                pTail = pTail->pNext;
            }

            if (pHead == nullptr)
            {
                pHead = allocateNode(data);
                pTail = pHead;
            }

            size++;
        }

        node* search(T data)
        {
            node* pCur = pHead;
            unsigned int index = 0;
            while (pCur)
            {
                if (pCur->data == data)
                    break;

                index++;
                pCur = pCur->pNext;
            }

            return pCur;
        }

        void remove(T data)
        {
            node* pCur = search(data);
            if (pCur)
            {
                if (pCur->pPrev)
                    pCur->pPrev->pNext = pCur->pNext;
                else
                    pHead = pCur->pNext;

                if (pCur->pNext)
                    pCur->pNext->pPrev = pCur->pPrev;
                else
                    pTail = pCur->pPrev;

                free(pCur);
                size--;
            }
        }

#if 1
        void printAllNode(bool isReverse)
        {
            node* pCur = pTail;

            if (isReverse)
            {
                pCur = pTail;
                while (pCur != nullptr)
                {
                    printf("%d ", pCur->data);
                    pCur = pCur->pPrev;
                }
            }
            else
            {
                pCur = pHead;
                while (pCur != nullptr)
                {
                    printf("%d ", pCur->data);
                    pCur = pCur->pNext;
                }
            }
        }
#endif
};

#endif

