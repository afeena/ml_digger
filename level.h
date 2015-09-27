#include <string>

class Level{
public:
    Level(std::string gate, std::string room);
    enum {
        EMPTY,
        WALL
    };
private:
    std::vector<uint8_t> gates;
    std::vector<uint8_t> room;
    
};

