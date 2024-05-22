#include "LinkedList.h"
#include <iostream>
#include <chrono>
#include <random>

template<typename T>
Node<T>* LinkedList::newNode(T data)
{
    Node<T>* temp = new Node<T>;
    temp->data = data;
    temp->ptrNext = nullptr;
    temp->ptrPrev = nullptr;
    return temp;
}

template<typename T>
void LinkedList::addElementEnd(Node<T>** list, T data)
{
    Node<T>* temp = LinkedList::newNode(data);
    if (*list == nullptr)
    {
        *list = temp;
    }
    else
    {
        Node<T>* current = *list;
        while (current->ptrNext != nullptr)
        {
            current = current->ptrNext;
        }
        current->ptrNext = temp;
        temp->ptrPrev = current;
    }
}

template<typename T>
void LinkedList::showNode(Node<T>* list)
{
    if (list == nullptr)
    {
        std::cout << "Lista inv�lida" << std::endl;
    }
    else if (list->ptrPrev != nullptr)
    {
        std::cout << "Estamos no meio da lista" << std::endl;
    }
    else
    {
        std::cout << "Elementos: ";
        Node<T>* current = list;
        while (current != nullptr)
        {
            std::cout << current->data << " ";
            current = current->ptrNext;
        }
        std::cout << std::endl;
    }
}

template<typename T>
void LinkedList::swapValue(Node<T>* node1, Node<T>* node2)
{
    T temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}

void LinkedList::randomList(Node<int>** list, int amount)
{
    if (amount == 0) return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    for (int count = 0; count < amount; count++)
    {
        LinkedList::addElementEnd(list, dis(gen));
    }
}

template<typename T>
Node<T>* LinkedList::duplicateList(Node<T>* list)
{
    Node<T>* temp = list;
    Node<T>* newList = nullptr;
    while (temp != nullptr)
    {
        LinkedList::addElementEnd(&newList, temp->data);
        temp = temp->ptrNext;
    }
    return newList;
}

template Node<int>* LinkedList::newNode(int);
template void LinkedList::addElementEnd(Node<int>**, int);
template void LinkedList::showNode(Node<int>*);
template void LinkedList::swapValue(Node<int>*, Node<int>*);
template Node<int>* LinkedList::duplicateList(Node<int>*);

template Node<float>* LinkedList::newNode(float);
template void LinkedList::addElementEnd(Node<float>**, float);
template void LinkedList::showNode(Node<float>*);
template void LinkedList::swapValue(Node<float>*, Node<float>*);
template Node<float>* LinkedList::duplicateList(Node<float>*);

template Node<char>* LinkedList::newNode(char);
template void LinkedList::addElementEnd(Node<char>**, char);
template void LinkedList::showNode(Node<char>*);
template void LinkedList::swapValue(Node<char>*, Node<char>*);
template Node<char>* LinkedList::duplicateList(Node<char>*);

// Instância explícita para newNode com tipo double
template Node<double>* LinkedList::newNode(double);
template void LinkedList::addElementEnd(Node<double>**, double);
template void LinkedList::showNode(Node<double>*);
template void LinkedList::swapValue(Node<double>*, Node<double>*);
template Node<double>* LinkedList::duplicateList(Node<double>*);

