#include "bubbleSort.h"
#include "../LinkedList/LinkedList.h"
#include <iostream>
#include <chrono>
#include <random>

template<typename T>
void BubbleSort::bubbleSort(Node<T>* lista, int iSize)
{
    bool bUnordered = false;
    int iLoop = 0;
    Node<T>* ptrTemp = nullptr;
    while (iLoop < iSize - 1)
    {
        Node<T>* current = lista;
        while (current->ptrNext != ptrTemp)
        {
            if (current->data > current->ptrNext->data)
            {
                LinkedList::swapValue(current, current->ptrNext);
                bUnordered = true;
            }
            current = current->ptrNext;
        }
        if (bUnordered == false) break;
        ptrTemp = current;
        iLoop++;
    }
}

template<typename T>
void BubbleSort::bubbleSortUnoptimized(Node<T>* lista, int iSize)
{
    Node<T>* ptrTemp = lista;
    int iCount = 0;
    while (iCount < iSize - 1)
    {
        ptrTemp = lista;
        while (ptrTemp->ptrNext != nullptr)
        {
            if (ptrTemp->data > ptrTemp->ptrNext->data)
            {
                LinkedList::swapValue(ptrTemp, ptrTemp->ptrNext);
            }
            ptrTemp = ptrTemp->ptrNext;
        }
        iCount++;
    }
}

void BubbleSort::medetempoBubbleSort(int iSize)
{
    int iCount = 0;
    while (iCount < iSize)
    {
        std::cout << "Teste " << iCount << std::endl;
        Node<int>* node1 = nullptr;
        LinkedList::randomList(&node1, 10000);
        Node<int>* node2 = LinkedList::duplicateList(node1);

        auto timeStart = std::chrono::high_resolution_clock::now();
        bubbleSortUnoptimized(node1, 10000);
        auto timeStop = std::chrono::high_resolution_clock::now();

        auto timeDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(timeStop - timeStart);
        std::cout << "Tempo de compila��o n�o otimizada = " << timeDuration.count() << std::endl;

        timeStart = std::chrono::high_resolution_clock::now();
        bubbleSort(node2, 10000);
        timeStop = std::chrono::high_resolution_clock::now();

        timeDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(timeStop - timeStart);
        std::cout << "Tempo de compila��o otimizada = " << timeDuration.count() << std::endl;
        std::cout << std::endl;
        iCount++;
    }
}

// Instâncias explícitas para int
template void BubbleSort::bubbleSort(Node<int>*, int);
template void BubbleSort::bubbleSortUnoptimized(Node<int>*, int);

// Instâncias explícitas para float
template void BubbleSort::bubbleSort(Node<float>*, int);
template void BubbleSort::bubbleSortUnoptimized(Node<float>*, int);

// Instâncias explícitas para char
template void BubbleSort::bubbleSort(Node<char>*, int);
template void BubbleSort::bubbleSortUnoptimized(Node<char>* , int);

// Instâncias explícitas para double
template void BubbleSort::bubbleSort(Node<double>*, int);
template void BubbleSort::bubbleSortUnoptimized(Node<double>*, int);
