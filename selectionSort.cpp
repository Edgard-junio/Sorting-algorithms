#include "LinkedList.h"
#include "selectionSort.h"
#include <iostream>
#include <chrono>
#include <random>

using std::cout;
using std::endl;
using std::string;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

void SelectionSort::selectionSort(Node* head)
{

    Node* outerLoop = nullptr;
    Node *innerLoop = nullptr;
    Node* minNode = nullptr;

    // Realizando loop externo
    for (outerLoop = head; outerLoop -> ptrNext != nullptr; outerLoop = outerLoop -> ptrNext)
    {
        minNode = outerLoop;

        // Encontrando o menor elemento no loop interno
        for (innerLoop = outerLoop -> ptrNext; innerLoop != nullptr; innerLoop = innerLoop -> ptrNext)
        {
            if (innerLoop -> iNum < minNode -> iNum)
            {
                minNode = innerLoop;
            }
        }

        // Trocando os valores
        LinkedList::swapValue(outerLoop, minNode); 
    }
}

void SelectionSort::optimizedSelectionSort(Node* head)
{
    if (head == nullptr) return;

    Node* current = head;  // Nó externo

    while (current != nullptr)
    {
        // Encontra o nó com o menor valor entre "current" e o fim da lista
        Node* minNode = current;
        Node* nextNode = current -> ptrNext;  // Nó interno para busca do mínimo

        while (nextNode != nullptr)
        {
            if (nextNode -> iNum < minNode -> iNum)
            {
                minNode = nextNode;
            }
            nextNode = nextNode->ptrNext;
        }

        // Se necessário, faça a troca entre "current" e "minNode"
        if (minNode != current)
        {
            LinkedList::swapValue(current, minNode); 
        }

        current = current -> ptrNext;
    }
}

void SelectionSort::medetempoSelectionSort(int iSize)
{
    int iCount = 0;
    while (iCount < iSize)
    {
        cout<<"Teste "<<iCount<<endl;
        Node* node1 = nullptr;
        LinkedList::randomList(node1, 10000); //função que cria nós aleatorios
        Node* node2 = LinkedList::duplicateList(node1);

        auto timeStart = high_resolution_clock::now();
        selectionSort(node1);// Executa o selection nao otimizado
        auto timeStop = high_resolution_clock::now();//medindo tempo de execução

        auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout<< "Tempo de compilação não otimizada = " <<timeDuration.count()<<endl;
        timeStart = high_resolution_clock::now();
        optimizedSelectionSort(node2); // Executa o selection otimizado
        timeStop = high_resolution_clock::now(); // medindo tempo de execução

        timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "Tempo de compilação otimizada = " << timeDuration.count() << endl;
        cout<<endl;
        iCount++;
    }
}

int main()
{
    SelectionSort::medetempoSelectionSort(1000);
    return 0;
}
