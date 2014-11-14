//TO BE IMPLEMENTED

#pragma once
#include "algorithms.h"

class HeldKarpAlgorithm {
private:
	static int C(int* s, int size_s, int i, AdjacencyMatrix *graph) {
		if (size_s == 2)
			return graph->get_weight(0, i);
		int min = INT_MAX;
		int *ss = new int[size_s-1];
		int cur, t;
		for (int j = 1; j < size_s; j++) {
			if (j != i) {
				for (t = 0; t < size_s; t++) {
					if (t == i)
						break;
					else
						ss[t] = s[t];
				}
				for (t++; t < size_s; t++) {
					ss[t-1] = s[t];
				}
				cur = C(ss, size_s-1, j, graph) + graph->get_weight(j, i);
				if ( cur < min) {
					min = cur;
				}
			}
		}
		delete [] ss;
		return min;
	}
public:
	static Output* perform_calculations(AdjacencyMatrix *graph) {
		Output* output = new Output(graph->get_size());
		int min_v = INT_MAX;
		int cur;
		int *s = new int[graph->get_size()];
		for (int i = 0; i < graph->get_size(); i++)
			s[i] = i;
		for (int i = 1; i < graph->get_size(); i++) {
			cur = C(s, graph->get_size(), i, graph) + graph->get_weight(i, 0);
			if (cur < min_v)
				min_v = cur;
		}
		output->set_value(min_v);
		delete [] s;
		return output;
	}
};