

#include <iostream> 
#include <string> 
#include "ml_digger.h"

int main(int argc, char *argv[]) {
	if (argc == 2) {
		std::string userInput = argv[ 1 ];
		std::string answer;
		Digger digger(userInput);
		digger.find_path();
	}
}
