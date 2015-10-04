#include "ml_digger.h"

#include "chromosome.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <set>
#include <ctime>


random_t random(time(nullptr));

Digger::Digger(std::string filename, int population_size, int mutate_points, int mutate_rate, int iters_before_mutation) :
map_filename(filename), population_size(population_size), mutate_points(mutate_points), mutate_rate(mutate_rate), iters_before_mutation(iters_before_mutation),
top_score(0), iterate_count(0), iterate_total(0) {

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

		this->iterate_count++;
		this->iterate_total++;
	}
	std::vector<int> path = restore_path(population[done.second]);
}

population_t Digger::generate_random_population() {
	population_t population;

	population.reserve(this->population_size);

	int path_len = this->map.size();
	int path_width = this->map.front().get_room().size();

	for (int i = 0; i < this->population_size; i++) {
		Chromosome chromosome = Chromosome::make_random(path_len, path_width);
		population.push_back(chromosome);
	}

	return population;
}

void Digger::calculate_path_score(population_t &population) {
	int path_width = this->map.front().get_room().size();

	for (auto &chromosome : population) {
		auto path = chromosome.get_path();
		int score = 0;
		int choosed_gate = 0;
		assert(path.size() == this->map.size());

		for (int i = 1; i < path.size(); i++) {
			Level &level_current = this->map[i];
			Level &level_prev = this->map[i - 1];

			auto room_current = level_current.get_room();
			auto room_prev = level_prev.get_room();
			auto gates = level_current.get_gates();

			int point_current = path[i];
			int point_prev = path[i - 1];

			bool available = false;
			bool gate_set = false;

			for (int gate : gates) {
				int step_current = point_current > gate ? -1 : 1;
				int step_prev = point_prev > gate ? -1 : 1;

				int current = point_current;
				int prev = point_prev;

				while (true) {
					int steps = 0;

					if (room_prev[prev] == Level::EMPTY && prev != gate) {
						steps++;
						prev += step_prev;
					}

					if (room_current[current] == Level::EMPTY && current != gate) {
						steps++;
						current += step_current;
					}

					if (steps > 0) {
						continue;
					}

					break;
				}

				if (prev == current && prev == gate) {
					choosed_gate = gate;
					available = true;
				}
			}

			if (available) {
				score++;
				if (!gate_set) {
					chromosome.push_gates(choosed_gate);
					gate_set = true;
				}
			}
		}

		if (score > this->top_score) {
			std::cout << "top: " << score << std::endl;
			this->top_score = score;
			this->iterate_count = 0;
		}

		chromosome.set_score(score);
	}
}

std::vector<chromosome_pair_t> Digger::round_wheel_selection(const population_t &population) const {
	int score_sum = 0;
	std::set<double> intervals = {0};
	std::vector<double> weights;

	for (auto &chromosome : population) {
		score_sum += chromosome.get_score();
	}

	double last = 0;
	for (auto &chromosome : population) {
		double current = static_cast<double> (chromosome.get_score()) / score_sum;
		last += current;

		intervals.insert(last);
		weights.push_back(current);
	}

	int finish = population.size();
	std::vector<chromosome_pair_t> selected_parents;
	std::piecewise_constant_distribution<double>
		base_dist(intervals.begin(), intervals.end(), weights.begin());

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

	if (this->iterate_count > this->iters_before_mutation) {
		for (int i = 0; i < population_children.size(); i++) {
			int rand = random() % 100;

			if (rand >= this->mutate_rate)
				continue;

			population_children[i].mutate(this->mutate_points);

		}
		iterate_count = 0;
	}

	return {population_children.begin(), population_children.begin() + this->population_size};
}

std::pair<bool, int> Digger::is_done(const population_t &population) const {
	int done_score = this->map.size() - 1;

	for (int i = 0; i < population.size(); i++) {
		int current_score = population[i].get_score();
		if (current_score >= done_score) {
			return
			{
				true, i
			};
		}
	}

	return { false, 0 };
}

std::vector<int> Digger::restore_path(const Chromosome &chromosome) const {
	std::vector<int> gates = chromosome.get_gates();

	std::vector<int> path;
	int current_gate = map.front().get_gates().front();

	for (int i = 0; i < gates.size(); i++) {
		path.push_back(gates[i] - current_gate);
		current_gate = gates[i];
	}

	return path;
}