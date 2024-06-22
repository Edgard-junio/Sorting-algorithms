#include "selectionSort.h"
#include "../LinkedList/LinkedList.h"
#include <iostream>
#include <chrono>
#include <random>

using std::cout;
using std::endl;
using std::string;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

// Método do Selection Sort não otimizado
template<typename T>
void SelectionSort::selectionSort(Node<T>* head)
{
    Node<T>* outerLoop = nullptr;
    Node<T> *innerLoop = nullptr;
    Node<T>* minNode = nullptr;

    for (outerLoop = head; outerLoop -> ptrNext != nullptr; outerLoop = outerLoop -> ptrNext) // Percorre a lista até o penúltimo elemento
    {
        minNode = outerLoop;

        // Procura o nó com o menor valor a partir do próximo nó ao nó atual
        for (innerLoop = outerLoop -> ptrNext; innerLoop != nullptr; innerLoop = innerLoop -> ptrNext)
        {
            if (innerLoop -> data < minNode -> data)
            {
                minNode = innerLoop;
            }
        }

        LinkedList::swapValue(outerLoop, minNode); // Troca os valores dos nós
    }
}

// Implementação do Selection Sort otimizado
template<typename T>
void SelectionSort::optimizedSelectionSort(Node<T>* head)
{
    if (head == nullptr) return;

    Node<T>* current = head;

    while (current != nullptr) // Percorre a lista até o último nó
    {
        Node<T>* minNode = current;
        Node<T>* nextNode = current -> ptrNext;

        // Procura o nó com o menor valor a partir do próximo nó ao nó atual
        while (nextNode != nullptr)
        {
            if (nextNode -> data < minNode -> data)
            {
                minNode = nextNode;
            }
            nextNode = nextNode->ptrNext;
        }

        // Se o nó mínimo não for o nó atual, troca os valores dos nós
        if (minNode != current)
        {
            LinkedList::swapValue(current, minNode); 
        }

        current = current -> ptrNext;
    }
}

// Função para medir o tempo dos dois métodos de Selection Sort
void SelectionSort::medetempoSelectionSort(int iSize)
{
    int iCount = 0;
    while (iCount < iSize)
    {
        cout << "Teste " << iCount << endl;
        Node<int>* node1 = nullptr;
        LinkedList::randomList(&node1, 10000); // Gera uma lista aleatória
        Node<int>* node2 = LinkedList::duplicateList(node1); // Duplica a lista

        // Mede o tempo da versão não otimizada
        auto timeStart = high_resolution_clock::now();
        selectionSort(node1);
        auto timeStop = high_resolution_clock::now();

        auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "Tempo de compila��o n�o otimizada = " << timeDuration.count() << endl;

        // Mede o tempo da versão otimizada
        timeStart = high_resolution_clock::now();
        optimizedSelectionSort(node2);
        timeStop = high_resolution_clock::now();

        timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "Tempo de compila��o otimizada = " << timeDuration.count() << endl;
        cout << endl;
        iCount++;
    }
}

// Instâncias explícitas para int
template void SelectionSort::selectionSort(Node<int>*);
template void SelectionSort::optimizedSelectionSort(Node<int>*);

// Instâncias explícitas para float
template void SelectionSort::selectionSort(Node<float>*);
template void SelectionSort::optimizedSelectionSort(Node<float>*);

// Instâncias explícitas para char
template void SelectionSort::selectionSort<char>(Node<char>* head);
template void SelectionSort::optimizedSelectionSort<char>(Node<char>* head);
