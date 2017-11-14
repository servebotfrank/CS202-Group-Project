#ifndef GAME_H_P_P
#define GAME_H_P_P

#include "platformerConfig.hpp"
#include "gameObjects.hpp"
#include "camera.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include <GL/glew.h>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Game {
public:
	Game(std::string title);

	void run();
	std::string getVersionString() const;
	glm::mat4 getProjection() const;
private:
	uint64_t versionMajor_;
	uint64_t versionMinor_;
	uint64_t versionRevision_;

	sf::ContextSettings contextSettings_;
	sf::Window window_;
	bool running_;
	std::vector<std::unique_ptr<GameObject>> gameObjects_;

	float fov_;
	glm::mat4 projection_;
	Camera camera_;

	void processEvents();
	void update();

	void draw() const;
	void swapFrameBuffers();
	void frameBufferResize(int32_t width, int32_t height) const;
};

#endif