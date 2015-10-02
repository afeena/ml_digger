#pragma once

#include <vector>

class Chromosome;
typedef std::vector<Chromosome> population_t;
typedef std::pair<Chromosome, Chromosome> chromosome_pair_t;
enum Dig : int {
	DIG_LEFT = -1,
	DIG_DOWN = 0,
	DIG_RIGHT = 1,
};
typedef std::vector<std::pair<Dig,int>> path_t;

