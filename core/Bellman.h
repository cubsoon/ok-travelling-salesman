// HeldKarpAlgorithm.h : Algorytm programowania dynamicznego.
// https://www.youtube.com/watch?v=zNEQTugO7NM
// http://cse.iitkgp.ac.in/~abhij/course/lab/Algo1/Autumn11/lab/assgn1.html

#pragma once
#include "algorithms.h"

class HeldKarpAlgorithm {
private:
	
	static int ** stored_B;
	static int ** stored_L;
	static unsigned int rows;
	static unsigned int cols;
	static unsigned int bits;

	// tworzenie tablicy optymalnych podrozwiazan (B)
	// i tablicy wskazujacej na uzyty w podrozwiazaniu wierzcholek (L)
	// ich rozmiar: kolumn - V-1
	//             wierszy - 2^(V-1)
	static void create_tables(Graph * g) {
		cols = g->get_size() - 1;
		bits = g->get_size() - 1;
		rows = (1U << bits);

		stored_B = new int * [cols];
		stored_L = new int * [cols];
		for (unsigned int c = 0; c < cols; c++) {
			stored_B[c] = new int [rows];
			stored_L[c] = new int [rows];
			for (unsigned int r = 0; r < rows; r++) {
				stored_B[c][r] = -1;
				stored_L[c][r] = -1;
			}
		}
	}

	static void delete_tables() {
		for (unsigned int c = 0; c < cols; c++) {
			delete [] stored_B[c];
			delete [] stored_L[c];
		}
		delete [] stored_B;
		delete [] stored_L;
		cols = 0U;
		bits = 0U;
		rows = 0U;
	}

	static int B(Graph * g, unsigned int set, unsigned int target) {
		// czesciowe rozwiazanie juz policzone
		if (stored_B[target][set] != -1)
			return stored_B[target][set];
		
		// wszystkie wierzcholki wykorzystane
		if (set == ((1U << (bits)) - 1))
			return stored_B[target][set] = g->get_weight(0, target+1);

		// uzupelnianie tablicy optymalnych podrozwiazan
		int cur;
		int best = INT_MAX-1;
		for (unsigned int b = 0; b < bits; b++) {
			if (b != target && (set & (1U << b)) == 0) {
				cur = g->get_weight(b+1, target+1) + B(g, set | (1U << b), b);
				if (cur < best) {
					stored_L[target][set] = b;
					best = cur;
				}
			}
		}
		return stored_B[target][set] = best;
	}

public:
	static Cycle* perform_calculations(Graph graph) {
		Cycle* output = new Cycle(graph.get_size());
		create_tables(&graph);

		// szukanie najlepszego rozwiazanie na podstawie tablicy B
		int best_v = INT_MAX-1;
		unsigned int best_t;
		for (unsigned int i = 0; i < cols; i++) {
			int cur = B(&graph, 1U << i, i) + graph.get_weight(i+1, 0);
			if ( cur < best_v ) {
				best_v = cur;
				best_t = i;
			}
		}

		// odtwarzanie cyklu na podstawie tablicy L
		output->set_cycle_lenght(best_v);
		unsigned int cur_set = 1U << best_t;
		unsigned int cur_tar = best_t;
		output->push_node(best_t + 1);
		while (cur_set != (1U << (bits)) - 1) {
			int new_tar = stored_L[cur_tar][cur_set];
			output->push_node(new_tar + 1);
			cur_tar = new_tar;
			cur_set = cur_set | (1U << new_tar);
		}
		output->push_node(0);
		
		delete_tables();

		return output;
	}
};

int ** HeldKarpAlgorithm::stored_B = NULL;
int ** HeldKarpAlgorithm::stored_L = NULL;
unsigned int HeldKarpAlgorithm::rows = 0U;
unsigned int HeldKarpAlgorithm::cols = 0U;
unsigned int HeldKarpAlgorithm::bits = 0U;



