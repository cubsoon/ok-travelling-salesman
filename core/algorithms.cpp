#include "stdafx.h"
#include "algorithms.h"

Output::Output(int size_of_cycle) {
	current = 0;
	this->size_of_cycle = size_of_cycle;
	this->cycle = new int[size_of_cycle];
}

Output::~Output() {
	delete [] cycle;
}

void Output::push_cycle(int node) {
		cycle[current] = node;
		current++;
}

int Output::pop_cycle() {
		current--;
		return cycle[current+1];
}

void Output::print_result(std::ostream *output, bool verbose) {
	if (verbose) *output << "Liczba elementow cyklu: ";
	*output << size_of_cycle << std::endl;
	if (verbose) *output << "Cykl: ";
	for (int i = 0; i < size_of_cycle; i++)
		*output << cycle[i] << " ";
	*output << std::endl;
	if (verbose) *output << "Wartosc cyklu: ";
	*output << value << std::endl;
}

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
			matrix[i][j] = min_distance + rand()%(max_distance - min_distance + 1);
			matrix[j][i] = matrix[i][j];
		}
		matrix[i][i] = 0;
	}
}


Algorithm::Algorithm(std::istream *input) {
	*input >> number_of_nodes;
	_create_matrix(number_of_nodes);
	for (int i = 0; i < number_of_nodes; i++)
		for (int j = 0; j < number_of_nodes; j++)
			*input >> matrix[i][j];
}

Algorithm::~Algorithm() {
	for (int i = 0; i < number_of_nodes; i++)
		delete [] matrix[i];
	delete [] matrix;
}

Output* Algorithm::perform_calculations() {
	Output *output = new Output(number_of_nodes);
	int value = 0;
	for (int i = 0; i < number_of_nodes; i++)
	{
		output->push_cycle(i);
		value += matrix[i][(i+1)%number_of_nodes];
	}
	output->set_value(value);
	return output;
}

void Algorithm::print_graph(std::ostream *output, bool verbose) {
	if (verbose) *output << "Liczba wierzcholkow: ";
	*output << number_of_nodes << std::endl;
	if (verbose) *output << "Macierz grafu:" << std::endl;
	for (int i = 0; i < number_of_nodes; i++) {
		for (int j = 0; j < number_of_nodes; j++)
			*output << matrix[i][j] << " ";
		*output << std::endl;
	}
	*output << std::endl;
}