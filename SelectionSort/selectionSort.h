#pragma once
#include "../LinkedList/LinkedList.h"

namespace SelectionSort
{
    template<typename T>
    void selectionSort(Node<T>* head);

    template<typename T>
    void optimizedSelectionSort(Node<T>* head);

    void medetempoSelectionSort(int iSize);
}

