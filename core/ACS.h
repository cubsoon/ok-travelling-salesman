// ACS.h: Algorytm znajdujacy dobrej jakosci przyblizone 
// rozwiazanie problemu komiwoja¿era poprzez symulacjê kolonii mrowek.

#pragma once
#include "algorithms.h"

class ACSAlgorithm {
private:
	static int NUMBER_OF_ANTS; // ilosc zasymulowanych mrowek

	static float PH_PER_EDGE; // stala proporcjonalna do pozostawianych na krawedziach feromonow

	static float PH_AT_BEGINNING; // poczatkowa ilosc feromonow na krawedziach

	static float **ph_matrix; // macierz feromonow 
	                          //   (dziala jak wazona sasiedztwa, wagi co innego oznaczaja)
	
	// czysci tablice odwiedzonych wiercholkow
	static void clear_visited(bool bv[], int n) {
		for (int i = 0; i < n; i++) {
			bv[i] = false;
		}
	}

public:
	static Cycle* perform_calculations(Graph graph) {
		Cycle* best = new Cycle(graph.get_size()); // najlepsze rozwiazanie
		best->set_cycle_lenght(INT_MAX-1);         //

		Cycle current(graph.get_size()); // obecne rozwiazanie (trasa mrowki)
		
		srand(time(NULL));
		
		ph_matrix = new float * [graph.get_size()];      // tworzenie macierzy feromonow
		for (int i = 0; i < graph.get_size(); i++) {     //
			ph_matrix[i] = new float [graph.get_size()]; //
			for (int j = 0; j < graph.get_size(); j++)   //
				ph_matrix[i][j] = PH_AT_BEGINNING;       //
		}                                                //

		bool* visited = new bool [graph.get_size()]; // tablica odwiedzonych wierzcholkow

		for (int ant = 0; ant < NUMBER_OF_ANTS; ant++) {
			current.clear_cycle();
			clear_visited(visited, graph.get_size());
			int first_node = rand()%graph.get_size(); // losujemy poczatek 
			int prev_node = first_node;               //   trasy mrowki
			current.push_node(first_node);            //
			visited[prev_node] = true;                //
			for (int n = 0; n < graph.get_size(); n++) {
				// suma feromonow na wszystkich krawedziach wychodzacych z
				//   obecnego wierzcholka
				float p_sum = 0.0f;
				for (int v = 0; v < graph.get_size(); v++) {
					if (!visited[v]) {
						p_sum += ph_matrix[prev_node][v];
					}
				}
				// losowa liczba z przedzialu [0, 1)
				float random = float(rand())/RAND_MAX;
				// wybor losowego, wolnego wierzcholka 
				// prawdopodobienstwo jest tym wieksze, im wiecej feromonow na krawedzi 
				float p_current = 0.0f;
				for (int v = 0; v < graph.get_size(); v++) {
					if (!visited[v]) {
						p_current += ph_matrix[prev_node][v] / p_sum;
						if (random <= p_current) {
							// wylosowany wierzcholek v:
							// dodany do cyklu
							visited[v] = true;
							current.push_node(v);
							// zauktalizowana dlugosc cyklu
							current.add_cycle_lenght(graph.get_weight(prev_node, v));
							// dodane feromony = PH_PER_EDGE/(dlugosc krawedzi)
							ph_matrix[prev_node][v] += PH_PER_EDGE / graph.get_weight(prev_node, v);
							ph_matrix[v][prev_node] = ph_matrix[prev_node][v];
							prev_node = v;
							break;
						}
					}
				}
			}
			// dodanie dlugosci krawedzi zamykajacej cykl
			current.add_cycle_lenght(graph.get_weight(prev_node, first_node));
			// aktualizacja najepszego rozwiazania, o ile obecne jest lepsze
			if  (current.get_cycle_lenght() < best->get_cycle_lenght())
				*best = current;
		}

		for (int i = 0; i < graph.get_size(); i++) 
			delete [] ph_matrix[i];
		delete [] ph_matrix;

		return best;
	}
};

float **ACSAlgorithm::ph_matrix = NULL;
float ACSAlgorithm::PH_PER_EDGE = 1000.0f;
float ACSAlgorithm::PH_AT_BEGINNING = 1.0f;
int ACSAlgorithm::NUMBER_OF_ANTS = 10000;