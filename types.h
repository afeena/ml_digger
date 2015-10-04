#pragma once

#include <random>
#include <vector>

class Chromosome;

typedef std::mt19937 random_t;

typedef std::vector<Chromosome> population_t;
typedef std::pair<Chromosome, Chromosome> chromosome_pair_t;
typedef std::vector<int> path_t;
