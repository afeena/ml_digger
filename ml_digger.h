#pragma once

#include "level.h"
#include "types.h"
#include "chromosome.h"

#include <string>
#include <random>
#include <vector>

class Chromosome;

class Digger {
public:
	Digger(std::string filename);
	void find_path();
	void print(const path_t &path) const;

private:
	std::string map_filename;
	std::vector<Level> map;
	
	int top_score;
	int iterate_count;
	int iterate_total;

	void read_map();
	void calculate_path_score(population_t &population);
	std::pair<bool, int> is_done(const population_t &population) const;

	population_t generate_random_population();
	population_t generate_next_population(const population_t &population);
	std::vector<int> restore_path(const Chromosome &chromosome) const;
	std::vector<chromosome_pair_t> round_wheel_selection(const population_t &population) const;
};