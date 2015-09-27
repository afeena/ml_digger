#include "ml_digger.h"
#include <fstream>

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
            this->map.emplace_back(gate,room);
 
        }
        map_file.close();
    }

}



