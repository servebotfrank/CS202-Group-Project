#include "game.hpp"

Game::Game(std::string title) : versionMajor_{Platformer_VERSION_MAJOR},
			   versionMinor_{Platformer_VERSION_MINOR},
			   versionRevision_{Platformer_VERSION_REVISION},
			   contextSettings_{
							/*depth_bits*/ 24, /*stencil_bits*/ 8, /*antialiasing*/ 4,
							/*major*/ Platformer_OPENGL_MAJOR,
							/*minor*/ Platformer_OPENGL_MINOR },
			   window_{
							sf::VideoMode(800, 600), title,
							sf::Style::Default, contextSettings_ },
			   running_{false} {
	std::cout << "Application Version: " << getVersionString() << std::endl;
	glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void Game::run() {
	running_ = true;
	while(running_) {
		processEvents();

		update();

		clear();
		draw();
		swapFrameBuffers();
	}
}

std::string Game::getVersionString() const {
	std::string versionString =
		std::to_string(versionMajor_)+"."+
		std::to_string(versionMinor_)+"."+
		std::to_string(versionRevision_) ;
	return versionString;
}

void Game::processEvents() {
	sf::Event event;
	while(window_.pollEvent(event)) {
		switch(event.type) {
			case sf::Event::Closed:
				running_ = false;
				break;
			case sf::Event::Resized:
				frameBufferResize(static_cast<int>(event.size.width), static_cast<int>(event.size.height));
				break;
			case sf::Event::LostFocus:
			case sf::Event::GainedFocus:
			case sf::Event::TextEntered:
			case sf::Event::KeyPressed:
			case sf::Event::KeyReleased:
			case sf::Event::MouseWheelMoved:
			case sf::Event::MouseWheelScrolled:
			case sf::Event::MouseButtonPressed:
			case sf::Event::MouseButtonReleased:
			case sf::Event::MouseMoved:
			case sf::Event::MouseEntered:
			case sf::Event::MouseLeft:
			case sf::Event::JoystickButtonPressed:
			case sf::Event::JoystickButtonReleased:
			case sf::Event::JoystickMoved:
			case sf::Event::JoystickConnected:
			case sf::Event::JoystickDisconnected:
			case sf::Event::TouchBegan:
			case sf::Event::TouchMoved:
			case sf::Event::TouchEnded:
			case sf::Event::SensorChanged:
			case sf::Event::Count:
				break;
		}
	}
}

void Game::update() {
	
}

void Game::clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Game::draw() const {
	
}

void Game::frameBufferResize(int width, int height) const {
	glViewport(0, 0, width, height);
}

void Game::swapFrameBuffers() {
	window_.display();
}
