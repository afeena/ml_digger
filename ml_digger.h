#pragma once
#include <string>
#include <vector>
#include "level.h"
#include "types.h"


class Chromosome;

class Digger {
public:
	Digger(std::string filename);
	path_t find_path();
	void print(population_t population);

	
private:
	int map_bound_x;
	int levels_count;
	std::string map_filename;
	std::vector<Level> map;

	void read_map();
	void find_path_score(population_t population);
	
	population_t generate_random_population(int size);
	population_t generate_next_population();
	std::vector<chromosome_pair_t> make_selection();

};