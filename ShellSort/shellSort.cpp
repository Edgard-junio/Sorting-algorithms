#include "ShellSort.h"
#include "../LinkedList/LinkedList.h"
#include <iostream>
#include <chrono>

using std::cout;
using std::endl;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

template<typename T>
void ShellSort::shellSort(Node<T>** head, int n)
{
    if ((*head) == nullptr)
    {
        cout << "Lista vazia" << endl;
        return;
    }

    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            Node<T>* current = *head;
            for (int j = 0; j < i; j++)
            {
                if (current == nullptr)
                    break;
                current = current->ptrNext;
            }
            if (current == nullptr)
                break;

            T temp = current->data;
            Node<T>* inner = current->ptrPrev;
            while (inner != nullptr && inner->data > temp)
            {
                LinkedList::swapValue(inner->ptrNext, inner);
                inner = inner->ptrPrev;
            }
            if (inner != nullptr)
                inner->ptrNext->data = temp;
        }
    }   
}

template<typename T>
void ShellSort::optimizedshellSort(Node<T>** head, int n)
{
    if ((*head) == nullptr)
    {
        cout << "Lista vazia" << endl;
        return;
    }
    int gap = 1;
    while (gap < n)
    {
        gap =( 3 * gap + 1); //A sequência corresponde a 1, 4, 13, 40, 121,... 
        //Knuth (1973) mostrou experimentalmente que esta sequencia é difícil de ser batida por mais de 20% em eficiência.
    }
    

    while (gap > 0) 
    {
        for (int i = gap; i < n; i++)
        {
            Node<T>* current = *head;
            for (int j = 0; j < i; j++)
            {
                if (current == nullptr)
                    break;
                current = current->ptrNext;
            }
            if (current == nullptr)
                break;

            T temp = current->data;
            Node<T>* inner = current->ptrPrev;
            while (inner != nullptr && inner->data > temp)
            {
                LinkedList::swapValue(inner->ptrNext, inner);
                inner = inner->ptrPrev;
            }
            if (inner != nullptr)
                inner->ptrNext->data = temp;
        }
        gap = gap / 3;
    }    
}

template<typename T>
void ShellSort::medetempoShellSort(T iSize)
{
    int iCount = 0;
    while (iCount < iSize)
    {
        cout << "Teste " << iCount << endl;
        Node<T>* node1 = nullptr;
        LinkedList::randomList(&node1, 10000);
        Node<T>* node2 = LinkedList::duplicateList(node1);

        auto timeStart = high_resolution_clock::now();
        ShellSort::shellSort(&node1,10000);
        auto timeStop = high_resolution_clock::now();

        auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "Tempo de compila��o n�o otimizada = " << timeDuration.count() << endl;

        timeStart = high_resolution_clock::now();
        ShellSort::optimizedshellSort(&node2,10000);
        timeStop = high_resolution_clock::now();

        timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "Tempo de compila��o otimizada = " << timeDuration.count() << endl;
        cout << endl;
        iCount++;
    }
}

template void ShellSort::shellSort(Node<int>**, int);
template void ShellSort::shellSort(Node<float>**, int);
template void ShellSort::shellSort(Node<char>**, int);
template void ShellSort::shellSort(Node<double>**, int);

template void ShellSort::optimizedshellSort(Node<int>**, int);
template void ShellSort::optimizedshellSort(Node<float>**, int);
template void ShellSort::optimizedshellSort(Node<char>**, int);
template void ShellSort::optimizedshellSort(Node<double>**, int);

template void ShellSort::medetempoShellSort(int);