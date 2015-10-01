#pragma once
#include <string>
#include <random>
#include <vector>
#include <deque>
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
	static std::mt19937 random_gen;

	void read_map();
	void find_path_score(population_t &population);
	
	population_t generate_random_population(int size);
	population_t generate_next_population(population_t population);
	std::deque<Chromosome> make_selection(population_t population);
	std::vector<chromosome_pair_t> round_wheel_selection(population_t population);

};