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
	Digger(std::string filename, int population_size, int mutate_points, int mutate_rate, int iters_before_mutation);
	void find_path();

private:
	std::string map_filename;
	std::vector<Level> map;

	int top_score;
	int iterate_count;
	int iterate_total;

	const int population_size;
	const int mutate_points;
	const int mutate_rate;
	const int iters_before_mutation;

	void read_map();
	void calculate_path_score(population_t &population);
	std::pair<bool, int> is_done(const population_t &population) const;

	population_t generate_random_population();
	population_t generate_next_population(const population_t &population);
	std::vector<int> restore_path(const Chromosome &chromosome) const;
	std::vector<chromosome_pair_t> round_wheel_selection(const population_t &population) const;
};