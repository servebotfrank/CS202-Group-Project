#include "gameObjectFactory.hpp"

GameObjectFactory::GameObjectFactory()
	: shaderObjects_(0), meshObjects_(0) {}

std::shared_ptr<GameObject> GameObjectFactory::make(
	GameObjectTypes objectType,
	const std::string &pathToObj,
	const std::string &pathToVertSource,
	const std::string &pathToFragSource,
	const glm::vec3 &initialPosition,
	std::shared_ptr<std::vector<double>> elevations) {

	std::cout << "mesh" << std::endl;
	bool foundMesh = false;
	auto meshIterator = meshObjects_.begin();
	if(meshObjects_.size() != 0) {
		for(; meshIterator != meshObjects_.end(); ++meshIterator) {
			if( pathToObj == (*meshIterator)->getPathToModel() ) {
				foundMesh = true;
				break;
			}
		}
	}
	std::cout << "mesh test" << std::endl;
	if(!foundMesh) {
		meshObjects_.push_back(std::make_shared<Mesh>(pathToObj));
		meshIterator = --meshObjects_.end();
	}

	std::cout << "shader test" << std::endl;
	bool foundShader = false;
	auto shaderIterator = shaderObjects_.begin();
	if(!meshObjects_.empty()) {
		for(; shaderIterator != shaderObjects_.end(); ++shaderIterator) {
			if( (*shaderIterator)->getPathToVertexSource() == pathToVertSource
				&& (*shaderIterator)->getPathToFragSource() == pathToFragSource ) {
				foundShader = true;
				break;
			}
		}
	}
	if(!foundShader) {
		shaderObjects_.push_back(std::make_shared<Shader>(pathToVertSource, pathToFragSource));
		shaderIterator = --shaderObjects_.end();
	}

	std::cout << "switch" << std::endl;
	switch(objectType) {
		case GameObjectTypes::PLATFORM:
			return std::make_shared<Platform>(*meshIterator, *shaderIterator, initialPosition, elevations);
		case GameObjectTypes::PLAYER:
			return std::make_shared<Player>(*meshIterator, *shaderIterator, initialPosition, elevations);
		case GameObjectTypes::ENEMY:
			return std::make_shared<Enemy>(*meshIterator, *shaderIterator, initialPosition, elevations);
		case GameObjectTypes::HAZARD:
			return std::make_shared<Hazard>(*meshIterator, *shaderIterator, initialPosition, elevations);
		default:
			throw std::runtime_error("Error::GameObjectFactory::unreconized enum for game object type");
			break;
	}
}

void GameObjectFactory::cleanUp() {
	for(auto shaderIterator = shaderObjects_.begin(); shaderIterator != shaderObjects_.end(); ++shaderIterator) {
		if((*shaderIterator).use_count() == 1) {
			shaderObjects_.erase(shaderIterator);
		}
	}
	for(auto meshIterator = meshObjects_.begin(); meshIterator != meshObjects_.end(); ++meshIterator) {
		if((*meshIterator).use_count() == 1) {
			meshObjects_.erase(meshIterator);
		}
	}
}


