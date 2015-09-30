
#include "chromosome.h"
#include <random>
#include <iostream>
#include <ctime>
#include "types.h"

Chromosome::Chromosome() {

}

Chromosome Chromosome::make_random(int bound, int path_length) {

	Chromosome chromosome;
	std::uniform_int_distribution<int> step_count_dist(0, bound);
	std::uniform_int_distribution<int> direction_dist(0,1);
	static std::mt19937 random_gen(time(nullptr));

	for (int i = 0; i < path_length; i++) {
		int step_count = step_count_dist(random_gen);
		int direction = direction_dist(random_gen);
		
		if(direction)
			chromosome.path.push_back({DIG_RIGHT, step_count});
		else
			chromosome.path.push_back({DIG_LEFT, step_count});
	}
	chromosome.score.first = 0;
	chromosome.score.second = 0;

//	for (auto element : chromosome.path) {
//			std::cout << element.first<<" ";
//			std::cout << element.second<<" ";
//	}
//	std::cout<<std::endl;

	return chromosome;
}

void Chromosome::set_score(std::pair<int,int> score) {
	this->score.first = score.first;
	this->score.second = score.second;
}

std::pair<int,int> Chromosome::get_score() {
	return this->score;
}

path_t Chromosome::get_path() {
	return this->path;
}





