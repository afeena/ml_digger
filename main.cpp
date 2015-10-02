#include "config.h"
#include "ml_digger.h"

#include <ctime>
#include <iostream>
#include <string>
#include <random>

const int Config::POPULATION_SIZE = 16;
const int Config::MUTATE_SIZE = 3;
const int Config::MUTATE_RATE = 4;
const int Config::ITERS_FOR_MUTATION = 1000;
const int Config::ROOM_BORDER_SIZE = 3;

std::mt19937 random(time(nullptr));

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " map_file.txt" << std::endl;
		return EXIT_FAILURE;
	}

	std::string userInput = argv[1];
	Digger digger(userInput);
	digger.find_path();
}
