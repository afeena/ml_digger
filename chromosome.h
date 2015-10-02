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
	static Chromosome make_random(int path_length, int path_width);

private:
	int score;
	
	int path_width;
	path_t path;
};

