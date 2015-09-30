#include "ml_digger.h"
#include <fstream>
#include <iostream>
#include "chromosome.h"

Digger::Digger(std::string filename) {
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

}

population_t Digger::generate_random_population(int size) {
	population_t population;
	for (int i = 0; i <= size; i++) {
		Chromosome chromosome = Chromosome::make_random(15, 17);
		population.push_back(chromosome);
	}
	//print(population);
	return population;
}

void Digger::find_path_score(population_t population) {
	for (int i = 0; i < population.size(); i++) {
		int current_position = this->map[0].get_gates()[0];
		path_t path = population[i].get_path();
		std::pair<int,int> score = {0,0};
		
		for (int j = 0; j < this->map.size(); j++) {
			if (!this->map[j].is_can_down(current_position))
				return;
			score.first = j;
			
			int direction = path[j].first;
			int step_count = path[j].second;
			
			int possible_steps = this->map[j].countup_possible_steps(current_position,direction,step_count);
			
			score.second = possible_steps;
			
			if(possible_steps != step_count)
				break;
				
			current_position += direction*step_count;
			

		}
		population[i].set_score(score);
	}
}

void Digger::print(population_t population){
	for (int i = 0; i < population.size(); i++){
		for (auto element : population[i].get_path()) {
			std::cout << element.first<<" ";
			std::cout << element.second<<" ";
		}
		std::cout<<std::endl;
		std::cout<<population[i].get_score().first<<" "<<population[i].get_score().second;
		std::cout<<std::endl;
		
	}

	}







