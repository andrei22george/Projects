/**
 * @author Iclodean Andrei-George
 * @group 30223
 * 
 * 
 * Specificațiile problemei: Se cere implementarea corectă și eficientă a algoritmului de căutare în adâncime 
 * (Depth-First Search - DFS). Pentru reprezentarea grafurilor va trebui să folosești liste de adiacență.
 * De asemenea va trebui să: Implementarea algoritmului Tarjan pentru componente tare conexe
 * Implementezi sortarea topologică (vezi capitolul 22.4)

 * 
 * Interpretarea personală despre complexitate (timp și spațiu), despre cazurile de testare (favorabil, 
 * mediu-statistic si nefavorabil):
 * 
 * 1. DFS   
 *     Pentru implementarea DFS am folosit reprezentarea grafului cu ajutorul listelor de adiacenta. Fiecare nod are mai multe
 * atribute precum key, color, timpul de descoperire, timpul de finalizare, parintele, lungimea listei de adiacenta si lista sa de
 * adiacenta in sine.
 *    Complexitatea de timp a alogritmlui este O(V + E), unde V este numarul de varfuri, iar E numarul de arce.
 * 
 * 2. Sortare Topologica
 *      Pentru a implementa sortarea topologica, am folosit aceeasi structura a grafului ca in cazul DFS si am modificat functia de
 * DFS, astfel incat la finalizarea fiecarui nod, acesta este adaugat primul intr-o lista simplu inltnatuita. La final, lista este
 * afisata cu key-ul, timpul de descoperire / timpul de finalizare al fiecarui element (nod) din ea.
 * 
 * 3. Tarjan
 *      Pentru implementarea Algoritmului lui Tarjan de gasire a SCC am folosit o noua structura pentru reprezentarea grafului bazata
 * tot reprezentarea folosind liste de adiacenta, insa fiecare nod are niste atribuite diferite corespunzatoare algoritmului in cauza:
 * key, index, lowLink, comp, onStack, adjSize si lista de adiacenta in sine.
 *      Complexitatea de timp a algoritmului este O (V + E).
 * 
 * 4. Evaluarea performantei algoritmului DFS
 *      Pentru a evalua performanta algoritmului DFS am creat grafuri in care am variat numarul de arce, respectiv numarul de noduri,
 * tinand insa cont sa nu generez acelasi arc de doua ori. Aatfel, generez doua noduri random, unul destinatie si unul care urmeaza a
 * fi introdus si folosind functia checkEdges() verific daca nodul selectat pentru a fi introdus se afla deja in lista de adiacenta
 * a nodului destinatie. In cazul in care se afla, generez un alt nod, pana cand acesta este la prima aparitie in lista de adiacenta a
 * nodului destinatie.
 *
 */
#include <iostream>
#include "Profiler.h"

Profiler p("lab11");

using namespace std;

// DFS si SORTARE TOPOLOGICA

typedef struct Node
{
    int key;
    int color;
    int discoveryTime;
    int finalTime;
    struct Node* parent;
    int adjSize;
    struct Node** adj;
}Node;

typedef struct Graph
{
    int nrNodes;
    Node** v;
}Graph;

typedef struct listNode
{
    Node* v;
    struct listNode* next;
}listNode;

enum
{
    COLOR_WHITE,
    COLOR_GRAY,
    COLOR_BLACK
};

listNode* create(Node* node)
{
    listNode* q = (listNode*)malloc(sizeof(listNode));
    q->v = node;
    q->next = NULL;
    return q;
}

void insertInFront(listNode** list, Node* v)
{
    listNode* q = create(v);
    if (*list == NULL)
        *list = q;
    else
    {
        q->next = *list;
        *list = q;
    }
}

void printList(listNode* first)
{
    cout << "topological sort using dfs on a dag is:\n";
    for (listNode* i = first; i != NULL; i = i->next)
        cout << i->v->key << " (" << i->v->discoveryTime << "/" << i->v->finalTime << ")  ";
    cout << "\n";
}

void dfsVisit(Graph* graph, Node* v, int& time)
{
    time = time + 1;
    v->discoveryTime = time;
    v->color = COLOR_GRAY;

    for (int i = 0; i < v->adjSize; i++)
    {
        if (v->adj[i]->color == COLOR_WHITE)
        {
            v->adj[i]->parent = v;
            dfsVisit(graph, v->adj[i], time);
        }
    }
    v->color = COLOR_BLACK;
    time = time + 1;
    v->finalTime = time;
}

void dfs(Graph* graph, int& time) // to add Operation
{
    for (int i = 0; i < graph->nrNodes; i++)
    {
        graph->v[i]->color = COLOR_WHITE;
        graph->v[i]->parent = NULL;
    }

    time = 0;

    for (int i = 0; i < graph->nrNodes; i++)
        if (graph->v[i]->color == COLOR_WHITE)
            dfsVisit(graph, graph->v[i], time);
}

void dfsVisitTopologicalSort(Graph* graph, Node* v, int& time, listNode** list)
{
    time = time + 1;
    v->discoveryTime = time;
    v->color = COLOR_GRAY;

    for (int i = 0; i < v->adjSize; i++)
    {
        if (v->adj[i]->color == COLOR_WHITE)
        {
            v->adj[i]->parent = v;
            dfsVisitTopologicalSort(graph, v->adj[i], time, list);
        }
    }
    v->color = COLOR_BLACK;
    time = time + 1;
    v->finalTime = time;
    insertInFront(list, v); // as each vertex is finished, insert it onto the front of a linked list
}

void dfsTopologicalSort(Graph* graph, int& time, listNode** list)
{
    for (int i = 0; i < graph->nrNodes; i++)
    {
        graph->v[i]->color = COLOR_WHITE;
        graph->v[i]->parent = NULL;
    }

    time = 0;

    for (int i = 0; i < graph->nrNodes; i++)
        if (graph->v[i]->color == COLOR_WHITE)
            dfsVisitTopologicalSort(graph, graph->v[i], time, list);
}

void topologicalSort(Graph* graph, int& time)
{
    listNode* list = NULL;
    dfsTopologicalSort(graph, time, &list);

    printList(list);

}

int k = 0;

void preorder(int p[], int n, int key, int order[])
{
    for (int i = 0; i < n; i++)
        if (p[i] == key)
        {
            // cout << i << " ";
            order[k] = i;
            k++;
            preorder(p, n, i, order);
        }
    return;
}

void graphToParentArray(Graph* graph, int p[], int n)
{
    for (int i = 0; i < graph->nrNodes; i++)
    {
        if (graph->v[i]->parent == NULL)
            p[i] = -1;
        else
            p[i] = graph->v[i]->parent->key;
    }
}

void printDFStree(Graph* graph)
{
    int n = graph->nrNodes;
    int* spaces = (int*)calloc(n, sizeof(int));
    int* order = (int*)calloc(n, sizeof(int));
    int* p = (int*)calloc(n, sizeof(int));

    graphToParentArray(graph, p, n);

    for (int i = 0; i < n; i++)
    {
    int i2 = i;
    if (p[i2] == -1)
        spaces[i] = 0;
    else
        while (p[i2] != -1)
        {
            i2 = p[i2];
            spaces[i]++;
        }
    }

    /*cout << "parrent array is:\n";
    for (int i = 0; i < n; i++)
        cout << p[i] << " ";
    cout << "\n";*/

    preorder(p, n, -1, order);

    cout << "DFS tree is:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < spaces[order[i]]; j++)
            cout << "    ";
        cout << "(" << order[i] << ")" << "\n";
    }
    cout << "\n";

    k = 0;
    free(order);
    free(spaces);

    if (p != NULL) {
        free(p);
        p = NULL;
    }
}

void printAdjList(Graph* graph)
{
    cout << "adjacency lists:\n";
    for (int i = 0; i < graph->nrNodes; i++)
    {
        cout << "(" << graph->v[i]->adjSize << ") " << graph->v[i]->key << ": ";
        for (int j = 0; j < graph->v[i]->adjSize; ++j)
            cout << graph->v[i]->adj[j]->key << " ";
        cout << "\n";
    }
    cout << "\n";
}

void printVertexesDFS(Graph* graph)
{
    cout << "each vertex after DFS is:\n";
    for (int i = 0; i < graph->nrNodes; i++)
        if(graph->v[i]->parent == NULL)
            cout << graph->v[i]->key << ": times: " << graph->v[i]->discoveryTime << "/" << graph->v[i]->finalTime << " parent: NULL" << "\n";
        else
            cout << graph->v[i]->key << ": times: " << graph->v[i]->discoveryTime << "/" << graph->v[i]->finalTime << " parent: " << graph->v[i]->parent->key << "\n";
    cout << "\n";
}

void initializeGraph(Graph* graph)
{
    graph->v[0]->adjSize = 2;
    graph->v[0]->adj[0] = graph->v[1];
    graph->v[0]->adj[1] = graph->v[3];

    graph->v[1]->adjSize = 1;
    graph->v[1]->adj[0] = graph->v[4];

    graph->v[2]->adjSize = 2;
    graph->v[2]->adj[0] = graph->v[4];
    graph->v[2]->adj[1] = graph->v[5];

    graph->v[3]->adjSize = 1;
    graph->v[3]->adj[0] = graph->v[1];

    graph->v[4]->adjSize = 1;
    graph->v[4]->adj[0] = graph->v[3];

    graph->v[5]->adjSize = 1;
    graph->v[5]->adj[0] = graph->v[5];
}

void initializeGraph2(Graph* graph)
{
    graph->v[0]->adjSize = 0;

    graph->v[1]->adjSize = 0;

    graph->v[2]->adjSize = 1;
    graph->v[2]->adj[0] = graph->v[3];

    graph->v[3]->adjSize = 1;
    graph->v[3]->adj[0] = graph->v[1];

    graph->v[4]->adjSize = 2;
    graph->v[4]->adj[0] = graph->v[0];
    graph->v[4]->adj[1] = graph->v[1];

    graph->v[5]->adjSize = 2;
    graph->v[5]->adj[0] = graph->v[0];
    graph->v[5]->adj[1] = graph->v[2];
} // another demo for topological sort

// TARJAN ALGORITHM

typedef struct NodeT
{
    int key;
    int index;
    int lowLink;
    int comp;
    bool onStack;
    int adjSize;
    struct NodeT** adj;
}NodeT;

typedef struct GraphT
{
    int nrNodes;
    NodeT** v;
}GraphT;

typedef struct NodeS
{
    NodeT* u;
    struct NodeS* next;
} NodeS;

NodeS* createT(NodeT* node)
{
    NodeS* q = (NodeS*)malloc(sizeof(NodeS));
    q->u = node;
    q->next = NULL;
    return q;
}

void push(NodeS** stack, NodeT* node)
{
    NodeS* q = createT(node);
    if (*stack == NULL)
        *stack = q;
    else
    {
        q->next = *stack;
        *stack = q;
    }
}

NodeT* pop(NodeS** stack)
{
    if (*stack == NULL)
        return NULL;
    else
    {
        NodeT* nodeToPop = (*stack)->u;
        NodeS* aux;
        aux = (*stack)->next;
        free(*stack);
        *stack = aux;
        return nodeToPop;
    }
}

void strongConnect(GraphT* graph, NodeT* u, int& index, NodeS** S, int& nrComponents)
{
    u->index = index;
    u->lowLink = index;
    index = index + 1;
    push(S, u);
    u->onStack = true;
    for (int i = 0; i < u->adjSize; i++)
        if (u->adj[i]->index == -1)
        {
            strongConnect(graph, u->adj[i], index, S, nrComponents);
            u->lowLink = min(u->lowLink, u->adj[i]->lowLink);
        }
        else if (u->adj[i]->onStack != true)
            u->lowLink = min(u->lowLink, u->adj[i]->index);
    
    if (u->lowLink == u->index)
    {
        nrComponents = nrComponents + 1;
        NodeT* v = (NodeT*)malloc(sizeof(NodeT));
        do
        {
            v = pop(S);
            v->onStack = false;
            v->comp = nrComponents;
        } while (v != u);
    }
}

void tarjan(GraphT* graph)
{
    int index = 0;
    NodeS* S = NULL;
    int nrComponents = 0;

    for (int i = 0; i < graph->nrNodes; i++)
    {
        graph->v[i]->index = -1;
        graph->v[i]->lowLink = -1;
        graph->v[i]->onStack = false;
        graph->v[i]->comp = 0;
    }

    for (int i = 0; i < graph->nrNodes; i++)
        if (graph->v[i]->index == -1)
            strongConnect(graph, graph->v[i], index, &S, nrComponents);

    cout << "Tarjan SCC algo:\nindex: " << index << "\nnumber of components: " << nrComponents << "\n";
}

void initializeGraphTarjan(GraphT* graph)
{
    graph->v[0]->adjSize = 0;

    graph->v[1]->adjSize = 2;
    graph->v[1]->adj[0] = graph->v[0];
    graph->v[1]->adj[1] = graph->v[3];

    graph->v[2]->adjSize = 3;
    graph->v[2]->adj[0] = graph->v[1];
    graph->v[2]->adj[1] = graph->v[3];
    graph->v[2]->adj[2] = graph->v[4];

    graph->v[3]->adjSize = 1;
    graph->v[3]->adj[0] = graph->v[5];

    graph->v[4]->adjSize = 2;
    graph->v[4]->adj[0] = graph->v[5];
    graph->v[4]->adj[1] = graph->v[6];

    graph->v[5]->adjSize = 2;
    graph->v[5]->adj[0] = graph->v[3];
    graph->v[5]->adj[1] = graph->v[7];

    graph->v[6]->adjSize = 2;
    graph->v[6]->adj[0] = graph->v[4];
    graph->v[6]->adj[1] = graph->v[7];

    graph->v[7]->adjSize = 0;
}

void printAdjListTarjan(GraphT* graph)
{
    cout << "adjacency lists for Tarjan demo:\n";
    for (int i = 0; i < graph->nrNodes; i++)
    {
        cout << "(" << graph->v[i]->adjSize << ") " << graph->v[i]->key << ": ";
        for (int j = 0; j < graph->v[i]->adjSize; ++j)
            cout << graph->v[i]->adj[j]->key << " ";
        cout << "\n";
    }
    cout << "\n";
}

void demo()
{
    // creez graful 

    Graph* graph = (Graph*)malloc(sizeof(graph));
    graph->nrNodes = 6;
    graph->v = (Node**)malloc(graph->nrNodes * sizeof(Node*));
    for (int i = 0; i < graph->nrNodes; ++i) {
        graph->v[i] = (Node*)malloc(sizeof(Node));
        memset(graph->v[i], 0, sizeof(Node));
    }

    Node** u = (Node**)malloc(graph->nrNodes * sizeof(Node*));
    for (int i = 0; i < graph->nrNodes; i++)
    {
        u[i] = (Node*)malloc(sizeof(Node));
        memset(u[i], 0, sizeof(Node));
        u[i]->key = i;
    }

    for (int i = 0; i < graph->nrNodes; i++)
        graph->v[i] = u[i];

    for (int i = 0; i < graph->nrNodes; i++)
    {
        graph->v[i]->adj = (Node**)malloc(graph->nrNodes * sizeof(Node));
        memset(graph->v[i]->adj, 0, sizeof(Node*));
    }

    // demo for DFS
    initializeGraph(graph);
    printAdjList(graph);
    int time = 0;
    dfs(graph, time);
    printDFStree(graph);
    printVertexesDFS(graph);

    // demo for Topological Sort
    time = 0;
    initializeGraph(graph);
    topologicalSort(graph, time);
    cout << "\n";

    // demo 2 for Topological Sort
    time = 0;
    initializeGraph2(graph);
    printAdjList(graph);
    topologicalSort(graph, time);
    cout << "\n";

    // DEMO FIR TARJAN ALGORITHM

    GraphT* graphT = (GraphT*)malloc(sizeof(graphT));
    graphT->nrNodes = 8;
    graphT->v = (NodeT**)malloc(graphT->nrNodes * sizeof(NodeT*));
    for (int i = 0; i < graphT->nrNodes; ++i) {
        graphT->v[i] = (NodeT*)malloc(sizeof(NodeT));
        memset(graphT->v[i], 0, sizeof(NodeT));
    }

    NodeT** uT = (NodeT**)malloc(graphT->nrNodes * sizeof(NodeT*));
    for (int i = 0; i < graphT->nrNodes; i++)
    {
        uT[i] = (NodeT*)malloc(sizeof(NodeT));
        memset(uT[i], 0, sizeof(NodeT));
        uT[i]->key = i;
    }

    for (int i = 0; i < graphT->nrNodes; i++)
        graphT->v[i] = uT[i];

    for (int i = 0; i < graphT->nrNodes; i++)
    {
        graphT->v[i]->adj = (NodeT**)malloc(graphT->nrNodes * sizeof(NodeT));
        memset(graphT->v[i]->adj, 0, sizeof(NodeT*));
    }

    initializeGraphTarjan(graphT);
    printAdjListTarjan(graphT);

    tarjan(graphT);

}

// ANALIZA DFS

void dfsVisitAnalysis(Graph* graph, Node* v, int& time, Operation* op)
{
    //op->count();
    time = time + 1;
    op->count();
    v->discoveryTime = time;
    op->count();
    v->color = COLOR_GRAY;

    for (int i = 0; i < v->adjSize; i++)
    {
        op->count();
        if (v->adj[i]->color == COLOR_WHITE)
        {
            op->count();
            v->adj[i]->parent = v;
            op->count();
            dfsVisitAnalysis(graph, v->adj[i], time, op);
        }
    }
    op->count();
    v->color = COLOR_BLACK;
    //op->count();
    time = time + 1;
    op->count();
    v->finalTime = time;
}

void dfsAnalysis(Graph* graph, int& time, Operation* op)
{
    for (int i = 0; i < graph->nrNodes; i++)
    {
        op->count();
        graph->v[i]->color = COLOR_WHITE;
        op->count();
        graph->v[i]->parent = NULL;
    }

    //op->count();
    time = 0;

    for (int i = 0; i < graph->nrNodes; i++)
    {
        op->count();
        if (graph->v[i]->color == COLOR_WHITE)
        {
            op->count();
            dfsVisitAnalysis(graph, graph->v[i], time, op);
        }   
    }
        
}

void free_graph(Graph* graph)
{
    if (graph->v != NULL) {
        for (int i = 0; i < graph->nrNodes; ++i) {
            if (graph->v[i] != NULL) {
                if (graph->v[i]->adj != NULL) {
                    free(graph->v[i]->adj);
                    graph->v[i]->adj = NULL;
                }
                graph->v[i]->adjSize = 0;
                free(graph->v[i]);
                graph->v[i] = NULL;
            }
        }
        free(graph->v);
        graph->v = NULL;
    }
    graph->nrNodes = 0;
}

bool checkEdges(Graph graph, int randomNodeDest, int randomNodeSel)
{
    for (int j = 0; j < graph.v[randomNodeDest]->adjSize; j++)
        if (randomNodeSel == graph.v[randomNodeDest]->adj[j]->key)
            return false;
    return true;
}

void perf()
{
    int n, time;

    // veriez numarul de muchii

    for (n = 1000; n <= 4500; n += 100)
    {
        Operation op = p.createOperation("DFS-edges", n);
        Graph graph;
        graph.nrNodes = 100;

        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for (int i = 0; i < graph.nrNodes; ++i)
        {
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
        }

        Node** u = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for (int i = 0; i < graph.nrNodes; i++)
        {
            u[i] = (Node*)malloc(sizeof(Node));
            memset(u[i], 0, sizeof(Node));
            u[i]->key = i;
        }

        for (int i = 0; i < graph.nrNodes; i++)
            graph.v[i] = u[i];

        for (int i = 0; i < graph.nrNodes; i++)
        {
            graph.v[i]->adj = (Node**)malloc(graph.nrNodes * sizeof(Node));
            memset(graph.v[i]->adj, 0, sizeof(Node*));
        }

        int randomNodeDest, randomNodeSel;
        for (int i = 0; i < n; i++)
        {
            randomNodeDest = rand() % graph.nrNodes;
            randomNodeSel = rand() % graph.nrNodes;

            while (checkEdges(graph, randomNodeDest, randomNodeSel) == false)
                randomNodeSel = rand() % graph.nrNodes;

            graph.v[randomNodeDest]->adj[graph.v[randomNodeDest]->adjSize] = u[randomNodeSel];
            graph.v[randomNodeDest]->adjSize++;

        }
        
        /*for (int i = 0; i < graph.nrNodes; i++)
        {
            cout << graph.v[i]->key << ": ";
            for (int j = 0; j < graph.v[i]->adjSize; ++j)
                cout << graph.v[i]->adj[j]->key << " ";
            cout << graph.v[i]->adjSize << "\n";
        }
        cout << "\n";*/

        time = 0;
        dfsAnalysis(&graph, time, &op);
        free_graph(&graph);
    }

    // variez numarul de noduri

    for (n = 100; n <= 200; n += 10)
    {
        Operation op = p.createOperation("DFS-vertices", n);
        Graph graph;
        graph.nrNodes = n;

        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for (int i = 0; i < graph.nrNodes; ++i) {
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
        }

        Node** u = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for (int i = 0; i < graph.nrNodes; i++)
        {
            u[i] = (Node*)malloc(sizeof(Node));
            memset(u[i], 0, sizeof(Node));
            u[i]->key = i;
        }

        for (int i = 0; i < graph.nrNodes; i++)
            graph.v[i] = u[i];

        for (int i = 0; i < graph.nrNodes; i++)
        {
            graph.v[i]->adj = (Node**)malloc(graph.nrNodes * sizeof(Node));
            memset(graph.v[i]->adj, 0, sizeof(Node*));
        }

        int randomNodeDest, randomNodeSel;
        for (int i = 0; i < 4500; i++)
        {
            randomNodeDest = rand() % graph.nrNodes;
            randomNodeSel = rand() % graph.nrNodes;

            while (checkEdges(graph, randomNodeDest, randomNodeSel) == false)
                randomNodeSel = rand() % graph.nrNodes;

            graph.v[randomNodeDest]->adj[graph.v[randomNodeDest]->adjSize] = u[randomNodeSel];
            graph.v[randomNodeDest]->adjSize++;

        }

        time = 0;
        dfsAnalysis(&graph, time, &op);
        free_graph(&graph);
    }

    p.showReport();
}

int main()
{
    demo();
    //perf();
    return 0;
}
