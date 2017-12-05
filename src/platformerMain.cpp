#include "game.hpp"
#include <iostream>

int main() {
	try {
		// create the Game Object
		Game platformerGame("Test Window");
		// start the main event loop
		platformerGame.run();
	} catch (std::runtime_error e){
		std::cout << "runtime_error::" << e.what() << std::endl;
	}
	return EXIT_SUCCESS;
}
