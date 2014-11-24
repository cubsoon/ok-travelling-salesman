// Greedy.h : Algorytm znajdyjacy cykl od wiercholka 0,
// wybierajacy najblizsze niewykorzystane wierzcholki.

#pragma once
#include "algorithms.h"
 
class GreedyAlgorithm {
public:
	static Output* perform_calculations(AdjacencyMatrix graph) {
		Output *output = new Output(graph.get_size());
		
		// tablica odwiedzonych wierzcholkow
		bool *used = new bool[graph.get_size()];
		for (int i = 1; i < graph.get_size(); i++)
			used[i] = false;
		
		// pierwszy odwiedzony wierzcholek - indeks 0
		used[0] = true;
		int last = 0;
		output->push_cycle(0);

		int min_v, min_i;
		int sum_v = 0;
		for (int n = 0; n < graph.get_size() - 1; n++) {
			// wyszukiwanie wiercholka o najkrotszej drodze z poprzedniego
			for (int i = 0; i < graph.get_size(); i++)
				if (used[i] == false) {
					min_v = graph.get_weight(last, i);
					min_i = i;
					break;
				}
			for (int i = min_i + 1; i < graph.get_size(); i++) 
				if (used[i] == false && graph.get_weight(last, i) < min_v) {
					min_v = graph.get_weight(last, i);
					min_i = i;
				}

			// laczna droga
			sum_v += min_v;

			// dodawanie kolejnych wierzcholkow do cyklu
			used[min_i] = true;
			last = min_i;
			output->push_cycle(min_i);
		}

		// droga z ostatniego wiercholka do pierwszego (0)
		sum_v += graph.get_weight(last, 0);

		output->set_value(sum_v);
		return output;
	}
};

