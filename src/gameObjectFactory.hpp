/*
	A class prototype that manages the creation of game objects
	Ensures that there are not multiple copies of shaders or meshes
*/

#ifndef GAME_OBJECT_FACTORY_H_P_P
#define GAME_OBJECT_FACTORY_H_P_P

#include <vector>
#include <list>
#include <memory>
#include <string>

#include "shader.hpp"
#include "mesh.hpp"
#include "gameObjects.hpp"

class GameObjectFactory {
public:
	// constructor - initializes vector sizes to 0
	GameObjectFactory();

	// creates a shared pointer to a GameObject. is used in Game::loadLevel
	// doesn't load meshes or shaders if they have already been loaded
	std::shared_ptr<GameObject> make(
		GameObjectTypes objectType,
		const std::string &pathToObj,
		const std::string &pathToVertSource,
		const std::string &pathToFragSource,
		const glm::vec3 &initialPosition,
		std::shared_ptr<std::vector<double>> elevations);

	// never used
	void cleanUp(); // deletes shaders and meshes with only 1 owner - if this is
					// the owner
private:
	std::list<std::shared_ptr<Shader>> shaderObjects_;
	std::list<std::shared_ptr<Mesh>> meshObjects_;
};

#endif
