// Naive.h : Algorytm przeszukujacy cala przestrzen rozwiazan.
//
// Kolejne permutaje sa generowane algorytmem Steinhausa–Johnsona–Trottera.
// http://en.wikipedia.org/wiki/Steinhaus%E2%80%93Johnson%E2%80%93Trotter_algorithm
//
// Wysiada juz dla 12 wierzcholkow.

#pragma once
#include "algorithms.h"

class NaiveAlgorithm {
private:
	// Algorytm SJT definiuje liczbe posiadajaca kierunek.
	static int* permutation;
	static int* direction;

	// Poczatkowe ustawienie liczb do permutowania.
	static void prepare_permutation(int size) {
		permutation = new int[size];
		direction = new int[size];
		for (int i = 0; i < size; i++) {
			permutation[i] = i;
			direction[i] = -1;
		}
	}

	// Znajduje najwieksza liczbe "mobilna" (jesli istnieje)
	static int get_greatest_mobile_int(int size) {
		int max_i = -1, max_v;
		int i;
		for (i = 0; i < size; i++)
			if (i + direction[i] >= 0 && i + direction[i] < size)
				if (permutation[i] > permutation[i+direction[i]]) {
					max_i = i;
					max_v = permutation[i];
					break;
				}
		for (i++; i < size; i++)
			if (i + direction[i] >= 0 && i + direction[i] < size)
				if (permutation[i] > permutation[i+direction[i]])
					if (permutation[i] > max_v) {
						max_i = i;
						max_v = permutation[i];
					}
		return max_i;
	}

	// Generuje nastepna permutacje.
	static void next_permutation(int mobile, int size) {
		int v = permutation[mobile];
		// Indeksy dwoch liczb
		int	i1 = mobile;
		int	i2 = mobile+direction[mobile];
		// Zamien obie liczby (i ich kierunki)
		int t;
		t = permutation[i1];
		permutation[i1] = permutation[i2];
		permutation[i2] = t;
		t = direction[i1];
		direction[i1] = direction[i2];
		direction[i2] = t;
		// Odwroc kierunek wszystkich liczb wiekszych od "mobilnej"
		for (int n = 0; n < size; n++)
			if (permutation[n] > v)
				direction[n] *= -1;
	}

	static int get_sum_of_weights(AdjacencyMatrix *graph) {
		int sum = 0;
		int i;
		for (i = 0; i < graph->get_size()-1; i++) {
			sum += graph->get_weight(permutation[i], permutation[i+1]);
		}
		sum += graph->get_weight(permutation[i], permutation[0]);
		return sum;
	}
public:
	static Output* perform_calculations(AdjacencyMatrix graph) {
		prepare_permutation(graph.get_size());
		int i, v;
		// Pierwsza permutacja - 0 1 2 ... n
		int *best_permutation = new int[graph.get_size()];
		for (int n = 0; n < graph.get_size(); n++)
			best_permutation[n] = permutation[n];
		int best_v = get_sum_of_weights(&graph);
		// Dopoki istnieje liczba "mobilna" - istnieja kolejne permutacje.
		while ( (i = get_greatest_mobile_int(graph.get_size())) >= 0 ) {
			next_permutation(i, graph.get_size());
			if ( (v = get_sum_of_weights(&graph)) < best_v ) {
				best_v = v;
				for (int n = 0; n  < graph.get_size(); n++)
					best_permutation[n] = permutation[n];
			}
		}
		// wyjscie
		Output* output = new Output(graph.get_size());
		for (int n = 0; n < graph.get_size(); n++)
			output->push_cycle(best_permutation[n]);
		output->set_value(best_v);

		delete [] best_permutation;
		delete [] permutation;
		delete [] direction;
		return output;
	}
};

int *NaiveAlgorithm::permutation = NULL;
int *NaiveAlgorithm::direction = NULL;