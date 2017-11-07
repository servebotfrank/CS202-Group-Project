/*
Minimal code to get an SFML window on the screen
with an opengl context
*/

#include "platformerConfig.hpp"

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio>

int main() {
	std::cout << "App Version: " <<
		Platformer_VERSION_MAJOR << "." <<
		Platformer_VERSION_MINOR << "." <<
		Platformer_VERSION_REVISION << std::endl;

	// settings for an opengl context
	sf::ContextSettings settings;
	settings.depthBits = 24;
	//settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 3;	// OpenGL version 3.3 which has the modern programable pipeline

	// create the window
	sf::Window window(sf::VideoMode(800, 600), "Test Window", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	window.setActive(true);

	// init opengl states
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.3f, 1.0f); // blue-grey

	// main loop
	sf::Clock clock;
	bool running = true;
	while(running) {
		sf::Time elapsed = clock.restart();

		// process events
		sf::Event event;
		while(window.pollEvent(event)) {
			switch(event.type) {
				case sf::Event::Closed:
					running = false;
					continue;
					break;
				case sf::Event::Resized:
					glViewport(0, 0, static_cast<int>(event.size.width), static_cast<int>(event.size.height));
					break;
				default:
					break;
			}
		}

		// clear OpenGL buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// swap frame buffers
		window.display();
	}

	return 0;
}
