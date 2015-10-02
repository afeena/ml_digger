#pragma once

#include "config.h"
#include "types.h"

#include <random>

class Chromosome {
public:
	Chromosome();
	void mutate();
	void set_score(int score);
	int get_score() const;
	const path_t& get_path() const;

	static chromosome_pair_t make_crossover(const chromosome_pair_t &parents);
	static Chromosome make_random(int bound, int path_length);

private:
	int score;
	path_t path;

	static std::mt19937 random_gen;
};

