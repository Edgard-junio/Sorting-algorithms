#pragma once
#include "../LinkedList/LinkedList.h"

namespace BubbleSort
{
    template<typename T>
    void bubbleSort(Node<T>* lista, int iSize);

    template<typename T>
    void bubbleSortUnoptimized(Node<T>* lista, int iSize);

    void medetempoBubbleSort(int iSize);
}

