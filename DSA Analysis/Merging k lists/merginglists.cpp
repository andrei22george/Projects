/**
 * @author Iclodean Andrei-George
 * @group 30223
 *
 * Specificațiile problemei: Se cere implementarea corectă și eficientă a unei metode de complexitate (𝑛 * 𝑙𝑜𝑔 𝑘 ) pentru
 * interclasarea a k șiruri sortate. Unde n este numărul total de elemente (Sugestie: folosiți un
 * heap, vezi notițele de la seminarul al 2-lea).
 *
 * Interpretarea personală despre complexitate (timp și spațiu), despre cazurile de testare (favorabil,
 * mediu-statistic si nefavorabil):
 * 
 * 1. Generare k liste aleatoare, avand in total n elemente
 * 
 *      Pentru generarea listelor, am folosit o tabela de dispersie folosind metoda chaining. Mai intai, am generat un sir de numere random folosind functia predefinita
 * in profiler (FillRandomArray), sir sortat in ordine descrescatoare, ca mai apoi cand va fi introdus in liste, acesea sa fie ordonate crescator.
 *      Apoi, cu ajutorul metodei chaining si a functiei rand(), am generat index-uri random, reprezentand numarul listei unde vor fi plasate in mod aleator elementele
 * generate.
 *      Pentru a ma asigura ca voi avea o acoperire completa si nu voi avea liste nule, m-am asigurat ca generez mai intai toti indexii de la 1 la k, pentru a avea 
 * cel putin un element in fiecare lista. Realizez acest lucru folosind Knuth Shuffle pentru a amesteca in mod random toti indexii de la 1 la k.
 *      Dupa ce am plasat in fiecare lista cate un element, astfel incat nici una nu mai este nula, voi continua sa plasez in mod random cate un element pana ce
 * ating n elemente in total (dupa Knuth Shuffle mai am de plasat n - k elemente).
 * 
 * 2. Interclasarea celor k liste, folosind un Min Heap (Extragerea primelor elemente din fiecare lista si crearea heap-ului)
 *      
 *      Deoarece Min Heap-ul va retine mereu in radacina cel mai mic element, vom extrage primul element din fiecare lista, urmand ca apoi sa-l retinem intr-un
 * astfel de heap. Intrucat listele sunt deja sortate, este sigur ca unul dintre primele elemente va fi si cel mai mic dintre toate.
 *      Vom extrage apoi primul nod (pop(H)) si incrementam pointer-ul la lista din care tocmai l-am extras. Urmatorul element din acea lista este acum adaugat
 * in heap si urmeaza sa restabilm proprietatea de heap. Repetam acest proces pana cand heap-ul este gol.
 *      In final, am pastrat o lista separata in care se afla acum toate listele interclasate.
 * 
 *      Acest algoritm este mai eficient decat interclasarea succesiva a doua cate doua liste (care are o complexitate O(nk log n)).
 *      Complexitatea de timp a algoritmului este O(n log k).
 */


#include <iostream>
#include "Profiler.h"

Profiler p("lab4");

using namespace std;

// CONSTANTE

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5
#define k1 5
#define k2 10
#define k3 100
#define MAX_SIZE_DEMO 20
#define kDemo 4
#define K_STEP_SIZE 10
#define K_MAX_SIZE 500
#define K_n 10000

// VARIABILE GLOBALE

int indexesLeftKDemo = kDemo;
int indexesKDemo[kDemo];

int indexesLeftK1 = k1; // numarul de indexsi ramas la fiecare pas al generarii listelor random
int indexesK1[k1]; // vectorul cu primii k indexsi generati, este amesecat folosind Knuth Shuffle
int indexesLeftK2 = k2;
int indexesK2[k2];
int indexesLeftK3 = k3;
int indexesK3[k3];

int currentIndex = 0; // indexul curent pentru fiecare element in momentul construirii Min Heap.

// STRUCTURI

typedef struct node
{
    int key;
    struct node* next;
} NodeT;

NodeT* create(int key)
{
    NodeT* q = (NodeT*)malloc(sizeof(NodeT));
    q->key = key;
    q->next = NULL;
    return q;
}

typedef struct {
    int key; // valoarea
    int index; // poizita din heap unde i = 0, k-1
    int originList; // LISTA din care provine elementul repsectiv
}Heap;

// FUNCTII DE PRINT DIVERSE

void printLists(NodeT* list[], int K)
{
    int i;
    for (i = 0; i < K; i++)
    {
        cout << i + 1 << ": ";
        if (list[i] != NULL)
        {
            NodeT* p;
            p = list[i];
            while (p != NULL)
            {
                cout << " " << p->key;
                p = p->next;
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

void printOrderedList(NodeT* q)
{
    cout << "k merged lists are: ";
    while (q != NULL)
    {
        cout << q->key << " ";
        q = q->next;
    }
    cout << "\n";
}

void printHeap(Heap H[], int k)
{
    for (int i = 0; i < k; i++)
        cout << "element is: " << H[i].key << " from list index: " << H[i].originList + 1 << " at heap pos: " << H[i].index << "\n";

    for (int i = 0; i < k; i++)
        cout << H[i].key << " ";
}

// GENERAREA LISTELOR RANDOM

void knuthShuffle(int indexes[], int end)
{
    for (int i = end - 1; i >= 1; i--)
    {
        int c = rand() % (i + 1);
        if (c != i)
            swap(indexes[i], indexes[c]);
    }
}

int hashFunction(int k)
{
    return rand() % k;
}

void createRandomIndexesK1(int indexes[])
{
    for (int i = 0; i < k1; i++)
        indexes[i] = i;
    knuthShuffle(indexes, k1);
}

void insertK1(NodeT* list[], int key)
{
    NodeT* newEl = create(key);
    int index;
    if (indexesLeftK1 >= 0)
    {
        indexesLeftK1--;
        index = indexesK1[indexesLeftK1];
        
    }  
    else
        index = hashFunction(k1);

    if (list[index] == NULL)
    {
        list[index] = newEl;
    }
    else
    {
        newEl->next = list[index];
        list[index] = newEl;
    }
}

void generateK1Lists(NodeT* list[], int n, int K)
{
    int v[MAX_SIZE];
    FillRandomArray(v, n, 10, 1000, false, DESCENDING);

    for (int i = 0; i < K; i++)
    {
        list[i] = NULL;
    }

    createRandomIndexesK1(indexesK1);

    for (int i = 0; i < n; i++)
        insertK1(list, v[i]);
    //printLists(list, K);
}

void createRandomIndexesK2(int indexes[])
{
    for (int i = 0; i < k2; i++)
        indexes[i] = i;
    knuthShuffle(indexes, k2);
}

void insertK2(NodeT* list[], int key)
{
    NodeT* newEl = create(key);
    int index;
    if (indexesLeftK2 >= 0)
    {
        indexesLeftK2--;
        index = indexesK2[indexesLeftK2];

    }
    else
        index = hashFunction(k2);

    if (list[index] == NULL)
    {
        list[index] = newEl;
    }
    else
    {
        newEl->next = list[index];
        list[index] = newEl;
    }
}

void generateK2Lists(NodeT* list[], int n, int K)
{
    int v[MAX_SIZE];
    FillRandomArray(v, n, 10, 1000, false, DESCENDING);

    for (int i = 0; i < K; i++)
    {
        list[i] = NULL;
    }

    createRandomIndexesK2(indexesK2);

    for (int i = 0; i < n; i++)
        insertK2(list, v[i]);
    //printLists(list, K);
}

void createRandomIndexesK3(int indexes[])
{
    for (int i = 0; i < k3; i++)
        indexes[i] = i;
    knuthShuffle(indexes, k3);
}

void insertK3(NodeT* list[], int key)
{
    NodeT* newEl = create(key);
    int index;
    if (indexesLeftK3 >= 0)
    {
        indexesLeftK3--;
        index = indexesK3[indexesLeftK3];

    }
    else
        index = hashFunction(k3);

    if (list[index] == NULL)
    {
        list[index] = newEl;
    }
    else
    {
        newEl->next = list[index];
        list[index] = newEl;
    }
}

void generateK3Lists(NodeT* list[], int n, int K)
{
    int v[MAX_SIZE];
    FillRandomArray(v, n, 10, 1000, false, DESCENDING);

    for (int i = 0; i < K; i++)
    {
        list[i] = NULL;
    }

    createRandomIndexesK3(indexesK3);

    for (int i = 0; i < n; i++)
        insertK3(list, v[i]);
    //printLists(list, K);
}

void createRandomIndexesDemo(int indexes[])
{
    for (int i = 0; i < kDemo; i++)
        indexes[i] = i;
    knuthShuffle(indexes, kDemo);
}

void insert(NodeT* list[], int key)
{
    NodeT* newEl = create(key);
    int index;
    if (indexesLeftKDemo >= 0)
    {
        indexesLeftKDemo--;
        index = indexesKDemo[indexesLeftKDemo];

    }
    else
        index = hashFunction(kDemo);

    if (list[index] == NULL)
    {
        list[index] = newEl;
    }
    else
    {
        newEl->next = list[index];
        list[index] = newEl;
    }
}

void generateKDemoLists(NodeT* list[], int n, int K)
{
    int v[MAX_SIZE];
    FillRandomArray(v, n, 10, 1000, false, DESCENDING);

    for (int i = 0; i < K; i++)
    {
        list[i] = NULL;
    }

    createRandomIndexesDemo(indexesKDemo);

    for (int i = 0; i < n; i++)
        insert(list, v[i]);
    printLists(list, K);
}

// BUILD MIN HEAP RELATED STUFF (using bottom up)

int left(int i)
{
    return 2 * i + 1;
}

int right(int i)
{
    return 2 * i + 2;
}

void heapifyDemo(Heap H[], int heapSize, int i)
{
    int leftC = left(i);
    int rightC = right(i);
    int smallest, aux;
    smallest = i;

    if (leftC < heapSize && H[leftC].key < H[i].key)
    {
        smallest = leftC;
    }
    else smallest = i;

    if (rightC < heapSize && H[rightC].key < H[smallest].key)
    {
        smallest = rightC;
    }

    if (smallest != i)
    {
        aux = H[i].key;
        H[i].key = H[smallest].key;
        H[smallest].key = aux;
        aux = H[i].originList;
        H[i].originList = H[smallest].originList;
        H[smallest].originList = aux;
        heapifyDemo(H, heapSize, smallest);
    }
}

void buildMinHeapDemo(Heap H[], int heapSize)
{
    for (int i = heapSize / 2 - 1; i >= 0; i--)
        heapifyDemo(H, heapSize, i);
}

// FUNCTIE PENTRU EXTRAGEREA PRIMELOR ELEMENTE DIN FIECARE DIN CELE K LISTE GENERARE

void extractFirstsDemo(NodeT* list[], Heap H[], int K)
{
    for (int i = 0; i < K; i++)
    {
        if (list[i] != NULL)
        {
            H[i].key = list[i]->key;
            H[i].index = currentIndex;
            currentIndex++;
            H[i].originList = i;
        }
    }
}

// MERGES

NodeT* mergeTwoListsDemo(NodeT* list1, NodeT* list2)
{
    if (list1 == NULL)
        return list2;
    if (list2 == NULL)
        return list1;

    NodeT* mergedList = NULL;

    if (list1->key < list2->key)
    {
        NodeT* temp = create(list1->key);
        mergedList = temp;
        list1 = list1->next;
    }
    else
    {
        NodeT* temp = create(list2->key);
        mergedList = temp;
        list2 = list2->next;
    }

    NodeT* current = mergedList;
    while (list1 != NULL && list2 != NULL)
    {
        if (list1->key > list2->key)
        {
            NodeT* temp = create(list2->key);
            current->next = temp;
            list2 = list2->next;
        }
        else
        {
            NodeT* temp = create(list1->key);
            current->next = temp;
            list1 = list1->next;
        }
        current = current->next;
    }

    while (list1 != NULL)
    {
        NodeT* temp = create(list1->key);
        current->next = temp;
        list1 = list1->next;
        current = current->next;
    }
    current->next = list1;

    while (list2 != NULL)
    {
        NodeT* temp = create(list2->key);
        current->next = temp;
        list2 = list2->next;
        current = current->next;
    }

    return mergedList;
}

void kWayMergeDemo(NodeT* list[], NodeT** O, Heap H[], int n, int K)
{
    extractFirstsDemo(list, H, K);
    buildMinHeapDemo(H, K);

    int heapSize = K - 1;
    NodeT* p = NULL;
    NodeT* q;
    *O = NULL;

    while (heapSize > 1)
    {
        Heap Mins = H[0];

        if (*O == NULL)
        {
            *O = create(H[0].key);
            p = *O;
        }
        else
        {
            q = create(Mins.key);
            p->next = q;
            p = q;
        }

        if (list[Mins.originList]->next != NULL)
        {
            list[Mins.originList] = list[Mins.originList]->next;
            H[0].key = list[Mins.originList]->key;
            H[0].originList = Mins.originList;
        }
        else
        {
            H[0] = H[heapSize];
            heapSize--;
        }

        heapifyDemo(H, heapSize + 1, 0);

    }

    NodeT* list3;
    NodeT* list1 = list[H[1].originList];
    NodeT* list2 = list[H[0].originList];
    //mergeTwoListsDemo(list1, list2, &list3);
    list3 = mergeTwoListsDemo(list1, list2);

    if (p != NULL)
        p->next = list3;
}

// ANALIZA: BUILD MIN HEAP RELATED STUFF (using bottom up)

void heapify(Heap H[], int heapSize, int i, Operation& opComp, Operation& opAttr)
{
    int leftC = left(i);
    int rightC = right(i);
    int smallest, aux;
    smallest = i;

    if (leftC < heapSize && H[leftC].key < H[i].key)
    {
        opComp.count();
        smallest = leftC;
    }
    else smallest = i;

    if (rightC < heapSize && H[rightC].key < H[smallest].key)
    {
        opComp.count();
        smallest = rightC;
    }

    if (smallest != i)
    {
        opAttr.count(3);
        aux = H[i].key;
        H[i].key = H[smallest].key;
        H[smallest].key = aux;

        //opAttr.count();
        aux = H[i].originList;
        H[i].originList = H[smallest].originList;
        H[smallest].originList = aux;
        heapify(H, heapSize, smallest, opComp, opAttr);
    }
}

void buildMinHeap(Heap H[], int heapSize, Operation& opComp, Operation& opAttr)
{
    for (int i = heapSize / 2 - 1; i >= 0; i--)
        heapify(H, heapSize, i, opComp, opAttr);
}

// ANALIZA: FUNCTIE PENTRU EXTRAGEREA PRIMELOR ELEMENTE DIN FIECARE DIN CELE K LISTE GENERARE

void extractFirsts(NodeT* list[], Heap H[], int K)
{
    for (int i = 0; i < K; i++)
    {
        if (list[i] != NULL)
        {
            H[i].key = list[i]->key;
            H[i].index = currentIndex;
            currentIndex++;
            H[i].originList = i;
        }
    }
}

// ANALIZA: MERGES

NodeT* mergeTwoLists(NodeT* list1, NodeT* list2, Operation& opComp, Operation& opAttr)
{
    if (list1 == NULL)
        return list2;
    if (list2 == NULL)
        return list1;

    NodeT* mergedList = NULL;

    opComp.count();
    if (list1->key < list2->key)
    {
        opAttr.count(2);
        NodeT* temp = create(list1->key);
        mergedList = temp;
        list1 = list1->next;
    }
    else
    {
        opAttr.count(3);
        NodeT* temp = create(list2->key);
        mergedList = temp;
        list2 = list2->next;
    }

    NodeT* current = mergedList;
    while (list1 != NULL && list2 != NULL)
    {
        if (list1->key > list2->key)
        {
            opComp.count();
            opAttr.count(2);
            NodeT* temp = create(list2->key);
            current->next = temp;
            list2 = list2->next;
        }
        else
        {
            opComp.count();
            opAttr.count(2);
            NodeT* temp = create(list1->key);
            current->next = temp;
            list1 = list1->next;
        }
        current = current->next;
    }

    while (list1 != NULL)
    {
        opAttr.count(2);
        NodeT* temp = create(list1->key);
        current->next = temp;
        list1 = list1->next;
        current = current->next;
    }
    current->next = list1;

    while (list2 != NULL)
    {
        opAttr.count(2);
        NodeT* temp = create(list2->key);
        current->next = temp;
        list2 = list2->next;
        current = current->next;
    }

    return mergedList;
}

void kWayMerge(NodeT* list[], NodeT** O, Heap H[], int n, int K, Operation& opComp, Operation& opAttr)
{
   
    extractFirsts(list, H, K);
    buildMinHeap(H, K, opComp, opAttr);

    int heapSize = K - 1;
    NodeT* p = NULL;
    NodeT* q;
    *O = NULL;

    while (heapSize > 1)
    {
        opAttr.count();
        Heap Mins = H[0];

        if (*O == NULL)
        {
            opAttr.count(2);
            *O = create(H[0].key);

            opAttr.count();
            p = *O;
        }
        else
        {
            opAttr.count(2);
            q = create(Mins.key);

            opAttr.count();
            p->next = q;

            opAttr.count();
            p = q;
        }

        if (list[Mins.originList]->next != NULL)
        {
            opAttr.count(2);
            list[Mins.originList] = list[Mins.originList]->next;
            H[0].key = list[Mins.originList]->key;
            H[0].originList = Mins.originList;
        }
        else
        {
            opAttr.count();
            H[0] = H[heapSize];
            heapSize--;
        }

        heapify(H, heapSize, 0, opComp, opAttr);

    }

    NodeT* list3;
    opAttr.count(2);
    NodeT* list1 = list[H[1].originList];
    NodeT* list2 = list[H[0].originList];
    list3 = mergeTwoLists(list1, list2, opComp, opAttr);

    if (p != NULL)
    {
        opAttr.count();
        p->next = list3;
    }
        
}

// DEMO

void demo()
{
    Heap H[MAX_SIZE_DEMO];
    NodeT* O;
    NodeT* list[kDemo];

    generateKDemoLists(list, MAX_SIZE_DEMO, kDemo);

    kWayMergeDemo(list, &O, H, MAX_SIZE_DEMO, kDemo);

    NodeT* p = O;
    printOrderedList(p);
}

// ANALIZA 1 (k1, k2, k3 constante, n variaza)

void startAnalysisK1(int n)
{
    Heap Hk1[MAX_SIZE];
    NodeT* Ok1;
    NodeT* listK1[k1];

    Operation opComp = p.createOperation("InterclasareK1Liste.comp", n);
    Operation opAttr = p.createOperation("InterclasareK1Liste.attr", n);

    generateK1Lists(listK1, n, k1);
    kWayMerge(listK1, &Ok1, Hk1, n, k1, opComp, opAttr);

    p.addSeries("InterclasareK1Liste", "InterclasareK1Liste.attr", "InterclasareK1Liste.comp");
}

void startAnalysisK2(int n)
{
    Heap Hk2[MAX_SIZE];
    NodeT* Ok2;
    NodeT* listK2[k2];

    Operation opComp = p.createOperation("InterclasareK2Liste.comp", n);
    Operation opAttr = p.createOperation("InterclasareK2Liste.attr", n);

    generateK1Lists(listK2, n, k2);
    kWayMerge(listK2, &Ok2, Hk2, n, k2, opComp, opAttr);

    p.addSeries("InterclasareK2Liste", "InterclasareK2Liste.attr", "InterclasareK2Liste.comp");
}

void startAnalysisK3(int n)
{
    Heap Hk3[MAX_SIZE];
    NodeT* Ok3;
    NodeT* listK3[k3];

    Operation opComp = p.createOperation("InterclasareK3Liste.comp", n);
    Operation opAttr = p.createOperation("InterclasareK3Liste.attr", n);

    generateK1Lists(listK3, n, k3);
    kWayMerge(listK3, &Ok3, Hk3, n, k3, opComp, opAttr);

    p.addSeries("InterclasareK3Liste", "InterclasareK3Liste.attr", "InterclasareK3Liste.comp");
}

void perf1()
{
    int n;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        startAnalysisK1(n);
        startAnalysisK2(n);
        startAnalysisK3(n);
    }
    p.createGroup("InterclasareKListe", "InterclasareK1Liste", "InterclasareK2Liste", "InterclasareK3Liste");
    p.showReport();
}

// ANALIZA 2 (n constant, k variaza)

void insertK(NodeT* list[], int key, int k)
{
    NodeT* newEl = create(key);
    int index;
    index = hashFunction(k);

    if (list[index] == NULL)
    {
        list[index] = newEl;
    }
    else
    {
        newEl->next = list[index];
        list[index] = newEl;
    }
}

void generateKLists(NodeT* list[], int n, int k)
{
    int v[MAX_SIZE];
    FillRandomArray(v, n, 10, 1000, false, DESCENDING);

    for (int i = 0; i < k; i++)
    {
        list[i] = NULL;
    }

    for (int i = 0; i < n; i++)
        insertK(list, v[i], k);
}

void perf2()
{
    for (int k = K_STEP_SIZE; k <= K_MAX_SIZE; k += K_STEP_SIZE)
    {
        Heap H[K_n];
        NodeT* O;
        NodeT* list[K_n];

        Operation opComp = p.createOperation("InterclasareKVarListe.comp", k);
        Operation opAttr = p.createOperation("InterclasareKVarListe.attr", k);

        int indexes[K_MAX_SIZE];
        int indexesLeft = k;
        generateKLists(list, K_n, k);
        kWayMerge(list, &O, H, K_n, k, opComp, opAttr);
        p.addSeries("InterclasareKVarListe", "InterclasareKVarListe.attr", "InterclasareKVarListe.comp");
    }
    p.showReport();
}

int main()
{
    demo();
    // perf1();
    // perf2();
    return 0;
}
