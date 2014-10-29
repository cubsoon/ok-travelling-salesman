// core.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "algorithms.h"

void print_usage(_TCHAR* argv0) {
	std::cout << "Usage:" << std::endl;
	std::wcout << "\t" << argv0 << " <algorithm name> file <file name>" << std::endl;
	std::cout << "\t\t" << "Gets graph from file." << std::endl;
	std::wcout << "\t" << argv0 << " <algorithm name> generate <no. of nodes> <min. weight> <max. weight>" << std::endl;
	std::cout << "\t\t" << "Generates graph with random edge weights." << std::endl;
	std::wcout << "\t" << argv0 << " <algorithm name>" << std::endl;
	std::cout << "\t\t" << "Gets the graph from stdin (same format as file)." << std::endl << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "\t" << "verbose" << std::endl;
	std::cout << "\t\t" << "Debug output." << std::endl;
	std::cout << "\t" << "savegraph <file name>" << std::endl;
	std::cout << "\t\t" << "Saves input graph as a file." << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int i;
	print_usage(argv[0]);
	std::cin >> i;
	return 0;
}

