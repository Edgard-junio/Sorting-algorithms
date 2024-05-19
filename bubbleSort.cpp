#include "bubbleSort.h"
#include "LinkedList.h"
#include <iostream>
#include <chrono>
#include <random>

void BubbleSort::bubbleSort(Node* lista, int iSize)
{
    bool bUnordered = false; // Inicia uma variável bool para saber se a lista está ordenada
    int iLoop = 0; // Inicia um contador
    Node* ptrTemp = nullptr;
    while (iLoop < iSize - 1)
    {
        Node* current = lista; // Novo ponteiro apontando para o início da lista
        while (current->ptrNext != ptrTemp)
        {
            if (current->iNum > current->ptrNext->iNum)
            {
                LinkedList::swapValue(current, current->ptrNext); // Troca os valores caso não esteja ordenado
                bUnordered = true;
            }
            current = current->ptrNext; // Atualiza o ponteiro
        }
        if (bUnordered == false) break; // Se não acontecer uma troca ele para o loop
        ptrTemp = current; // Atualiza até onde o loop deve ir
        iLoop++;
    }
}

void BubbleSort::bubbleSortUnoptimized(Node* lista, int iSize)
{
    // Bubblesort não otimizado
    Node* ptrTemp = lista;
    int iCount = 0;
    while (iCount < iSize - 1)
    {
        ptrTemp = lista; // Ponteiro aponta pro início da lista
        while (ptrTemp->ptrNext != nullptr)
        {
            if (ptrTemp->iNum > ptrTemp->ptrNext->iNum)
            {
                LinkedList::swapValue(ptrTemp, ptrTemp->ptrNext); // Se necessário, efetua a troca
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
        Node* node1 = nullptr;
        LinkedList::randomList(node1, 10000); // Função que cria nós aleatórios
        Node* node2 = LinkedList::duplicateList(node1);

        auto timeStart = std::chrono::high_resolution_clock::now();
        bubbleSortUnoptimized(node1, 10000);
        auto timeStop = std::chrono::high_resolution_clock::now(); // Medindo tempo de execução

        auto timeDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(timeStop - timeStart);
        std::cout << "Tempo de compilação não otimizada = " << timeDuration.count() << std::endl;

        timeStart = std::chrono::high_resolution_clock::now();
        bubbleSort(node2, 10000); // Executa o bubbleSort

        timeStop = std::chrono::high_resolution_clock::now(); // Medindo tempo de execução

        timeDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(timeStop - timeStart);
        std::cout << "Tempo de compilação otimizada = " << timeDuration.count() << std::endl;
        std::cout << std::endl;
        iCount++;
    }
}

int main()
{
    BubbleSort::medetempoBubbleSort(100);
    return 0;
}
