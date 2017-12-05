#ifndef GAME_H_P_P
#define GAME_H_P_P

// our headers
#include "platformerConfig.hpp" // our application version numbers
#include "gameObjects.hpp" // GameObject Player Platform Enemy
#include "camera.hpp" // Camera
#include "gameObjectFactory.hpp" // GameObjectFactory

// standard headers
#include <string> // string
#include <iostream> // cout endl
#include <vector> // vector
#include <memory> // shared_ptr

// use glew if on linux else use gl3.h
// the sections with __linux__ should also work with
// windows but we never used windows
#ifdef __linux__
	#include <GL/glew.h>
	#include <SFML/OpenGL.hpp>
#else
	#include <OpenGL/gl3.h>
#endif


#include <SFML/System.hpp>
#include <SFML/Window.hpp> // sf::window
#include <SFML/Graphics.hpp> // sf::image
#include <SFML/Audio.hpp>
#include <glm/glm.hpp> // glm::vec3, glm::mat4
#include <glm/gtc/matrix_transform.hpp>

class Game {
public:
	// constructor initializes data members in the initializer list
	// calls loadLevel and sets the playerIterator_ to the first iterator 
	// in the vector of GameObjects gameObjects_
	Game(std::string title);

	// the main event loop
	void run();

	// returns a string of the applicaion version and the versions of 
	// opengl glm and sfml
	std::string getDependancyAndAppInfoString() const;

	// returns the projection matrix which transforms the model from model space to clip space
	// used in the GameObjects draw function and in their vertex shaders
	glm::mat4 getProjection() const;

	uint16_t getFramerateLimit() const;
	void setFramerateLimit(uint16_t framerateLimit);
private:
	uint64_t versionMajor_;
	uint64_t versionMinor_;
	uint64_t versionRevision_;

	// used to initialize the window in the initializer list
	sf::ContextSettings contextSettings_;
	// the sfml window
	sf::Window window_;
	// while true run the event loop in run()
	bool running_;
	// is a shared ptr because at one point we wanted to do more with collisions(conservation of momentum)
	// and to do that the physics_object a member of GameObject would have to know about the other GameObject
	std::vector<std::shared_ptr<GameObject>> gameObjects_;
	// used to give the player controls
	std::vector<std::shared_ptr<GameObject>>::iterator playerIterator_;
	// makes objects 
	GameObjectFactory objectFactory_;

	// 
	float fov_;
	glm::mat4 projection_;
	Camera camera_;

	uint16_t framerateLimit_;

	// is a shared ptr because at one point we wanted elevations to change and for each physics object to
	// recieve those changes
	std::shared_ptr<std::vector<double>> elevations_;

	// used in the enemy's draw function so that they pulse - uses a sin function
	sf::Clock clock_;

	// sets the window to active and the frameratelimit to framerateLimit_(30)
	void initSFMLStates();
	// enables face culling, depth testing, and glew
	void initOpenGLStates() const;

	void processCommand(std::string & command);
	// prints instructions on how to play if the player enters a key that isn't reconized(not left or right arrow or space)
	void help() const;
	// polls sfml events and sends commands to the player
	void processEvents();
	// calls each GameObject's updatePhysics function
	void update();
	// checks each GameOject against everyother GameObject. It is overkill but at one point
	// we where going to use it for terrain collisions
	void checkCollisions();

	// loads a level from a text file
	void loadLevel(const std::string &pathToFile);
	// not implimented
	void saveLevel(const std::string &pathToFile);
	// loads a gameObject from a text file
	void loadGameObject(std::ifstream &input, GameObjectTypes type);
	// not implimented
	void saveGameObject();

	// calls each gameObjects draw function
	void draw(const sf::Time &elapsed) const;
	// calls sfml's display function
	void swapFrameBuffers();
	// when there is a resize event in the process events function this is called
	// it resets the size of the viewport to match the size of the screen
	void frameBufferResize(int32_t width, int32_t height) const;

	void soundManager();
};

#endif
