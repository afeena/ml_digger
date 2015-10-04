#pragma once

#include "config.h"
#include "types.h"

class Chromosome {
public:
	Chromosome(int path_len = 0, int path_width = 0);
	void mutate();
	void set_score(int score);
	int get_score() const;
	void push_gates(int gate_position);
	std::vector<int> get_gates() const;
	const path_t& get_path() const;
	
	static chromosome_pair_t make_crossover(const chromosome_pair_t &parents);
	static Chromosome make_random(int path_length, int path_width);

private:
        const int path_len;
	const int path_width;

	int score;
	path_t path;
	std::vector<int> gates;
};

