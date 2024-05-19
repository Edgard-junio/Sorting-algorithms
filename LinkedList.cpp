#include "LinkedList.h"
#include <iostream>
#include <chrono>
#include <random>

Node* LinkedList::newNode(int iValor)
{
    Node* ptrTemp = new Node; // Alocando memória
    ptrTemp->iNum = iValor; // Atualizando os parâmetros do Node
    ptrTemp->ptrNext = nullptr;
    ptrTemp->ptrPrev = nullptr;
    return ptrTemp;
}

void LinkedList::addElementEnd(Node** list, int iValor)
{
    Node* ptrTemp = newNode(iValor); // Cria um novo elemento
    if (*list == nullptr)
    {
        *list = ptrTemp; // Como a lista é vazia nosso novo nó será o primeiro
    }
    else
    {
        Node* ptrCurrent = *list;
        while (ptrCurrent->ptrNext != nullptr)
        {
            ptrCurrent = ptrCurrent->ptrNext; // Levando o ponteiro pro final da lista
        }
        ptrCurrent->ptrNext = ptrTemp;
        ptrTemp->ptrPrev = ptrCurrent; // Atualizando os parâmetros
    }
}

void LinkedList::showNode(Node* list)
{
    if (list == nullptr)
    {
        std::cout << "Lista inválida" << std::endl;
    }
    else if (list->ptrPrev != nullptr)
    {
        std::cout << "Estamos no meio da lista" << std::endl;
    }
    else
    {
        std::cout << "Elementos: ";
        Node* ptrCurrent = list; // Cria um ponteiro auxiliar
        while (ptrCurrent != nullptr)
        {
            std::cout << ptrCurrent->iNum << " ";
            ptrCurrent = ptrCurrent->ptrNext; // Atualizando o nó
        }
        std::cout << std::endl;
    }
}

void LinkedList::swapValue(Node* iValue_1, Node* iValue_2)
{
    int iTemp = iValue_1->iNum;

    iValue_1->iNum = iValue_2->iNum;

    iValue_2->iNum = iTemp;
}

void LinkedList::randomList(Node* &lista, int iAmount)
{
    if (iAmount == 0) return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);

    for (int icount = 0; icount < iAmount; icount++)
    {
        addElementEnd(&lista, dis(gen)); // Adicionando um elemento aleatório
    }
}

Node* LinkedList::duplicateList(Node* lista)
{
    // Esta função recebe uma lista qualquer e retorna uma outra lista exatamente igual

    Node* ptrTemp = lista;
    Node* newList = nullptr;
    while (ptrTemp != nullptr)
    {
        addElementEnd(&newList, ptrTemp->iNum);
        ptrTemp = ptrTemp->ptrNext;
    }
    return newList;
}