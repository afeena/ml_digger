#include "ml_digger.h"
#include <fstream>

Digger::Digger(std::string filename) {
    this->map_filename = filename;
    this->read_map();
}

void Digger::read_map() {
    std::ifstream map_file(this->map_filename.c_str());
    std::string readed_line;
    if (map_file.is_open()) {
        while (std::getline(map_file, readed_line)) {
            std::vector<uint8_t> map_raw;
            for (int i = 0; i < readed_line.length(); i++) {
                switch (readed_line[i]) {
                    case '-':
                    case 'U':
                    case 'T':
                        map_raw.push_back(0);
                        break;
                    default:
                        map_raw.push_back(1);
                        break;

                }
            }
            this->map.push_back(map_raw);
        }
        map_file.close();
    }

}



