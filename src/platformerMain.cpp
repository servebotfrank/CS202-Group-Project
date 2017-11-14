#include "game.hpp"
#include <iostream>

int main() {
	try {
		Game platformerGame("Test Window");
		platformerGame.run();
	} catch (std::runtime_error e){
		std::cout << "runtime_error::" << e.what() << std::endl;
	}
	return EXIT_SUCCESS;
}
