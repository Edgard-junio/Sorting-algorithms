#include <iostream>
#include <chrono>
#include <random>

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
    Node* ptrPrev;
}Node;

Node* newNode(int);
void addElementEnd(Node**,int);
void showNode(Node*);
void swapValue(Node*,Node*);
void bubbleSort(Node*, int);
void randomList(Node*&, int);
void bubbleSortUnoptimized(Node*);
Node* duplicateList(Node*);
void medetempo(int);

int main()
{
    medetempo(100);
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
        ptrTemp->ptrPrev = ptrCurrent;//Atualizando os parâmetros
    }
}

void showNode(Node* list)
{
    if(list == nullptr)
    {
        cout<<"Lista inválida"<<endl;
    }
    else if(list->ptrPrev != nullptr)
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
        cout<<endl;
        
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
    
    Node* ptrtemp = lista;
    int icount  = 0;//inicia um contador para diminuir a quantidade de interações
    while (icount < iSize - 1)
    {
        bUnordered = false;

        while (ptrtemp->ptrNext != nullptr && icount < iSize)
        {
            if(ptrtemp->iNum > ptrtemp->ptrNext->iNum)
            {
                swapValue(ptrtemp,ptrtemp->ptrNext);//trocando os valores
                bUnordered = true; //Nossa lista não esta ordenada
            }
            ptrtemp = ptrtemp->ptrNext;
        }
        if (bUnordered == false) break;
        icount++;
    }
    

    
    if(bUnordered == true)
    {
        bubbleSort(lista,iSize-1); /*como o vetor não esta ordenado repetiremos o método para o vetor sem o ultimo elemento, 
        ele já esta na sua posição*/
    }
}

void randomList(Node* &lista, int iAmount) {
    if(iAmount == 0) return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);

    for(int icount = 0; icount < iAmount; icount++) {
        addElementEnd(&lista, dis(gen));//adicionando um elemento aleatorio
    }
}
void bubbleSortUnoptimized(Node* lista)
{
    //Bubblesort não otimizado
    Node* ptrtemp = lista;
    while (ptrtemp != nullptr)
    {
        Node* minNode = ptrtemp;
        Node* current = ptrtemp->ptrNext;

        while (current != nullptr)
        {
            if(minNode->iNum > current->iNum)
            {
                swapValue(minNode,current);//trocando os valores
            }
            current = current->ptrNext;//atualiza pro proximo nó
        }
        ptrtemp = ptrtemp->ptrNext;//atualiza pro proximo nó
    }
}

Node* duplicateList(Node* lista)
{
    //esta função recebe uma lista qualquer e retorna uma outra ista exatamente igual

    Node* ptrTemp = lista;
    Node* newList = nullptr;
    while(ptrTemp != nullptr)
    {
        addElementEnd(&newList,ptrTemp->iNum);
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
        bubbleSortUnoptimized(node1);
        auto timeStop = high_resolution_clock::now();//medindo tempo de execução

        auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout<< "tempo de compilação não otimizada   = " <<timeDuration.count()<<endl;
        timeStart = high_resolution_clock::now();
        bubbleSort(node2, 10000); // Executa o bubbleSort
        timeStop = high_resolution_clock::now(); // medindo tempo de execução

        timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        cout << "tempo de compilação otimizada   = " << timeDuration.count() << endl;
        cout<<endl;
        iCount++;
    }
    
}