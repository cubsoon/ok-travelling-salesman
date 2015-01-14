#include "stdafx.h"
#include "algorithms.h"

Graph::Graph(int number_of_nodes, int min_distance, int max_distance) {
	srand((unsigned int)(time(time_t(0))));

	this->size = number_of_nodes;
	_allocate_matrix(number_of_nodes);

	for (int i = 0; i < number_of_nodes; i++) {
		for (int j = 0; j < i; j++) {
			weighted_adjacency_matrix[i][j] = min_distance + rand()%(max_distance - min_distance + 1);
			weighted_adjacency_matrix[j][i] = weighted_adjacency_matrix[i][j];
		}
		weighted_adjacency_matrix[i][i] = 0;
	}
}

Graph::Graph(std::istream *input) {
	*input >> this->size;
	_allocate_matrix(size);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			*input >> weighted_adjacency_matrix[i][j];
}

Graph::Graph(Graph &other) {
	this->size = other.size;
	_allocate_matrix(this->size);
	for (int i = 0; i < this->size; i++)
	for (int j = 0; j < this->size; j++)
		weighted_adjacency_matrix[i][j] = other.weighted_adjacency_matrix[i][j];
}

void Graph::_allocate_matrix(int size) {
	this->weighted_adjacency_matrix = new int*[size];
	for (int i = 0; i < size; i++)
		this->weighted_adjacency_matrix[i] = new int[size];
}

void Graph::_deallocate_matrix() {
	for (int i = 0; i < this->size; i++)
		delete [] this->weighted_adjacency_matrix[i];
	delete [] this->weighted_adjacency_matrix;
}

Graph::~Graph() {
	_deallocate_matrix();
}

int Graph::get_size() {
	return this->size;
}

int Graph::get_weight(int from, int to) {
	return this->weighted_adjacency_matrix[from][to];
}



Cycle::Cycle(int node_vector_lenght) {
	current = 0;
	cycle_lenght = 0;
	this->node_vector_lenght = node_vector_lenght;
	this->node_vector = new int[node_vector_lenght];
	for (int i = 0; i < node_vector_lenght; i++)
		this->node_vector[i] = -1;
}

Cycle::Cycle(const Cycle &other) {
	this->node_vector_lenght = other.node_vector_lenght;
	this->current = other.current;
	this->cycle_lenght = other.cycle_lenght;
	this->node_vector = new int[this->node_vector_lenght];
	for (int i = 0; i < this->current; i++)
		this->node_vector[i] = other.node_vector[i];
}

Cycle &Cycle::operator=(const Cycle &other) {
    this->node_vector_lenght = other.node_vector_lenght;
	this->current = other.current;
	this->cycle_lenght = other.cycle_lenght;
	for (int i = 0; i < this->current; i++)
		this->node_vector[i] = other.node_vector[i];
    return *this;
  }

Cycle::~Cycle() {
	delete [] node_vector;
}

void Cycle::clear_cycle() {
	this->current = 0;
	this->cycle_lenght = 0;
}

void Cycle::push_node(int node) {
		node_vector[current] = node;
		current++;
}

int Cycle::pop_node() {
		current--;
		return node_vector[current+1];
}

void Cycle::print_cycle(std::ostream *output, bool verbose) {
	if (verbose) *output << "Liczba elementow cyklu: ";
	*output << node_vector_lenght << std::endl;
	if (verbose) *output << "Cykl: ";
	for (int i = 0; i < node_vector_lenght; i++)
		*output << node_vector[i] << " ";
	*output << std::endl;
	if (verbose) *output << "Wartosc cyklu: ";
	*output << cycle_lenght << std::endl;
}

void Graph::print_graph(std::ostream *output, bool verbose) {
	if (verbose) *output << "Liczba wierzcholkow: ";
	*output << this->size << std::endl;
	if (verbose) *output << "Macierz grafu:" << std::endl;
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++)
			*output << weighted_adjacency_matrix[i][j] << " ";
		*output << std::endl;
	}
	*output << std::endl;
}

Cycle* PlaceholderAlgorithm::perform_calculations(Graph graph) {
	Cycle *output = new Cycle(graph.get_size());
	int cycle_lenght = 0;
	for (int i = 0; i < graph.get_size(); i++)
	{
		output->push_node(i);
		cycle_lenght += graph.get_weight(i, (i+1)%graph.get_size());
	}
	output->set_cycle_lenght(cycle_lenght);
	return output;
}