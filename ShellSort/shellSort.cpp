#include "ShellSort.h"
#include "../LinkedList/LinkedList.h"
#include <iostream>
#include <chrono>

using std::cout;
using std::endl;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

// Função para explicar o algoritmo Shell Sort
void ShellSort::aboutShellSort()
{
    cout << endl;

    cout << "O algoritmo Shell Sort é uma extensão do método de ordenação por inserção. Ao invés de comparar elementos adjacentes, ele opera dividindo a lista original em sublistas menores, conhecidas como lacunas (ou gaps), e então ordenando essas sublistas usando o algoritmo de inserção." << endl;

    cout << endl;
}

// Método do Shell Sort não otimizado
template<typename T>
void ShellSort::shellSort(Node<T>** head, int n)
{
    if ((*head) == nullptr)
    {
        cout << "Lista vazia" << endl;
        return;
    }

    // Loop para definir o tamanho do gap e executar o insertion sort para cada gap
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
            // Aplica o insertion sort dentro do gap
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

// Método do Shell Sort otimizado com sequência de gaps de Knuth
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
    
    // Executa o Shell Sort com a sequência de gaps de Knuth
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
            // Aplica o insertion sort dentro do gap
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

// Função para medir o tempo dos dois métodos de Shell Sort
template<typename T>
void ShellSort::medetempoShellSort(T iSize)
{
    int iCount = 0;
    while (iCount < iSize)
    {
        cout << "Teste " << iCount << endl;
        Node<T>* node1 = nullptr;
        LinkedList::randomList(&node1, 10000); // Gera uma lista aleatória
        Node<T>* node2 = LinkedList::duplicateList(node1); // Duplica a lista

        // Mede o tempo da versão não otimizada
        auto timeStart = high_resolution_clock::now();
        ShellSort::shellSort(&node1,10000);
        auto timeStop = high_resolution_clock::now();

        auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "Tempo de compila��o n�o otimizada = " << timeDuration.count() << endl;

        // Mede o tempo da versão otimizada
        timeStart = high_resolution_clock::now();
        ShellSort::optimizedshellSort(&node2,10000);
        timeStop = high_resolution_clock::now();

        timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "Tempo de compila��o otimizada = " << timeDuration.count() << endl;
        cout << endl;
        iCount++;
    }
}

// Instâncias explícitas para int, float, char e double
template void ShellSort::shellSort(Node<int>**, int);
template void ShellSort::shellSort(Node<float>**, int);
template void ShellSort::shellSort(Node<char>**, int);
template void ShellSort::shellSort(Node<double>**, int);

template void ShellSort::optimizedshellSort(Node<int>**, int);
template void ShellSort::optimizedshellSort(Node<float>**, int);
template void ShellSort::optimizedshellSort(Node<char>**, int);
template void ShellSort::optimizedshellSort(Node<double>**, int);

// Instância explícita para a função de medição do tempo com int
template void ShellSort::medetempoShellSort(int);
