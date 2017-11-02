/*
Getting a window on the screen quick and dirty like.
All of this will be wrapped up in appropriate classes.
Compile on linux with 'make'
*/

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio>

int main() {
	// init window for an opengl context
	sf::ContextSettings settings;
	settings.depthBits = 24;
	//settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 3;	// OpenGL version 3.3 which has the modern programable pipeline

	sf::Window window(sf::VideoMode(800, 600), "Test Window", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	window.setActive(true);

	// init opengl states
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // grey

	// main loop
	bool running = true;
	while(running) {

		// process events
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed) {
				running = false;
			} else if(event.type == sf::Event::Resized) {
				glViewport(0, 0, event.size.width, event.size.height);
			}
			// else if keyboard and mouse events
		}

	/*
		if(!runningCommand) {
			// get command from user
		} else {
			// update game logic
			// update physics logic
		}
	*/

		// clear buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw
		//auto v = getGameObjects();
		//for(auto s:v)
			//s->draw();

		// swap frame buffers
		window.display();
	}

	return 0;
}
