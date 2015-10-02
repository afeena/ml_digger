#pragma once

#include <cstdint>
#include <string>
#include <vector>

class Level {
public:
	Level(std::string gate, std::string room);
	bool is_can_down(int position) const;
	const std::vector<uint8_t>& get_gates() const;
	const std::vector<uint8_t>& get_room() const;
	int countup_possible_steps(int start, int direction, int step_count) const;

	enum {
		EMPTY,
		WALL
	};

private:
	std::vector<uint8_t> gates;
	std::vector<uint8_t> room;
};

