/*
	A class prototype that manages the creation of game objects
	Ensures that there are not multiple copies of resources
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

enum class GameObjectTypes { PLATFORM, PLAYER };

class GameObjectFactory {
public:
	GameObjectFactory();

	std::unique_ptr<GameObject> make(
		GameObjectTypes objectType,
		const std::string &pathToObj,
		const std::string &pathToVertSource,
		const std::string &pathToFragSource );

	void cleanUp(); // deletes shaders and meshes with only 1 owner - if this is
					// the owner
private:
	std::list<std::shared_ptr<Shader>> shaderObjects_;
	std::list<std::shared_ptr<Mesh>> meshObjects_;
};

#endif
