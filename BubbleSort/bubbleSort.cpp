#include "bubbleSort.h"
#include "../LinkedList/LinkedList.h"
#include <iostream>
#include <chrono>
#include <random>

// Método bubbleSort otimizado
template<typename T>
void BubbleSort::bubbleSort(Node<T>* lista, int iSize)
{
    bool bUnordered = false; // Flag para verificar se houve troca
    int iLoop = 0;
    Node<T>* ptrTemp = nullptr;
    while (iLoop < iSize - 1)
    {
        Node<T>* current = lista;
        while (current->ptrNext != ptrTemp) // Percorre a lista até o ponto ordenado
        {
            if (current->data > current->ptrNext->data)
            {
                LinkedList::swapValue(current, current->ptrNext); // Troca os valores dos nós
                bUnordered = true;
            }
            current = current->ptrNext;
        }
        if (bUnordered == false) break;
        ptrTemp = current;
        iLoop++;
    }
}

// Método bubbleSort não otimizado
template<typename T>
void BubbleSort::bubbleSortUnoptimized(Node<T>* lista, int iSize)
{
    Node<T>* ptrTemp = lista;
    int iCount = 0;
    while (iCount < iSize - 1)
    {
        ptrTemp = lista;
        while (ptrTemp->ptrNext != nullptr) // Percorre a lista inteira
        {
            if (ptrTemp->data > ptrTemp->ptrNext->data)
            {
                LinkedList::swapValue(ptrTemp, ptrTemp->ptrNext); // Troca os valores dos nós
            }
            ptrTemp = ptrTemp->ptrNext;
        }
        iCount++;
    }
}

// Função para medir o tempo dos dois métodos de bubbleSort
void BubbleSort::medetempoBubbleSort(int iSize)
{
    int iCount = 0;
    while (iCount < iSize)
    {
        std::cout << "Teste " << iCount << std::endl;
        Node<int>* node1 = nullptr;
        LinkedList::randomList(&node1, 10000); // Gera uma lista aleatória
        Node<int>* node2 = LinkedList::duplicateList(node1); // Duplica a lista

        // Mede o tempo da versão não otimizada
        auto timeStart = std::chrono::high_resolution_clock::now();
        bubbleSortUnoptimized(node1, 10000); 
        auto timeStop = std::chrono::high_resolution_clock::now();

        auto timeDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(timeStop - timeStart);
        std::cout << "Tempo de compila��o n�o otimizada = " << timeDuration.count() << std::endl;

        // Mede o tempo da versão otimizada
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
