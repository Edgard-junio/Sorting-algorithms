#include <iostream>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;
using std::string;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

typedef struct Node{
    
    int iNum;
    Node* ptrNext;
    Node* ptrBefore;
}Node;

Node* newNode(int);
void addElementEnd(Node**,int);
void showNode(Node*);
void swapValue(Node*,Node*);
void bubbleSort(Node*, int);

int main()
{
    Node* node = nullptr;
    addElementEnd(&node, 999);
    addElementEnd(&node, 123);
    addElementEnd(&node, 1);
    addElementEnd(&node, 14);
    addElementEnd(&node, 9);
    addElementEnd(&node, 2);
    bubbleSort(node,6);
    showNode(node);

    
    return 0;
}
Node* newNode(int iValor)
{
    Node* ptrTemp = (Node*)malloc(sizeof(Node)); //Alocando memória
    ptrTemp->iNum = iValor; //Atualizando os parametros do Node
    ptrTemp->ptrNext = nullptr;
    ptrTemp->ptrNext = nullptr;
    return ptrTemp;
}

void addElementEnd(Node** list, int iValor)
{
    Node* ptrTemp = newNode(iValor); //cria um novo elemento
    if(*list == nullptr)
    {
        *list = ptrTemp;//Como a lista é vazia nosso novo nó será o primeiro
    }
    else
    {
        Node* ptrCurrent = *list; 
        while (ptrCurrent->ptrNext != nullptr)
        {
            ptrCurrent = ptrCurrent->ptrNext;//Levando o ponteiro pro final da lista
        }
        ptrCurrent->ptrNext = ptrTemp;
        ptrTemp->ptrBefore = ptrCurrent;//Atualizando os parâmetros
    }
}

void showNode(Node* list)
{
    if(list == nullptr)
    {
        cout<<"Lista inválida"<<endl;
    }
    else if(list->ptrBefore != nullptr)
    {
        cout<<"Estamos no meio da lista"<<endl;
    }
    else
    {
        cout<<"Elementos: ";
        Node* ptrCurrent = list; //cria um ponteiro auxiliar
        while (ptrCurrent != nullptr)
        {
            cout<<ptrCurrent->iNum<<" ";
            ptrCurrent = ptrCurrent->ptrNext;//Atualizando o nó
        }
        
    }
}

void swapValue(Node* iValue_1, Node* iValue_2)
{
    int iTemp = iValue_1->iNum;
    
    iValue_1->iNum = iValue_2->iNum;
    
    iValue_2->iNum = iTemp;
    
}

void bubbleSort(Node* lista,int iSize)
{
    bool bUnordered = false; // Como boa prática iniciaremos a variável já dizendo que ela é falsa
    
    if(lista == nullptr) return; // Se o primeiro elemento é nulo a função para
    
    bUnordered = false; // Dizemos que nosso vetor esta ordenado
    Node* ptrtemp = lista;
    int icount  = 0;//inicia um contador para diminuir a quantidade de interações
    while (ptrtemp->ptrNext != nullptr && icount < iSize)
    {
        if(ptrtemp->iNum > ptrtemp->ptrNext->iNum)
        {
            swapValue(ptrtemp,ptrtemp->ptrNext);//trocando os valores
            bUnordered = true; //Nossa lista não esta ordenada
        }
        ptrtemp = ptrtemp->ptrNext;
    }
    
    if(bUnordered == true)
    {
        bubbleSort(lista,iSize-1); /*como o vetor não esta ordenado repetiremos o método para o vetor sem o ultimo elemento, 
        ele já esta na sua posição*/
    }

}