#ifndef GAME_H_P_P
#define GAME_H_P_P

#include "platformerConfig.hpp"
#include "gameObjects.hpp"

#include <string>
#include <iostream>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

class Game {
public:
	Game(std::string title);

	void run();
	std::string getVersionString() const;
private:
	uint64_t versionMajor_;
	uint64_t versionMinor_;
	uint64_t versionRevision_;

	sf::ContextSettings contextSettings_;
	sf::Window window_;
	bool running_;
	std::vector<GameObject> gameObjects_;

	void processEvents();
	void update();

	void clear() const;
	void draw() const;
	void frameBufferResize(int width, int height) const;
	void swapFrameBuffers();
};

#endif
