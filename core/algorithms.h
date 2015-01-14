#pragma once

#include "stdafx.h"

class Cycle {
private:
	int current;
	int *node_vector;
	int node_vector_lenght;
	int cycle_lenght;
public:
	Cycle(int);
	Cycle(const Cycle &);
	~Cycle();
	Cycle &operator=(const Cycle &);
	void set_cycle_lenght(int l) {cycle_lenght = l;};
	void add_cycle_lenght(int l) {cycle_lenght += l;};
	int get_cycle_lenght() {return cycle_lenght;};
	void clear_cycle();
	void push_node(int);
	int pop_node();
	void print_cycle(std::ostream*, bool);
};


class Graph {
private:
	void _allocate_matrix(int);
	void _deallocate_matrix();
	int **weighted_adjacency_matrix;
	int size;
public:
	Graph(int, int, int);
	Graph(std::istream*);
	Graph(Graph &);
	~Graph();
	int get_size();
	int get_weight(int, int);
	void print_graph(std::ostream*, bool verbose);
};

class PlaceholderAlgorithm {
public:
	static Cycle* perform_calculations(Graph);
};