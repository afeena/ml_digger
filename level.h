#include <string>

class Level{
public:
    Level(std::string input_line);
private:
    std::vector<uint8_t> gates;
    std::vector<uint8_t> room;
    
};

