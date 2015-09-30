#include <string>

class Level {
public:
	Level(std::string gate, std::string room);
	bool is_can_down(int position);
	std::vector<uint8_t> get_gates();	
	std::vector<uint8_t> get_room();
	int countup_possible_steps(int start, int direction, int step_count);
	enum {
		EMPTY,
		WALL
	};
	
private:
	
	std::vector<uint8_t> gates;
	std::vector<uint8_t> room;

};

