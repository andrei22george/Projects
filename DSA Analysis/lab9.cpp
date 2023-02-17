/**
 * @author Iclodean Andrei-George
 * @group 30223
 *
 * Specificațiile problemei: Se cere implementarea corecta si eficienta a operatiilor de baza pe multimi disjuncte (capitolul
 * 21.1 din carte ) si a algoritmului lui Kruskal (gasirea arborelui de acoperire minima) folosind multimi disjuncte (capitolul 23.2).
 *
 * Interpretarea personală despre complexitate (timp și spațiu), despre cazurile de testare (favorabil,
 * mediu-statistic si nefavorabil):
 * 
 * 1. Operatiile pe multimi disjuncte
 *      Pentru implementarea operatiilor Make-Set, Find-Set si Union, am folosit implementarea din carte. Pentru demo-ul acestei functii am
 * folosit exemplul din Cormen, mai precis figura 21.4, pentru care am afisat pentru fiecare nod in urma operatiilor, parintele suprem si
 * parintele, fiind aplicata euristica union by rank (la functia de Union) si path compression (la functia de Find-Set).
 * 
 * 2. Reprezentare grafului in memorie
 *      Pentru reprezentarea grafului in memorie am foloit o structura ce contine numarul de noduri din graf, numarul de muchii (folosesc in 
 * special pentru partea de analiza a operatiilor pe multimi disjuncte folosind Kruskal), un vector de noduri si un vector de muchii.
 * Muchiile in sine sunt o alta structura, ele avand cele doua extremitati si ponderea (weight-ul) fiecareia.
 *      Pentru constructia arborelui, se primesc ca parametrii 4 siruri, anume: un sir de noduri, un sir de extremitati de start, un sir de
 * extremitati de end si un sir de ponderi pentru fiecare muchie.
 * 
 * 3. Algoritmul lui Kruskal
 *      Pentru implementarea algoritmului lui Kruskal de gasire a MST, trimit ca parametrii subprogramului 2 structuri de tipul graf (G si A),
 * unde G este graful dat, iar A va fi MST-ul rezultat.
 *      Apoi, pentru fiecare nod din vectorul de noduri, apelez functia Make-Set si creez si un vector de Set-uri, unde se gasesc Set-urile create
 * pentru fiecare nod din graf. Urmeaza sortarea tuturor muchiilor in functie de ponderea lor.
 * Apoi, pentru fiecare muchie, caut setul corespunzator varfului de inceput al muchiei (u pentru o muchie (u, v)), in functie de key, prin
 * vectorul de Set-uri creat anterior. Analog si pentru varful de final al muchiei (v pentru o muchie (u, v)). Salvez cele doua set-uri gasite,
 * iar daca Find-Set(u) != Find-Set(v), adaug muchia gasita in graful A si apelez functia Union.
 * 
 * 4. Evaluarea operatiilor pe multimi disjuncte folosind algoritmul lui Kruskal
 *      Pentru a evalua operatiile pe multimi disjuncte prin intermediul Kruskal, am generat, pentru fiecare n, sirurile cu care construiesc
 * graful dupa urmatorul model:
 *      i. Sirul de noduri contine elemente n elemente de la 0 la n - 1 sortate crescator
 *      ii. Sirul de noduri de inceput de muchii ce contine 4 * n elemente, de la 0 la n - 1, iar apoi de la pozitia n - 1 la 4 * n, 
 *          elemente random din multimea de noduri
 *      iii. Sirul de noduri de final de muchii ce contine 4 * n elemente, de la 1 la n, iar apoi de la pozitia n - 1 la 4 * n, 
 *           elemente random din multimea de noduri, dar diferite de elementul de la aceeasi pozitie din vectorul creat la ii. pentru a nu avea
 *           o muchie de forma (u, u).
 *      Prin pasii ii. si iii. ma asigur ca graful este conex, neorientat si aleatoriu si are 4 * n muchii.
 *      iv. Sirul de ponderi care genereaza 4 * n ponderi cu valori intre 1 si 50, una pentru fiecare muchie.
 * In final, in functia KruskalOperations() numar folosind variabila Operation opSet operatiile pe multimi disjuncte.
 * 
 */

#include <iostream>
#include "Profiler.h"

Profiler p("lab9");

using namespace std;

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define N_demo 9

// STRUCTURI

typedef struct SetD
{
    char key;
    struct SetD* parent;
    int rank;
}SetD;

typedef struct Set
{
    int key;
    struct Set* parent;
    int rank;
}Set;

typedef struct Edge
{
    Set* start; // u
    Set* end; // v
    int weight;
}Edge;

typedef struct muchie
{
    int start; // u
    int end; // v
    int weight;
}muchie;

typedef struct
{
    int numOfNodes; // nmumarul de noduri
    int numOfEdges; // numarul de muchii (pentru analiza va fi n * 4 constant)
    int* nodes; // sirul de noduri nodes[numOfNodes]
    // Edge arrayEdges[400]; // sirul de muchii de tip Edge
    muchie arrayMuchii[4 * MAX_SIZE];

}graf;

// DEMO

SetD* makeSetDemo(char key)
{
    SetD* x = (SetD*)malloc(sizeof(SetD));
    x->parent = x;
    x->rank = 0;
    x->key = key;
    return x;
}

void linkDemo(SetD* x, SetD* y)
{
    if (x->rank > y->rank)
        y->parent = x;
    else
    {
        x->parent = y;
        if (x->rank == y->rank)
            y->rank = y->rank + 1;
    }   
}

SetD* findSetDemo(SetD* x)
{
    if (x != x->parent)
        x->parent = findSetDemo(x->parent);
    return x->parent;
}

void unionSetDemo(SetD* x, SetD* y)
{
    linkDemo(findSetDemo(x), findSetDemo(y));
}

void printSetDemo(SetD* x)
{
    cout << "member key: " << x->key;
    cout << " / representative key: " << findSetDemo(x)->key;
    cout << " / parent key is: " << x->parent->key << "\n";
}

// KRUSKAL

Set* makeSet(int key)
{
    Set* x = (Set*)malloc(sizeof(Set));
    x->parent = x;
    x->rank = 0;
    x->key = key;
    return x;
}

void link(Set* x, Set* y)
{
    if (x->rank > y->rank)
        y->parent = x;
    else
    {
        x->parent = y;
        if (x->rank == y->rank)
            y->rank = y->rank + 1;
    }
}

Set* findSet(Set* x)
{
    if (x != x->parent)
        x->parent = findSet(x->parent);
    return x->parent;
}

Set* findSetOperations(Set* x, Operation &opSet)
{
    if (x != x->parent)
    {
        opSet.count();
        x->parent = findSet(x->parent);
    }
    return x->parent;
}

void unionSetOperations(Set* x, Set* y, Operation &opSet)
{
    link(findSetOperations(x, opSet), findSetOperations(y, opSet));
}

void unionSet(Set* x, Set* y)
{
    link(findSet(x), findSet(y));
}

void printSet(Set* x)
{
    cout << "node key: " << x->key << "\n";
}

void buildGraph(graf* G, int n, int m, int nodes[], int start[], int end[], int weight[])
{
    G->numOfNodes = n;
    G->numOfEdges = m;
    G->nodes = (int*)calloc(G->numOfNodes, sizeof(int));

    for (int i = 0; i < G->numOfNodes; i++)
        G->nodes[i] = nodes[i];

    for (int i = 0; i < m; i++)
    {
        G->arrayMuchii[i].start = start[i];
        G->arrayMuchii[i].end = end[i];
        G->arrayMuchii[i].weight = weight[i];
    }
}

void printAdjList(graf* G)
{
    cout << "number of nodes: " << G->numOfNodes << "\n";
    for (int i = 0; i < G->numOfNodes; i++)
    {
        cout << "node: " << G->nodes[i] << " has edges: ";
        for (int j = 0; j < G->numOfEdges; j++)
            if (G->arrayMuchii[j].start == G->nodes[i] || G->arrayMuchii[j].end == G->nodes[i])
                cout << "(" << G->arrayMuchii[j].start << ", " << G->arrayMuchii[j].end << ", " << G->arrayMuchii[j].weight << ") ";
        cout << "\n";
    }
    cout << "\n";
}

void printEdges(graf* G)
{
    for (int i = 0; i < G->numOfEdges; i++)
        cout << G->arrayMuchii[i].start << ", " << G->arrayMuchii[i].end << " of weight " << G->arrayMuchii[i].weight << "\n";
    cout << "\n";
}

void sortEdges(graf* G)
{
    for (int i = 0; i < G->numOfEdges; i++)
        for (int j = 0; j < G->numOfEdges; j++)
            if (G->arrayMuchii[i].weight < G->arrayMuchii[j].weight)
            {
                swap(G->arrayMuchii[i].start, G->arrayMuchii[j].start);
                swap(G->arrayMuchii[i].end, G->arrayMuchii[j].end);
                swap(G->arrayMuchii[i].weight, G->arrayMuchii[j].weight);
            }
}

graf* Kruskal(graf* G, graf* A)
{
    int numOfEdgesA = 0; // nuamrul de muchii al MST rezultat (urmeaza sa fie determinat cu fiecare muchie adaugata in MST)

    Set* setList[MAX_SIZE]; // lista seturilor facute din nodurile lui G

    for (int i = 0; i < G->numOfNodes; i++)
        setList[i] = makeSet(G->nodes[i]);

    sortEdges(G);

    for (int i = 0; i < G->numOfEdges; i++)
    {
        Set* u = (Set*)malloc(sizeof(Set));
        Set* v = (Set*)malloc(sizeof(Set));

        for (int j = 0; j < G->numOfNodes; j++) // caut prin lista de set-uri, cel care are key-ul = u din muchia (u, v)
        {
            if (G->arrayMuchii[i].start == setList[j]->key)
                u = setList[j];
        }
        for (int j = 0; j < G->numOfNodes; j++) // caut prin lista de set-uri, cel care are key-ul = v din muchia (u, v)
        {
            if (G->arrayMuchii[i].end == setList[j]->key)
                v = setList[j];
        }

        if (findSet(u) != findSet(v))
        {
            // adauga in A muchia (u, v)
            A->arrayMuchii[numOfEdgesA].start = G->arrayMuchii[i].start;
            A->arrayMuchii[numOfEdgesA].end = G->arrayMuchii[i].end;
            A->arrayMuchii[numOfEdgesA].weight = G->arrayMuchii[i].weight;
            numOfEdgesA++;
            unionSet(v, u);
        }

    }
    A->numOfEdges = numOfEdgesA;
    return A;
}

graf* KruskalOperations(graf* G, graf* A)
{
    Operation opSet = p.createOperation("OperatiiSeturi", G->numOfNodes);
    
    int numOfEdgesA = 0;

    Set* setList[MAX_SIZE];

    opSet.count(G->numOfNodes);
    for (int i = 0; i < G->numOfNodes; i++)
        setList[i] = makeSet(G->nodes[i]);

    sortEdges(G);

    for (int i = 0; i < G->numOfEdges; i++)
    {
        Set* u = (Set*)malloc(sizeof(Set));
        Set* v = (Set*)malloc(sizeof(Set));

        for (int j = 0; j < G->numOfNodes; j++)
        {
            if (G->arrayMuchii[i].start == setList[j]->key)
                u = setList[j];
        }
        for (int j = 0; j < G->numOfNodes; j++)
        {
            if (G->arrayMuchii[i].end == setList[j]->key)
                v = setList[j];
        }

        opSet.count(2);
        if (findSetOperations(u, opSet) != findSetOperations(v, opSet))
        {
            A->arrayMuchii[numOfEdgesA].start = G->arrayMuchii[i].start;
            A->arrayMuchii[numOfEdgesA].end = G->arrayMuchii[i].end;
            A->arrayMuchii[numOfEdgesA].weight = G->arrayMuchii[i].weight;
            numOfEdgesA++;
            opSet.count(2); // union apeleaza link, iar apoi in link de 2 ori find set
            unionSetOperations(v, u, opSet);
        }
    }
    A->numOfEdges = numOfEdgesA;
    return A;
}

int totalWeightOfMST(graf* G)
{
    int sum = 0;

    for (int i = 0; i < G->numOfEdges; i++)
        sum += G->arrayMuchii[i].weight;
    return sum;
}

void demo()
{
    SetD* a = (SetD*)malloc(sizeof(SetD));
    SetD* b = (SetD*)malloc(sizeof(SetD));
    SetD* c = (SetD*)malloc(sizeof(SetD));
    SetD* d = (SetD*)malloc(sizeof(SetD));
    SetD* e = (SetD*)malloc(sizeof(SetD));
    SetD* f = (SetD*)malloc(sizeof(SetD));
    SetD* g = (SetD*)malloc(sizeof(SetD));
    SetD* h = (SetD*)malloc(sizeof(SetD));

    a = makeSetDemo('A');
    b = makeSetDemo('B');
    c = makeSetDemo('C');
    d = makeSetDemo('D');
    e = makeSetDemo('E');
    f = makeSetDemo('F');
    g = makeSetDemo('G');
    h = makeSetDemo('H');

    printSetDemo(a);
    printSetDemo(b);
    printSetDemo(c);
    printSetDemo(d);
    printSetDemo(e);
    printSetDemo(f);
    printSetDemo(g);
    printSetDemo(h);
    cout << "\n";

    unionSetDemo(d, f);
    unionSetDemo(g, d);
    
    printSetDemo(f);
    printSetDemo(g);
    printSetDemo(d);
    cout << "\n";

    unionSetDemo(h, c);
    unionSetDemo(e, c);
    unionSetDemo(b, h);
    printSetDemo(c);
    printSetDemo(h);
    printSetDemo(b);
    printSetDemo(e);
    cout << "\n";

    unionSetDemo(e, g);
    printSetDemo(a);
    printSetDemo(b);
    printSetDemo(c);
    printSetDemo(d);
    printSetDemo(e);
    printSetDemo(f);
    printSetDemo(g);
    printSetDemo(h);
    cout << "\n";

    int nodes[N_demo] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    int start[14] = { 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 2, 3, 6 };
    int end[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 7, 7, 5, 8, 5, 8 };
    int weight[14] = { 4, 8, 7, 9, 10, 2, 1, 7, 8, 11, 4, 2, 14, 6 };

    /*int nodes1[4] = {0, 1, 2, 3};
    int start1[5] = { 0, 1, 2, 0, 0 };
    int end1[5] = { 1, 3, 3, 2, 3 };
    int weight1[5] = { 10, 15, 4, 6, 5 };*/

    graf* G = (graf*)malloc(sizeof(graf));
    graf* A = (graf*)malloc(sizeof(graf));

    buildGraph(G, N_demo, 14, nodes, start, end, weight);

    printAdjList(G);
    printEdges(G);

    //sortEdges(G);

    //printEdges(G);

    A = Kruskal(G, A);
    printEdges(A);

    cout << "MST weight is: " << totalWeightOfMST(A)<<"\n";
}

void print(int a[], int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << "\n\n";
}

void kruskalAnalysis()
{
    int nodesVector[MAX_SIZE];
    int startVector[4 * MAX_SIZE];
    int endVector[4 * MAX_SIZE];
    int weightVector[4 * MAX_SIZE];
    int n, toInsert;

    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        FillRandomArray(nodesVector, n, 0, n - 1, true, ASCENDING);
        FillRandomArray(startVector, n - 1, 0, n - 2, true, ASCENDING);
        FillRandomArray(endVector, n - 1, 1, n - 1, true, ASCENDING);
        FillRandomArray(weightVector, 4 * n, 1, 50, false, UNSORTED);

        for(int i = n - 1; i < 4 * n; i++)
            startVector[i] = rand() % n;

        for (int i = n - 1; i < 4 * n; i++)
        {
            toInsert = rand() % n;
            while (startVector[i] == toInsert)
            {
                toInsert = rand() % n;
            }
            endVector[i] = toInsert;
        }
            
        graf* G = (graf*)malloc(sizeof(graf));
        graf* A = (graf*)malloc(sizeof(graf));

        buildGraph(G, n, 4 * n, nodesVector, startVector, endVector, weightVector);

        //printAdjList(G);
        //printEdges(G);

        //sortEdges(G);

        //printEdges(G);

        A = KruskalOperations(G, A);
        //printEdges(A);

        //cout << "MST weight is: " << totalWeightOfMST(A) << "\n";

        //print(nodesVector, n);
        //print(startVector, 4 * n);
        //print(endVector, 4 * n);
        //print(weightVector, 4 * n);

    }
    p.showReport();


}

int main()
{
    demo();
    // kruskalAnalysis();
    return 0;
}
