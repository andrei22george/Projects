/**
 * @author Iclodean George
 * @group 30223
 *
 * Specificațiile problemei: Se cere implementarea corectă și eficientă a 3 metode directe de sortare (sortarea bulelor,
 * sortarea prin inserție – folosind inserție liniară sau binară, și sortarea prin selecție)
 * 
 * Interpretarea personală despre complexitate (timp și spațiu), despre cazurile de testare (favorabil,
 * mediu-statistic si nefavorabil)
 * 
 * Cazul 1. Average ((Binary) Insertion Sort is best)
 * 
 * Pe cazul average, ca total de operatii, cel mai mare numar de operatii a fost obtinut de algoritmul Bubble Sort,
 * in timp ce Insertion Sort (folosind insertia liniara) si Selection Sort au avut un numar foarte apropiat de operatii.
 * Cel mai bun numar de atribuiri a fost obtinut folosind Selection Sort, urmat de Insertion Sort si, la o diferenta
 * semnificativa, Bubble Sort.
 * Cel mai bun numar de comparatii a fost obtinu folosind Insertion Sort, urmat apoi de Selection Sort si Bubble Sort,
 * care au numarul de comparatii foarte apropiate.
 * 
 * Insertion Sort folosind insertia binara are per total cel mai mic numar de operatii comapartiv cu ceilalti 3
 * algoritmi, in acest total fiind dominant numarul de atribuiri in fata celui de comparatii.
 * Observam ca numarul de atribuiri este aproximativ identic la cele doua variante de Insertion Sort, insa cel de
 * comparatii este semnificativ mai mic folosind varianta binary.
 * 
 * Complexitatile de timp sunt: O(n^2) (Bubble Sort), O(n^2) (Insertion Sort), O(n^2) (Selection Sort), 
 * O(n^2) (Binary Insertion Sort)
 * 
 * Cazul 2. Best (Bubble Sort is best)
 * 
 * Pe cazul best, cel mai eficient algoritm este Bubble Sort, avand per total cel mai mic numar de operatii, urmat apoi
 * de Insertion Sort si, in final, de Selection Sort, al carui numar de operatii este semnificativ mai mare comparativ
 * cu restul doua. Astfel, Bubble Sort si Insertion Sort au in acest caz complexitate liniara si nu patratica ca in
 * restul cazurilor.
 * Cel mai bun numar de atriburi se obtine folosind Bubble Sort si Selection Sort, care efectuteaza 0 atriburi, in timp
 * ce Insertion Sort realizeaza un numar de atriburi egal cu dublul numarului de elemente din sir.
 * Cel mai bun numar de comparatii a fost obtinut folosind InsertionSort, realizandu-se 0 comparatii. Bubble Sort 
 * a obtinut un numar de comparatii egal cu numarul de elemnte din vector, in timp ce Selection Sort realizaeaza un
 * numar semnificativ de mare de comparatii fata de ceilalti doi algoritmi.
 * 
 * Binary Insertion Sort este in best case mai putin eficient ca Insertion Sort prin insertie liniara, dar mai
 * eficient totusi ca Selection Sort, din nou numarul de atribuiri fiind dominant celui de comparatii.
 * 
 * Complexitatile de timp sunt: O(n) (Bubble Sort), O(n) (Insertion Sort), O(n^2) (Selection Sort), 
 * O(n log n) (Binary Insertion Sort)
 * 
 * Cazul 3. Worst (Selection Sort is best)
 * 
 * Pe cazul worst, cel mai mic numar total de operatii este cel obtinut folosind Selection Sort, fiind urmat de Insertion
 * Sort, iar cel mai putin eficient fiind Bubble Sort.
 * Cel mai mic numar de atriburi a fost realiza de Selection Sort, fiind urmat de Insertion Sort si apoi de Bubble Sort
 * la o diferenta semnificativa.
 * In acest caz, numerele de comparatii sunt foarte apropiate pentru toti cei 3 algoritmi, astfel ca pe grafic este
 * vizibila o singura parabola.
 * 
 * In acest caz, observam ca numarul total de operatii este dublu pentru folosind insertia liniara, fata de cea 
 * binara in cazul Insertion Sort.
 * 
 * Complexitatile de timp sunt: O(n^2) (Bubble Sort), O(n^2) (Insertion Sort), O(n^2) (Selection Sort), 
 * O(n^2) (Binary Insertion Sort)
 * 
 * Complexitatea de spatiu este O(1) pentru toti algoritmii. Insa, daca pentru Binary Search folosim o varianta
 * recusriva in locul celei iterative, ea devine O(log n).
 * 
 * Am implementat 4 variante de algoritmi pentru sortarea unui sir.
 * Varianta 1. Bubble Sort
 *		- se face o trece prin sir, de la primul element
 *		- pentru fiecare element, il comparam cu elementul urmator si daca ordincea nu e cortcta, se intreschimba
 *		- avansam la urmatorul element
 *		- dupa fiecare parcurgere, elementul cel mai mare din parcurgerea respectiva e pe ultima pozitie
 * 
 * Varianta 2/3. Insertion Sort (binary si liniar)
 *		- la fiecare pas, cautam pozitia primului element din partea nesortata in cea sortata.
 *		- diferenta intre cele doua este ca in loc de a folosi cautarea liniara pentru a gasi pozitia elementului
 *		  in partea sortata, folosim cautarea binara. Astfel, timpul de inserare al unui element se reduce de la
 *		  O(n) la O(log n)
 * 
 * Varianta 4. Selection Sort
 *		- se cauta minimul de la inceputul partii nesortate pana la sfarsitul ei (n)
 *		- se aduce apoi pe ultima pozitie din cele sortate
 * 
 * de scris:
 * Analiza de performanta pe best, worst, average
 * Complexitatile algoritmilor
 * Cel mai rapid alg pe worst, average, best
 */


// 1. bubble sort
// 2. insertion sort liniar / binar
// 3. selection sort

// profiler
// count operatii
// for 100 -> 1000 prima oara

#include <iostream>
#include "Profiler.h"

Profiler p("lab1");

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5

using namespace std;

void print(int a[], int n)
{
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << "\n";
}

void bubbleSort(int a[], int n)
{
	Operation opComp = p.createOperation("bubbleSort.comp", n);
	Operation opAttr = p.createOperation("bubbleSort.attr", n);

	int aux;
	bool flag;
	for (int i = 0; i < n - 2; i++)
	{
		flag = false;
		for (int j = n - 1; j >= i + 1; j--)
		{
			opComp.count();
			if (a[j] < a[j - 1])
			{
				opAttr.count(3);
				aux = a[j];
				a[j] = a[j - 1];
				a[j - 1] = aux;
				flag = true;
			}
		}
		opComp.count();
		if (flag == false) // optimizare, se verifica daca s-au facut interschimbari
			return;
	}
}

void insertionSort(int a[], int n)
{
	Operation opComp = p.createOperation("insertionSort.comp", n);
	Operation opAttr = p.createOperation("insertionSort.attr", n);

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

void selectionSort(int a[], int n)
{
	Operation opComp = p.createOperation("selectionSort.comp", n);
	Operation opAttr = p.createOperation("selectionSort.attr", n);

	int min, aux;
	for (int i = 0; i < n - 2; i++)
	{
		min = i;
		for (int j = i + 1; j < n; j++)
		{
			opComp.count();
			if (a[j] < a[min])
				min = j;
		}
		if (min != i) // pentru stabilitatea algoritmului
		{
			opAttr.count(3);
			aux = a[min];
			a[min] = a[i];
			a[i] = aux;
		}
	}
}

int binarySearch(int a[], int n, int key, Operation &opComp, Operation &opAttr)
{
	int stanga = 0;
	int dreapta = n;
	int mijloc;

	while (stanga < dreapta)
	{
		mijloc = (stanga + dreapta) / 2;
		opComp.count();
		if (a[mijloc] <= key)
			stanga = mijloc + 1;
		else dreapta = mijloc;
	}
	return stanga;

}

void binaryInsertionSort(int a[], int n)
{
	Operation opComp = p.createOperation("binaryInsertionSort.comp", n);
	Operation opAttr = p.createOperation("binaryInsertionSort.attr", n);
	
	int aux, index, j;
	
	for (int i = 1; i < n; i++)
	{
		opAttr.count();
		aux = a[i];
		index = binarySearch(a, i, aux, opComp, opAttr);
		j = i;
		
		while (j > index)
		{
			opAttr.count();
			a[j] = a[j - 1];
			j--;
		}
		opAttr.count();
		a[index] = aux;
	}
}

void demo() // demo pe acelasi sir predefinit de mine, folosind fiecare din cele 4 sortari
{
	int v1[] = {11, 9, 3, 12, 5, 7, 2, 9, 5};
	int n1 = sizeof(v1) / sizeof(v1[0]);

	bubbleSort(v1, n1);
	cout << "sorting with bubbleSort() is:" << "\n";
	print(v1, n1);

	int v2[] = { 11, 9, 3, 12, 5, 7, 2, 9, 5 };
	int n2 = sizeof(v2) / sizeof(v2[0]);

	insertionSort(v2, n2);
	cout << "sorting with insertionSort() is:" << "\n";
	print(v2, n2);

	int v3[] = { 11, 9, 3, 12, 5, 7, 2, 9, 5 };
	int n3 = sizeof(v3) / sizeof(v3[0]);

	selectionSort(v3, n3);
	cout << "sorting with selectionSort() is:" << "\n";
	print(v3, n3);

	int v4[] = { 11, 9, 3, 12, 5, 7, 2, 9, 5 };
	int n4 = sizeof(v4) / sizeof(v3[0]);

	binaryInsertionSort(v4, n4);
	cout << "sorting with binaryInsertionSort() is:" << "\n";
	print(v4, n4);
}

void perf(int order)
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
			bubbleSort(v1, n);
			insertionSort(v2, n);
			selectionSort(v3, n);
			binaryInsertionSort(v4, n);
		}
	}
	
	p.divideValues("bubbleSort.attr", NR_TESTS);
	p.divideValues("bubbleSort.comp", NR_TESTS);
	p.addSeries("bubbleSort", "bubbleSort.attr", "bubbleSort.comp");

	p.divideValues("insertionSort.attr", NR_TESTS);
	p.divideValues("insertionSort.comp", NR_TESTS);
	p.addSeries("insertionSort", "insertionSort.attr", "insertionSort.comp");

	p.divideValues("selectionSort.attr", NR_TESTS);
	p.divideValues("selectionSort.comp", NR_TESTS);
	p.addSeries("selectionSort", "selectionSort.attr", "selectionSort.comp");

	p.divideValues("binaryInsertionSort.attr", NR_TESTS);
	p.divideValues("binaryInsertionSort.comp", NR_TESTS);
	p.addSeries("binaryInsertionSort", "binaryInsertionSort.attr", "binaryInsertionSort.comp");

	p.createGroup("attributions", "bubbleSort.attr", "insertionSort.attr", "selectionSort.attr");
	p.createGroup("comparisons", "bubbleSort.comp", "insertionSort.comp", "selectionSort.comp");
	p.createGroup("total", "bubbleSort", "insertionSort", "selectionSort");
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
	// demo();
	perf_all();
	return 0;
}
