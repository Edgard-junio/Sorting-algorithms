#include <iostream>
#include "../LinkedList/LinkedList.h"
#include "tree.h"
#include <chrono>
#include <random>

using namespace std;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

// Função para criar um novo nó da árvore
template<typename T>
treeNode<T>* tree::createtreeNode(T iValue)
{
    treeNode<T>* tmp = (treeNode<T>*) malloc(sizeof(treeNode<T>));
    
    // Verifica se a alocação de memória foi bem-sucedida
    if (tmp == nullptr) 
    {
        cerr << "Erro em createtreeNode: malloc" << endl;
        exit(1);
    }
    
    tmp->iPayload = iValue;
    tmp->ptrLeft = nullptr;
    tmp->ptrRight = nullptr;
    
    return tmp;
}

// Função para inserir um novo nó na árvore
template<typename T>
treeNode<T>* tree::inserttreeNode(treeNode<T>* startingtreeNode, T iData)
{
    if (startingtreeNode == nullptr)
    {
        return createtreeNode(iData);
    }
    
    if (iData < startingtreeNode->iPayload)
    {
        startingtreeNode->ptrLeft = inserttreeNode(startingtreeNode->ptrLeft, iData);
    }
    else
    {
        startingtreeNode->ptrRight = inserttreeNode(startingtreeNode->ptrRight, iData);
    }
    
    return startingtreeNode;
}

// Função para encontrar o nó com menor valor na subárvore
template<typename T>
Node<T>* tree::lesserLeaf(Node<T>* ptrStartingNode)
{
    Node<T>* ptrCurrent = ptrStartingNode;
    
    while (ptrCurrent != nullptr & ptrCurrent -> ptrLeft != nullptr) ptrCurrent = ptrCurrent -> ptrLeft;
    
    return ptrCurrent;
}

// Função para fazer a travessia DFS (Depth-First Search)
template<typename T>
void tree::dfsTraversal(treeNode<T>* startingtreeNode)
{
    if (startingtreeNode == nullptr) return;
    
    cout << startingtreeNode->iPayload << " ";
    
    dfsTraversal(startingtreeNode->ptrLeft);
    dfsTraversal(startingtreeNode->ptrRight);
}

// Função para deletar um nó da árvore
template <typename T>
Node<T>* tree::deleteNode(Node<T>* ptrStartingNode, int iData)
{
    if (ptrStartingNode == nullptr) return nullptr;
    
    if (iData < ptrStartingNode -> iPayload) ptrStartingNode -> ptrLeft = deleteNode(ptrStartingNode -> ptrLeft, iData);
    else if (iData > ptrStartingNode -> iPayload) ptrStartingNode -> ptrRight = deleteNode(ptrStartingNode -> ptrRight, iData);
    else
    {
        Node<T>* ptrTemp = nullptr;
        
        // Caso o nó não tenha filho à esquerda
        if (ptrStartingNode -> ptrLeft == nullptr)
        {
            ptrTemp = ptrStartingNode -> ptrRight;
            free(ptrStartingNode);
            
            return ptrTemp;
        }
        // Caso o nó não tenha filho à direita
        else if (ptrStartingNode -> ptrRight == nullptr)
        {
            ptrTemp = ptrStartingNode -> ptrLeft;
            free(ptrStartingNode);
            
            return ptrTemp;
        }
        
        // Caso o nó tenha ambos os filhos
        ptrTemp = lesserLeaf(ptrStartingNode -> ptrRight);
        
        ptrStartingNode -> iPayload = ptrTemp -> iPayload;
        
        ptrStartingNode -> ptrRight = deleteNode(ptrStartingNode -> ptrRight, ptrTemp -> iPayload);
        
    }
    
    return ptrStartingNode;
}

// Função para fazer a travessia BFS (Breadth-First Search)
template <typename T>
void tree::bfsTraversal(treeNode<T>* startingNode)
{
    if (startingNode == nullptr) return;

    // Inicializa uma fila para armazenar os nós da árvore a serem visitados
    Node<treeNode<T>*>* queueFront = nullptr;
    Node<treeNode<T>*>* queueRear = nullptr;

    LinkedList::addElementEnd(&queueRear, startingNode);
    queueFront = queueRear;

    // Processa cada nó na fila até que todos os nós tenham sido visitados
    while (queueFront != nullptr)
    {
        treeNode<T>* currentNode = queueFront->data;

        std::cout << currentNode -> iPayload << " "; // Imprime o valor do nó atual

        // Adiciona os filhos à esquerda do nó atual à fila (se existirem)
        if (currentNode->ptrLeft != nullptr)
        {
            LinkedList::addElementEnd(&queueRear, currentNode -> ptrLeft);
            if (queueFront == nullptr)
            {
                queueFront = queueRear;
            }
        }

        // Adiciona os filhos à direita do nó atual à fila (se existirem)
        if (currentNode -> ptrRight != nullptr)
        {
            LinkedList::addElementEnd(&queueRear, currentNode -> ptrRight);
            if (queueFront == nullptr)
            {
                queueFront = queueRear;
            }
        }
        queueFront = queueFront -> ptrNext;
    }
}

// Função para buscar um valor específico na árvore utilizando BFS (Breadth-First Search)
template<typename T>
treeNode<T>* tree::searchBFS(treeNode<T>* startingNode, T value)
{
    if (startingNode == nullptr) return nullptr;
    
    // Inicializa uma fila para armazenar os nós da árvore a serem visitados
    Node<treeNode<T>*>* queueFront = nullptr;
    Node<treeNode<T>*>* queueRear = nullptr;

    LinkedList::addElementEnd(&queueRear, startingNode);
    queueFront = queueRear;

    // Processa cada nó na fila até que todos os nós tenham sido visitados
    while (queueFront != nullptr)
    {
        treeNode<T>* currentNode = queueFront -> data;

        // Verifica se o valor do nó atual corresponde ao valor procurado
        if (currentNode -> iPayload == value)
        {
            return currentNode;
        }

        // Adiciona os filhos à esquerda do nó atual à fila (se existirem)
        if (currentNode -> ptrLeft != nullptr)
        {
            LinkedList::addElementEnd(&queueRear, currentNode -> ptrLeft);
            if (queueFront == nullptr)
            {
                queueFront = queueRear;
            }
        }

        // Adiciona os filhos à direita do nó atual à fila (se existirem)
        if (currentNode -> ptrRight != nullptr)
        {
            LinkedList::addElementEnd(&queueRear, currentNode -> ptrRight);
            if (queueFront == nullptr)
            {
                queueFront = queueRear;
            }
        }
        queueFront = queueFront -> ptrNext;
    }

    return nullptr;
}

// Função para calcular a altura da árvore
template<typename T>
int tree::treeHeight(treeNode<T>* startingtreeNode)
{
    if (startingtreeNode == nullptr) return 0;
    else
    {
        int iLeftHeight = treeHeight(startingtreeNode -> ptrLeft); // Calcula a altura da subárvore à esquerda de forma recursiva
        int iRightHeight = treeHeight(startingtreeNode -> ptrRight); // Calcula a altura da subárvore à direita de forma recursiva
        
         // Retorna a altura máxima entre as subárvores mais a raiz atual
        return max(iLeftHeight, iRightHeight) + 1;
    }
}

// Função para buscar um valor específico na árvore utilizando DFS (Depth-First Search)
template<typename T>
treeNode<T>* tree::dfsSearch(treeNode<T>* startingtreeNode, T value)
{
    if (startingtreeNode == nullptr || startingtreeNode -> iPayload == value) return startingtreeNode;

    // Realiza a busca recursivamente na subárvore à esquerda
    treeNode<T>* leftResult = dfsSearch(startingtreeNode -> ptrLeft, value); 
    if (leftResult != nullptr) return leftResult;
    
    // Se não encontrado na subárvore à esquerda, realiza a busca na subárvore à direita
    return dfsSearch(startingtreeNode -> ptrRight, value);
}

// Função para criar uma árvore binária com valores inteiros aleatórios
void tree::randomtree(treeNode<int>*& root, int amount)
{
    if (amount == 0) return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000); // Distribuição uniforme de números inteiros no intervalo [1, 100]

    for (int count = 0; count < amount; count++)
    {
        root = tree::inserttreeNode(root, dis(gen));
    }
}

// Função para comparar o tempo de criação de uma árvore e de uma lista
void tree::CompareTimeListTree(int iSize) 
{
    int iCount = 0;
    while (iCount < iSize) 
    {
        cout << "Teste " << iCount << endl;

        // Tempo de criação da árvore
        auto timeStart = high_resolution_clock::now();
        treeNode<int>* node1 = nullptr; 
        tree::randomtree(node1, 100000);
        auto timeStop = high_resolution_clock::now();

        auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "Tempo de criação de uma árvore = " << timeDuration.count() << " nanosegundos" << endl;

        // Tempo de criação da lista
        timeStart = high_resolution_clock::now();
        Node<int>* node2 = nullptr;
        LinkedList::randomList(&node2, 100000);
        timeStop = high_resolution_clock::now();

        timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "Tempo de criação de uma lista = " << timeDuration.count() << " nanosegundos" << endl;
        cout << endl;
        iCount++;
    }
}

// Função para comparar o tempo de busca BFS e DFS
void tree::CompareTimeBfsDfs(int iSize)
{
    if (iSize == 0)
    {
        cout << "Erro" << endl;
        return;
    }

    int valueToSearch = 854;  // Certifique-se de que esse valor existe na árvore

    for (int iCount = 0; iCount < iSize; iCount++)
    {
        cout << "Teste " << iCount << endl;
        treeNode<int>* root = nullptr; 
        tree::randomtree(root, 100000);

        // Verifique se o valor realmente está na árvore
        root = tree::inserttreeNode(root, valueToSearch);

        // Tempo de busca BFS
        auto timeStart = high_resolution_clock::now();
        tree::searchBFS(root, valueToSearch);
        auto timeStop = high_resolution_clock::now();

        auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "Tempo de busca BFS = " << timeDuration.count() << " nanosegundos" << endl;

        // Tempo de busca DFS
        timeStart = high_resolution_clock::now();
        tree::dfsSearch(root, valueToSearch);
        timeStop = high_resolution_clock::now();

        timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "Tempo de busca DFS = " << timeDuration.count() << " nanosegundos" << endl;

        cout<<endl;
    }
}

// Instanciações explícitas para int
template treeNode<int>* tree::createtreeNode(int);
template treeNode<int>* tree::inserttreeNode(treeNode<int>*, int);
template void tree::dfsTraversal(treeNode<int>*);
template int tree::treeHeight(treeNode<int>*);
template treeNode<int>* tree::dfsSearch(treeNode<int>*, int);
template void tree::bfsTraversal(treeNode<int>* startingNode);
template treeNode<int>* tree::searchBFS(treeNode<int>* startingNode, int value);

// Instanciações explícitas para double
template treeNode<double>* tree::createtreeNode(double);
template treeNode<double>* tree::inserttreeNode(treeNode<double>*, double);
template void tree::dfsTraversal(treeNode<double>*);
template int tree::treeHeight(treeNode<double>*);
template treeNode<double>* tree::dfsSearch(treeNode<double>*, double);
template void tree::bfsTraversal(treeNode<double>* startingNode);
template treeNode<double>* tree::searchBFS(treeNode<double>* startingNode, double value);


// Instanciações explícitas para float
template treeNode<float>* tree::createtreeNode(float);
template treeNode<float>* tree::inserttreeNode(treeNode<float>*, float);
template void tree::dfsTraversal(treeNode<float>*);
template int tree::treeHeight(treeNode<float>*);
template treeNode<float>* tree::dfsSearch(treeNode<float>*, float);
template void tree::bfsTraversal(treeNode<float>* startingNode);
template treeNode<float>* tree::searchBFS(treeNode<float>* startingNode, float value);
