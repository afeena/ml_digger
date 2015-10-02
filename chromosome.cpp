#include "chromosome.h"

#include "types.h"

#include <random>
#include <iostream>

extern std::mt19937 random;

Chromosome::Chromosome() : score(0) {
}

Chromosome Chromosome::make_random(int path_length, int path_width) {
	Chromosome chromosome;
	
	chromosome.path_width = path_width;
	chromosome.path.reserve(path_length);
	chromosome.score = 0;

	std::uniform_int_distribution<int> step_count_dist(0, path_width);
	std::uniform_int_distribution<int> direction_dist(0, 1);
	
	for (int i = 0; i < path_length; i++) {
		int step_count = step_count_dist(random);
		int direction = direction_dist(random);

		if (direction > 0)
			chromosome.path.push_back({DIG_RIGHT, step_count});
		else
			chromosome.path.push_back({DIG_LEFT, step_count});
	}

	return chromosome;
}

chromosome_pair_t Chromosome::make_crossover(const chromosome_pair_t &parents) {
	int rand = random()%100;
	
	if (rand <=30)
		return parents;
	
	int path_len = parents.first.path.size();

	chromosome_pair_t childs = parents;
	std::pair<int, int> cross_points;
	std::uniform_int_distribution<int> cut_point_dist(0, path_len - 1);

	cross_points.first = cut_point_dist(random);
	do {
		cross_points.second = cut_point_dist(random);
	} while (cross_points.second == cross_points.first);

	if (cross_points.first > cross_points.second)
		std::swap(cross_points.first, cross_points.second);

	for (int i = cross_points.first; i <= cross_points.second; i++) {
		std::swap(childs.first.path[i], childs.second.path[i]);
	}

	childs.first.score = 0;
	childs.second.score = 0;

	return childs;
}

void Chromosome::mutate() {
	std::uniform_int_distribution<int> mutation_dist(0, this->path.size() - 1);
	std::uniform_int_distribution<int> step_count_dist(0, this->path_width);
	std::uniform_int_distribution<int> direction_dist(0, 1);

	for (int i = 0; i < Config::MUTATE_SIZE; i++) {
		int mutate_point = mutation_dist(random);
		int step_count = step_count_dist(random);
		int direction = direction_dist(random);

		if (direction > 0)
			this->path[mutate_point] = {DIG_RIGHT, step_count};
		else
			this->path[mutate_point] = {DIG_LEFT, step_count};
	}
}

void Chromosome::set_score(int score) {
	this->score = score;
}

int Chromosome::get_score() const {
	return this->score;
}

const path_t& Chromosome::get_path() const {
	return this->path;
}





