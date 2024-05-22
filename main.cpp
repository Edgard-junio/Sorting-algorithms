#include <iostream>
#include "LinkedList/LinkedList.h"
#include "ShellSort/ShellSort.h"
#include "BubbleSort/bubbleSort.h"
#include "SelectionSort/selectionSort.h"
#include "InsertionSort/insertionSort.h"

using namespace LinkedList;
using namespace ShellSort;
using namespace SelectionSort;
using namespace BubbleSort;
using namespace InsertionSort;

int main()
{
    medetempoBubbleSort(100);
    medetempoInsertionSort(100);
    medetempoSelectionSort(100);
    medetempoShellSort(100);
}