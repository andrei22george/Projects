/**
 * @author Iclodean Andrei-George
 * @group 30223
 *
 * Specificațiile problemei: Se cere implementarea corectă și eficientă a două metode de construire a structurii de date
 * Heap i.e. “de jos în sus” (bottom-up) și “de sus în jos” (top-down). De asemenea, se cere
 * implementarea algoritmului heapsort.

 *
 * Interpretarea personală despre complexitate (timp și spațiu), despre cazurile de testare (favorabil,
 * mediu-statistic si nefavorabil)
 * 
 * Metoda 1. Bottom Up
 * 
 *      Prima metoda de construire a unui heap realizata este metoda Bottom Up (de jos in sus). Metoda presupune construirea unui heap
 * dintr-un sir, aplicand pentru fiecare nod functia Heapify, in vederea stabilirii proprietatii de heap pe sirul (care poate fi
 * vizualizat ca arbore).
 * 
 * Metoda 2. Top Down
 * 
 *      Cea de a doua metoda de construire a unui heap realizata, este metoda Top Down (de sus in jos). Aceasta presupune construirea unui
 * heap prin adaugarea unui nod la sfarsitul arborelui (daca vizualizam sirul ce se doreste a deveni heap, ca pe un arbore).
 * Dupa adaugarea unui nod, in cazul in care propreietatea de heap nu este respectata, se va aplica functia increaseKey, in vederea
 * restabilirii proprietatii de heap.
 * 
 * Folosind cele doua metode descrise anterior, am realizat algoritmul Heapsort, astfel functia heapsortBU fiind algoritmul Heapsort care
 * foloseste metoda Bottom Up de construire a heap-ului folosit, iar functia heapsortTD fiind acelasi algoritm de sortare, dar care 
 * foloseste metoda Top Down de construire a heap-ului.
 * 
 * In functia demo, am apelat astfel:
 *      1. heapsortBU pentru a exemplifica corectitudinea algoritmului Heapsort folosind metodea Bottom Up de constructie a heap-ului
 *      2. heapsortTD pentru a exemplifica corectitudinea algoritmului Heapsort folosind metodea Top Down de constructie a heap-ului
 *      3. BuildMaxHeap1 (echivalentul lui BUILD-MAX-HEAP din carte) pentru a exemplifica corectitudinea algoritmului de constructie
 *         a unui heap folosind metoda Bottom Up
 *      4. BuildMaxHeap2 (echivalentul lui BUILD-MAX-HEAP' din carte) pentru a exemplifica corectitudinea algoritmului de constructie
 *         a unui heap folosind metoda Top Down
 *  
 * In continuare, voi analiza comparativ cele doua metode pe cele doua cazuri (average si worst) cerute in cerinta.
 * 
 * Cazul 1. Average (Bottom Up is best)
 * 
 * Pe cazul average, cea mai eficienta metoda este cea Bottom Up. Se observa ca atat numarul de atribuiri, cat si cel de comparatii
 * si cel total este semnificativ mai mare in cazul metodei Top Down.
 * De pe grafic se observa ca complexitatea de timp a ambelor metode este liniara, insa cea a metodei Bottom Up este O(n), in timp 
 * ce cea a metodei Top Down este O(n logn).
 * 
 * Cazul 2. Worst for Top Down

 * Pentru metoda Top Down de constructie a heap-ului, am constatat ca cel mai ineficient caz este atunci cand sirul dat este ordonat
 * crescator. Metoda Top Down adauga la fiecare pas un nod nou la finalul arborelui, iar apoi verifica proprietatea de heap si in cazul
 * in care nu este repectata se aplica Increase Key pentru a aduce nodul la nivelul la care are loc proprietatea de heap (bubbeling up).
 * Astfel, daca fiecare nod adaugat va fi mai mare decat nodul anterior, proprietatea de heap nu va fi respectata constant, fiind nevoie
 * de functia de Increase Key pentru restabilirea proprietatii de heap la fiecare pas. Astfel, algoritmul devine extrem de ineficient.

 * Cazul 2. Worst for Bottom Up

 * In cazul metodei Bottom Up, worst case-ul are loc in momentul in care ultimul nivel al arborelui este pe jumatate exact jumatate 
 * plin, iar sirul este ordonat strict crescator. Astfel, vom obtine siruri de genul:
 * 1, 2
 * 1, 2, 3, 4, 5
 * 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
 * 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23
 * etc.
 * Observam ca numarul maxim de elemente are o crestere neregulata: 2, 5, 11, 23, 47, 95, 191, 383, 767, 1535, 3071, 6143, 12287.
 * Formula cu care se determina aceste numere este 2^n - 1 - 2^(n-2) care rezulta de pe desenele arborilor binari.
 * Incadrandu-ne in limitele din laborator, avem n intre 7 (lungime 95) si 13 (lungime 6143) sau 14 (lungime 12287).
 *
 */

#include <iostream>
#include "Profiler.h"

Profiler p("lab2");

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5
#define MAX_SIZE_BU 12287

using namespace std;

void print(int a[], int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << "\n";
}

int parent(int i)
{
    return (i - 1) / 2;
}

int left(int i)
{
    return 2 * i + 1;
}

int right(int i)
{
    return 2 * i + 2;
}

void heapify(int a[], int heapSize, int i, Operation &opComp, Operation &opAttr) // i este index-ul parintelui
{ 
    int leftC = left(i);
    int rightC = right(i);
    int largest, aux;
    largest = i;

    if (leftC < heapSize && a[leftC] > a[i])
    {
        opComp.count();
        largest = leftC;
    }
    else largest = i;

    if (rightC < heapSize && a[rightC] > a[largest])
        largest = rightC;

    if (largest != i)
    {
        opAttr.count(3);
        aux = a[i];
        a[i] = a[largest];
        a[largest] = aux;
        heapify(a, heapSize, largest, opComp, opAttr);
    }
}

void heapifyS(int a[], int heapSize, int i) // folosesc aceasta functie de heapify in functia de heapsortBU pentru nu avea opComp
                                            // si opAttr ca parametrii.
{
    int leftC = left(i);
    int rightC = right(i);
    int largest, aux;
    largest = i;

    if (leftC < heapSize && a[leftC] > a[i])
    {
        largest = leftC;
    }
    else largest = i;

    if (rightC < heapSize && a[rightC] > a[largest])
        largest = rightC;

    if (largest != i)
    {
        aux = a[i];
        a[i] = a[largest];
        a[largest] = aux;
        heapifyS(a, heapSize, largest);
    }
}

// Metoda 1 de construire a heap-ului, de jos in sus (Bottom Up)

void buildMaxHeap1(int a[], int heapSize) // de jos in sus, bottom up (echivalent cu BUILD-MAX-HEAP din carte)
{
    Operation opComp = p.createOperation("BottomUp.comp", heapSize);
    Operation opAttr = p.createOperation("BottomUp.attr", heapSize);

    // a[heap_size] = a[length];
    for (int i = heapSize / 2 - 1; i >= 0; i--)
        heapify(a, heapSize, i, opComp, opAttr);
}

// Metoda 2 de construire a heap-ului, de sus in jos (Top Down)

void increaseKey(int a[], int i, int key, Operation &opComp, Operation &opAttr)
{
    int aux;
    
    opComp.count();
    if (key < a[i])
        return;
    opAttr.count();
    a[i] = key;
    while (i > 0 && a[parent(i)] < a[i])
    {
        opComp.count();
        opAttr.count(3);
        aux = a[i];
        a[i] = a[parent(i)];
        a[parent(i)] = aux;
        i = parent(i);
    }
}

void heapInsert(int a[], int &hs, int key, Operation &opComp, Operation &opAttr)
{
    // heap_size++;
    hs++;
    opAttr.count();
    // a[heap_size] = key;
    a[hs] = key;
    increaseKey(a, hs, key, opComp, opAttr);
}

void buildMaxHeap2(int a[], int n) // de sus in jos, top down (echivalent cu BUILD-MAX-HEAP' din carte)
{
    Operation opComp = p.createOperation("TopDown.comp", n);
    Operation opAttr = p.createOperation("TopDown.attr", n);

    int hs = -1;

    for (int i = 0; i < n; i++)
        heapInsert(a, hs, a[i], opComp, opAttr);
}

// heapsort folosind metoda Bottom Up de construire a heap-ului

void heapsortBU(int a[], int n)
{
    int aux;
    buildMaxHeap1(a, n);
    for (int i = n - 1; i > 0; i--)
    {
        aux = a[0];
        a[0] = a[i];
        a[i] = aux;
        n--;
        heapifyS(a, i, 0);
    }
}

// heapsort folosind metoda Top Down de construire a heap-ului

void heapsortTD(int a[], int n)
{
    int aux;
    buildMaxHeap2(a, n);
    for (int i = n - 1; i > 0; i--)
    {
        // swap(a[0], a[i])

        aux = a[0];
        a[0] = a[i];
        a[i] = aux;
        n--;
        heapifyS(a, i, 0);
    }
}

void demo()
{
    int v1[] = { 11, 9, 3, 12, 5, 7, 2, 9, 5 };
    int n = sizeof(v1) / sizeof(v1[0]);

    heapsortBU(v1, n);
    cout << "sorting with heapsort() using Bottom Up method is: " << "\n";
    print(v1, n);

    int v2[] = { 11, 9, 3, 12, 5, 7, 2, 9, 5 };
    heapsortTD(v2, n);
    cout << "sorting with heapsort() using Top Down method is: " << "\n";
    print(v2, n);

    int v3[] = { 11, 9, 3, 12, 5, 7, 2, 9, 5 };
    buildMaxHeap1(v3, n);
    cout << "building a heap using Bottom Up method is: " << "\n";
    print(v3, n);

    int v4[] = { 11, 9, 3, 12, 5, 7, 2, 9, 5 };
    buildMaxHeap2(v4, n);
    cout << "building a heap using Top Down method is: " << "\n";
    print(v4, n);
}

void perf(int order)
{
    int v1[MAX_SIZE];
    int v2[MAX_SIZE];
    int n;

    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        for (int test = 0; test < NR_TESTS; test++)
        {
            FillRandomArray(v1, n, 10, 1000, false, order);
            for (int i = 0; i < n; i++) // copii pentru sirul generat
            {
                v2[i] = v1[i];
            }
            /*int v3[] = {1,2,3,4,5,6,7,8,9,10,11};
            int n3 = sizeof(v3) / sizeof(v1[0]);
            buildMaxHeap1(v3, n3);
            int v4[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 };
            int n4 = sizeof(v4) / sizeof(v1[0]);
            buildMaxHeap1(v4, n4);
            int v5[];
            int n5 = pow2(n) - pow2(n - 2) - 1;
            for (int i = 0; i < n5; i++)
                v5[i] = i + 1;*/
            buildMaxHeap1(v1, n);
            buildMaxHeap2(v2, n);
            
        }
    
    }

    p.divideValues("BottomUp.attr", NR_TESTS);
    p.divideValues("BottomUp.comp", NR_TESTS);
    p.addSeries("BottomUp", "BottomUp.attr", "BottomUp.comp");

    p.divideValues("TopDown.attr", NR_TESTS);
    p.divideValues("TopDown.comp", NR_TESTS);
    p.addSeries("TopDown", "TopDown.attr", "TopDown.comp");

    p.createGroup("attributions", "BottomUp.attr", "TopDown.attr");
    p.createGroup("comparisons", "BottomUp.comp", "TopDown.comp");
    p.createGroup("total", "BottomUp", "TopDown");
}

int pow2(int n)
{
    int res = 1;
    for (int i = 0; i <= n; i++)
        res *= 2;
    return res;
}

void perf2(int order)
{
    int v1[MAX_SIZE_BU];
    int n;

    for (n = 6; n <= 13; n += 1)
    {
        for (int test = 0; test < NR_TESTS; test++)
        {
            int size = pow2(n) - pow2(n - 2) - 1;
            for (int i = 0; i < size; i++)
                v1[i] = i + 1;
            buildMaxHeap1(v1, size);
       

        }

    }

    p.divideValues("BottomUp.attr", NR_TESTS);
    p.divideValues("BottomUp.comp", NR_TESTS);
    p.addSeries("BottomUp", "BottomUp.attr", "BottomUp.comp");
}

void worstBU(int order)
{
    int n, size;
    int v1[MAX_SIZE_BU];

    for (n = 3; n <= 13; n++)
    {
        size = pow2(n) - pow2(n - 2) - 1;
        for (int i = 0; i < size; i++)
            v1[i] = i + 1;

        buildMaxHeap1(v1, size);
        // FillRandomArray(v2, size, 1, size, true, order);
        // buildMaxHeap2(v2, size);
    }
    p.addSeries("BottomUpWorst", "BottomUpWorst.attr", "BottomUpWorst.comp");
}

void perf_all()
{
    p.reset("average");
    perf(UNSORTED);
    
    p.reset("worstBU");
    perf2(UNSORTED);

    p.reset("worstTD");
    perf(ASCENDING);

    //p.reset("worstBU");
    //worstBU(ASCENDING);

    p.showReport();
}

int main()
{
    // demo();
    perf_all();
    return 0;
}

