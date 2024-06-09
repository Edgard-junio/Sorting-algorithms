#include <iostream>

using namespace std;

typedef struct Node
{
    int iPayload;
    Node* ptrLeft;
    Node* ptrRight;
} Node;

typedef struct LinkedListNode
{
    Node* ptrNode;
    LinkedListNode* ptrNext;
} LinkedListNode;

typedef struct LinkedList
{
    LinkedListNode* ptrFirst;
} LinkedList;

LinkedList* newLinkedList();
LinkedListNode* newNode(Node*);
void addElement(LinkedList*, Node*);
void removeElement(LinkedList*, int);
Node* createNode(int);
Node* insertNode(Node*, int);
void bfsTraversal(Node*);
void dfsTraversal(Node*);
int treeHeight(Node*);
Node* bfsSearch(Node*, int);
Node* dfsSearch(Node*, int);

int main()
{
    Node* root = nullptr;
    
    root = insertNode(root, 42);
    root = insertNode(root, 13);
    root = insertNode(root, 11);
    root = insertNode(root, 10);
    root = insertNode(root, 28);
    root = insertNode(root, 51);
    root = insertNode(root, 171);
    
    cout << "BFS Traversal: ";
    bfsTraversal(root);
    cout << endl;
    
    cout << "DFS Traversal: ";
    dfsTraversal(root);
    cout << endl;
    
    cout << "Tree height: " << treeHeight(root) << endl;
    
    int searchValue = 10;
    cout << "Procurando por " << searchValue << " usando BFS: " << (bfsSearch(root, searchValue) != nullptr ? "Encontrado" : "Não encontrado") << endl;
    cout << "Procurando por " << searchValue << " usando DFS: " << (dfsSearch(root, searchValue) != nullptr ? "Encontrado" : "Não encontrado") << endl;
    
    return 0;
}

Node* createNode(int iValue)
{
    Node* tmp = (Node*) malloc(sizeof(Node));
    
    if (tmp == nullptr)
    {
        cerr << "Erro em createNode: malloc" << endl;
        exit(1);
    }
    
    tmp->iPayload = iValue;
    tmp->ptrLeft = nullptr;
    tmp->ptrRight = nullptr;
    
    return tmp;
}

LinkedList* newLinkedList()
{
    LinkedList* temp = (LinkedList*) malloc(sizeof(LinkedList));
    temp->ptrFirst = nullptr; 

    return temp;
}

LinkedListNode* newNode(Node* node)
{
    LinkedListNode* temp = (LinkedListNode*) malloc(sizeof(LinkedListNode));
    temp->ptrNode = node;
    temp->ptrNext = nullptr;
    
    return temp;
}

void addElement(LinkedList* list, Node* node)
{
    LinkedListNode* temp = newNode(node);
    
    if (list->ptrFirst == nullptr)
    {
        list->ptrFirst = temp;
    } 
    else
    {
        LinkedListNode* lastNode = list->ptrFirst;
        
        while(lastNode->ptrNext != nullptr)
        {
            lastNode = lastNode->ptrNext;
        }
        
        lastNode->ptrNext = temp;
    }
}

void removeElement(LinkedList* list, int value)
{
    // Saindo de fininho - caso especial: lista de vazia ou inexistente
    if (list == nullptr || list -> ptrFirst == nullptr)
    {
        cout << "removeElement: Lista Vazia" << endl;
        return;
    }    
    
    LinkedListNode* current = list -> ptrFirst;
    LinkedListNode* previous = nullptr;
    
    // Segundo caso especial - o primeiro nó é o escolhido
    if (current -> ptrNode -> iPayload == value)
    {
        list -> ptrFirst = list -> ptrFirst -> ptrNext;
        free(current);
        return;
    }
    
    while (current != nullptr && current -> ptrNode -> iPayload != value)
    {
        previous = current;
        current = current -> ptrNext;
    }
    
    // Saímos de fininho - terceiro caso especial - elemento não encontrado
    if (current == nullptr) return;
    
    // Reparar a lista para remoção
    previous -> ptrNext = current -> ptrNext;
    
    free(current);
}

Node* insertNode(Node* startingNode, int iData)
{
    if (startingNode == nullptr)
    {
        return createNode(iData);
    }
    
    if (iData < startingNode->iPayload)
    {
        startingNode->ptrLeft = insertNode(startingNode->ptrLeft, iData);
    }
    else
    {
        startingNode->ptrRight = insertNode(startingNode->ptrRight, iData);
    }
    
    return startingNode;
}

void bfsTraversal(Node* startingNode)
{
    if (startingNode == nullptr) return;
    
    LinkedList* queueList = newLinkedList();
    addElement(queueList, startingNode);
    
    while (queueList->ptrFirst != nullptr)
    {
        Node* currentNode = queueList->ptrFirst->ptrNode;
        cout << currentNode->iPayload << " ";
        
        if (currentNode->ptrLeft != nullptr)
        {
            addElement(queueList, currentNode->ptrLeft);
        }
        
        if (currentNode->ptrRight != nullptr)
        {
            addElement(queueList, currentNode->ptrRight);
        }
        
        // Remova este nó da lista apenas após visitá-lo e adicionar seus filhos
        removeElement(queueList, currentNode->iPayload);
    }
}

void dfsTraversal(Node* startingNode)
{
    if (startingNode == nullptr) return;
    
    cout << startingNode->iPayload << " ";
    
    dfsTraversal(startingNode->ptrLeft);
    dfsTraversal(startingNode->ptrRight);
}

int treeHeight(Node* startingNode)
{
    if (startingNode == nullptr) return 0;
    else
    {
        int iLeftHeight = treeHeight(startingNode -> ptrLeft);
        int iRightHeight = treeHeight(startingNode -> ptrRight);
        
        return max(iLeftHeight, iRightHeight) + 1;
    }
}

Node* bfsSearch(Node* startingNode, int value)
{
    if (startingNode == nullptr)
    {
        return nullptr;
    }
    
    LinkedList* queueList = newLinkedList();
    addElement(queueList, startingNode);
    
    while (queueList->ptrFirst != nullptr)
    {
        Node* currentNode = queueList->ptrFirst->ptrNode;
        
        if (currentNode->iPayload == value)
        {
            return currentNode;
        }
        
        if (currentNode->ptrLeft != nullptr)
        {
            addElement(queueList, currentNode->ptrLeft);
        }
        
        if (currentNode->ptrRight != nullptr)
        {
            addElement(queueList, currentNode->ptrRight);
        }
        
        // Remova este nó da lista apenas após verificá-lo e adicionar seus filhos
        removeElement(queueList, currentNode->iPayload);
    }
    
    return nullptr;
}

Node* dfsSearch(Node* startingNode, int value)
{
    if (startingNode == nullptr || startingNode -> iPayload == value) return startingNode;
    
    Node* leftResult = dfsSearch(startingNode -> ptrLeft, value);
    if (leftResult != nullptr) return leftResult;
    
    return dfsSearch(startingNode->ptrRight, value);
}
