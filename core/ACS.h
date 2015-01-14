
#pragma once
#include "algorithms.h"

class ACSAlgorithm {
private:
	static int N_ANT;
	static float P_PER_EDGE;
	static float DECAY;

	static float **p_matrix;
	
	static void clear_visited(bool bv[], int n) {
		for (int i = 0; i < n; i++) {
			bv[i] = false;
		}
	}

public:
	static Cycle* perform_calculations(Graph graph) {
		Cycle* best = new Cycle(graph.get_size());
		best->set_cycle_lenght(INT_MAX-1);
		Cycle current(graph.get_size());
		srand(time(NULL));
		
		p_matrix = new float * [graph.get_size()];
		for (int i = 0; i < graph.get_size(); i++) {
			p_matrix[i] = new float [graph.get_size()];
			for (int j = 0; j < graph.get_size(); j++)
				p_matrix[i][j] = 1.0f;
		}

		bool* visited = new bool [graph.get_size()];

		for (int ant = 0; ant < N_ANT; ant++) {
			current.clear_cycle();
			clear_visited(visited, graph.get_size());
			int first_node = rand()%graph.get_size();
			int prev_node = first_node;
			current.push_node(first_node);
			visited[prev_node] = true;
			for (int n = 0; n < graph.get_size(); n++) {
				float p_sum = 0.0f;
				for (int v = 0; v < graph.get_size(); v++) {
					if (!visited[v]) {
						p_sum += p_matrix[prev_node][v];
					}
				}
				float random = rand()/float(RAND_MAX);
				float p_current = 0.0f;
				for (int v = 0; v < graph.get_size(); v++) {
					if (!visited[v]) {
						p_current += p_matrix[prev_node][v] / p_sum;
						if (random <= p_current) {
							visited[v] = true;
							current.push_node(v);
							current.add_cycle_lenght(graph.get_weight(prev_node, v));
							p_matrix[prev_node][v] += P_PER_EDGE / graph.get_weight(prev_node, v);
							p_matrix[v][prev_node] = p_matrix[prev_node][v];
							prev_node = v;
							break;
						}
					}
				}
			}
			current.add_cycle_lenght(graph.get_weight(prev_node, first_node));
			if  (current.get_cycle_lenght() < best->get_cycle_lenght())
				*best = current;
		}
		return best;
	}
};

float **ACSAlgorithm::p_matrix = NULL;
float ACSAlgorithm::P_PER_EDGE = 10000.0f;
int ACSAlgorithm::N_ANT = 10000;