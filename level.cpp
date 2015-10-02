#include "level.h"

#include "config.h"

Level::Level(std::string gate, std::string room) {
	for (int i = 0; i < gate.length(); i++) {
		switch (gate[i]) {
			case '-':
			case 'U':
			case 'T':
				this->gates.push_back(i);
				break;
			default:
				break;
		}
	}
	if (room == "") {
		for (int i = 0; i < Config::PATH_LEN; i++)
			this->room.push_back(EMPTY);
	}
	for (int i = 0; i < room.length(); i++) {
		switch (room[i]) {
			case '-':
				this->room.push_back(EMPTY);
				break;
			default:
				this->room.push_back(WALL);
				break;
		}
	}
}

int Level::countup_possible_steps(int start, int direction, int step_count) const {
	int count = 0;
	int finish = start + step_count * direction;

	for (int i = start; i != finish; i += direction) {
		if (this->room[i] == WALL)
			break;

		count++;
	}

	return count;
}

bool Level::is_can_down(int position) const {
	for (int i = 0; i < this->gates.size(); i++) {
		if (this->gates[i] == position)
			return true;
	}
	return false;
}

const std::vector<uint8_t>& Level::get_gates() const {
	return this->gates;
}

const std::vector<uint8_t>& Level::get_room() const {
	return this->room;
}




