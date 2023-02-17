/**
 * @author Iclodean Andrei-George
 * @group 30223
 *
 * Specificațiile problemei: Se cere implementarea corecta si eficienta a operatiilor de management ale unui arbore de
 * statistica de ordine
 *
 * Interpretarea personală despre complexitate (timp și spațiu), despre cazurile de testare (favorabil,
 * mediu-statistic si nefavorabil):
 *
 * 1. Build Tree
 *      Pentru construirea unui arbore binar de cautare echilibrat din sirul 1, 2, ..., n este folosita strategia
 * divide et impera. Este ales elementul din mijlocul sirului ca radacina si apoi, in mod recursiv, se apeleaza
 * functia de constructie pentru constructia subarborelui stang (de la inceput la jumatate - 1) si a celui drept
 * (de la jumatate + 1 la sfarsit). Pentru fiecare nod este calculat size-ul folosind functia findSize.
 * Complexitatea de timp a algoritmului este O(n).
 *
 * 2. Pretty Print
 *      Pentru functia de pretty print, fac o parcurgere in preordine a arborelui, afisand fiecare nod pe linie noua. Insa in vectorul
 * spaces am salvat adancimea fiecarui nod pentru a putea afisa numarul necesar de spatii inaintea nodului, astfel incat afisarea sa fie
 * formatata corect. De asemenea, am afisat dupa nod, intre paranteze, size-ul acestuia.
 *
 * 3. OS Select
 *      Subprogramul OS Select primeste ca parametrii arborele creat anterior si un index. Acesta returneaza nodul
 * al carui key este al i-lea cel mai mic dintre toate key-urile din arbore. Acest lucru este bazat pe campul size
 * al fiecarui nod.
 *      In cel mai rau caz, complexitatea de timp a algoritmului este proportionala cu inaltmiea arborelui.
 * Astfel, complexitatea de timp este O(lg n).
 *      Algoritmul este asemanastor celui de QuickSelect.
 *
 * 4. OS Delete
 *      Functia de OS Delete este asemanastoare steregrii obisnuite dintr-un arbore binar de cautare.
 *      Insa, deoarece este nevoie de recalcularea size-ului nodurior in urma stergerii unui anume nod, am implementat doua variante,
 * dintre care una mai eficienta ce nu adauga complexitate algoritmului.
 *      4.1. osDelete() calculeaza size-ul recursiv inainte de a returna radacina, folosind functia de calculare a size-ului pentru un nod
 * (mai ineficient)
 *      4.2. osDeleteDiffSize() calculeaza size-ul prin decrementarea acestuia la fiecare pas ajuns si inainte de stergere, fara a fi
 * necesara apelarea functiei recursive, fiind astfel mai eficient.
 * 5. Analiza
 *      Pentru evaluarea operatiilor de management am variat dimensiunea sirului (n) de la 100 la 10.000 cu un pas de 100. Apoi, pentru
 * 5 teste (NR_TESTS), am generat vectorul v cu numere de la 1, 2, ..., n din care am construit un arbore binar de cautrare echilibrat.
 * Apoi, am generat indexsi random de n ori, insa la fiecare generare, numarul maxim de indexsi a scazut cu 1, pentru a alege strict din
 * indexsii ramasi si a nu fi nevoit sa fac OS Select, iar mai apoi OS Delete, pentru un index care nu mai exista in arbore.
 * Am numarat operatiile si atribuirile in functiile de Build Tree, OS Select si OS Delete si apoi am impartit rezultatele la NR_TESTS.
 * In final am realizat suma operatiilor de atribuire si comparatie pentru fiecare valoare a lui n, dar si trei grafice.
 *
 */


#include <iostream>
#include "Profiler.h"

Profiler p("lab7");

using namespace std;

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5
#define N 11

typedef struct NodeT
{
    int key;
    struct NodeT* left;
    struct NodeT* right;
    int size;
}NodeT;

NodeT* create(int key)
{
    NodeT* node = (NodeT*)malloc(sizeof(NodeT));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->size = 0;
    return node;
}

// FUNCTII DE PRINT

void inorderPrint(NodeT* root)
{
    if (root != NULL)
    {
        inorderPrint(root->left);
        cout << root->key << " ";
        inorderPrint(root->right);
    }
}

void preorderPrint(NodeT* root)
{
    if (root != NULL)
    {
        cout << root->key << " " << "of size " << root->size << "\n";
        preorderPrint(root->left);
        preorderPrint(root->right);
    }
}

void prettyPrint(NodeT* root, int spaces[])
{
    if (root == NULL)
        return;

    for (int i = 0; i < spaces[root->key - 1]; i++)
        cout << "   ";
    cout << root->key << " (" << root->size << ")" << "\n";
    prettyPrint(root->left, spaces);
    prettyPrint(root->right, spaces);
}

// DEMO

int nodeSize(NodeT* root)
{
    if (root == NULL)
        return 0;

    return nodeSize(root->left) + nodeSize(root->right) + 1;
}

NodeT* buildTree(int v[], int left, int right, int &size)
{
    if (left > right)
        return NULL;

    int middle = (left + right) / 2;

    NodeT* root = (NodeT*)malloc(sizeof(NodeT));
    root = create(v[middle]);

    root->left = buildTree(v, left, middle - 1, size);
    root->right = buildTree(v, middle + 1, right, size);

    root->size = nodeSize(root->left) + nodeSize(root->right) + 1;

    return root;
}

int depth(NodeT* root, int key)
{
    if (root == NULL)
        return -1;

    int distance = -1;

    if (root->key == key)
        return distance + 1;

    distance = depth(root->left, key);
    if (distance >= 0)
        return distance + 1;

    distance = depth(root->right, key);
    if (distance >= 0)
        return distance + 1;

    return distance;
}

void initializeSpaces(NodeT* root, int v[], int n)
{
    for (int i = 0; i < n; i++)
        v[i] = depth(root, i + 1);
}

// seamana cu quickSelect
NodeT* osSelect(NodeT* root, int i)
{
    int r = nodeSize(root->left) + 1;
    // int r = root->left->size + 1;
    if (i == r)
        return root;
    else if (i < r)
        return osSelect(root->left, i);
    else
        return osSelect(root->right, i - r);
}

NodeT* smallestNode(NodeT* root)
{
    if (root == NULL)
        return NULL;

    NodeT* node = root;
    while (node->left != NULL)
        node = node->left;

    return node;
}

NodeT* osDelete(NodeT* root, int i)
{
    NodeT* node;

    if (root == NULL)
        return root;

    if (i < root->key)
        root->left = osDelete(root->left, i);
    else if (i > root->key)
        root->right = osDelete(root->right, i);
    else
    {
        if (!root->left)
        {
            node = root->right;
            free(root);
            return node;
        }
        else if (!root->right)
        {
            node = root->left;
            free(root);
            return node;
        }

        node = smallestNode(root->right);
        root->key = node->key;
        root->right = osDelete(root->right, node->key);
    }

    root->size = nodeSize(root->left) + nodeSize(root->right) + 1;
    return root;
}

// functie de delete in care size-ul este modificat nerecursiv
NodeT* osDeleteDiffSize(NodeT* root, int i)
{
    NodeT* node;
    if (root == NULL)
        return root;
    if (i < root->key)
    {
        (root->size)--;
        root->left = osDelete(root->left, i);
    }

    else if (i > root->key)
    {
        (root->size)--;
        root->right = osDelete(root->right, i);
    }
    else
    {
        if (root->left == NULL)
        {
            node = root->right;
            (node->size)--;
            free(root);
            return node;
        }
        else if (root->right == NULL)
        {
            node = root->left;
            (node->size)--;
            free(root);
            return node;
        }
        node = smallestNode(root->right);
        root->key = node->key;
        root->right = osDelete(root->right, node->key);
    }

    return root;
}

int randomIndex(int n)
{
    return rand() % (n + 1 - 1) + 1;
}

void demo()
{
    int v[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    NodeT* tree = (NodeT*)malloc(sizeof(NodeT));
    int size = 0;
    int spaces[N] = { 0 };

    tree = buildTree(v, 0, N - 1, size);

    //preorderPrint(tree);
    cout << "initial tree is:\n";
    initializeSpaces(tree, spaces, N);
    prettyPrint(tree, spaces);
    cout << "\n";

    //tree = osDelete(tree, 7);
    //preorderPrint(tree);
    //cout << "\n";
    //tree = osDelete(tree, 6);
    //preorderPrint(tree);
    //cout << "\n";
    //tree = osDelete(tree, 11);
    //preorderPrint(tree);

    // gaseste al 3 lea, 5 lea si 9 lea cel mai mic element si delete

    // 3rd smallest key find and delete
    NodeT* x = osSelect(tree, 3);
    cout << 3 << "rd smallest key is: " << x->key << "\n\n";
    cout << "deleting key: " << x->key << "\n";
    tree = osDelete(tree, x->key);
    initializeSpaces(tree, spaces, N);
    prettyPrint(tree, spaces);
    cout << "\n";

    // 5th smallest key find and delete
    x = osSelect(tree, 5);
    cout << 5 << "th smallest key is: " << x->key << "\n\n";
    cout << "deleting key: " << x->key << "\n";
    tree = osDelete(tree, x->key);
    initializeSpaces(tree, spaces, N);
    prettyPrint(tree, spaces);
    cout << "\n";

    // 9th smallest key find and delete
    x = osSelect(tree, 9);
    cout << 9 << "th smallest key is: " << x->key << "\n\n";
    cout << "deleting key: " << x->key << "\n";
    tree = osDelete(tree, x->key);
    initializeSpaces(tree, spaces, N);
    prettyPrint(tree, spaces);
    cout << "\n";
}

// ANALIZA OPERATIILOR DE MANAGEMENT (BUILD, SELECT, DELETE)

NodeT* buildTreeAnalysis(int v[], int left, int right, int& size, Operation& opComp, Operation& opAttr)
{
    if (left > right)
        return NULL;

    int middle = (left + right) / 2;

    opAttr.count();
    NodeT* root = create(v[middle]);

    root->left = buildTree(v, left, middle - 1, size);
    root->right = buildTree(v, middle + 1, right, size);

    root->size = nodeSize(root->left) + nodeSize(root->right) + 1;

    return root;
}

int selectRandomIndex(int v[], int maxIndex)
{
    int index;

    index = rand() % maxIndex + 1;
    return index;
}

// functie pentru a genera un index random din cele ramase dupa fiecare selectie
int nodeSizeAnalysis(NodeT* root, Operation& opComp, Operation& opAttr)
{
    if (root == NULL)
        return 0;

    return nodeSizeAnalysis(root->left, opComp, opAttr) + nodeSizeAnalysis(root->right, opComp, opAttr) + 1;
}

NodeT* osSelectAnalysis(NodeT* root, int i, Operation& opComp, Operation& opAttr)
{
    opAttr.count();
    int r = nodeSizeAnalysis(root->left, opComp, opAttr) + 1;
    // int r = root->left->size + 1;
    opComp.count();
    if (i == r)
        return root;
    else
    {
        opComp.count();
        if (i < r)
            return osSelectAnalysis(root->left, i, opComp, opAttr);
        else
            return osSelectAnalysis(root->right, i - r, opComp, opAttr);
    }
}

NodeT* smallestNodeAnalysis(NodeT* root, Operation& opComp, Operation& opAttr)
{
    if (root == NULL)
        return NULL;

    NodeT* node = root;
    while (node->left != NULL)
        node = node->left;

    return node;
}

NodeT* osDeleteAnalysis(NodeT* root, int i, Operation& opComp, Operation& opAttr)
{
    NodeT* node;
    if (root == NULL)
        return root;
    opComp.count();
    if (i < root->key)
        root->left = osDeleteAnalysis(root->left, i, opComp, opAttr);
    else
    {
        opComp.count();
        if (i > root->key)
            root->right = osDeleteAnalysis(root->right, i, opComp, opAttr);
        else
        {
            if (root->left == NULL)
            {
                node = root->right;
                free(root);
                return node;
            }
            else if (root->right == NULL)
            {
                node = root->left;
                free(root);
                return node;
            }

            opAttr.count(2);
            node = smallestNode(root->right);
            root->key = node->key;
            root->right = osDeleteAnalysis(root->right, node->key, opComp, opAttr);
        }
    }
    root->size = nodeSizeAnalysis(root->left, opComp, opAttr) + nodeSizeAnalysis(root->right, opComp, opAttr) + 1;
    return root;
}

void osAnalysis()
{
    int v[MAX_SIZE];
    int n;

    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        for (int test = 0; test < NR_TESTS; test++)
        {
            NodeT* tree = (NodeT*)malloc(sizeof(NodeT));
            NodeT* find = (NodeT*)malloc(sizeof(NodeT));
            int size = 0;
            int ap[MAX_SIZE] = { 0 };
            int maxIndex = n;
            Operation opComp = p.createOperation("OS.comp", n);
            Operation opAttr = p.createOperation("OS.attr", n);

            // sir cu elemente de la 1 la n si construire arbore din el
            FillRandomArray(v, n, 1, n, true, ASCENDING);
            tree = buildTreeAnalysis(v, 0, n - 1, size, opComp, opAttr);

            for (int i = 0; i < n; i++)
            {
                int index = selectRandomIndex(v, maxIndex);
                maxIndex--; // numarul de indexsi ramasi in arbore, din care se poate alege
                find = osSelectAnalysis(tree, index, opComp, opAttr);
                tree = osDeleteAnalysis(tree, find->key, opComp, opAttr);
            }
        }
    }
    p.divideValues("OS.attr", NR_TESTS);
    p.divideValues("OS.comp", NR_TESTS);
    p.addSeries("OS", "OS.comp", "OS.attr");
    p.showReport();
}

int main()
{
    demo();
    // osAnalysis();

    return 0;
}
