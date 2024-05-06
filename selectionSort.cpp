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

int main()
{
    Node* list = nullptr;
    int numElements = 10000;  // Número de elementos a serem gerados aleatoriamente

    randomList(list, numElements);  // Gerando a lista com elementos aleatórios

    cout << "Lista original gerada aleatoriamente: ";
    displayList(list);
    
    // Isso somente pode ser feito quando o tipo for declarado de forma indireta;
    //time_point<std::chrono::high_resolution_clock>
    auto timeStart = high_resolution_clock::now();
    selectionSort(list);
    auto timeStop = high_resolution_clock::now();
    
    cout << "Lista ordenada: ";
    displayList(list);
    
    auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << "Tempo utilizado: " << timeDuration.count() << " nanosegundos." << endl;
    cout << "=========================================" << endl;
    
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
    
    cout << "Payload ";
    
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
