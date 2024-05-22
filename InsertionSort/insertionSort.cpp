#include "insertionSort.h"
#include "../LinkedList/LinkedList.h"
#include <iostream>
#include <chrono>
#include <random>

using std::endl;
using std::cout;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

template<typename T>
void InsertionSort::insertionSort(Node<T>* lista)
{
    Node<T>* ptrTemp = lista;
    while (ptrTemp != nullptr)
    {
        Node<T>* current = ptrTemp;
        while (current->ptrPrev != nullptr)
        {
            if(current->ptrPrev->data > current->data)
            {
                LinkedList::swapValue(current->ptrPrev, current);
            }
            current = current->ptrPrev;
        }
        ptrTemp = ptrTemp->ptrNext;
    }
}

template<typename T>
void InsertionSort::optimizedInsertionSort(Node<T>* head)
{
    if (head == nullptr || head -> ptrNext == nullptr)
        return; 

    Node<T>* ptrTemp = head -> ptrNext;
    while (ptrTemp != nullptr)
    {
        T iValorInserir = ptrTemp -> data;
        Node<T>* current = ptrTemp -> ptrPrev;
        while (current != nullptr && current -> data > iValorInserir)
        {
            current -> ptrNext -> data = current -> data;
            current = current -> ptrPrev;
        }
        if (current == nullptr)
        {
            head -> data = iValorInserir;
        }
        else
        {
            current -> ptrNext-> data = iValorInserir;
        }
        ptrTemp = ptrTemp -> ptrNext;
    }
}

void InsertionSort::medetempoInsertionSort(int iSize)
{
    int iCount = 0;
    while (iCount < iSize)
    {
        cout << "Teste " << iCount << endl;
        Node<int>* node1 = nullptr;
        LinkedList::randomList(&node1, 10000);
        Node<int>* node2 = LinkedList::duplicateList(node1);

        auto timeStart = high_resolution_clock::now();
        InsertionSort::insertionSort(node1);
        auto timeStop = high_resolution_clock::now();

        auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "Tempo de compila��o n�o otimizada = " << timeDuration.count() << endl;

        timeStart = high_resolution_clock::now();
        InsertionSort::optimizedInsertionSort(node2);
        timeStop = high_resolution_clock::now();

        timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "Tempo de compila��o otimizada = " << timeDuration.count() << endl;
        cout << endl;
        iCount++;
    }
}

// Instâncias explícitas para int
template void InsertionSort::insertionSort(Node<int>*);
template void InsertionSort::optimizedInsertionSort(Node<int>*);

// Instâncias explícitas para float
template void InsertionSort::insertionSort(Node<float>*);
template void InsertionSort::optimizedInsertionSort(Node<float>*);

// Instâncias explícitas para char
template void InsertionSort::insertionSort(Node<char>*);
template void InsertionSort::optimizedInsertionSort(Node<char>*);

// Instâncias explícitas para double
template void InsertionSort::insertionSort(Node<double>*);
template void InsertionSort::optimizedInsertionSort(Node<double>*);

