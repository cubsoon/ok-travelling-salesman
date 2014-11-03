// core.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "algorithms.h"
#include "Greedy.h"

using namespace std;

void print_usage(char argv0[]) {
	cout << "Usage:" << endl;
	cout << "\t" << argv0 << " <algorithm name> file <file name>" << endl;
	cout << "\t\t" << "Gets graph from file." << endl;
	cout << "\t" << argv0 << " <algorithm name> generate <no. of nodes> <min. weight> <max. weight>" << endl;
	cout << "\t\t" << "Generates graph with random edge weights." << endl;
	cout << "\t" << argv0 << " <algorithm name>" << endl;
	cout << "\t\t" << "Gets the graph from stdin (same format as file)." << endl << endl;
	cout << "Options:" << endl;
	cout << "\t" << "verbose" << endl;
	cout << "\t\t" << "Debug output." << endl;
	cout << "\t" << "savegraph <file name>" << endl;
	cout << "\t\t" << "Saves input graph as a file." << endl;
	cout << "\t" << "printgraph" << endl;
	cout << "\t\t" << "Before performing calculations prints the graph." << endl;
	cout << "\t" << "saveresult <file name>" << endl;
	cout << "\t\t" << "Saves non-verbose output to file." << endl;
}

#define A_GREEDY ("greedy")

int main(int argc, char* argv[])
{
	enum Source {FILE, GENERATION, STDIN};
	bool verbose = false;
	bool save_graph_to_file = false;
	bool save_result_to_file = false;
	bool print_graph = false;
	
	Algorithm *algorithm = NULL;

	Source source = STDIN;
	int gargv[3] = {0, 0, 0};

	char *algorithm_name = NULL;
	char *input_file_name = NULL;
	char *output_graph_file_name = NULL;
	char *output_result_file_name = NULL;
		
	bool correct_parsing = true;
	for (int n = 1; n < argc; n++) {
		if (strcmp(argv[n], "verbose") == 0)
			verbose = true;
		else if (strcmp(argv[n], "savegraph") == 0) {
			if (n+1 < argc) {
				n++;
				save_graph_to_file = true;
				output_graph_file_name = argv[n];
			}
			else {
				correct_parsing = false;
				break;
			}
		}
		// === PARSING ALGORITHM NAME ===
		else if (strcmp(argv[n], A_GREEDY) == 0 ||
				 strcmp(argv[n], "dood") == 0)
			algorithm_name = argv[n];
		// ==============================
		else if (strcmp(argv[n], "file") == 0) {
			if (n+1 < argc) {
				n++;
				source = FILE;
				input_file_name = argv[n];
			}
			else
			{
				correct_parsing = false;
				break;
			}
		}
		else if (strcmp(argv[n], "generate") == 0) {
			if (n+3 < argc) {
				source = GENERATION;
				n++;
				gargv[0] = atoi(argv[n]);
				n++;
				gargv[1] = atoi(argv[n]);
				n++;
				gargv[2] = atoi(argv[n]);
			}
			else {
				correct_parsing = false;
				break;
			}
		}
		else if (strcmp(argv[n], "printgraph") == 0)
			print_graph = true;
		else if (strcmp(argv[n], "savegraph") == 0) {
			if (n+1 < argc) {
				save_graph_to_file = true;
				n++;
				output_graph_file_name = argv[n];
			}
			else {
				correct_parsing = false;
				break;
			}
		}
		else if (strcmp(argv[n], "saveresult") == 0) {
			if (n+1 < argc) {
				save_result_to_file = true;
				n++;
				output_result_file_name = argv[n];
			}
			else {
				correct_parsing = false;
				break;
			}
		}
		else {
			correct_parsing = false;
			break;
		}
	}

	if (correct_parsing == true)
	{
		if (verbose) {
				cout << "tryb gadatliwy" << endl << "algorytm: ";
				cout << (algorithm_name ? algorithm_name : "placeholder");
				cout << endl << "zapis grafu do pliku: " << save_graph_to_file;
				cout << " " << (output_graph_file_name ? output_graph_file_name : "");
				cout << endl << "zrodlo grafu: ";
				cout << (source==FILE ? "FILE" : 
					(source==GENERATION ? "GENERATION" : 
					(source==STDIN ? "STDIN" : "nie znane")));
				cout << " " << (input_file_name ? input_file_name : "");
				cout << endl << "argumenty generacji: ";
				cout << gargv[0] << " " << gargv[1];
				cout << " " << gargv[2] << endl;
				cout << "drukuj graf: " << print_graph << endl << endl;
		}

		istream* input_stream = NULL;
		if (source==STDIN)
			input_stream = &cin;
		else if (source==FILE) {
			input_stream = new ifstream(input_file_name);
		}

		// === CREATING ALGORITHM OBJECT ===
		if (algorithm_name == NULL)
			algorithm = input_stream ? new Algorithm(input_stream) : new Algorithm(gargv[0], gargv[1], gargv[2]);
		else if (strcmp(algorithm_name, A_GREEDY) == 0)
			algorithm = input_stream ? new Greedy(input_stream) : new Greedy(gargv[0], gargv[1], gargv[2]);
		// =================================

		if (source==FILE) {
			delete input_stream;
		}

		if (print_graph)
			algorithm->print_graph(&cout, verbose);

		if (save_graph_to_file) {
			ofstream* output_file = new ofstream(output_graph_file_name);
			algorithm->print_graph(output_file, false);
			delete output_file;
		}

		Output *output = algorithm->perform_calculations();
		output->print_result(&cout, verbose);

		if (save_result_to_file) {
			ofstream* output_file = new ofstream(output_result_file_name);
			output->print_result(output_file, false);
		}

		delete output;
		delete algorithm;
	}
	else
		print_usage(argv[0]);
		return -1;
	return 0;
}

