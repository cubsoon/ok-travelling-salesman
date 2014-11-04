#pragma once
#include "algorithms.h"
 
class Greedy :
	public Algorithm
{
public:
	Greedy(int non, int min, int max) : Algorithm(non, min, max) {};
	Greedy(std::istream* input) : Algorithm(input) {};

	Output* perform_calculations() {
		Output *output = new Output(number_of_nodes);
		
		// tablica odwiedzonych wierzcholkow
		bool *used = new bool[number_of_nodes];
		for (int i = 1; i < number_of_nodes; i++)
			used[i] = false;
		
		// pierwszy odwiedzony wierzcholek - indeks 0
		used[0] = true;
		int last = 0;
		output->push_cycle(0);

		int min_v, min_i;
		int sum_v = 0;
		for (int n = 0; n < number_of_nodes - 1; n++) {
			// wyszukiwanie wiercholka o najkrotszej drodze z poprzedniego
			for (int i = 0; i < number_of_nodes; i++)
				if (used[i] == false) {
					min_v = matrix[last][i];
					min_i = i;
					break;
				}
			for (int i = min_i + 1; i < number_of_nodes; i++) 
				if (used[i] == false && matrix[last][i] < min_v) {
					min_v = matrix[last][i];
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
		sum_v += matrix[last][0];

		output->set_value(sum_v);
		return output;
	}
};

