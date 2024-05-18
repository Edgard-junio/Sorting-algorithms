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
    void randomList(Node*&, int);
    void insertionSort(Node*);
    void optimizedInsertionSort(Node*);
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

void LinkedList::insertionSort(Node* lista)
{
    Node* ptrTemp = lista; // Ponteiro para o início da lista
    while (ptrTemp != nullptr) // Enquanto não chegarmos ao final da lista
    {
        Node* current = ptrTemp; // Criando um ponteiro para o elemento atual
        while (current->ptrPrev != nullptr) // Percorrendo a lista de trás para frente
        {
            if(current->ptrPrev->iNum > current->iNum) // Se o elemento anterior for maior que o atual
            {
                swapValue(current->ptrPrev, current); // Troca os valores dos elementos
            }
            current = current->ptrPrev; // Movendo para o próximo elemento anterior
        }
        ptrTemp = ptrTemp->ptrNext; // Movendo para o próximo elemento na lista
    }
}

void LinkedList::optimizedInsertionSort(Node* head)
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

LinkedList::Node* LinkedList::duplicateList(Node* lista)
{
    // Esta função recebe uma lista qualquer e retorna uma outra lista exatamente igual

    Node* ptrTemp = lista;
    Node* newList = nullptr;
    while(ptrTemp != nullptr)
    {
        addElementEnd(&newList,ptrTemp->iNum);
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
        insertionSort(node1); // Executa o insertionsort nao otimizado
        auto timeStop = std::chrono::high_resolution_clock::now(); // Medindo tempo de execução

        auto timeDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(timeStop - timeStart);
        std::cout << "Tempo de compilação não otimizada   = " << timeDuration.count() << std::endl;
        
        timeStart = std::chrono::high_resolution_clock::now();
        optimizedInsertionSort(node2); // Executa o insertionsort otimizado
        timeStop = std::chrono::high_resolution_clock::now(); // Medindo tempo de execução

        timeDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(timeStop - timeStart);
        std::cout << "Tempo de compilação otimizada   = " << timeDuration.count() << std::endl;
        std::cout << std::endl;
        iCount++;
    }
}

int main()
{
    LinkedList::medetempo(100);
    return 0;
}
