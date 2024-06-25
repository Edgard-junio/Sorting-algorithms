# Sorting-algorithms

Nesse repositório, serão apresentados dois algorítimos de ordenação, bubbleSort e selectioSort, ambos aplicados em listas duplamente encadeadas:

## bubbleSort
O Bubble Sort é um algoritmo simples de ordenação que percorre repetidamente a lista, compara elementos adjacentes e os troca se estiverem na ordem errada. É um algoritmo intuitivo, mas não muito eficiente para grandes conjuntos de dados.

## selectionSort
A ideia da ordenação por seleção é procurar o menor elemento do vetor (ou maior) e movimentá-lo para a primeira (ou última) posição do vetor. Repete-se para os n elementos do vetor.


## insertionSort

O algoritmo de ordenação por inserção é um método simples e eficiente que ordena a lista um elemento por vez, o que realiza o movimento dos elementos não ordenados para a posição correta na lista ordenada.

## shellSort

Shell Sort é um algoritmo de ordenação que é uma extensão do algoritmo de inserção. Ele divide a lista original em um número menor de sublistas específico, chamado de lacuna (gap), e ordena essas sublistas por meio do algoritmo de inserção.

## Árvore Binária

Uma árvore binária é uma estrutura de dados hierárquica onde cada nó tem, no máximo, dois filhos: um à esquerda e outro à direita. Quando se insere um novo nó, ele é comparado ao nó atual: se for menor, é inserido à esquerda; se for maior, à direita. Isso mantém a árvore organizada para facilitar buscas e operações.
Duas formas comuns de percorrer uma árvore binária são a busca em profundidade (DFS) e a busca em largura (BFS).

## Como executar?

No seu terminal, rode o seguinte código: g++ main.cpp LinkedList/LinkedList.cpp ShellSort/ShellSort.cpp ShellSort/ShellSort.h LinkedList/LinkedList.h BubbleSort/bubbleSort.cpp BubbleSort/bubbleSort.h InsertionSort/insertionSort.cpp InsertionSort/insertionSort.h SelectionSort/selectionSort.cpp SelectionSort/selectionSort.h -o  teste.
