/**
 * @author Iclodean Andrei-George
 * @group 30223
 *
 * Specificațiile problemei: Se cere implementarea corectă si eficienta a unor algoritmi de complexitate liniara pentru
 * transformarea arborilor multicai îintre urmatoarele reprezentari: R1, R2, R3.
 *
 * Interpretarea personală despre complexitate (timp și spațiu), despre cazurile de testare (favorabil,
 * mediu-statistic si nefavorabil):
 *
 * 1. Reprezentarea R1
 *
 *      Pentru realizarea reprezentarii R1 am folosit o structura ce are 2 elemente, "key", ce retine valoarea unui nod si "parent",
 * ce retine parintele acelui nod in reprezentarea arborelui folosind un vector de tati.
 * Mai apoi, am initializat aceasta structura folosind vectorul de tati dat pentru demo in laborator.
 *      Inainte de folosirea R1, aceasta este initializata pentru fiecare nod in parte.
 *
 * 2. Pretty Print R1
 *
 *      Pentru a realiza functia prettyPrintR1(), am folosit un vector de aparitii, pe care l-am initializat pe baza valorilor din
 * P[].parents.
 *      Am extras apoi radacina, si am cautat toti fiii acesteia, a caror numar de aparitii l-am crescut in vectorul ap[].
 * Apoi, am afisat radacina pe primul rand, iar apoi, pentru nodurile din ap[] care au o valoare ap[nod.key] diferita de 0, am afisat
 * pe urmatoarea linie 3 spatii si nod.key. Pentru fiecare nod din vectorul de tati care are valoarea parintelui egala cu nod.key, am
 * afisat 6 spatii pe linie noua si nod.key a carei valoare tocmai am gasit-o folosind conditia anterioara.
 *
 * 3. Reprezentarea R2
 *
 *      Pentru reprezentarea R2, am folosit doua structuri diferite (R2 si R21), intrucat am reusit Transformarea T2 doar prin a doua
 * varianta de structura.
 *      Prima structura (R2) are un camp key ce retine valoarea nodului si un vector de copii pentru nodul respectiv.
 * Ideea de declarare este de a avea un pointer la radacina arborelui, care mai apoi are un vector de copii, fiecare la randul sau avand
 * alt vector de copii etc. Prin aceasta abordare, am avut un numar maxim de copii pe care il poate avea fiecare nod (constanta KIDS),
 * fiind 3 in acest caz.
 *      A doua structura (R21) are acelasi camp key, insa foloseste o lista simplu inlantuita pentru pastrarea copiilor fiecarui nod.
 * Adaptez principiul de first si last al unei astfel de liste, avand un camp NodeT* children si un camp NodeT* lastChildren pe post de
 * last, dar si o variabila care numara numarul de copii al fiecareui nod. Astfel, ideea de implementare este de a avea un vector de astfel
 * de structuri, una pentru fiecare nod din arbore.
 *      Aceasta abordare presupune si initializarea listei inainte de folosire, fiecare nod in parte este initializat cu valoarea sa
 * (1,..., n), nil pentru children si lastChildren si 0 pentru numarul de copii (functiile initializeNodeR21() si initializeArrayR21()).
 *
 * 4. Transform T1
 *
 *      Folosind prima structura, realizez transformarea pentru fiecare nod din arbore, insa prima oara stabilesc radacina de la care se
 * va porni reprezentarea in memorie a arborelui.
 *      Pentru fiecare nod care este fiu al radacinii introduc in vectorul de fii al radacinii acel nod creat cu functia createNewNodeT1,
 * care creeaza o strucura de tip R2 pentru cheia care trebuie introdusa.
 *      Pentru fiecare nod din vecotrul de fii al radacinii aplic apoi acelasi algoritm.
 *
 *      Folosind a doua structura, este nevoie mai intai sa initializez fiecare nod din lista. Apoi, pentru fiecare nod care nu este
 * radacina, creez un nod de inserat in lista simplu inlantuita. Daca lista nodului curent a carui lista de fii o construiesc nu este
 * goala, ultimul copil este acum legat la nodul ce se insereaza, care devine acum ultimul copil. Numarul de copii creste.
 * Altfel, first (adica children al nodului curent), va deveni nodul care trebuie inserat, la fel si last pana la un evenetual urmator nod.
 * Numarul de copii creste si aici. Cu aceasta ocazie, salvez si radacina pentru a putea fi folosita mai tarziu in afisare.
 *
 * 5. Pretty Print R2
 *
 *      Pentru prettyPrintR2() afisez radacina pe prima linie, iar apoi pentru fiecare fiu al radacinii, 3 spatii si pentru fiecare din cei KIDS
 * (3 aici) copii ai radacinii, afisez 6 spatii si copilul.
 *
 * 6. Reprezentarea R3
 *
 *      Pentru reprezentarea R3 am folosit din nou doua liste simplu inlantuite, una pentru fiul din stanga si una pentru fiul din dreapta al fiecarui nod.
 * Fiecare lista va avea maxim un element adaugat (cea din stanga daca nodul are fii, iar cea din dreatpa daca are frati).
 *
 * 7. Transform T2
 *
 *      Este nevoie de o initializare a structurii folosite si pentru aceasta transformare prin care pun cheia fiecareui nod si initializez atat copilul stang
 * cat si cel drept cu 0.
 *      Apoi, parcurg fiecare indice in parte, si pentru nodul corespunzator, daca are copii, si pe legatura din stanga salvez fiul, daca are, iar pe cea
 * din dreapta copii etc.
 *
 * 8. Pretty Print R3
 *
 *      Penrtru prettyPrintR3() transform arborele binar creat intr-un nou vector de tati corespunzator unui arbore binar si nu unuia multicai si afisez apoi
 * acel vector in mod recursiv folosind o parcurgere in preordine.
 *
 */

#include <iostream>
#include "Profiler.h"

using namespace std;

Profiler p("lab6");

#define NODES 9 // in R1, arborele poate sa aiba maxim NODES noduri
#define KIDS 3 // in R2, fiecare nod poate sa aiba maxim KIDS noduri copil
#define NR_TESTS 5

// STRUCTURI

typedef struct node
{
    int key;
    struct node* next;
}NodeT;

typedef struct R1 // vector de tati
{
    int key;
    int parent;
};

typedef struct R2 // vector pt fiecare nod
{
    int key;
    R2* kids[KIDS];
};

typedef struct R21
{
    int key;
    NodeT* children;
    NodeT* finalChildren;
    int numberOfChildren;
};

typedef struct R3
{
    int key;
    NodeT* leftChild; // or child
    NodeT* rightSibling; // or sibling
};

// DEMO

void initializeR1(R1 P[], int parents[])
{
    for (int i = 0; i < NODES; i++)
    {
        P[i].key = i + 1;
        P[i].parent = parents[i];
    }
}

void prettyPrintR1(R1 P[])
{
    cout << "pretty print for R1 is: \n\n";

    int ap[NODES+1] = { 0 };
    int root;

    for (int i = 0; i < NODES; i++)
        if (P[i].parent == -1)
            root = P[i].key;

    for (int i = 0; i < NODES; i++)
        if (P[i].parent == root)
            ap[P[i].key]++;

    cout << root << "\n";

    for (int i = 0; i < NODES; i++)
        if (P[i].parent != -1 && ap[P[i].key] != 0)
        {
            cout << "   ";
            cout << P[i].key << "\n";
            for (int j = 0; j < NODES; j++)
                if (P[j].parent == P[i].key)
                    cout << "      " << P[j].key << "\n";
        }

    cout << "\n\n";
}

R2* createNewNodeT1(int key)
{
    R2* newNode = new R2;
    newNode->key = key;
    for (int i = 0; i < KIDS; i++)
        newNode->kids[i] = NULL;
    return newNode;
}

int findRootR1(R1 P[])
{
    for (int i = 0; i < NODES; i++)
        if (P[i].parent == -1)
            return P[i].key;

}

void transformT1Demo(R1 P[], R2* mWay)
{
    int counter = 0;

    mWay->key = findRootR1(P);

    for (int i = 0; i < NODES; i++)
        if (P[i].parent == mWay->key)
        {
            mWay->kids[counter] = createNewNodeT1(P[i].key);
            counter++;
        }

    for (int i = 0; i < KIDS; i++)
    {
        counter = 0;
        for (int j = 0; j < NODES; j++)
            if (P[j].parent == mWay->kids[i]->key)
            {
                mWay->kids[i]->kids[counter] = createNewNodeT1(P[j].key);
                counter++;
            }
    }
}

void prettyPrintR2(R2* mWay)
{
    cout << "pretty print for R2 is: \n\n";
    cout << mWay->key << "\n";
    for (int i = 0; i < KIDS; i++)
    {
        cout << "   " << mWay->kids[i]->key << "\n";
        for (int j = 0; j < KIDS; j++)
            if(mWay->kids[i]->kids[j] != NULL)
                cout << "      " << mWay->kids[i]->kids[j]->key << "\n";

    }
    cout << "\n\n";
}

R21 initializeNodeR21(R21 node, int key)
{
    node.key = key;
    node.children = NULL;
    node.finalChildren = NULL;
    node.numberOfChildren = 0;
    return node;
}

void initializeArrayR21(R21 mWay[], int n)
{
    for (int i = 0; i < n; i++)
        mWay[i] = initializeNodeR21(mWay[i], i + 1);
}

NodeT* create(int key)
{
    NodeT* q = (NodeT*)malloc(sizeof(NodeT));
    q->key = key;
    q->next = NULL;
    return q;
}

void transformT1usingSLL(R1 P[], R21 mWay[], int n, int& root)
{
    int i = 0;

    while(i < n)
    {
        int currentParent = P[i].parent;
        NodeT* childToInsert = create(P[i].key);

        if (childToInsert->key != findRootR1(P))
        {
            if (mWay[currentParent - 1].children != NULL)
            {
                mWay[currentParent - 1].finalChildren = childToInsert;
                mWay[currentParent - 1].finalChildren->next = childToInsert;
                mWay[currentParent - 1].numberOfChildren++;

            }
            else
            {
                mWay[currentParent - 1].children = childToInsert;
                mWay[currentParent - 1].finalChildren = childToInsert;
                mWay[currentParent - 1].numberOfChildren++;
            }
        }
        else
            root = childToInsert->key;

        i++;
    }
}

void printR21(R21 mWay[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "node: " << mWay[i].key << " has children: ";
        while (mWay[i].children != NULL)
        {
            cout << mWay[i].children->key << " ";
            mWay[i].children = mWay[i].children->next;
        }
        cout << "\n";
    }
}

void prettyPrintR21(R21 mWay[], int i)
{
    cout << "pretty prin for R21 is: \n";
}

R3 initializeNodeR3(R3 node, int key)
{
    node.key = key;
    node.leftChild = create(0);
    node.rightSibling = create(0);
    return node;
}

void initializeArrayR3(R3 binary[], int n)
{
    for (int i = 0; i < n; i++)
        binary[i] = initializeNodeR3(binary[i], i + 1);
}

void transformT2(R21 mWay[], R3 binary[], int n)
{
    int i = 0;

    while(i < n) // pe rand, fiecare nod din arbore
    {
        if (mWay[i].numberOfChildren) // daca nodul curent are copii
        {
            NodeT* childToInsert = mWay[i].children; // ia primul copil din lista de copii
            int currentParrent = mWay[i].key; // salveaza parintele lui
            int currentNumberOfChildren = 1; // numar copii parintelui salvat mai sus, pana sunt cati trebuie

            binary[currentParrent - 1].leftChild = mWay[i].children; // in left-ul nodului curent pune primul copil

            while (childToInsert->next != NULL) // cat timp parintele curent mai are copii
            {
                if (currentNumberOfChildren < mWay[i].numberOfChildren) // si numarul curent de copii nu este inca cel care trebuie sa fie pentru nodul curent
                {
                    currentParrent--;
                    currentParrent = childToInsert->key; // salveaza cheia copilului ca parinte curent
                    currentParrent--;
                    binary[currentParrent].rightSibling = childToInsert->next; // in dreeapta nodurlui curent (primul copil al nodului cu care am intrat), pune-l pe fratele sau
                    currentNumberOfChildren++; // creste counter-ul de copii pusi pana acum
                    childToInsert = childToInsert->next; // treci la urmatorul copil din lista de copii
                }
            }
        }
        i++;
    }
}

void printR3(R3 binary[], int n)
{
    cout << "key left right\n";
    for (int i = 0; i < n; i++)
    {
        cout << binary[i].key << ":  ";
        cout << binary[i].leftChild->key << "    ";
        cout << binary[i].rightSibling->key << "\n";
    }
}

// creeaza o lista de parinti pentru arborele binar din R3

void createParentListFromR3(R3 binary[], int parents[])
{
    for (int i = 0; i < NODES; i++)
        if (binary[i].leftChild->key != 0 && binary[i].rightSibling->key == 0)
        {
            parents[binary[i].key - 1] = -1;
            parents[binary[i].leftChild->key - 1] = binary[i].key;
            break;
        }

    for (int i = 0; i < NODES; i++)
        if (binary[i].leftChild->key != 0)
            parents[binary[i].leftChild->key - 1] = binary[i].key;

    for (int i = 0; i < NODES; i++)
        if (binary[i].rightSibling->key != 0)
            parents[binary[i].rightSibling->key - 1] = binary[i].key;
}

void preorder(int parents[], int n, int key, int ap[])
{
    for (int i = 0; i < n; i++)
        if (parents[i] == key)
        {
            if (ap[i + 1] == -1)
                cout << "   ";
            else cout << "      ";
            cout << i + 1 << "\n";
            preorder(parents, n, i + 1, ap);
        }
    return;
}

int findRootR3(R3 binary[], int n)
{
    for (int i = 0; i < NODES; i++)
        if (binary[i].leftChild->key != 0 && binary[i].rightSibling->key == 0)
            return binary[i].key;
}

void initializeAp(R3 binary[], int ap[], int n, int parents[])
{
    for (int i = 0; i < n; i++)
        if (parents[i] == findRootR3(binary, n))
            ap[i + 1] = -1;
}

void prettyPrintR3(R3 binary[], int parents[], int n, int ap[])
{
    cout << "pretty print for R3 is: \n\n";

    cout << findRootR3(binary, n) << "\n";

    createParentListFromR3(binary, parents);

    preorder(parents, n, findRootR3(binary, n), ap);
}

void demo()
{
    R1 P[NODES];
    R2* mWay1 = new R2;
    R21 mWay2[NODES];
    R3 binary[NODES];
    int parents[NODES] = { 2, 7, 5, 2, 7, 7, -1, 5, 2 };
    int rootR21 = 0;
    int p[NODES] = { 0 };
    int ap[NODES] = { 0 };

    initializeR1(P, parents);
    prettyPrintR1(P);

    transformT1Demo(P, mWay1);
    prettyPrintR2(mWay1);

    initializeArrayR21(mWay2, NODES);
    transformT1usingSLL(P, mWay2, NODES, rootR21);
    // printR21(mWay, NODES);

    initializeArrayR3(binary, NODES);
    transformT2(mWay2, binary, NODES);
    //printR3(binary, NODES);

    initializeAp(binary, ap, NODES, parents);
    prettyPrintR3(binary, p, NODES, ap);

    /*int p1[NODES] = {-1, 1, 2, 2, 2, 1, 6, 6, 1};
    int p2[NODES] = { -1, 1, 2, 2, 1, 5, 5, 5, 1 };
    int p3[NODES] = { -1, 1, 1, 3, 3, 3, 1, 7, 7 };
    int p4[NODES] = { -1, 1, 2, 2, 1, 5, 5, 5, 1 };
    int p5[NODES] = { -1, 1, 2, 2, 2, 1, 1, 7, 7 };*/

}

// ANALYSIS

void transformT1Analysis(R1 P[], R2* mWay, int n)
{
    Operation opAttr = p.createOperation("TransformT1.attr", n);
    Operation opComp = p.createOperation("TransformT1.comp", n);

    int counter = 0;

    opComp.count();
    opAttr.count();
    mWay->key = findRootR1(P);

    for (int i = 0; i < n; i++)
    {
        opComp.count();
        if (P[i].parent == mWay->key)
        {
            opAttr.count();
            mWay->kids[counter] = createNewNodeT1(P[i].key);
            counter++;
        }
    }

    for (int i = 0; i < KIDS; i++)
    {
        counter = 0;
        for (int j = 0; j < n; j++)
        {
            opComp.count();
            if (P[j].parent == mWay->kids[i]->key)
            {
                opAttr.count();
                mWay->kids[i]->kids[counter] = createNewNodeT1(P[j].key);
                counter++;
            }
        }

    }
    p.addSeries("TransformareT1", "TransformT1.attr", "TransformT1.comp");
    // P.showReport();

}

void transformT1usingSLLAnalysis(R1 P[], R21 mWay[], int n, int& root)
{
    Operation opAttr = p.createOperation("TransformT1SLL.attr", n);
    Operation opComp = p.createOperation("TransformT1SLL.comp", n);

    int i = 0;

    while (i < n)
    {
        opAttr.count(2);
        int currentParent = P[i].parent;
        NodeT* childToInsert = create(P[i].key);

        opComp.count();
        if (childToInsert->key != findRootR1(P))
        {
            opComp.count();
            if (mWay[currentParent - 1].children != NULL)
            {
                opAttr.count(2);
                mWay[currentParent - 1].finalChildren->next = childToInsert;
                mWay[currentParent - 1].finalChildren = childToInsert;
                mWay[currentParent - 1].numberOfChildren++;

            }
            else
            {
                opAttr.count(2);
                mWay[currentParent - 1].children = childToInsert;
                mWay[currentParent - 1].finalChildren = childToInsert;
                mWay[currentParent - 1].numberOfChildren++;
            }
        }
        else
            root = childToInsert->key;

        i++;
    }
    p.addSeries("TransformareT1SLL", "TransformT1SLL.attr", "TransformT1SLL.comp");
}

void startT1Analysis()
{
    R1 P[NODES];
    R2* multiWay = new R2;

    int v1[8] = { -1, 1, 1, 3, 3, 1, 6, 6 };
    int v2[9] = { -1, 1, 1, 3, 3, 3, 1, 7, 7 };
    int v3[10] = { -1, 1, 2, 2, 2, 1, 6, 6, 1, 9 };
    int v4[11] = { -1, 1, 2, 2, 1, 5, 5, 5, 1, 9, 9 };
    int v5[12] = { -1, 1, 2, 2, 1, 5, 5, 5, 1, 9, 9, 9 };
    int v6[13] = { -1, 1, 2, 2, 2, 1, 6, 6, 6, 1, 10, 10, 10 };


    initializeR1(P, v1);
    transformT1Analysis(P, multiWay, 8);

    initializeR1(P, v2);
    transformT1Analysis(P, multiWay, 9);

    initializeR1(P, v3);
    transformT1Analysis(P, multiWay, 10);

    initializeR1(P, v4);
    transformT1Analysis(P, multiWay, 11);

    initializeR1(P, v5);
    transformT1Analysis(P, multiWay, 12);

    initializeR1(P, v6);
    transformT1Analysis(P, multiWay, 13);

    p.showReport();
}

void startT1SLLAnalysis()
{
    R1 P[NODES];
    R21 mWay[NODES];
    int root = 0;

    int v1[8] = { -1, 1, 1, 3, 3, 1, 6, 6 };
    int v2[9] = { -1, 1, 1, 3, 3, 3, 1, 7, 7 };
    int v3[10] = { -1, 1, 2, 2, 2, 1, 6, 6, 1, 9 };
    int v4[11] = { -1, 1, 2, 2, 1, 5, 5, 5, 1, 9, 9 };
    int v5[12] = { -1, 1, 2, 2, 1, 5, 5, 5, 1, 9, 9, 9 };
    int v6[13] = { -1, 1, 2, 2, 2, 1, 6, 6, 6, 1, 10, 10, 10 };

    initializeR1(P, v1);
    initializeArrayR21(mWay, 8);
    transformT1usingSLLAnalysis(P, mWay, 8, root);

    initializeR1(P, v2);
    initializeArrayR21(mWay, 9);
    transformT1usingSLLAnalysis(P, mWay, 9, root);

    initializeR1(P, v3);
    initializeArrayR21(mWay, 10);
    transformT1usingSLLAnalysis(P, mWay, 10, root);

    initializeR1(P, v4);
    initializeArrayR21(mWay, 11);
    transformT1usingSLLAnalysis(P, mWay, 11, root);

    initializeR1(P, v5);
    initializeArrayR21(mWay, 12);
    transformT1usingSLLAnalysis(P, mWay, 12, root);

    initializeR1(P, v6);
    initializeArrayR21(mWay, 13);
    transformT1usingSLLAnalysis(P, mWay, 13, root);

    p.showReport();
}

int main()
{
    demo();
    // startT1Analysis();
    // startT1SLLAnalysis();
    return 0;
}
