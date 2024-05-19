#pragma once

typedef struct Node
{
    int iNum;
    Node* ptrNext;
    Node* ptrPrev;
}Node;

namespace LinkedList
{
    Node* newNode(int);
    void addElementEnd(Node**, int);
    void showNode(Node*);
    void swapValue(Node*, Node*);
    void randomList(Node*&, int);
    Node* duplicateList(Node*);
}