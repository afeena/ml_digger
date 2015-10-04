#include "level.h"

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

	if (room.empty()) {
		for (int i = 0; i < gate.size(); i++)
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

const std::vector<uint8_t>& Level::get_gates() const {
	return this->gates;
}

const std::vector<uint8_t>& Level::get_room() const {
	return this->room;
}