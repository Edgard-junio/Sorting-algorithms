#pragma once
#include "../LinkedList/LinkedList.h"

namespace ShellSort
{
    template<typename T>
    void shellSort(Node<T>** head, int n);

    template<typename T>
    void optimizedshellSort(Node<T>** head, int n);

    template<typename T>
    void medetempoShellSort(T iSize);
}

