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
void randomList(Node*&, int);
void insertSort(Node*);

int main()
{
    Node* node = nullptr;
    randomList(node,10); //função que cria nós aleatorios
    
    auto timeStart = high_resolution_clock::now();
    insertSort(node);
    auto timeStop = high_resolution_clock::now();//medindo tempo de execução
    showNode(node);

    auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout<<"tempo de compilaçao = "<<timeDuration.count()<<endl;
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

void randomList(Node* &lista, int iAmount) {
    if(iAmount == 0) return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);

    for(int icount = 0; icount < iAmount; icount++) {
        addElementEnd(&lista, dis(gen));//adicionando um elemento aleatorio
    }
}

void insertSort(Node* lista)
{
    Node* ptrTemp = lista;//ponteiro pro inicio da lista
    while (ptrTemp->ptrNext != nullptr)
    {
        Node* current = ptrTemp;//criando os parametros de comparação
        Node* ptrAux = ptrTemp->ptrNext;
        while (current->ptrPrev != lista)
        {
            if(current->iNum > ptrAux->iNum)
            {
                swapValue(current, ptrAux); //fazendo a troca quando um elemento de maior valor vem 
                // antes de um de maior valor
            }
            current = current->ptrPrev;//Nesse algoritimo valtamos o current ate o começo
        }
        ptrTemp = ptrTemp->ptrNext;//atualizando ptrTemp
    }
    
}