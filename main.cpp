#include "ml_digger.h"

#include <ctime>
#include <iostream>
#include <string>
#include <random>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " map_file.txt" << std::endl;
		return EXIT_FAILURE;
	}

	std::string userInput = argv[1];
	Digger digger(userInput, 50, 2, 3, 10);
	digger.find_path();
}