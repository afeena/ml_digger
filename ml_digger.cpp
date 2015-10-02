#include "ml_digger.h"

#include "config.h"
#include "chromosome.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <set>

extern std::mt19937 random;

Digger::Digger(std::string filename) : map_filename(filename), top_score(0), iterate_count(0) {
	this->read_map();
}

void Digger::read_map() {
	std::ifstream map_file(this->map_filename);
	std::string gate;
	std::string room;

	assert(map_file.is_open());

	while (!map_file.eof()) {
		std::getline(map_file, gate);
		std::getline(map_file, room);

		this->map.emplace_back(gate, room);
	}
}

void Digger::find_path() {
	population_t population = this->generate_random_population();
	this->calculate_path_score(population);
	std::pair<bool, int> done = {false, 0};

	while (!done.first) {
		population = generate_next_population(population);
		this->calculate_path_score(population);
		done = this->is_done(population);

	}

	print(population[done.second]);
	//	TODO: return path
}

population_t Digger::generate_random_population() {
	population_t population;

	int path_len = this->map.size();
	int path_width = this->map.front().get_room().size() - Config::ROOM_BORDER_SIZE;

	for (int i = 0; i < Config::POPULATION_SIZE; i++) {
		Chromosome chromosome = Chromosome::make_random(path_len, path_width);
		population.push_back(chromosome);
	}

	return population;
}

void Digger::calculate_path_score(population_t &population) {
	int path_width = this->map.front().get_room().size() - Config::ROOM_BORDER_SIZE;

	for (int i = 0; i < population.size(); i++) {
		auto path = population[i].get_path();
		int current_position = this->map.front().get_gates().front();
		int score = 0;

		for (int j = 0; j < this->map.size(); j++) {
			if (!this->map[j].is_can_down(current_position))
				break;

			score = j << 16;

			int direction = path[j].first;
			int step_count = path[j].second;

			int possible_steps = this->map[j].countup_possible_steps(current_position, direction, step_count);

			score |= 0xFFFF & (path_width - possible_steps);

			if (score > this->top_score) {
				std::cout << "level: " << (score >> 16) << ", step: " << (score & 0xFFFF) << std::endl;
				this->top_score = score;
				this->iterate_count = 0;
			}

			if (possible_steps != step_count)
				break;

			current_position += direction * step_count;
		}

		population[i].set_score(score);
	}

	this->iterate_count++;
}

std::vector<chromosome_pair_t> Digger::round_wheel_selection(const population_t &population) const {
	int score_sum = 0;

	for (int i = 0; i < population.size(); i++) {
		score_sum += population[i].get_score();
	}

	std::set<double> intervals = {0};
	std::vector<double> weights;

	double last = 0;
	for (int i = 0; i < population.size(); i++) {
		double current = static_cast<double> (population[i].get_score()) / score_sum;
		last += current;

		intervals.insert(last);
		weights.push_back(current);
	}

	std::vector<chromosome_pair_t> selected_parents;
	std::piecewise_constant_distribution<double>
		base_dist(intervals.begin(), intervals.end(), weights.begin());
	int finish = population.size();

	for (int i = 0; i < population.size(); i += 2) {
		double dice;

		dice = base_dist(random);
		auto first_bound = intervals.upper_bound(dice);
		int first_parent = std::distance(intervals.begin(), first_bound) - 1;

		std::vector<double> cutted_weights = weights;
		cutted_weights[first_parent] = 0;
		std::piecewise_constant_distribution<double>
			cutted_dist(intervals.begin(), intervals.end(), cutted_weights.begin());

		dice = cutted_dist(random);
		auto second_bound = intervals.upper_bound(dice);
		int second_parent = std::distance(intervals.begin(), second_bound) - 1;

		selected_parents.push_back({population[first_parent], population[second_parent]});
	}

	return selected_parents;
}

population_t Digger::generate_next_population(const population_t &population) {
	std::vector<chromosome_pair_t> parents = round_wheel_selection(population);
	population_t population_children;

	for (int i = 0; i < parents.size(); i++) {
		chromosome_pair_t children = Chromosome::make_crossover(parents[i]);
		population_children.push_back(children.first);
		population_children.push_back(children.second);
	}

	if (this->iterate_count > Config::ITERS_FOR_MUTATION) {
		for (int i = 0; i < population_children.size(); i++) {
			int rand = random() % 100;

			if (rand >= Config::MUTATE_RATE)
				continue;

			population_children[i].mutate();
		}

		//		this->iterate_count = 0;
		//		this->top_score = 0;
	}

	return {population_children.begin(), population_children.begin() + Config::POPULATION_SIZE};
}

std::pair<bool, int> Digger::is_done(const population_t &population) const {
	int done_score = this->map.size() - 1;

	for (int i = 0; i < population.size(); i++) {
		int current_score = population[i].get_score() >> 16;
		if (current_score == done_score)
			return {true, i};
	}

}

void Digger::print(const Chromosome &chromosome) const {
	auto path = chromosome.get_path();
	std::string down = "dig down";
	std::string right = "dig right";
	std::string left = "dig left";
	std::string direction;

	for (auto &element : path) {
		if (element.first == Dig::DIG_LEFT)
			direction = left;
		else
			direction = right;

		std::cout
			<< down << " " << direction << " "
			<< element.second << " " << std::endl;
	}

	std::cout << down << std::endl;
}
