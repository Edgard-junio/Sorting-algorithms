#pragma once
#include "../LinkedList/LinkedList.h"

namespace InsertionSort
{
    template<typename T>
    void insertionSort(Node<T>* lista);

    template<typename T>
    void optimizedInsertionSort(Node<T>* head);

    void medetempoInsertionSort(int iSize);
}

