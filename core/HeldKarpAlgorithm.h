//TO BE IMPLEMENTED

#pragma once
#include "algorithms.h"

class HeldKarpAlgorithm {
private:
	// int ** B
	// Tablica optymalnych podrozwiazan.
	// Pierwszy indeks to zbior wierzcholkow wchodzacych w rozwiazanie.
	// Zbior zapisany binarnie (bit 1 na pewnej poz. 
	//                                   - wiercholek nalezy do zbioru).
	// Drugi indeks to ostatni wierzcholek optymalnego podrozwiazania.
	//
	// === PRZYKLADOWO ===
	// Dany graf o 5 wiercholkach.
	// Tablica ma rozmiar 2^3 na 4.
	// (2^3 - wszystkie mozliwe podzbiory wiercholkow 
	//                                     miedzy pierwszym a ostatnim)
	// (4 - mozliwe ostatnie wiercholki)
	//
	// Przykladowy indeks:
	// [ 0  b  1  1  0 ][ 2 ] 
	//        (4)(2)(1)  (3)    <= bity odpowiadaja danym wiercholkom
	//          /\                   pierwszym jest wiercholek (0)   
	//			||
	//     jako ze (3) jest ostatnim wiercholkiem,
	//      nie jest brany pod uwage w zbiorze
	//
	// Wartosc B[0b110][2] to najkrotsza droga wychodzaca z wiercholka (0),
	//     przechodzaca przez wierzcholki (2) i (4) i konczaca sie w (3).
	//
	// Rozwiazanie TSP to wartosc minimalna:
	// B[0b111][n] + koszt( (n+1), (0) ),   dla n = {0, 1, 2, 3}
	// ===================
	static int ** B;
	static int ** L;
	static unsigned int rows;
	static unsigned int rows_s;
	static unsigned int cols;

	static void create_tables(int size) {
		// Ilosc wierzcholkow bez pierwszego (|V|-1).
		cols = size - 1;
		// Ilosc podzbiorow zbioru pozostalych wierzcholkow 2^(|V|-2).
		rows_s = size - 2;
		rows = 2 << rows_s;
		// Tworzenie tablic.
		// Tutaj widac zlozonosc pamieciowa O(n*2^n).
		B = new int * [rows];
		for (unsigned int i = 0; i < rows; i++)
			B[i] = new int[cols];
	}

	static unsigned int remove_bit(unsigned int set, unsigned int pos) {
		return set & ~(1U << pos);
	}

	static unsigned int add_bit(unsigned int set, unsigned int pos) {
		return set | (1U << pos);
	}

	static void calculate_tables(AdjacencyMatrix * g);

public:
	static Output* perform_calculations(AdjacencyMatrix graph) {
		Output* output = new Output(graph.get_size());
		create_tables(graph.get_size());
		calculate_tables(&graph);
		int min = B[rows-1][0];
		for (unsigned int i = 1; i < cols; i++) {
			int cur = B[rows-1][i];
			if ( cur < min )
				min = cur;
		}
		output->set_value(min);
		return output;
	}
};

int ** HeldKarpAlgorithm::B = NULL;
int ** HeldKarpAlgorithm::L = NULL;
unsigned int HeldKarpAlgorithm::cols = 0;
unsigned int HeldKarpAlgorithm::rows = 0;
unsigned int HeldKarpAlgorithm::rows_s = 0;


