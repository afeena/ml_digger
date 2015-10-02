#include "config.h"
#include "ml_digger.h"

#include <iostream>
#include <string>

const int Config::POPULATION_SIZE = 15;
const int Config::LEVEL_COUNTS = 16;
const int Config::MUTATE_SIZE = 2;

int main(int argc, char *argv[]) {
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " map_file.txt" << std::endl;
		return EXIT_FAILURE;
	}

	std::string userInput = argv[1];
	Digger digger(userInput);
	digger.find_path();
}
