#include <iostream>
#include <chrono>
#include <random>

using std::cin;
using std::cout;
using std::endl;
using std::string;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

typedef struct Node
{
    int iPayload;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

Node* createNode(int);
void addElement(Node**, int);
void displayList(Node*);
void randomList(Node*&, int);
void swapValue(Node*,Node*);
void selectionSort(Node*);
void optimizedSelectionSort(Node*);
Node* duplicateList(Node*);
void medetempo(int);

int main()
{
    medetempo(100);      
    return 0;
}

Node* createNode(int iPayload)
{
    Node* temp = (Node*) malloc(sizeof(Node));
    temp -> iPayload = iPayload;
    temp -> ptrNext = nullptr;
    temp -> ptrPrev = nullptr;
    
    return temp;
}


void addElement(Node** head, int iPayload)
{
    Node* newNode = createNode(iPayload);
    // newNode -> ptrNext = nullptr;
    
    if (*head == nullptr)
    {
        // newNode -> ptrPrev = nullptr;
        (*head) = newNode;
        return;
    }
    
    Node* temp = (*head);
    
    // Percorremos a lista até seu fim (ptrNext do último nó é NULL)
    while (temp -> ptrNext != nullptr) temp = temp -> ptrNext;
    
    newNode -> ptrPrev = temp; // newNode aponta para o fim da lista
    temp -> ptrNext = newNode; // Antigo último elemento aponta para o novo nó
}

void displayList(Node* node)
{
    if (node == nullptr)
    {
        cout << "Lista vazia: Não é possível realizar displayList" << endl;
        return;
    }
    
    if (node -> ptrPrev != nullptr)
    {
        cout << "Meio ou Fim da lista: Não é possível realizar displayList" << endl;
        return;
    }
    
    Node* temp = node;
    
    // Percorremos a lista até seu fim (ptrNext do último nó é NULL)
    while (temp != nullptr)
    {
        cout << temp -> iPayload << " ";
        temp = temp -> ptrNext;
    }
    
    cout << endl;
}

void randomList(Node* &lista, int iAmount) 
{
    if(iAmount == 0) return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);

    for(int icount = 0; icount < iAmount; icount++)
    {
        addElement(&lista, dis(gen)); // Adicionando um elemento aleatório
    }
}

void swapNodes(Node* node1, Node* node2) {
    int temp = node1 -> iPayload;
    node1 -> iPayload = node2 -> iPayload;
    node2 -> iPayload = temp;
}

void selectionSort(Node* head)
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
            if (innerLoop -> iPayload < minNode -> iPayload)
            {
                minNode = innerLoop;
            }
        }
        
        // Trocando os valores
        swapNodes(outerLoop, minNode);
    }
}

void optimizedSelectionSort(Node* head)
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
            if (nextNode -> iPayload < minNode -> iPayload)
            {
                minNode = nextNode;
            }
            nextNode = nextNode->ptrNext;
        }

        // Se necessário, faça a troca entre "current" e "minNode"
        if (minNode != current)
		{
            swapNodes(current, minNode);
        }

        current = current -> ptrNext;
    }
}


Node* duplicateList(Node* lista)
{
    //esta função recebe uma lista qualquer e retorna uma outra ista exatamente igual

    Node* ptrTemp = lista;
    Node* newList = nullptr;
    while(ptrTemp != nullptr)
    {
        addElement(&newList,ptrTemp->iPayload);
        ptrTemp = ptrTemp->ptrNext;
    }
    return newList;
}

void medetempo(int iSize)
{
    int iCount = 0;
    while (iCount < iSize)
    {
        cout<<"teste "<<iCount<<endl;
        Node* node1 = nullptr;
        randomList(node1, 10000); //função que cria nós aleatorios
        Node* node2 = duplicateList(node1);

        auto timeStart = high_resolution_clock::now();
        selectionSort(node1);// Executa o selection nao otimizado
        auto timeStop = high_resolution_clock::now();//medindo tempo de execução

        auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout<< "tempo de compilação não otimizada   = " <<timeDuration.count()<<endl;
        timeStart = high_resolution_clock::now();
        optimizedSelectionSort(node2); // Executa o selection otimizado
        timeStop = high_resolution_clock::now(); // medindo tempo de execução

        timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "tempo de compilação otimizada   = " << timeDuration.count() << endl;
        cout<<endl;
        iCount++;
    }
    
}
