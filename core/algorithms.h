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
	~Output();
	void set_value(int i) {value = i;};
	void push_cycle(int);
	int pop_cycle();
	void print_result(std::ostream*, bool);
};

class Algorithm {
private:
	void _create_matrix(int);
protected:
	int number_of_nodes;
	int **matrix;
public:
	Algorithm(int, int, int);
	Algorithm(std::istream*);
	~Algorithm();
	virtual Output* perform_calculations();
	void print_graph(std::ostream*, bool);
};