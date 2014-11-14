#include "stdafx.h"
#include "algorithms.h"

AdjacencyMatrix::AdjacencyMatrix(int number_of_nodes, int min_distance, int max_distance) {
	srand((unsigned int)(time(time_t(0))));

	this->size = number_of_nodes;
	_allocate_matrix(number_of_nodes);

	for (int i = 0; i < number_of_nodes; i++) {
		for (int j = 0; j < i; j++) {
			matrix[i][j] = min_distance + rand()%(max_distance - min_distance + 1);
			matrix[j][i] = matrix[i][j];
		}
		matrix[i][i] = INT_MAX;
	}
}

AdjacencyMatrix::AdjacencyMatrix(std::istream *input) {
	*input >> this->size;
	_allocate_matrix(size);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			*input >> matrix[i][j];
}

AdjacencyMatrix::AdjacencyMatrix(AdjacencyMatrix &other) {
	this->size = other.size;
	_allocate_matrix(this->size);
	for (int i = 0; i < this->size; i++)
	for (int j = 0; j < this->size; j++)
		matrix[i][j] = other.matrix[i][j];
}

void AdjacencyMatrix::_allocate_matrix(int size) {
	this->matrix = new int*[size];
	for (int i = 0; i < size; i++)
		this->matrix[i] = new int[size];
}

void AdjacencyMatrix::_deallocate_matrix() {
	for (int i = 0; i < this->size; i++)
		delete [] this->matrix[i];
	delete [] this->matrix;
}

AdjacencyMatrix::~AdjacencyMatrix() {
	_deallocate_matrix();
}

int AdjacencyMatrix::get_size() {
	return this->size;
}

int AdjacencyMatrix::get_weight(int from, int to) {
	return this->matrix[from][to];
}



Output::Output(int size_of_cycle) {
	current = 0;
	this->size_of_cycle = size_of_cycle;
	this->cycle = new int[size_of_cycle];
}

Output::Output(Output &other) {
	this->size_of_cycle = other.size_of_cycle;
	this->current = other.current;
	this->cycle = new int[this->size_of_cycle];
	for (int i = 0; i < current; i++)
		this->cycle[i] = other.cycle[i];
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

void AdjacencyMatrix::print_graph(std::ostream *output, bool verbose) {
	if (verbose) *output << "Liczba wierzcholkow: ";
	*output << this->size << std::endl;
	if (verbose) *output << "Macierz grafu:" << std::endl;
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++)
			*output << matrix[i][j] << " ";
		*output << std::endl;
	}
	*output << std::endl;
}

Output* PlaceholderAlgorithm::perform_calculations(AdjacencyMatrix graph) {
	Output *output = new Output(graph.get_size());
	int value = 0;
	for (int i = 0; i < graph.get_size(); i++)
	{
		output->push_cycle(i);
		value += graph.get_weight(i, (i+1)%graph.get_size());
	}
	output->set_value(value);
	return output;
}