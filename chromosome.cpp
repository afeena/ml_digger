
#include "chromosome.h"
#include <random>
#include <iostream>
#include <ctime>
#include "types.h"

std::mt19937 Chromosome::random_gen = std::mt19937(time(nullptr));

Chromosome::Chromosome() : score(0) {

}

Chromosome Chromosome::make_random(int bound, int path_length) {

	Chromosome chromosome;
	std::uniform_int_distribution<int> step_count_dist(0, bound - 1);
	std::uniform_int_distribution<int> direction_dist(0, 1);


	for (int i = 0; i < path_length; i++) {
		int step_count = step_count_dist(random_gen);
		int direction = direction_dist(random_gen);

		if (direction)
			chromosome.path.push_back({DIG_RIGHT, step_count});
		else
			chromosome.path.push_back({DIG_LEFT, step_count});
	}
	chromosome.score = 0;

	return chromosome;
}

chromosome_pair_t Chromosome::make_cross(chromosome_pair_t parents) {
	int path_len = parents.first.path.size();

	std::pair<int, int> cross_points;
	std::uniform_int_distribution<int> cut_point_dist(0, path_len - 1);

	cross_points.first = cut_point_dist(random_gen);
	do {
		cross_points.second = cut_point_dist(random_gen);
	} while (cross_points.second == cross_points.first);

	if (cross_points.first > cross_points.second)
		std::swap(cross_points.first, cross_points.second);

	for (int i = cross_points.first; i <= cross_points.second; i++) {
		std::swap(parents.first.path[i], parents.second.path[i]);
	}

	return parents;
}

void Chromosome::mutate() {
	std::uniform_int_distribution<int> mutation_dist(0, this->path.size() - 1);
	std::uniform_int_distribution<int> step_count_dist(0, 15);
	std::uniform_int_distribution<int> direction_dist(0, 1);
	
	int mutate_point = mutation_dist(random_gen);
	int step_count = step_count_dist(random_gen);
	int direction = direction_dist(random_gen);

	if (direction)
		this->path[mutate_point] = {DIG_RIGHT, step_count};
	else
		this->path[mutate_point] = {DIG_LEFT, step_count};

}

void Chromosome::set_score(int score) {
	this->score = score;
}

int Chromosome::get_score() {
	return this->score;
}

path_t Chromosome::get_path() {
	return this->path;
}





