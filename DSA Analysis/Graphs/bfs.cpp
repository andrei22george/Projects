/**
 * @author Iclodean Andrei-George
 * @group 30223
 *
 * Specificatiile problemei: Determinarea vecinilor unei celule, implementarea algoritmului BFS,
 * afisarea arborelui BFS, evaluarea performantei algoritmului BFS, Bonus: determinarea celui mai scurt drum.
 *
 * Interpretarea personala despre complexitate (timp si spatiu), despre cazurile de testare (favorabil,
 * mediu-statistic si nefavorabil):
 * 
 * 1. Determinarea vecinilor unei celule
 *      Pentru determinarea vecinilor unei celule, am efectuat o serie de verificari atat asupra punctului
 * dat, cat si asupra vecinilor sai. Astfel, pentru inceput, verific daca punctul insine este valid, adica
 * daca in grid.txt pe pozitia sa se afla valoarea 0. Altfel, punctul este intr-un zid. Apoi, ma asigur ca
 * punctul dat este in grid si nu in afara sa.
 *      In cazul, vecinilor, exista maxim 4 vecini pentru fiecare nod, pentru care am verificat daca sunt sau 
 * nu zid (1 in grid.txt) si in caz ca sunt valizi, i-am adaugat in vectorul de vecini, incrementand un contor
 * initializat cu 0.
 * 
 * 2. Implementarea algoritmului BFS
 *      Pentru algoritmul BFS am folosit pseudocodul din sectiunea 22.2 din Cormen implementat pe structura
 * grafului data in bfs.h. Astfel, algoritmul realizeaza BFS pe graful graph, pornind din nodul sursa s.
 * Complexitatea de timp a algoritmului este O(V + E), unde V si E sunt numarul de noduri, respectiv de muchii.
 * 
 * 3. Afisarea arborelui BFS
 *      Pentru functia ce realizeaza pretty print-ul arborelui BFS pornind de la vectorul de parinti construit,
 * am implementat 2 elemente majore. Prima parte numara pentru fiecare nod, numarul de pasi pentru a ajunge in
 * vectorul de parinti la radacina, adica la valoarea -1. Astfel, pentru fiecare nod voi avea in vectorul 
 * spaces numarul de spatii necesar pentru afisarea fiecarui nod.
 *      Al doilea element major este functia recursiva "preorder", a carei concept este asemenea unei parcugeri 
 * in preordine, dar are scopul de a sorta vectorul de parinti, astfel incat sa infatiseze o parcurgere in 
 * preordine a arborelui. Astfel, pentru fiecare nod pornind de la radacina, cat timp acesta mai are copii, ei 
 * sunt adaugati in vectorul order.
 *      La sfarsit, se face afisarea dupa formatul cerut.
 * 
 * 4. Evaluarea performantei algoritmului BFS
 *      In cazul evaluarii performantei BFS, am generat grafuri dupa cerintele date, astfel ca pentru varierea
 * numarului de muchii, generez un graf cu 100 de noduri, pentru care adaug deja 100 de muchii, fiecare de la
 * nodul 0 la 1, 1 la 2, ..., 99 la 0, restul de n - 100 de muchii fiid plasate intre cate doua noduri random
 * diferite (nu de la acelasi nod la el insusi), asigurandu-ma astfel ca graful obtinut este conex.
 * Aplica apoi BFS pe graful generat.
 *      Analog pentru varierea numarului de noduri, insa aici cele n muchii initiale sunt adaugate pentru fiecare
 * nou numar de noduri, iar numarul de muchii este apoi 4500 - n. 
 * 
 * 5. Bonus: Determinarea celui mai scurt drum
 *      Pentru determinarea celui mai scurt drum, am realizat BFS cu nodul sursa drept nodul start, iar apoi
 * am reconstruit traseul porinind dinspre nodul end. Inainte insa, verific daca nodul end este sau nu BLACK
 * in urma executarii BFS-ului, iar daca nu este inseamna ca este inaccesibil din nodul start, fapt pentru
 * care returnez -1, fara a mai incerca sa ajung la el prin reconstructia traseului.
 *      In caz contrar, cat timp inca nu am ajuns la start, adaug in vectorul path nodul curent, si acestuia
 * ii atribui parintele sau. Deoarce distanta nodului end reprezinta lungimea vectorului path, control porneste
 * cu valoarea acestia si scade la fiecare atribuire pana la gasirea nodului start.
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "bfs.h"
#include "Profiler.h"

using namespace std;

int k = 0; // contor prelucrarea vectorului de parinti din bfs_tree

int get_neighbors(const Grid *grid, Point p, Point neighb[])
{
    // TODO: fill the array neighb with the neighbors of the point p and return the number of neighbors
    // the point p will have at most 4 neighbors (up, down, left, right)
    // avoid the neighbors that are outside the grid limits or fall into a wall
    // note: the size of the array neighb is guaranteed to be at least 4

    int neighbCounter = 0; // numarul de vecini al unui point

    if (grid->mat[p.row][p.col] == 1 || ((p.row < 0 || p.row > grid->rows) && (p.col < 0 || p.col > grid->cols)))
        return 0;
    
    if (p.row - 1 >= 0 && p.row - 1 <= grid->rows && grid->mat[p.row - 1][p.col] != 1) // sus
    {
        neighb[neighbCounter].col = p.col;
        neighb[neighbCounter].row = p.row - 1;
        neighbCounter++;
    }

    if (p.row - 1 >= 0 && p.row - 1 <= grid->rows && grid->mat[p.row + 1][p.col] != 1) // jos
    {
         neighb[neighbCounter].col = p.col;
         neighb[neighbCounter].row = p.row + 1;
         neighbCounter++;
    }

    if (p.col - 1 >= 0 && p.col - 1 <= grid->cols && grid->mat[p.row][p.col - 1] != 1) // stanga
    {
         neighb[neighbCounter].col = p.col - 1;
         neighb[neighbCounter].row = p.row;
         neighbCounter++;
    }

    if (p.col - 1 >= 0 && p.col - 1 <= grid->cols && grid->mat[p.row][p.col + 1] != 1) // dreapta
    {
         neighb[neighbCounter].col = p.col + 1;
         neighb[neighbCounter].row = p.row;
         neighbCounter++;
    }

    return neighbCounter;
}

void grid_to_graph(const Grid *grid, Graph *graph)
{
    //we need to keep the nodes in a matrix, so we can easily refer to a position in the grid
    Node *nodes[MAX_ROWS][MAX_COLS];
    int i, j, k;
    Point neighb[4];

    //compute how many nodes we have and allocate each node
    graph->nrNodes = 0;
    for(i=0; i<grid->rows; ++i){
        for(j=0; j<grid->cols; ++j){
            if(grid->mat[i][j] == 0){
                nodes[i][j] = (Node*)malloc(sizeof(Node));
                memset(nodes[i][j], 0, sizeof(Node)); //initialize all fields with 0/NULL
                nodes[i][j]->position.row = i;
                nodes[i][j]->position.col = j;
                ++graph->nrNodes;
            }else{
                nodes[i][j] = NULL;
            }
        }
    }
    graph->v = (Node**)malloc(graph->nrNodes * sizeof(Node*));
    k = 0;
    for(i=0; i<grid->rows; ++i){
        for(j=0; j<grid->cols; ++j){
            if(nodes[i][j] != NULL){
                graph->v[k++] = nodes[i][j];
            }
        }
    }

    //compute the adjacency list for each node
    for(i=0; i<graph->nrNodes; ++i){
        graph->v[i]->adjSize = get_neighbors(grid, graph->v[i]->position, neighb);
        if(graph->v[i]->adjSize != 0){
            graph->v[i]->adj = (Node**)malloc(graph->v[i]->adjSize * sizeof(Node*));
            k = 0;
            for(j=0; j<graph->v[i]->adjSize; ++j){
                if( neighb[j].row >= 0 && neighb[j].row < grid->rows &&
                    neighb[j].col >= 0 && neighb[j].col < grid->cols &&
                    grid->mat[neighb[j].row][neighb[j].col] == 0){
                        graph->v[i]->adj[k++] = nodes[neighb[j].row][neighb[j].col];
                }
            }
            if(k < graph->v[i]->adjSize){
                //get_neighbors returned some invalid neighbors
                graph->v[i]->adjSize = k;
                graph->v[i]->adj = (Node**)realloc(graph->v[i]->adj, k * sizeof(Node*));
            }
        }
    }

    /*for (int i = 0; i < graph->nrNodes; i++)
    {
        cout << graph->v[i]->position.col << ": ";
        for (int j = 0; j < graph->v[i]->adjSize; ++j)
            cout << graph->v[i]->adj[j]->position.col << " ";
        cout << graph->v[i]->adjSize << "\n";
    }*/
}

void free_graph(Graph *graph)
{
    if(graph->v != NULL){
        for(int i=0; i<graph->nrNodes; ++i){
            if(graph->v[i] != NULL){
                if(graph->v[i]->adj != NULL){
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

typedef struct NodeQ
{
    Node *vertex;
    struct NodeQ* next;
}NodeQ;

void bfs(Graph *graph, Node *s, Operation *op)
{
    // TOOD: implement the BFS algorithm on the graph, starting from the node s
    // at the end of the algorithm, every node reachable from s should have the color BLACK
    // for all the visited nodes, the minimum distance from s (dist) and the parent in the BFS tree should be set
    // for counting the number of operations, the optional op parameter is received
    // since op can be NULL (when we are calling the bfs for display purposes), you should check it before counting:
    // if(op != NULL) op->count();

    Node** Queue = (Node**)calloc(graph->nrNodes, sizeof(Node));
    int queueHead = 0;
    int queueTail = 0;

    for (int i = 0; i < graph->nrNodes; i++)
    {
        if (op != NULL)
            op->count();
        graph->v[i]->color = COLOR_WHITE;
        if (op != NULL)
            op->count();
        graph->v[i]->dist = 0;
        if (op != NULL)
            op->count();
        graph->v[i]->parent = NULL;
    }

    if (op != NULL)
        op->count();
    s->color = COLOR_GRAY;
    if (op != NULL)
        op->count();
    s->dist = 0;
    if (op != NULL)
        op->count();
    s->parent = NULL;

    if (op != NULL)
        op->count();
    Queue[queueTail++] = s; // enqueue(Q, s)

    while (queueHead != queueTail)
    {
        if (op != NULL)
            op->count();
        Node* u = Queue[queueHead++]; // dequeue(Q)
        for (int i = 0; i < u->adjSize; i++)
        {
            if (op != NULL)
                op->count();
            if (u->adj[i]->color == COLOR_WHITE)
            {
                if (op != NULL)
                    op->count();
                u->adj[i]->color = COLOR_GRAY;
                if (op != NULL)
                    op->count();
                u->adj[i]->dist = u->dist + 1;
                if (op != NULL)
                    op->count();
                u->adj[i]->parent = u;
                if (op != NULL)
                    op->count();
                Queue[queueTail++] = u->adj[i]; // enqueue(Q, v)
            }
        }
        if (op != NULL)
            op->count();
        u->color = COLOR_BLACK;
    }
}

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

void print_bfs_tree(Graph *graph)
{
    //first, we will represent the BFS tree as a parent array
    int n = 0; //the number of nodes
    int *p = NULL; //the parent array
    Point *repr = NULL; //the representation for each element in p

    //some of the nodes in graph->v may not have been reached by BFS
    //p and repr will contain only the reachable nodes
    int *transf = (int*)malloc(graph->nrNodes * sizeof(int));
    for(int i=0; i<graph->nrNodes; ++i){
        if(graph->v[i]->color == COLOR_BLACK){
            transf[i] = n;
            ++n;
        }else{
            transf[i] = -1;
        }
    }
    if(n == 0){
        //no BFS tree
        free(transf);
        return;
    }

    int err = 0;
    p = (int*)malloc(n * sizeof(int));
    repr = (Point*)malloc(n * sizeof(Node));
    for(int i=0; i<graph->nrNodes && !err; ++i){
        if(graph->v[i]->color == COLOR_BLACK){
            if(transf[i] < 0 || transf[i] >= n){
                err = 1;
            }else{
                repr[transf[i]] = graph->v[i]->position;
                if(graph->v[i]->parent == NULL){
                    p[transf[i]] = -1;
                }else{
                    err = 1;
                    for(int j=0; j<graph->nrNodes; ++j){
                        if(graph->v[i]->parent == graph->v[j]){
                            if(transf[j] >= 0 && transf[j] < n){
                                p[transf[i]] = transf[j];
                                err = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    free(transf);
    transf = NULL;

    if(!err){
        // TODO: pretty print the BFS tree
        // the parrent array is p (p[k] is the parent for node k or -1 if k is the root)
        // when printing the node k, print repr[k] (it contains the row and column for that point)
        // you can adapt the code for transforming and printing multi-way trees from the previous labs

        // n e numarul de elemente din vectorul parinte
        // print repr[k]->col, repr[k]->row

        // construiesc vectorul de spatii de pus inaintea fiecarui nod, in functie de distanta
        // dintre el si nodul radacina (cati pasi dureaza sa ajung de la el la nodul radacina
        // prin vectorul de parinti)

        
        int* spaces = (int*)calloc(n, sizeof(int));
        int* order = (int*)calloc(n, sizeof(int));

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

        preorder(p, n, -1, order);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < spaces[order[i]]; j++)
                cout << "        ";
            cout << "(" << repr[order[i]].row << ", " << repr[order[i]].col << ")" << "\n";
        }
        
        k = 0;
        free(order);
        free(spaces);
    }

    if(p != NULL){
        free(p);
        p = NULL;
    }
    if(repr != NULL){
        free(repr);
        repr = NULL;
    }
}

int shortest_path(Graph *graph, Node *start, Node *end, Node *path[])
{
    // TODO: compute the shortest path between the nodes start and end in the given graph
    // the nodes from the path, should be filled, in order, in the array path
    // the number of nodes filled in the path array should be returned
    // if end is not reachable from start, return -1
    // note: the size of the array path is guaranteed to be at least 1000

    Node* step = (Node*)malloc(sizeof(Node));
    int pathCounter;
    Node** Queue = (Node**)calloc(graph->nrNodes, sizeof(Node));
    int queueHead = 0;
    int queueTail = 0;

    for (int i = 0; i < graph->nrNodes; i++)
    {
        graph->v[i]->color = COLOR_WHITE;
        graph->v[i]->dist = 0;
        graph->v[i]->parent = NULL;
    }

    start->color = COLOR_GRAY;
    start->dist = 0;
    start->parent = NULL;

    Queue[queueTail++] = start;

    while (queueHead != queueTail)
    {
        Node* u = Queue[queueHead++];
        for (int i = 0; i < u->adjSize; i++)
        {
            if (u->adj[i]->color == COLOR_WHITE)
            {
                u->adj[i]->color = COLOR_GRAY;
                u->adj[i]->dist = u->dist + 1;
                u->adj[i]->parent = u;
                Queue[queueTail++] = u->adj[i];
            }
        }
        u->color = COLOR_BLACK;
    }

    if (end->color != COLOR_BLACK) // nodul end nu este accesibil din start (in dfs nu a fost marcat ca fiind black)
        return -1;

    pathCounter = end->dist - 1;

    for (step = end; step != start; step = step->parent)
        path[pathCounter--] = step;

    return end->dist;
}

void performance()
{
    int n, i;
    Profiler p("bfs");

    // vary the number of edges
    for (n = 1000; n <= 4500; n += 100) {
        Operation op = p.createOperation("bfs-edges", n);
        Graph graph;
        graph.nrNodes = 100;
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for (i = 0; i < graph.nrNodes; ++i) {
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
        }
        // TODO: generate n random edges
        // make sure the generated graph is connected

        Node** u = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for (int i = 0; i < graph.nrNodes; i++)
        {
            u[i] = (Node*)malloc(sizeof(Node));
            memset(u[i], 0, sizeof(Node));
            u[i]->position.row = i;
            u[i]->position.col = i;
        }

        for (int i = 0; i < graph.nrNodes; i++)
            graph.v[i] = u[i];

        for (int i = 0; i < graph.nrNodes; i++)
        {
            graph.v[i]->adj = (Node**)malloc(graph.nrNodes * sizeof(Node));
            memset(graph.v[i]->adj, 0, sizeof(Node*));
        }

        for (int i = 0; i < graph.nrNodes - 1; i++)
        {
            graph.v[i]->adj[graph.v[i]->adjSize] = graph.v[i + 1];
            graph.v[i]->adjSize++;
        }
        graph.v[graph.nrNodes - 1]->adj[graph.v[graph.nrNodes - 1]->adjSize] = graph.v[0];
        graph.v[graph.nrNodes - 1]->adjSize++;

        int randomNodeDest, randomNodeSel;
        for (int i = 0; i < n - 100; i++)
        {
            randomNodeDest = rand() % graph.nrNodes;
            randomNodeSel = rand() % graph.nrNodes;
            while (randomNodeDest == randomNodeSel)
                randomNodeSel = rand() % graph.nrNodes;

            // cout << "from node: " << randomNodeDest << " to node: " << randomNodeSel << "\n";

            // graph.v[randomNodeDest]->adj[graph.v[randomNodeDest]->adjSize] = (Node*)malloc(sizeof(Node));
            graph.v[randomNodeDest]->adj[graph.v[randomNodeDest]->adjSize] = u[randomNodeSel];
            graph.v[randomNodeDest]->adjSize++;

        }

        /*for (int i = 0; i < graph.nrNodes; i++)
        {
            cout << graph.v[i]->position.col << ": ";
            for (int j = 0; j < graph.v[i]->adjSize; ++j)
                cout << graph.v[i]->adj[j]->position.col << " ";
            cout << graph.v[i]->adjSize << "\n";
        }*/

        /*int s = 0;
        for (int i = 0; i < graph.nrNodes; i++)
        {
            s += graph.v[i]->adjSize;
        }
        cout << n << ": " << s << "\n";*/
 

        bfs(&graph, graph.v[0], &op);
        free_graph(&graph);
    }

        // vary the number of vertices
        for (n = 100; n <= 200; n += 10) {
            Operation op = p.createOperation("bfs-vertices", n);
            Graph graph;
            graph.nrNodes = n;
            //initialize the nodes of the graph
            graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
            for (i = 0; i < graph.nrNodes; ++i) {
                graph.v[i] = (Node*)malloc(sizeof(Node));
                memset(graph.v[i], 0, sizeof(Node));
            }
            // TODO: generate 4500 random edges
            // make sure the generated graph is connected

            Node** u = (Node**)malloc(graph.nrNodes * sizeof(Node*));
            for (int i = 0; i < graph.nrNodes; i++)
            {
                u[i] = (Node*)malloc(sizeof(Node));
                memset(u[i], 0, sizeof(Node));
                u[i]->position.row = i;
                u[i]->position.col = i;
            }

            for (int i = 0; i < graph.nrNodes; i++)
                graph.v[i] = u[i];

            for (int i = 0; i < graph.nrNodes; i++)
            {
                graph.v[i]->adj = (Node**)malloc(graph.nrNodes * sizeof(Node));
                memset(graph.v[i]->adj, 0, sizeof(Node*));
            }

            for (int i = 0; i < graph.nrNodes - 1; i++)
            {
                graph.v[i]->adj[graph.v[i]->adjSize] = graph.v[i + 1];
                graph.v[i]->adjSize++;
            }
            graph.v[graph.nrNodes - 1]->adj[graph.v[graph.nrNodes - 1]->adjSize] = graph.v[0];
            graph.v[graph.nrNodes - 1]->adjSize++;

            int randomNodeDest, randomNodeSel;
            for (int i = 0; i < 4500 - n; i++)
            {
                randomNodeDest = rand() % graph.nrNodes;
                randomNodeSel = rand() % graph.nrNodes;
                while (randomNodeDest == randomNodeSel)
                    randomNodeSel = rand() % graph.nrNodes;

                // cout << "from node: " << randomNodeDest << " to node: " << randomNodeSel << "\n";

                // graph.v[randomNodeDest]->adj[graph.v[randomNodeDest]->adjSize] = (Node*)malloc(sizeof(Node));
                graph.v[randomNodeDest]->adj[graph.v[randomNodeDest]->adjSize] = u[randomNodeSel];
                graph.v[randomNodeDest]->adjSize++;

            }

            /*for (int i = 0; i < graph.nrNodes; i++)
            {
                cout << graph.v[i]->position.col << ": ";
                for (int j = 0; j < graph.v[i]->adjSize; ++j)
                    cout << graph.v[i]->adj[j]->position.col << " ";
                cout << graph.v[i]->adjSize << "\n";
            }*/

            /*int s = 0;
            for (int i = 0; i < graph.nrNodes; i++)
            {
                s += graph.v[i]->adjSize;
            }
            cout << n << ": " << s << "\n";
            */

            bfs(&graph, graph.v[0], &op);
            free_graph(&graph);
        }

        p.showReport();
}
