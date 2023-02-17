/**
 * @author Iclodean Andrei-George
 * @group 30223
 *
 * Specificațiile problemei: Se cere implementarea corecta si eficienta a parcurgerii iterative si recursive al unui arbore
 * binar, respectiv hibridizare pentru quicksort.
 *
 *
 * Interpretarea personală despre complexitate (timp și spațiu), despre cazurile de testare (favorabil,
 * mediu-statistic si nefavorabil):
 * 1. Build Tree
 *      Pentru a construi arborele folosesc o functie care insereaza, pe rand cate un nod. Primul nod dat este radacina.
 *
 * 3. Parcurgere iterativa (inordine)
 *      Pentru a realiza o parcurgere in inordine folosesc o stiva, pe care am operatiile de push si pop ca functii, cea de push avand
 * parametrii stiva si un nod din arbore ce va fi introdus, iar cea de pop returnand un nod din arbore (NodeT).
 *      Apoi, parcurgand arborele pe ramura din stanga, adaug fiecare element in stiva, pana cand ajung la NULL.
 * Daca s-a ajuns la NULL si exista noduri in stiva, se va face pop acelui nod, va fi afisat, si se va continua pe stanga pana cand se 
 * ajunge din nou la NULL si se repeta actiunea pana cand stiva e goala si s-a parcurs tot arborele.
 * 
 * 4. Parcurgere iterativa vs recursiva arbore
 *      Pentru a analiza celor doua parcurgeri, am variat n de la 100 la 10000 si am generat un sir cu n elemente random. Apoi, am ales
 * un index random de la 0 la n - 1, iar elementul de la acel index din vector l-am ales ca radacina in arbore. Am inserat apoi restul
 * elementelor din sirul generat in arbore si l-am parcurs in inordine atat recursiv cat si iterativ, numarand doar afisarile.
 *      Totodata, am comparat si timpul de executie pentru cele doua metode, parcurgand acelasi arbore construit mai sus.
 *
 * 5. Hybrid QuickSort vs QuickSort
 *      Pentru compararea celor doua metode de sortare, am generat un sir de n elemente, cu n de la 100 la 10000, si am apelat pe
 * acelasi sir, pe rand, fiecare din cele doua sortari, numarand numarul de comparatii si atribuiri si realizand totalul.
 *
 * 6. Gasirea pragului optim
 *      Pentru a gasi pragul pentru care diferenta dintre cele doua metode de sortare este cea mai semnificativa, am incercat
 * mai multe variante de prag, incepand cu 30. Apoi, incercand 25 ca prag, observam ca diferenta totalului de operatii (atribuiri +
 * comparatii) efectuate dintre cele doua metode creste si deci, am ales, pe rand, pragurile 20, 18, 16, 14, 12, 10, 8 si 5.
 * Calculand captele intervalului de diferente pentru fiecare parg ales, am observat ca cele mai mari diferente au loc in jurul
 * pragurilor 16 si 14.
 *
 */

#include <iostream>
#include "Profiler.h"

Profiler p("lab8");

using namespace std;

#define MAX_SIZE 1000
#define STEP_SIZE 100
#define NR_TESTS 5 // numarul de teste pentru masurarea operatiilor
#define nr_tests 100 // numarul de teste pentru masurare timpului
#define PRAG 16

// PARCURGERE ITERATIVA VS RECURSIVA ARBORE

typedef struct NodeT
{
    int key;
    struct NodeT* left;
    struct NodeT* right;
}NodeT;

typedef struct NodeS
{
    NodeT* node;
    struct NodeS* next;

}NodeS;

NodeT* create(int key)
{
    NodeT* node = (NodeT*)malloc(sizeof(NodeT));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

NodeS* createStack(NodeT* node)
{
    NodeS* p = (NodeS*)malloc(sizeof(NodeS));
    p->node = node;
    p->next = NULL;
    return p;
}

NodeT* buildTree(int v[], int left, int right)
{
    if (left > right)
        return NULL;

    int middle = (left + right) / 2;

    NodeT* root = (NodeT*)malloc(sizeof(NodeT));
    root = create(v[middle]);

    root->left = buildTree(v, left, middle - 1);
    root->right = buildTree(v, middle + 1, right);

    return root;
}

NodeT* insertNode(NodeT* root, int key)
{
    if (root == NULL)
        return create(key);
    else
    {
        NodeT* q = root;
        NodeT* p = NULL;
        while (q != NULL)
        {
            p = q;
            if (key < q->key)
                q = q->left;
            else
                q = q->right;

        }
        if (key < p->key)
            p->left = create(key);
        else
            p->right = create(key);
    }
    return root;
}

void recursiveInorder(NodeT* root)
{
    if (root != NULL)
    {
        recursiveInorder(root->left);
        cout << root->key << " ";
        recursiveInorder(root->right);
    }
}

void recursivePreorder(NodeT* root)
{
    if (root != NULL)
    {
        cout << root->key << " ";
        recursivePreorder(root->left);
        recursivePreorder(root->right);
    }
}

// PARCURGERE FOLOSIND STACK

void push(NodeS** stack, NodeT* node)
{
    NodeS* p = createStack(node);
    if (*stack == NULL)
        *stack = p;
    else
    {
        p->next = *stack;
        *stack = p;
    }
}

NodeT* pop(NodeS** stack)
{
    if (*stack == NULL)
        return NULL;
    else
    {
        NodeT* aux = (NodeT*)malloc(sizeof(NodeT));
        aux = (*stack)->node;
        NodeS* q = (NodeS*)malloc(sizeof(NodeS));
        q = (*stack)->next;
        free(*stack);
        *stack = q;
        return aux;
    }
}

void iterativeInorderStack(NodeT* root)
{
    NodeT* currentNode = root; // nodul curent la care ma aflu in traversare
    NodeS* stack = NULL; // stiva pe care o voi folosi

    if (root == NULL)
        return;

    while (currentNode != NULL || stack != NULL) // daca nu am parcurs tot arborele sau stiva nu e goala
    {
        while (currentNode != NULL) // daca nu am ajuns la null
        {
            push(&stack, currentNode); // pune in stiva nodul
            currentNode = currentNode->left; // continua sa mergi pe stanga
        }
        currentNode = pop(&stack); // am ajuns la null => pop si afisarea cheii

        cout << currentNode->key << " ";

        currentNode = currentNode->right; // continua cu ramura dreapta
    }
}

void recursiveInorderAnalysis(NodeT* root, Operation& opPrintKey)
{
    if (root != NULL)
    {
        recursiveInorderAnalysis(root->left, opPrintKey);
        opPrintKey.count();
        recursiveInorderAnalysis(root->right, opPrintKey);
    }
}

void startRecursiveInorderAnalysis(NodeT* root, int n)
{
    Operation opPrintKey = p.createOperation("recursiveWalk.print", n);
    recursiveInorderAnalysis(root, opPrintKey);
}

void iterativeInorderStackAnalysis(NodeT* root, int n)
{
    Operation opPrintKey = p.createOperation("iterativeWalk.print", n);

    NodeT* currentNode = root; // nodul curent la care ma aflu in traversare
    NodeS* stack = NULL; // stiva pe care o voi folosi

    if (root == NULL)
        return;

    while (currentNode != NULL || stack != NULL)
    {
        while (currentNode != NULL)
        {
            push(&stack, currentNode);
            currentNode = currentNode->left;
        }
        currentNode = pop(&stack);

        opPrintKey.count(); // numara operatia de afisare

        currentNode = currentNode->right;
    }
}

void walkAnalysis()
{
    int v[MAX_SIZE];
    int n;

    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        NodeT* tree = NULL;

        // construiere bst din sir ordonat de la 1 la n

        // FillRandomArray(v, n, 1, n, true, ASCENDING);
        // tree = buildTree(v, 0, n - 1);
        // recursiveInorder(tree);*/

        // construre bst din sir random, cu radacina aleasa random
        FillRandomArray(v, n, 1, n, true, UNSORTED);
        int randomIndex = rand() % n; // aleg un index random de la 0 la n - 1
        int randomRootKey = v[randomIndex]; // elementul random care va fi radacina este v[index ales random]

        tree = insertNode(tree, randomRootKey); // radacina aleasa random este inserata prima
        for (int i = 0; i < n; i++)
            if (v[i] != randomRootKey) // verific sa nu mai inserez nodul ales ca radacina inca o data
                insertNode(tree, v[i]);

        startRecursiveInorderAnalysis(tree, n);
        iterativeInorderStackAnalysis(tree, n);

        p.startTimer("Iterative.time", n);
        for (int test = 0; test <= nr_tests; ++test)
        {
            iterativeInorderStackAnalysis(tree, n);
        }
        p.stopTimer("Iterative.time", n);

        p.startTimer("Recursive.time", n);
        for (int test = 0; test <= nr_tests; ++test)
        {
            startRecursiveInorderAnalysis(tree, n);
        }
        p.stopTimer("Recursive.time", n);

        p.createGroup("totalTime", "Iterative.time", "Recursive.time");
    }

    p.createGroup("IterativeVsRecursive", "recursiveWalk.print", "iterativeWalk.print");
    p.showReport();
}

// QUICKSORT VS QUICKSORT HIBRID

void print(int a[], int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << "\n";
}

void insertionSortDemo(int a[], int l, int n)
{
    int aux, j;
    for (int i = l; i <= n; i++)
    {
        aux = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > aux)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = aux;
    }
}

int partitionDemo(int a[], int l, int r)
{
    int p = a[r];
    int i = l - 1;
    for (int j = l; j <= r - 1; j++)
        if (a[j] < p)
        {
            i++;
            swap(a[i], a[j]);
        }
    swap(a[i + 1], a[r]);
    return i + 1;
}

void quicksortHybridDemo(int a[], int l, int r)
{
    if (l < r)
        if (r - l < PRAG)
            insertionSortDemo(a, l, r);
        else
        {
            int q = partitionDemo(a, l, r);
            quicksortHybridDemo(a, l, q - 1);
            quicksortHybridDemo(a, q + 1, r);
        }
}

void quicksortDemo(int a[], int l, int r) // quicksort for democase
{
    if (l < r)
    {
        int q = partitionDemo(a, l, r);
        quicksortDemo(a, l, q - 1);
        quicksortDemo(a, q + 1, r);
    }
}

int partition(int a[], int l, int r, Operation& opComp, Operation& opAttr)
{
    opAttr.count();
    int p = a[r];
    int i = l - 1;
    for (int j = l; j <= r - 1; j++)
    {
        opComp.count();
        if (a[j] < p)
        {
            i++;
            opAttr.count(3);
            swap(a[i], a[j]);
        }
    }
    opAttr.count(3);
    swap(a[i + 1], a[r]);
    return i + 1;
}

void quicksort(int a[], int l, int r, Operation& opComp, Operation& opAttr)
{
    if (l < r)
    {
        int q = partition(a, l, r, opComp, opAttr);
        quicksort(a, l, q - 1, opComp, opAttr);
        quicksort(a, q + 1, r, opComp, opAttr);
    }
}

void insertionSortIterative(int a[], int l, int n, Operation& opComp, Operation& opAttr)
{
    int aux, j;
    for (int i = l; i < n; i++)
    {
        opAttr.count();
        aux = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > aux)
        {
            opComp.count();
            opAttr.count();
            a[j + 1] = a[j];
            j--;
        }
        opAttr.count();
        a[j + 1] = aux;
    }
}

void quicksortHybrid(int a[], int l, int r, Operation& opComp, Operation& opAttr)
{
    if (l < r)
        if (r - l < PRAG)
            insertionSortIterative(a, l, r, opComp, opAttr);
        else
        {
            int q = partition(a, l, r, opComp, opAttr);
            quicksortHybrid(a, l, q - 1, opComp, opAttr);
            quicksortHybrid(a, q + 1, r, opComp, opAttr);
        }
}

void quicksortAnalysis(int a[], int n)
{
    Operation opComp = p.createOperation("QuickSort.comp", n);
    Operation opAttr = p.createOperation("QuickSort.attr", n);

    quicksort(a, 0, n - 1, opComp, opAttr);
}

void quicksortHybridAnalysis(int a[], int n)
{
    Operation opComp = p.createOperation("QuickSortHybrid.comp", n);
    Operation opAttr = p.createOperation("QuickSortHybrid.attr", n);

    quicksortHybrid(a, 0, n - 1, opComp, opAttr);
}

void compareQuicksort(int order)
{
    int v1[MAX_SIZE];
    int v2[MAX_SIZE];
    int v3[MAX_SIZE];
    int v4[MAX_SIZE];

    int n;

    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        for (int test = 0; test < NR_TESTS; test++)
        {
            FillRandomArray(v1, n, 10, 1000, false, order);
            for (int i = 0; i < n; i++) // copii pentru sirul generat
            {
                v2[i] = v1[i];
                v3[i] = v1[i];
                v4[i] = v1[i];
            }

            quicksortHybridAnalysis(v1, n);
            quicksortAnalysis(v2, n);
        }

        p.startTimer("QuickSortHybrid.time", n);
        for (int test = 0; test <= nr_tests; ++test)
        {
            quicksortHybridDemo(v3, 0, n - 1);
        }
        p.stopTimer("QuickSortHybrid.time", n);

        p.startTimer("QuickSort.time", n);
        for (int test = 0; test <= nr_tests; ++test)
        {
            quicksortHybridDemo(v4, 0, n - 1);
        }
        p.stopTimer("QuickSort.time", n);

        p.createGroup("totalTime", "QuickSortHybrid.time", "QuickSort.time");

    }

    p.divideValues("QuickSortHybrid.attr", NR_TESTS);
    p.divideValues("QuickSortHybrid.comp", NR_TESTS);
    p.addSeries("QuickSortHybrid", "QuickSortHybrid.attr", "QuickSortHybrid.comp");

    p.divideValues("QuickSort.attr", NR_TESTS);
    p.divideValues("QuickSort.comp", NR_TESTS);
    p.addSeries("QuickSort", "QuickSort.attr", "QuickSort.comp");

    p.createGroup("attributions", "QuickSortHybrid.attr", "QuickSort.attr");
    p.createGroup("comparisons", "QuickSortHybrid.comp", "QuickSort.comp");
    p.createGroup("total", "QuickSortHybrid", "QuickSort");

    p.showReport();
}

// DEMO

void demo()
{
    // demo pentru traversare iterativa si recursiva
    int v[] = { 11, 9, 3, 12, 5, 7, 2, 9, 5 };
    int n = sizeof(v) / sizeof(v[0]);

    NodeT* tree = NULL;
    tree = insertNode(tree, v[0]);
    for (int i = 1; i < n; i++)
        insertNode(tree, v[i]);

    cout << "recursive inorder traversal is: ";
    recursiveInorder(tree);
    cout << "\niterative inorder traversal is: ";
    iterativeInorderStack(tree);
    cout << "\nrecursive preorder traversal is: ";
    recursivePreorder(tree);
    cout << "\n\n";

    // demo pentru QuickSort si QuickSort Hibrid
    int v1[] = { 11, 9, 3, 12, 5, 7, 2, 9, 5 };

    quicksortHybridDemo(v1, 0, n - 1);
    cout << "sorting with quicksortHybrid() is: " << "\n";
    print(v1, n);

    int v2[] = { 11, 9, 3, 12, 5, 7, 2, 9, 5 };

    quicksortDemo(v2, 0, n - 1);
    cout << "sorting with quicksort() is: " << "\n";
    print(v2, n);
}

int main()
{
    demo();
    // compareQuicksort(UNSORTED);
    // walkAnalysis();
}
