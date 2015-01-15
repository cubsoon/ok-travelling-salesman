// BruteForce.h : Algorytm rekurencyjnie przeszukujacy zbior rozwiazan,
// ale nawracajacy przy rozwiazaniach, ktorych koszt czesciowy jest
// wiekszy niz koszt najlepszego poprzednio znalezionego rozwiazania.

#pragma once
#include "algorithms.h"

class BruteForceAlgorithm {
private:
	static void BnB(int c[], int c_i, int c_v, int last_used, bool not_used[], int bs[], int * bs_v, Graph * g) {
		// -- warunki nawracania --
		// czesciowe rozwiazanie jest gorsze
		if ( c_v >= *bs_v ) {
			not_used[last_used] = true;
			return;
		}
		// wszystkie wierzcholki wykorzystane
		if ( c_i == g->get_size() ) {
			// sprawdzenie pelnego rozwiazania
			if ( c_v + g->get_weight(last_used, 0) < *bs_v ) {
				*bs_v = c_v + g->get_weight(last_used, 0);
				for (int i = 0; i < g->get_size(); i++)
					bs[i] = c[i];
			}
			return;
		}
		// -- rekurencja --
		for (int i = 0; i < g->get_size(); i++)
			if (not_used[i]) {
				not_used[i] = false;
				c[c_i] = i;
				BnB(c, c_i + 1, c_v + g->get_weight(last_used, i), i, not_used, bs, bs_v, g);
				//         ^                 ^                     ^
				// zaglebienie rekurencji    |         ostatnio uzyty wierzcholek
				//            nowa wartosc czesciowego rozwiazania
				not_used[i] = true;
			}
		return;
	}
public:
	static Cycle* perform_calculations(Graph graph) {
		int bs_v = INT_MAX-1; // wartosc najlepszego rozwiazania
		int * c = new int[graph.get_size()]; // tablica obecnego rozwiazania
		int * bs = new int[graph.get_size()]; // tablica najlepszego rozwiazania
		bool * not_used = new bool[graph.get_size()]; // czy wierzcholek juz uzyty w rozwiazaniu
		for (int i = 1; i < graph.get_size(); i++)    //
			not_used[i] = true;                       //
		not_used[0] = false; // przeszukiwanie zaczynamy od wierzcholka '0'
		c[0] = 0;            //
		BnB(c, 1, 0, 0, not_used, bs, &bs_v, &graph);
		
		Cycle* output = new Cycle( graph.get_size() ); // wyjscie algorytmu
		for (int i = 0; i < graph.get_size(); i++)     //
			output->push_node(bs[i]);                  //
		output->set_cycle_lenght(bs_v);                //

		delete [] c;
		delete [] bs;
		delete [] not_used;

		return output;
	}
};

