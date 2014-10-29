#pragma once

#include "stdafx.h"

class Output {
private:
	int number_of_steps;
	int *cycle;
};

class Algorithm {
private:
	int number_of_nodes;
	int **matrix;
	void _create_matrix(int);
public:
	Algorithm(int, int, int);
	Algorithm(std::istream);
	~Algorithm();
	Output perform_calculations();
};