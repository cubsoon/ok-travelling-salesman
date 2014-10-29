#include "stdafx.h"
#include "algorithms.h"

void Algorithm::_create_matrix(int number_of_nodes) {
	this->matrix = new int*[number_of_nodes];
	for (int i = 0; i < number_of_nodes; i++)
		this->matrix[i] = new int[number_of_nodes];
}

Algorithm::Algorithm(int number_of_nodes, int min_distance, int max_distance) {
	srand((unsigned int)(time(time_t(0))));

	this->number_of_nodes = number_of_nodes;
	_create_matrix(number_of_nodes);

	for (int i = 0; i < number_of_nodes; i++) {
		for (int j = 0; j < i; j++) {
			matrix[i][j] = min_distance + rand()%(max_distance - min_distance);
			matrix[j][i] = matrix[i][j];
		}
		matrix[i][i] = 0;
	}
}

Algorithm::Algorithm(std::istream s) {
	s >> number_of_nodes;
	_create_matrix(number_of_nodes);
	for (int i = 0; i < number_of_nodes; i++)
		for (int j = 0; j < number_of_nodes; j++)
			s >> matrix[i][j];
}

Algorithm::~Algorithm() {
	for (int i = 0; i < number_of_nodes; i++)
		delete [] this->matrix[i];
	delete [] matrix;
}