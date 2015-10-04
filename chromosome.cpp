#include "chromosome.h"

#include <cassert>
#include <iostream>

extern random_t random;

Chromosome::Chromosome(int path_len, int path_width) : path_len(path_len), path_width(path_width), score(0) {
	this->path.reserve(path_len);
}

Chromosome Chromosome::make_random(int path_len, int path_width) {
	Chromosome chromosome(path_len, path_width);

	std::uniform_int_distribution<int> position_dist(0, path_width);

	for (int i = 0; i < path_len; i++) {
		chromosome.path.push_back(position_dist(random));
	}

	return chromosome;
}

chromosome_pair_t Chromosome::make_crossover(const chromosome_pair_t &parents) {
	chromosome_pair_t childs = parents;

	assert(parents.first.path_len == parents.second.path_len);

	std::pair<int, int> cross_points;
	std::uniform_int_distribution<int> cut_point_dist(0, parents.first.path_len - 1);

	do {
		cross_points.first = cut_point_dist(random);
		cross_points.second = cut_point_dist(random);
	} while (cross_points.second == cross_points.first);

	if (cross_points.first > cross_points.second)
		std::swap(cross_points.first, cross_points.second);

	for (int i = cross_points.first; i <= cross_points.second; i++) {
		std::swap(childs.first.path[i], childs.second.path[i]);
	}

	childs.first.score = 0;
	childs.second.score = 0;

	childs.first.gates.clear();
	childs.second.gates.clear();

	return childs;
}

void Chromosome::mutate(int mutate_points) {
	std::uniform_int_distribution<int> mutation_dist(0, this->path_len);
	std::uniform_int_distribution<int> position_dist(0, this->path_width);

	for (int i = 0; i < mutate_points; i++) {
		int mutate_point = mutation_dist(random);
		int new_position = position_dist(random);
		this->path[mutate_point] = new_position;
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

void Chromosome::push_gates(int gate_position) {
	this->gates.push_back(gate_position);
}

std::vector<int> Chromosome::get_gates() const {
	return this->gates;
}