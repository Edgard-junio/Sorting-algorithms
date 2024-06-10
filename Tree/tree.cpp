#include <iostream>
#include "../LinkedList/LinkedList.h"
#include "tree.h"
#include <chrono>
#include <random>

using namespace std;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

template<typename T>
treeNode<T>* tree::createtreeNode(T iValue)
{
    treeNode<T>* tmp = (treeNode<T>*) malloc(sizeof(treeNode<T>));
    
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

template<typename T>
Node<T>* tree::lesserLeaf(Node<T>* ptrStartingNode)
{
    Node<T>* ptrCurrent = ptrStartingNode;
    
    while (ptrCurrent != nullptr & ptrCurrent -> ptrLeft != nullptr) ptrCurrent = ptrCurrent -> ptrLeft;
    
    return ptrCurrent;
}

template<typename T>
void tree::dfsTraversal(treeNode<T>* startingtreeNode)
{
    if (startingtreeNode == nullptr) return;
    
    cout << startingtreeNode->iPayload << " ";
    
    dfsTraversal(startingtreeNode->ptrLeft);
    dfsTraversal(startingtreeNode->ptrRight);
}

template <typename T>
Node<T>* tree::deleteNode(Node<T>* ptrStartingNode, int iData)
{
    if (ptrStartingNode == nullptr) return nullptr;
    
    if (iData < ptrStartingNode -> iPayload) ptrStartingNode -> ptrLeft = deleteNode(ptrStartingNode -> ptrLeft, iData);
    else if (iData > ptrStartingNode -> iPayload) ptrStartingNode -> ptrRight = deleteNode(ptrStartingNode -> ptrRight, iData);
    else
    {
        Node<T>* ptrTemp = nullptr;
        
        if (ptrStartingNode -> ptrLeft == nullptr)
        {
            ptrTemp = ptrStartingNode -> ptrRight;
            free(ptrStartingNode);
            
            return ptrTemp;
        }
        else if (ptrStartingNode -> ptrRight == nullptr)
        {
            ptrTemp = ptrStartingNode -> ptrLeft;
            free(ptrStartingNode);
            
            return ptrTemp;
        }
        
        ptrTemp = lesserLeaf(ptrStartingNode -> ptrRight);
        
        ptrStartingNode -> iPayload = ptrTemp -> iPayload;
        
        ptrStartingNode -> ptrRight = deleteNode(ptrStartingNode -> ptrRight, ptrTemp -> iPayload);
        
    }
    
    return ptrStartingNode;
}

template <typename T>
void tree::bfsTraversal(treeNode<T>* startingNode)
{
    if (startingNode == nullptr) return;

    Node<treeNode<T>*>* queueFront = nullptr;
    Node<treeNode<T>*>* queueRear = nullptr;

    LinkedList::addElementEnd(&queueRear, startingNode);
    queueFront = queueRear;

    while (queueFront != nullptr)
    {
        treeNode<T>* currentNode = queueFront->data;

        std::cout << currentNode -> iPayload << " ";

        if (currentNode->ptrLeft != nullptr)
        {
            LinkedList::addElementEnd(&queueRear, currentNode -> ptrLeft);
            if (queueFront == nullptr)
            {
                queueFront = queueRear;
            }
        }

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

template<typename T>
treeNode<T>* tree::searchBFS(treeNode<T>* startingNode, T value)
{
    if (startingNode == nullptr) return nullptr;
    
    Node<treeNode<T>*>* queueFront = nullptr;
    Node<treeNode<T>*>* queueRear = nullptr;

    LinkedList::addElementEnd(&queueRear, startingNode);
    queueFront = queueRear;

    while (queueFront != nullptr)
    {
        treeNode<T>* currentNode = queueFront -> data;

        if (currentNode -> iPayload == value)
        {
            return currentNode;
        }

        if (currentNode -> ptrLeft != nullptr)
        {
            LinkedList::addElementEnd(&queueRear, currentNode -> ptrLeft);
            if (queueFront == nullptr)
            {
                queueFront = queueRear;
            }
        }

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

template<typename T>
int tree::treeHeight(treeNode<T>* startingtreeNode)
{
    if (startingtreeNode == nullptr) return 0;
    else
    {
        int iLeftHeight = treeHeight(startingtreeNode -> ptrLeft);
        int iRightHeight = treeHeight(startingtreeNode -> ptrRight);
        
        return max(iLeftHeight, iRightHeight) + 1;
    }
}

template<typename T>
treeNode<T>* tree::dfsSearch(treeNode<T>* startingtreeNode, T value)
{
    if (startingtreeNode == nullptr || startingtreeNode -> iPayload == value) return startingtreeNode;
    
    treeNode<T>* leftResult = dfsSearch(startingtreeNode -> ptrLeft, value);
    if (leftResult != nullptr) return leftResult;
    
    return dfsSearch(startingtreeNode -> ptrRight, value);
}

void tree::randomtree(treeNode<int>*& root, int amount)
{
    if (amount == 0) return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);

    for (int count = 0; count < amount; count++)
    {
        root = tree::inserttreeNode(root, dis(gen));
    }
}

void tree::CompareTimeListTree(int iSize) 
{
    int iCount = 0;
    while (iCount < iSize) 
    {
        cout << "Teste " << iCount << endl;

        auto timeStart = high_resolution_clock::now();
        treeNode<int>* node1 = nullptr; 
        tree::randomtree(node1, 100000);
        auto timeStop = high_resolution_clock::now();

        auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "Tempo de criação de uma árvore = " << timeDuration.count() << " nanosegundos" << endl;

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

        auto timeStart = high_resolution_clock::now();
        tree::searchBFS(root, valueToSearch);
        auto timeStop = high_resolution_clock::now();

        auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "Tempo de busca BFS = " << timeDuration.count() << " nanosegundos" << endl;

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