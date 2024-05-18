#include <iostream>
#include <chrono>
#include <random>

namespace LinkedList
{
    struct Node
    {
        int iNum;
        Node* ptrNext;
        Node* ptrPrev;
    };

    Node* newNode(int);
    void addElementEnd(Node**, int);
    void showNode(Node*);
    void swapValue(Node*, Node*);
    void bubbleSort(Node*, int);
    void randomList(Node*&, int);
    void bubbleSortUnoptimized(Node*, int);
    Node* duplicateList(Node*);
    void medetempo(int);
}

LinkedList::Node* LinkedList::newNode(int iValor)
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

void LinkedList::bubbleSort(Node* lista, int iSize)
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
                swapValue(current, current->ptrNext); // Troca os valores caso não esteja ordenado
                bUnordered = true;
            }
            current = current->ptrNext; // Atualiza o ponteiro
        }
        if (bUnordered == false) break; // Se não acontecer uma troca ele para o loop
        ptrTemp = current; // Atualiza até onde o loop deve ir
        iLoop++;
    }
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

void LinkedList::bubbleSortUnoptimized(Node* lista, int iSize)
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
                swapValue(ptrTemp, ptrTemp->ptrNext); // Se necessário, efetua a troca
            }
            ptrTemp = ptrTemp->ptrNext;
        }
        iCount++;
    }
}

LinkedList::Node* LinkedList::duplicateList(Node* lista)
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

void LinkedList::medetempo(int iSize)
{
    int iCount = 0;
    while (iCount < iSize)
    {
        std::cout << "Teste " << iCount << std::endl;
        Node* node1 = nullptr;
        randomList(node1, 10000); // Função que cria nós aleatórios
        Node* node2 = duplicateList(node1);

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
    LinkedList::medetempo(100);
    return 0;
}
