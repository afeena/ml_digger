#pragma once
#include <string>
#include <vector>


class Chromosome;
class Level;

class Digger{

public:
    Digger(std::string filename);
    std::string find_path();
    enum Commands {
        DOWN,
        LEFT,
        RIGHT
    };
private:
    int map_bound_x;
    int map_bound_y;
    std::string map_filename;
    std::vector<Level> map;
    
    void read_map();
    void find_path_score();
    std::vector<Chromosome> generate_random_population();
    std::vector<Chromosome> generate_next_population();
    std::vector<std::vector<Chromosome>> make_selection();
    
};