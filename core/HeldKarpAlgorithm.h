// HeldKarpAlgorithm.h : Algorytm programowania dynamicznego.
// https://www.youtube.com/watch?v=zNEQTugO7NM

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

	static int ** stored_B;
	static unsigned int rows;
	static unsigned int cols;
	static unsigned int bits;

	static void make_tables(Graph * g) {
		cols = g->get_size() - 1;
		bits = g->get_size() - 1;
		rows = 1 << bits;

		stored_B = new int * [cols];
		for (unsigned int c = 0; c < cols; c++) {
			stored_B[c] = new int [rows];
			for (unsigned int r = 0; r < rows; r++)
				stored_B[c][r] = -1;
		}
	}

	static int B(Graph * g, unsigned int set, int target) {
		if (stored_B[target][set] != -1)
			return stored_B[target][set];
		
		if (set == (1U << (bits+1)) - 1) 
			return g->get_weight(target+1, 0);

		int best, cur;
		unsigned int b;
		for (b = 0; b < bits; b++) {
			best = 2000000;
			if (b != target && (set & (1 << b)) == 0) {
				cur = g->get_weight(target+1, b+1) + B(g, set | (1U << b), b);
				if (cur < best)
					best = cur;
			}
		}
		return stored_B[target][set] = best;
	}

public:
	static Cycle* perform_calculations(Graph graph) {
		Cycle* output = new Cycle(graph.get_size());
		make_tables(&graph);
		int min = 1000000;
		for (unsigned int i = 0; i < cols; i++) {
			int cur = B(&graph, 1U << i, i);
			std::cout << cur << std::endl;
			if ( cur < min )
				min = cur;
		}
		output->set_cycle_lenght(min);
		return output;
	}
};

int ** HeldKarpAlgorithm::stored_B = NULL;
unsigned int HeldKarpAlgorithm::rows = 0;
unsigned int HeldKarpAlgorithm::cols = 0;
unsigned int HeldKarpAlgorithm::bits = 0;



