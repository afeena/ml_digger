#pragma once
#include <vector>
#include "types.h"

class Chromosome {
public:
	void mutate();
	path_t get_path();
	void set_score(std::pair<int,int> score);
	std::pair<int,int> get_score();
	
	static chromosome_pair_t make_cross(chromosome_pair_t parents);
	static Chromosome make_random(int bound, int path_length);


private:
	std::pair<int,int> score;
	path_t path;

	Chromosome();
};

