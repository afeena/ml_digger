#pragma once

#include <cstdint>
#include <string>
#include <vector>

class Level {
public:

	enum {
		EMPTY,
		WALL
	};

	Level(std::string gate, std::string room);
	const std::vector<uint8_t>& get_gates() const;
	const std::vector<uint8_t>& get_room() const;

private:
	std::vector<uint8_t> gates;
	std::vector<uint8_t> room;
};

