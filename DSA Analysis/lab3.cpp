/**
 * @author Iclodean Andrei-George
 * @group 30223
 *
 * Specificațiile problemei: Se cere implementarea corectă și eficientă a sortării folosind heap-uri (Heapsort) și sortarea
rapidă (Quicksort).
 * Analiza comparativă a unuia din algoritmii de sortare din Tema 1 (la alegere) în versiune iterativă vs recursivă. Analiza
 * se va efectua atât din perspectiva numărului de operații, cât și a timpului de rulare.
 * QuickSelect (Randomized-Select): implementare si exemplificare corectitudine
 *
 * Interpretarea personală despre complexitate (timp și spațiu), despre cazurile de testare (favorabil,
 * mediu-statistic si nefavorabil)
 *
 * 
 * 1. QuickSort
 * 
 * QuickSort este un algoritm de sortare care foloseste tehnica Divide et Impera, similar cu algoritmul Merge Sort.
 * Modul sau de functionare este alegerea unui pivot (cel mai din stanga element, cel mai din dreapta, cel median, 
 * element random), iar apoi partitionarea sirului in jurul acestuia. 
 * Apoi, QuickSort se aplica in mod recursiv pe partile din stanga si din dreapta.
 * QuickSort NU este un algoritm stabil.
 * 
 * Complexitatea de timp a algoritmului este O(n log n) atat pe Best Case, cat si pe Average Case, insa este O(n^2) pe Worst Case.
 * Datorita acestui fapt, QuickSort este considerat ca fiind un algoritm potrivit pentru sortarea unor cantitati mari de date.
 * 
 * Complexitatea de spatiu a algoritmului este O(log n).
 * 
 * Cazul 1. Average 
 * 
 * Pe cazul Average, din totalul operatiilor realizate de QuickSort, majoritar este numarul de atributii realizate.
 * Pentru analiza acestui caz, am folosit un sir generat aleator (UNSORTED).
 * 
 * Cazul 2. Worst
 * 
 * Pe cazul Worst, numarul operatiilor este semnificativ mai mare decat pe restul cazurilor. Astfel, inca de la un vector de dimensiune
 * 100, numarul de operatii ajugne la aproape 19000.
 * Din nou, majoritar este numarul de atributii in detrmientul celui de comparatii realizate de QuickSort.
 * Pentrul analiza acestui caz, am ales un sir ordonat ordonat descrescator, intrucat aleg pivotul ca fiind cel mai din dreapta 
 * element. Astfel, se vor genera doua siruri de lungimi foarte diferite, unul avand un singur element, iar celalat n - 1 elemente.
 * 
 * Cazul 3. Best
 * 
 * Pe cazul Best, numarul de operatii este mai mic, insa diferenta nu este la fel de dramatica ca pentru cazul Worst.
 * Numarul de atributii si comparatii este similar in acest caz, insa, totusi, numarul de atributii este mai mare.
 * Pentru analiza acestui caz am realizat doua subprograme noi, numite partitionMiddle() si quicksortBest(), care sunt similare
 * cu cele initiale, insa pivotul este ales drept elementul din mijlocul sirului (p = a[(l + r) / 2]), iar partitiile se realieaza
 * in jurul acestuia.
 * Indexii i si j iau pozitiile din stanga, respectiv din dreapta. i parcurge sirul inainte, pana cand un element cu o valoare mai 
 * mare sau egala cu pivotul este gasit. Indexul j parcurge sirul in sens invers lui i, pana cand un element cu o valoare mai mica
 * sau egala cu pivotul este gasit.
 * Daca i <= j, atunci se va interschimba a[i] cu a[j], iar apoi i este incrementat, iar j decrementat.
 * Algoritmul se opreste atunci cand i devine mai mare decat j.
 * Dupa aplicarea partitiei, toate elementele dinainte de al i-lea element sunt mai mici sau egale cu pivotul, iar toae cele de
 * dupa al j-lea element sunt mai mari sau egale cu pivotul.
 * 
 * 
 * Alegerea pivotului ca fiind elementul din mijloc, genereaza Best Case deoarece vom obtine un arbore binar balansat de inaltime
 * log n. Astfel, complexitatea devine O(n log n).
 * 
 * Cazul 4. HeapSort vs QuickSort: Average
 * 
 * Comparand graficele celor doi algoritmi, obsrvam ca ele sunt foarte apropiate, insa QuickSort apare pe grafic ca avand o 
 * crestere mai mica decat HeapSort.
 * Numarul de comparatii realizate de cele doua algoritme sunt insa extrem de similare.
 * 
 * Astfel, Quicksort este mai rapid si are utilizare in practica, dar din punct de vedere al memoriei, Heapsort este de preferat
 * atunci cand spatiul utilizat este important.
 * 
 * 2. Insertion Sort: Iterativ vs Recursiv (Average)
 * 
 * Analizand graficele algoritmului de Insertion Sort implementat atat iterativ, cat si recursiv, observam ca per total, numarul de
 * operatii este foarte similar, daca nu chiar identic.
 * 
 * Insa, analizand din perspectiva timpului de rulare, este de observat ca executand atat pe Debug, cat si pe Release, timpul 
 * de rulare al variantei recursive este mai mare decat a celei iterative.
 * 
 * 3. QuickSelect (Randomized-Select)
 * 
 * Algoritmul QuickSelect de parametrii a[], l, r, k, va returna al k-lea cel mai mic element al sirului a.
 * Functionarea acestuia este similara cu cea a lui QuickSort. Este alcatuit dintr-un subprogram de partitie si unul de select 
 * efectiv.
 * In PARTITION, se va alege indexul unui element numit pivot, si se vor plasa elementele mai mici ca el la stanga, iar cele mai 
 * mari ca el la dreapta.
 * In SELECT, are loc o asa zisa "cautare binara" pentru al k-lea cel mai mic element. Se va alege un pivot, daca el este elementul
 * cautat este returnat, iar daca nu se va apela PARTITION.
 * 
 * Complexitatea de timp pe cazul Average este O(n) (expected liniar), care deriva din O(n log n) de la QuickSort.
 * Worst Case-ul s-ar intampla in monmentul in care am partitiona mereu pe langa cel mai mare element ramas, fiecare partitie 
 * durand O(n), deci complexitatea ar fi O(n^2).
 * Acest caz poate fi, insa, evitat intrucat nici un input anume nu genereaza acest caz, iar pivotul ales este random.
 * 
**/

#include <iostream>
#include "Profiler.h"

Profiler p("lab3");

using namespace std;

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5 // numarul de teste pentru masurarea operatiilor
#define nr_tests 1000 // numarul de teste pentru masurarea timpului

void print(int a[], int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << "\n";
}

// HeapSort

int left(int i)
{
    return 2 * i + 1;
}

int right(int i)
{
    return 2 * i + 2;
}

void heapify(int a[], int heapSize, int i, Operation& opComp, Operation& opAttr)
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
    {
        opComp.count();
        largest = rightC;
    }

    if (largest != i)
    {
        opAttr.count(3);
        aux = a[i];
        a[i] = a[largest];
        a[largest] = aux;
        heapify(a, heapSize, largest, opComp, opAttr);
    }
}

void buildMaxHeap(int a[], int heapSize, Operation& opComp, Operation& opAttr)
{
    for (int i = heapSize / 2 - 1; i >= 0; i--)
        heapify(a, heapSize, i, opComp, opAttr);
}

void heapsort(int a[], int n)
{
    Operation opComp = p.createOperation("HeapSort.comp", n);
    Operation opAttr = p.createOperation("HeapSort.attr", n);

    int aux;
    buildMaxHeap(a, n, opComp, opAttr);
    for (int i = n - 1; i > 0; i--)
    {
        aux = a[0];
        a[0] = a[i];
        a[i] = aux;
        n--;
        heapify(a, i, 0, opComp, opAttr);
    }
}

// QuickSort

int partitionDemo(int a[], int l, int r) // partition for demo case
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

void quicksortAnalysis(int a[], int n)
{
    Operation opComp = p.createOperation("QuickSort.comp", n);
    Operation opAttr = p.createOperation("QuickSort.attr", n);

    quicksort(a, 0, n - 1, opComp, opAttr);
}

// Quickselect

int partitionQS(int a[], int l, int r) // partition for quickselect demo
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

int quickselect(int a[], int p, int r, int i)
{
    if (p == r)
        return a[p];
    int q = partitionQS(a, p, r);
    int k = q - p + 1;
    if (i == k)
        return a[q];
    else if (i < k)
        return quickselect(a, p, q - 1, i);
    else return quickselect(a, q + 1, r, i - k);
}

// Insertion Sort - Iterativ vs Recursiv

void insertionSortIterative(int a[], int n)
{
    Operation opComp = p.createOperation("insertionSortIterative.comp", n);
    Operation opAttr = p.createOperation("insertionSortIterative.attr", n);

    int aux, j;
    for (int i = 0; i < n; i++)
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

void insertionSortRecursive(int a[], int n, Operation& opComp, Operation& opAttr)
{
    if (n <= 1)
        return;

    insertionSortRecursive(a, n - 1, opComp, opAttr);

    opAttr.count();
    int value = a[n - 1];
    int index = n - 2;

    while (index >= 0 && a[index] > value)
    {
        opComp.count();
        opAttr.count();
        a[index + 1] = a[index];
        index--;
    }
    opAttr.count();
    a[index + 1] = value;
}

void insertionSortRecursiveAnalysis(int a[], int n)
{
    Operation opComp = p.createOperation("insertionSortRecursive.comp", n);
    Operation opAttr = p.createOperation("insertionSortRecursive.attr", n);

    insertionSortRecursive(a, n, opComp, opAttr);
}

void insertionSortRecursiveDemo(int a[], int n)
{
    if (n <= 1)
        return;

    insertionSortRecursiveDemo(a, n - 1);

    int value = a[n - 1];
    int index = n - 2;

    while (index >= 0 && a[index] > value)
    {
        a[index + 1] = a[index];
        index--;
    }
    a[index + 1] = value;
}

void demo()
{
    int v1[] = { 11, 9, 3, 12, 5, 7, 2, 9, 5 };
    int n = sizeof(v1) / sizeof(v1[0]);

    heapsort(v1, n);
    cout << "sorting with heapsort() is: " << "\n";
    print(v1, n);

    int v2[] = { 11, 9, 3, 12, 5, 7, 2, 9, 5 };

    quicksortDemo(v2, 0, n - 1);
    cout << "sorting with quicksort() is: " << "\n";
    print(v2, n);

    int v3[] = { 11, 9, 3, 12, 5, 7, 2, 9, 5 };

    insertionSortIterative(v3, n);
    cout << "sorting with insertionSortIterative() is: " << "\n";
    print(v3, n);

    int v4[] = { 11, 9, 3, 12, 5, 7, 2, 9, 5 };

    insertionSortRecursiveDemo(v4, n);
    cout << "sorting with insertionSortRecursive() is: " << "\n";
    print(v4, n);

    int v5[] = { 11, 9, 3, 12, 5, 7, 2, 2, 9, 5 };
    cout << "3rd smallest element with quickselect() is: " << quickselect(v5, 0, n - 1, 3);
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
            heapsort(v1, n);
            quicksortAnalysis(v2, n);
        }
    }

    p.divideValues("HeapSort.attr", NR_TESTS);
    p.divideValues("HeapSort.comp", NR_TESTS);
    p.addSeries("HeapSort", "HeapSort.attr", "HeapSort.comp");

    p.divideValues("QuickSort.attr", NR_TESTS);
    p.divideValues("QuickSort.comp", NR_TESTS);
    p.addSeries("QuickSort", "QuickSort.attr", "QuickSort.comp");

    p.createGroup("attributions", "HeapSort.attr", "QuickSort.attr");
    p.createGroup("comparisons", "HeapSort.comp", "QuickSort.comp");
    p.createGroup("total", "HeapSort", "QuickSort");
}

void perfInsertion(int order)
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
            insertionSortIterative(v1, n);
            insertionSortRecursiveAnalysis(v2, n);
        }

        p.startTimer("insertionSortIterative.time", n);
        for (int test = 0; test < nr_tests; ++test)
        {
            insertionSortIterative(v3, n);
        }
        p.stopTimer("insertionSortIterative.time", n);

        p.startTimer("insertionSortRecursive.time", n);
        for (int test = 0; test < nr_tests; ++test)
        {
            insertionSortRecursiveAnalysis(v4, n);
        }
        p.stopTimer("insertionSortRecursive.time", n);

        p.createGroup("totalTime", "insertionSortIterative.time", "insertionSortRecursive.time");
    }

    p.divideValues("insertionSortIterative.attr", NR_TESTS);
    p.divideValues("insertionSortIterative.comp", NR_TESTS);
    p.addSeries("insertionSortIterative", "insertionSortIterative.attr", "insertionSortIterative.comp");

    p.divideValues("insertionSortRecursive.attr", NR_TESTS);
    p.divideValues("insertionSortRecursive.comp", NR_TESTS);
    p.addSeries("insertionSortRecursive", "insertionSortRecursive.attr", "insertionSortRecursive.comp");

    p.createGroup("attributions", "insertionSortIterative.attr", "insertionSortRecursive.attr");
    p.createGroup("comparisons", "insertionSortIterative.comp", "insertionSortRecursive.comp");
    p.createGroup("total", "insertionSortIterative", "insertionSortRecursive");

    p.showReport();
}

void averageQuicksortHeapsort()
{
    p.reset("average");
    perf(UNSORTED);
    p.showReport();
}

void worstQuicksort(int order)
{
    p.reset("worst");
    
    int v[MAX_SIZE];

    int n;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        for (int test = 0; test < NR_TESTS; test++)
        {
            FillRandomArray(v, n, 10, 1000, false, order);
            quicksortAnalysis(v, n);
        }
    }

    p.divideValues("QuickSort.attr", NR_TESTS);
    p.divideValues("QuickSort.comp", NR_TESTS);
    p.addSeries("QuickSort", "QuickSort.attr", "QuickSort.comp");
    
    p.showReport();
    
}

void averageQuicksort(int order)
{
    p.reset("average");

    int v[MAX_SIZE];

    int n;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        for (int test = 0; test < NR_TESTS; test++)
        {
            FillRandomArray(v, n, 10, 1000, false, order);
            quicksortAnalysis(v, n);
        }
    }

    p.divideValues("QuickSort.attr", NR_TESTS);
    p.divideValues("QuickSort.comp", NR_TESTS);
    p.addSeries("QuickSort", "QuickSort.attr", "QuickSort.comp");

    p.showReport();

}

int partitionMiddle(int a[], int l, int r, Operation& opComp, Operation& opAttr)
{
    int i = l;
    int j = r;
    opAttr.count();
    int p = a[(l + r) / 2];

    while (i <= j)
    {
        while (a[i] < p)
        {
            opComp.count();
            i++;
        }
        while (a[j] > p)
        {
            opComp.count();
            j--;
        }

        if (i <= j)
        {
            opAttr.count(3);
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    return i;
}

void quicksortBest(int a[], int l, int r, Operation& opComp, Operation& opAttr)
{
    int q = partitionMiddle(a, l, r, opComp, opAttr);
    if (l < q - 1)
        quicksortBest(a, l, q - 1, opComp, opAttr);
    if (q < r)
        quicksortBest(a, q, r, opComp, opAttr);
}

void quicksortBestAnalysis(int a[], int n)
{
    Operation opComp = p.createOperation("QuickSort.comp", n);
    Operation opAttr = p.createOperation("QuickSort.attr", n);

    quicksortBest(a, 0, n - 1, opComp, opAttr);
}

void bestQuicksort(int order)
{
    p.reset("best");

    int v[MAX_SIZE];

    int n;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        for (int test = 0; test < NR_TESTS; test++)
        {
            FillRandomArray(v, n, 10, 1000, false, order);
            quicksortBestAnalysis(v, n);
        }
    }

    p.divideValues("QuickSort.attr", NR_TESTS);
    p.divideValues("QuickSort.comp", NR_TESTS);
    p.addSeries("QuickSort", "QuickSort.attr", "QuickSort.comp");

    p.showReport();
}

void perf_all()
{
    p.reset("average");
    perf(UNSORTED);
    p.reset("best");
    perf(ASCENDING);
    p.reset("worst");
    perf(DESCENDING);
    p.showReport();
}

int main()
{
    demo();
    // perf_all();
    // averageQuicksortHeapsort();
    // worstQuicksort(DESCENDING);
    // averageQuicksort(UNSORTED);
    // bestQuicksort(UNSORTED);
    // perfInsertion(UNSORTED);
    return 0;
}