#pragma once
#include <vector>
#include <random>
#include "types.h"

class Chromosome {
public:
	Chromosome();
	void mutate();
	path_t get_path();
	void set_score(int score);
	int get_score();
	
	static chromosome_pair_t make_cross(chromosome_pair_t parents);
	static Chromosome make_random(int bound, int path_length);


private:
	int score;
	path_t path;
	static std::mt19937 random_gen;

};

