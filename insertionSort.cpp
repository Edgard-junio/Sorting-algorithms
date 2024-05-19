#include "insertionSort.h"
#include "LinkedList.h"
#include <iostream>
#include <chrono>
#include <random>

void InsertionSort::insertionSort(Node* lista)
{
    Node* ptrTemp = lista; // Ponteiro para o início da lista
    while (ptrTemp != nullptr) // Enquanto não chegarmos ao final da lista
    {
        Node* current = ptrTemp; // Criando um ponteiro para o elemento atual
        while (current->ptrPrev != nullptr) // Percorrendo a lista de trás para frente
        {
            if(current->ptrPrev->iNum > current->iNum) // Se o elemento anterior for maior que o atual
            {
                LinkedList::swapValue(current->ptrPrev, current); // Troca os valores dos elementos
            }
            current = current->ptrPrev; // Movendo para o próximo elemento anterior
        }
        ptrTemp = ptrTemp->ptrNext; // Movendo para o próximo elemento na lista
    }
}

void InsertionSort::optimizedInsertionSort(Node* head)
{
    // Verifica se a lista está vazia ou contém apenas um elemento
    if (head == nullptr || head -> ptrNext == nullptr)
        return; 

    Node* ptrTemp = head -> ptrNext; // Começando a partir do segundo elemento
    while (ptrTemp != nullptr)
    {
        int iValorInserir = ptrTemp -> iNum;
        Node* current = ptrTemp -> ptrPrev; // Começando do nó anterior
        while (current != nullptr && current -> iNum > iValorInserir)
        {
            current -> ptrNext -> iNum = current -> iNum; // Deslocando os elementos para realizar a inserção
            current = current -> ptrPrev; // Movendo para o nó anterior
        }
        if (current == nullptr)
        {
            head -> iNum = iValorInserir; // Se atual for nullptr, precisamos inserir no início
        }
        else
        {
            current -> ptrNext-> iNum = iValorInserir; // Insere o valor na posição correta
        }
        ptrTemp = ptrTemp -> ptrNext; // Move para o próximo elemento
    }
}


void InsertionSort::medetempoInsertion(int iSize)
{
    int iCount = 0;
    while (iCount < iSize)
    {
        std::cout << "Teste " << iCount << std::endl;
        Node* node1 = nullptr;
        LinkedList::randomList(node1, 10000); // Função que cria nós aleatórios
        Node* node2 = LinkedList::duplicateList(node1);

        auto timeStart = std::chrono::high_resolution_clock::now();
        insertionSort(node1); // Executa o insertionsort nao otimizado
        auto timeStop = std::chrono::high_resolution_clock::now(); // Medindo tempo de execução

        auto timeDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(timeStop - timeStart);
        std::cout << "Tempo de compilação não otimizada = " << timeDuration.count() << std::endl;
        
        timeStart = std::chrono::high_resolution_clock::now();
        optimizedInsertionSort(node2); // Executa o insertionsort otimizado
        timeStop = std::chrono::high_resolution_clock::now(); // Medindo tempo de execução

        timeDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(timeStop - timeStart);
        std::cout << "Tempo de compilação otimizada = " << timeDuration.count() << std::endl;
        std::cout << std::endl;
        iCount++;
    }
}

int main()
{
    InsertionSort::medetempoInsertion(100);
    return 0;
}
