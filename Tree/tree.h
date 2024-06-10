#pragma once
#include "../LinkedList/LinkedList.h"
template <typename T>
struct treeNode
{
    T iPayload;
    treeNode* ptrLeft;
    treeNode* ptrRight;
};

namespace tree
{
    template<typename T>
    treeNode<T>* createtreeNode(T);

    template<typename T>
    treeNode<T>* inserttreeNode(treeNode<T>*, T);

    template<typename T>
    Node<T>* lesserLeaf(Node<T>* ptrStartingNode);

    template <typename T>
    Node<T>* deleteNode(Node<T>* ptrStartingNode, int iData);

    template<typename T>
    void dfsTraversal(treeNode<T>*);

    template <typename T>
    void bfsTraversal(treeNode<T>* startingNode);

    template<typename T>
    treeNode<T>* searchBFS(treeNode<T>* startingNode, T value);

    template<typename T>
    int treeHeight(treeNode<T>*);

    template<typename T>
    treeNode<T>* dfsSearch(treeNode<T>*, T);

    void randomtree(treeNode<int>*& list, int amount);

    void CompareTimeListTree(int isize);

    void CompareTimeBfsDfs(int iSize);

    void teste();
}