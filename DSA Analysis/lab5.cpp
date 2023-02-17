/**
 * @author Iclodean Andrei-George
 * @group 30223
 *
 * Specificațiile problemei: Se cere implementarea corecta si eficienta a operatiilor de inserare si cautare intr-o
 * tabela de dispersie ce foloseste adresarea deschisa cu verificare patratica.
 *
 * 
 * Interpretarea personală despre complexitate (timp și spațiu), despre cazurile de testare (favorabil,
 * mediu-statistic si nefavorabil):
 * 
 *	1. Inserare
 *		Functionarea operatiei de inserare in tabela de dispersie cu adresare deschisa si verificare patratica este urmatoarea:
 * functia de inserare este apelata cu parametrii T, ce reprezinta tabela de dispersie in care o cheie urmeaza sa fie inserata, m, ce
 * reprezinta dimensiunea tabelei de dispersie si cheia (value aici), care urmeaza sa fie introdusa in tabela.
 *		Pentru inserare, vom cauta apoi (sau "proba"), toate pozitiile (0 -> m - 1) folosind verificarea patratica. Astfel, este apelata
 * functia de hash, care va returna celula la care urmeaza a fi inserata valoarea. In cazul in care celula este goala, elementul este
 * introdus in tabela, altfel functia este reapelata si se va cauta o alta celula potrivita, insa tot prin intermediul functiei de hash.
 *		Functia returneaza celula la care a fost inserata valoarea data ca parametru, iar lista este actualizata.
 * 
 * 2. Cautare
 *		Asemenea functiei de inserare, cautarea in tabela de dispersie cauta (dupa campul "id", in acest caz), celula la care s-ar putea
 * afla valoarea trnasmisa prin parametru pentru a fi cautata.
 *		Odata ce functia de hash returneaza o indicele unei celule, este verificat daca continutul acestia este acelasi cu valoarea cautata.
 * In cazul in care valoarea a fost gasita, se returneaza indicele celulei la care a fost gasita, sau, altfel, se face o noua incercare prin
 * reapelarea functiei de hash. Daca tabela a fost epuizata si valaorea inca nu a fost gasita, va fi retrunat -1.
 * 
 * 3. Stergere
 *		Deoarece riscul de coliziune este crescut in cazul adresarii deschise spre deosebire de o alta metoda (e.g. chaining), stergerea
 * poate fi mai dificila. Daca am realiza o cautare si am pune -1 in locul valorii dorite (si inca ceva in campul "nume" precum " "),
 * ar exista riscul ca la o viitoare cautare in tabela, algoritmul se se opreasca la prima aparitie a valorii -1, care ar putea fi chiar
 * una dintre primele valori daca s-a sters in acea zona. Atsfel, va trebui sa marcam locul sters diferit (am folosit -2 pentru id si
 * "deleted" pentru nume).
 *		Pentru a ma asigura ca pot insera si pe pozitii unde a avut loc o stergere, voi modifica si inserarea pentru valoarea speciala -2.
 * 
 * Tabel 1. Cautarea unor elemente pentru diferiti factori de umplere a tabelei
 * 
 *		Pentru realizarea acesti cerinte, am enerat un sir aleator de numere. Apoi, pentru fiecare factor de umplere dat (de la 0.8 la 
 * 0.99) am calculat n = factor * N, care reprezinta numarul de elemente din sirul generat anterior (de N elemente), care trebuie
 * introdus in tabela, astfel incat factorul de umplere sa fie corespunzator.
 *		Pentru a ma asigura ca din cele 3000 de elemente de cautat, vor fi gasite aproximativ 1500, m-am asigurat ca 1500 de elemente 
 * sunt preluate din vectorul initial, intr-un mod care sa asigure ca sunt generate uniform cu probabilitate egala. Am parcurs vectorul
 * initial si am salvat tot al 6-lea element (10.000 / 1.500 aprox= 6).
 *		Pentru elementele care nu vor fi gasite, am generat elemente random dintr-un range diferit fata de cele generate pentru a fi 
 * introduse in tabela.
 *		Inainte de a incepe cautarea, am amestecat elementele din vectorul celor care urmeaza sa fie gasite, pentru a nu pastrea ordinea
 * de introducere in tabela.
 *		Am repetat acest proces de 5 ori, si am facut o medie pentru fiecare test, rezultand in coloana de "Efort mediu gasite", iar 
 * cea mai mare dintre cele 5 valori a reprezentant coloana de "Efort maxim gasite", pentru fiecare factor de umplere.
 *		Analog am procedat si pentru elementele ne-gasite.
 * 
 * Tabel 2. Cautarea unor elemente dupa stergerea altora, astfel incat factorul sa scada de la 0.99 la 0.8
 * 
 *		Pentru aceasta cerinta, am calculat numarul de elemente care ar trebui sa fie sters dupa formula n = (0.99 - 0.8) * N.
 * Am sters apoi n elemente alese din vectorul initial, insa alegerea a fost realizata din 5 in 5 pentru a avea o oarecare distrubutie 
 * uniforma (10.000 / n aprox= 5).
 *		In vederea selectarii elementelor ce urmeaza acum a fi gasite si ne-gasite, am folosit acelasi procedeu ca la Tabel 1. 
 *		Pentru numarul de celule accesate pentru fiecare coloana din tabel am folosit acelasi procedeu ca la Tabel 1.
 * 
 * 
 * 
 */


#include <iostream>
#include "Profiler.h"

Profiler p("lab5");

using namespace std;

#define N 10007
#define MAX_SIZE 1000
#define STEP_SIZE 100
#define NR_TESTS 5
#define N_demo 10
#define m_Analysis 3000
#define deleteFactorStart 0.99
#define deleteFactorEnd 0.8

typedef struct
{
	int id;
	char nume[30];
}Entry;

void print(int v[], int n)
{
	for (int i = 0; i < n; i++)
		cout << i + 1 << ": " << v[i] << "\n";
	cout << "\n";
}

void printDemo(int v[], int n)
{
	cout << "to insert: \n";
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
	cout << "\n\n";
}

void printHash(Entry T[], int n)
{
	for (int i = 0; i < n; i++)
		cout << i << ": " << T[i].id << " " << T[i].nume << "\n";
	cout << "\n";
}

void initializeTable(Entry T[], int m)
{
	for (int i = 0; i < m; i++)
	{
		T[i].id = -1;
		strcpy_s(T[i].nume, "");
	}
}

int hashFunction(Entry T[], int m, int value)
{
	int hashValue = value % m;
	if (T[hashValue].id == -1)
		return hashValue;
	else
	{
		for (int j = 0; j < m; j++)
		{
			int newHashValue = (hashValue + j * j) % m;
			if (T[newHashValue].id == -1)
				return newHashValue;
		}
	}
}

int initialHashing(int m, int key)
{
	return key % m;
}

int quadraticProbing(int m, int key, int i)
{
	return (initialHashing(m, key) + i * i) % m;
}

int hashInsertSingleValue(Entry T[], int value, int m)
{
	int i = 0;
	int j;

	do {
		j = quadraticProbing(m, value, i);
		if (T[j].id == -1 || T[j].id == -2) {
			T[j].id = value;
			sprintf_s(T[j].nume, "%d", value);
			return j;
		}
		else i++;
	} while (i < m);
	return -1;
}

void hashInsertArray(Entry T[], int v[], int m)
{
	int hashValue;
	int rehashValue;

	for (int i = 0; i < m; i++)
	{
		hashValue = v[i] % m;
		if (T[hashValue].id == -1)
		{
			// T[hashValue].id = hashValue;
			T[hashValue].id = v[i];
			sprintf_s(T[hashValue].nume, "%d", v[i]);

		}
		else
		{
			for (int j = 0; j < m; j++)
			{
				rehashValue = (hashValue + j * j) % m;
				if (T[rehashValue].id == -1)
				{
					// T[rehashValue].id = rehashValue;
					T[rehashValue].id = v[i];
					sprintf_s(T[rehashValue].nume, "%d", v[i]);
					break;
				}
			}
		}
	}
}

int hashSearch(Entry T[], int m, int key)
{
	int i = 0;
	int j;

	do {
		j = quadraticProbing(m, key, i);
		if (T[j].id == key)
			return j;
		i++;
	} while (T[j].id != -1 && i != m);
	return -1;
}

void printHashSearch(Entry T[], int value)
{
	int searchRes = hashSearch(T, N_demo, value);

	if (searchRes != -1)
		cout << "key " << value << " is at position " << searchRes << " in table \n";
	else
		cout << "key " << value << " is not in table" << " \n";
}

void hashDelete(Entry T[], int m, int key)
{
	int i = 0;
	int j;

	do {
		j = quadraticProbing(m, key, i);
		if (T[j].id == key)
		{
			T[j].id = -2;
			strcpy_s(T[j].nume, "deleted");
		}
		i++;
	} while (T[j].id != -1 && i != m);
}

int hashSearchAnalysis(Entry T[], int m, int key, int &count)
{
	int i = 0;
	int j;

	do {
		j = quadraticProbing(m, key, i);
		count++;
		if (T[j].id == key)
			return j;
		i++;
	} while (T[j].id != -1 && i != m);
	return -1;
}

double averageEfort(int v[])
{
	double sum = 0;
	for (int i = 0; i < NR_TESTS; i++)
		sum += v[i];
	return sum / NR_TESTS;
}

void demo()
{
	Entry T[N_demo];
	initializeTable(T, N_demo);
	int v[N_demo] = { 45, 23, 1, 56, 321, 134, 5, 6, 15, 78 };

	printDemo(v, N_demo);
	hashInsertArray(T, v, N_demo);
	printHash(T, N_demo);

	// searching for keys 56, 100, 321, 17

	printHashSearch(T, 56);
	printHashSearch(T, 100);
	printHashSearch(T, 321);
	printHashSearch(T, 17);
	cout << "\n";

	//deleting key 6

	hashDelete(T, N_demo, 6);
	printHash(T, N_demo);

	printHashSearch(T, 6);
	cout << "\n";

	// reinsetring 6

	hashInsertSingleValue(T, 6, N_demo);
	printHash(T, N_demo);
}

void knuthShuffle(int v[], int n)
{
	for (int i = n - 1; i >= 1; i--)
	{
		int c = rand() % (i + 1);
		if (c != i)
			swap(v[i], v[c]);
	}
}

void searchForFillFactor(int order, double factor)
{
	int k1 = 0;
	int arrayEfortGasite[NR_TESTS];
	int k2 = 0;
	int arrayEfortNegasite[NR_TESTS];
	for (int test = 0; test < NR_TESTS; test++)
	{
		int n = floor(factor * N);
		int v[N] = { 0 };
		Entry T[N];
		initializeTable(T, N);
		int efortGasite = 0;
		int efortNegasite = 0;

		FillRandomArray(v, n, 100, 10000, false, order);
		// print(v, N);
		hashInsertArray(T, v, N);
		// printHash(T, N);

		int toSearchFind[m_Analysis / 2];
		for (int i = 0; i < m_Analysis / 2; i++)
			toSearchFind[i] = v[i + 6];
		knuthShuffle(toSearchFind, m_Analysis / 2);
		// print(toSearchFind, m_Analysis / 2);

		int toSearchNotFind[m_Analysis / 2];
		for (int i = 0; i < m_Analysis / 2; i++)
			// toSearchNotFind[i] = -1 * toSearchFind[i];
			FillRandomArray(toSearchNotFind, m_Analysis / 2, 10, 99, false, UNSORTED);

		for (int i = 0; i < m_Analysis / 2; i++)
		{
			hashSearchAnalysis(T, N, toSearchFind[i], efortGasite);
			// cout << "gasite: " << efortGasite << "\n";
		}
		cout << "gasite: " << efortGasite << "\n";
		arrayEfortGasite[k1] = efortGasite;
		k1++;

		/*for (int i = 0; i < m_Analysis / 2; i++)
		{
			hashSearchAnalysis(T, N, toSearchNotFind[i], efortNegasite);
			// cout << "negasite: " << efortNegasite << "\n";
		}
		cout << "negasite: " << efortNegasite << "\n";
		arrayEfortNegasite[k2] = efortNegasite;
		k2++;*/

	}
	cout << "average: " << averageEfort(arrayEfortGasite) << "\n";
	// cout << "average: " << averageEfort(arrayEfortNegasite) << "\n";
}

void searchForEachFactor()
{
	double factor[5] = { 0.8, 0.85, 0.9, 0.95, 0.99 };
	for (int i = 0; i < 5; i++)
	{
		searchForFillFactor(UNSORTED, factor[i]);
		cout << "\n";
	}
		
	// searchForFillFactor(UNSORTED, factor[3]);
}

void deleteForFillFactor()
{
	int k1 = 0;
	int arrayEfortGasite[NR_TESTS];
	int k2 = 0;
	int arrayEfortNegasite[NR_TESTS];
	for (int test = 0; test < NR_TESTS; test++)
	{
		int n = floor(deleteFactorStart * N);
		int v[N] = { 0 };
		Entry T[N];
		initializeTable(T, N);
		int efortGasite = 0;
		int efortNegasite = 0;

		FillRandomArray(v, n, 100, 100000, false, UNSORTED);
		// print(v, N);
		hashInsertArray(T, v, N);
		//printHash(T, N);

		int nToDelete = floor((deleteFactorEnd - deleteFactorStart) * N);
		nToDelete *= -1;
		for (int i = 0; i < nToDelete; i++)
			hashDelete(T, N, v[i + 5]);

		int toSearchFind[m_Analysis / 2];
		for (int i = 0; i < m_Analysis / 2; i++)
			toSearchFind[i] = v[i + 6];

		int toSearchNotFind[m_Analysis / 2];
		for (int i = 0; i < m_Analysis / 2; i++)
			FillRandomArray(toSearchNotFind, m_Analysis / 2, 10, 99, false, UNSORTED);

		for (int i = 0; i < m_Analysis / 2; i++)
			hashSearchAnalysis(T, N, toSearchFind[i], efortGasite);
		cout << "gasite: " << efortGasite << "\n";
		arrayEfortGasite[k1] = efortGasite;
		k1++;

		for (int i = 0; i < m_Analysis / 2; i++)
			hashSearchAnalysis(T, N, toSearchNotFind[i], efortNegasite);
		cout << "negasite: " << efortNegasite << "\n\n";
		arrayEfortNegasite[k2] = efortNegasite;
		k2++;
	}
	cout << "\naverage: " << averageEfort(arrayEfortGasite) << "\n";
	cout << "average: " << averageEfort(arrayEfortNegasite) << "\n";
}

int main()
{
	demo();
	// searchForEachFactor();
	// deleteForFillFactor();
	return 0;
}