#ifndef GAME_H_P_P
#define GAME_H_P_P
#include <GL/glew.h>
#include "platformerConfig.hpp"
#include "gameObjects.hpp"
#include "camera.hpp"
#include "gameObjectFactory.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <memory>

#ifdef __linux__
	#include <GL/glew.h>
	#include <SFML/OpenGL.hpp>
#else
	#include <OpenGL/gl3.h>
#endif


#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp> // sf::image

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Game {
public:
	Game(std::string title);

	void run();

	std::string getDependancyAndAppInfoString() const;
	glm::mat4 getProjection() const;
	uint16_t getFramerateLimit() const;
	void setFramerateLimit(uint16_t framerateLimit);
private:
	uint64_t versionMajor_;
	uint64_t versionMinor_;
	uint64_t versionRevision_;

	sf::ContextSettings contextSettings_;
	sf::Window window_;
	bool running_;
	std::vector<std::shared_ptr<GameObject>> gameObjects_;
	std::vector<std::shared_ptr<GameObject>>::iterator playerIterator_;
	GameObjectFactory objectFactory_;

	float fov_;
	glm::mat4 projection_;
	Camera camera_;

	uint16_t framerateLimit_;

	std::shared_ptr<std::vector<double>> elevations_;

	void initSFMLStates();
	void initOpenGLStates() const;

	void processCommand();
	void help() const;
	void processEvents();
	void update();
	void checkCollisions() const;

	void loadLevel(const std::string &pathToFile);
	void saveLevel(const std::string &pathToFile);
	void loadGameObject(std::ifstream &input, GameObjectTypes type);
	void saveGameObject();

	void draw() const;
	void swapFrameBuffers();
	void frameBufferResize(int32_t width, int32_t height) const;
};

#endif
