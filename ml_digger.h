#pragma once

#include "level.h"
#include "types.h"

#include <string>
#include <random>
#include <vector>

class Chromosome;

class Digger {
public:
	Digger(std::string filename);
	void find_path();
	void print(const Chromosome &chromosome) const;

private:
	int map_bound_x;
	int levels_count;
	std::string map_filename;
	std::vector<Level> map;

	static std::mt19937 random_gen;
	static int top_score;
	static int iterate_count;
	void read_map();
	void calculate_path_score(population_t &population);
	std::pair<bool, int> is_done(const population_t &population) const;

	population_t generate_random_population(int size);
	population_t generate_next_population(const population_t &population) const;
	std::vector<chromosome_pair_t> round_wheel_selection(const population_t &population) const;
	std::vector<chromosome_pair_t> tournament_selection(const population_t &population) const;
};