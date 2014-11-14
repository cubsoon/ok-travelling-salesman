#pragma once

#include "stdafx.h"

class Output {
private:
	int current;
	int *cycle;
	int size_of_cycle;
	int value;
public:
	Output(int);
	Output(Output &);
	~Output();
	void set_value(int i) {value = i;};
	void push_cycle(int);
	int pop_cycle();
	void print_result(std::ostream*, bool);
};


class AdjacencyMatrix {
private:
	void _allocate_matrix(int);
	void _deallocate_matrix();
	int **matrix;
	int size;
public:
	AdjacencyMatrix(int, int, int);
	AdjacencyMatrix(std::istream*);
	AdjacencyMatrix(AdjacencyMatrix &);
	~AdjacencyMatrix();
	int get_size();
	int get_weight(int, int);
	void print_graph(std::ostream*, bool verbose);
};

class PlaceholderAlgorithm {
public:
	static Output* perform_calculations(AdjacencyMatrix);
};