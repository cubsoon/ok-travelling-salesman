// Greedy.h : Algorytm zachlanny buduj¹cy cykl poprzez wybieranie
// najkrotszych krawedzi grafu.

#pragma once
#include "algorithms.h"

class GreedyAlgorithm {
private: 

	struct Edge {
		int from;
		int to;
		int lenght;
	};

	static const int N_NONE = -1;
	struct Node {
		int previous;
		int next;
	};

	static int compare(const Edge *arg1, const Edge *arg2) {
		return arg1->lenght - arg2->lenght;
	}

	static bool does_not_close_cycle(Node *node, Edge edge) {
		int current_node = edge.from;
		while (current_node != N_NONE && current_node != edge.to)
			current_node = node[current_node].previous;
		return current_node == N_NONE;
	}

public:

	static Cycle* perform_calculations(Graph graph) {
		Cycle *output = new Cycle(graph.get_size());

		// -- Tworzymy wektor krawêdzi grafu. --
		int number_of_edges = graph.get_size()*(graph.get_size()-1);
		Edge *edge = new Edge[number_of_edges];
		int en = 0;
		for (int i = 0; i < graph.get_size(); i++) {
			for (int j = 0; j < graph.get_size(); j++) {
				if (i != j) {
					edge[en].from = i;
					edge[en].to = j;
					edge[en].lenght = graph.get_weight(i, j);
					en++;
				}
			}
		}

		// -- Sortujemy krawêdzie rosn¹co. --
		qsort((void *)edge, number_of_edges, sizeof(*edge), (int(*)(const void *, const void *))compare);

		// -- Wybór krawêdzi (od najkrótszych). --
		// tablica wiercholkow do oznaczania kolejnoœci
		Node *node = new Node[graph.get_size()];
		for (int n = 0; n < graph.get_size(); n++) {
			node[n].previous = N_NONE;
			node[n].next = N_NONE;
		}
		int ea = 0; // krawedzie dodane
		int ec = 0; // obecna krawedz
		int lenght = 0;
		// dopoki nie dodamy tyle krawedzi ile wiercholkow...
		while (ea < graph.get_size()) {
			// ...sprawdzamy czy dana krawedz pasuje do cyklu Hamiltona...
			if (node[edge[ec].from].next == N_NONE)
				if (node[edge[ec].to].previous == N_NONE)
					if (does_not_close_cycle(node, edge[ec]) || ea == graph.get_size()-1) {
						// ...i jesli tak to dodajemy ja
						ea++;
						lenght += edge[ec].lenght;
						node[edge[ec].from].next = edge[ec].to;
						node[edge[ec].to].previous = edge[ec].from;
					}
					ec++;
		}

		// -- Odczytujemy kolejnosc z tablicy wiercholkow. --
		int current_node = 0;
		for (int n = 0; n < graph.get_size(); n++) {
			output->push_node(current_node);
			current_node = node[current_node].next;
		}
		output->set_cycle_lenght(lenght);

		delete [] edge;
		delete [] node;

		return output;
	}
};

