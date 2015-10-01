#include "ml_digger.h"
#include <fstream>
#include <iostream>
#include <deque>
#include <random>
#include <ctime>
#include "chromosome.h"
#include <algorithm>
#include <set>

std::mt19937 Digger::random_gen = std::mt19937(time(nullptr));

Digger::Digger(std::string filename) : map_bound_x(0), levels_count(0) {
	this->map_filename = filename;
	this->read_map();
}

void Digger::read_map() {
	std::ifstream map_file(this->map_filename.c_str());
	std::string gate;
	std::string room;
	if (map_file.is_open()) {
		while (!map_file.eof()) {
			std::getline(map_file, gate);
			std::getline(map_file, room);
			this->map.emplace_back(gate, room);
		}
		map_file.close();
	}
	this->levels_count = this->map.size();
}

path_t Digger::find_path() {
	population_t population = this->generate_random_population(15);
	find_path_score(population);
	print(population);

	//	TODO: dummy
	this->round_wheel_selection(population);
}

population_t Digger::generate_random_population(int size) {
	population_t population;
	for (int i = 0; i < size; i++) {
		Chromosome chromosome = Chromosome::make_random(15, 17);
		population.push_back(chromosome);
	}
	//print(population);
	return population;
}

void Digger::find_path_score(population_t &population) {
	for (int i = 0; i < population.size(); i++) {
		int current_position = this->map[0].get_gates()[0];
		path_t path = population[i].get_path();
		int score = 0;

		for (int j = 0; j < this->map.size(); j++) {
			if (!this->map[j].is_can_down(current_position))
				break;

			score = j * 100;

			int direction = path[j].first;
			int step_count = path[j].second;

			int possible_steps = this->map[j].countup_possible_steps(current_position, direction, step_count);

			score += 15 - possible_steps;

			if (possible_steps != step_count)
				break;

			current_position += direction*step_count;


		}
		population[i].set_score(score);
	}
}

std::deque<Chromosome> Digger::make_selection(population_t population) {

	std::deque<Chromosome> pool;
	std::uniform_int_distribution<int> distribution(0, population.size() - 1);

	for (int i = 0; i < population.size(); i++) {
		Chromosome winner = population[i];
		int competitor = 0;
		do {
			competitor = distribution(random_gen);
		} while (competitor == i);

		if (winner.get_score() < population[competitor].get_score())
			winner = population[competitor];

		pool.push_back(winner);
	}

	return pool;
}

std::vector<chromosome_pair_t> Digger::round_wheel_selection(population_t population) {

	int score_sum = 0;

	for (int i = 0; i < population.size(); i++) {
		score_sum += population[i].get_score();
	}
	std::set<double> intervals;
	std::vector<double> weights;
	double prev = 0.0;
	intervals.insert(0);

	for (int i = 0; i < population.size(); i++) {
		double current = static_cast<double> (population[i].get_score()) / score_sum;
		intervals.insert(prev + current);
		weights.push_back(current);
		prev += current;

	}
	std::piecewise_constant_distribution<double>
		distribution(intervals.begin(), intervals.end(), weights.begin());

	std::vector<chromosome_pair_t> selected_parents;
	for (int i = 0; i < std::ceil(population.size() / 2); i++) {
		chromosome_pair_t parents;
		double dice;

		dice = distribution(random_gen);
		auto first_bound = intervals.upper_bound(dice);
		int first_element = std::distance(intervals.begin(), first_bound) - 1;
		parents.first = population[first_element];

		std::vector<double> cutted_weights = weights;
		cutted_weights[first_element] = 0;
		std::piecewise_constant_distribution<double>
			distribution(intervals.begin(), intervals.end(), cutted_weights.begin());

		dice = distribution(random_gen);
		auto second_bound = intervals.upper_bound(dice);
		int second_element = std::distance(intervals.begin(), second_bound) - 1;
		parents.second = population[second_element];

		selected_parents.push_back(parents);

	}

	return selected_parents;

}

population_t Digger::generate_next_population(population_t population) {
	//	std::deque<Chromosome> mating_pool = make_selection();
	//	std::random_shuffle(mating_pool.begin(), mating_pool.end(), random_gen);

}

void Digger::print(population_t population) {
	for (int i = 0; i < population.size(); i++) {

		auto path = population[i].get_path();

		for (auto &element : path) {
			std::cout << element.first << " ";
			std::cout << element.second << " ";
		}
		std::cout << std::endl;
		std::cout << population[i].get_score();
		std::cout << std::endl;

	}

}







