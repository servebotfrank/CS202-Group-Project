#include "gameObjectFactory.hpp"

GameObjectFactory::GameObjectFactory()
	: shaderObjects_(0), meshObjects_(0) {}

std::shared_ptr<GameObject> GameObjectFactory::make(
	GameObjectTypes objectType,
	const std::string &pathToObj,
	const std::string &pathToVertSource,
	const std::string &pathToFragSource ) {

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
	if(!foundMesh) {
		meshObjects_.push_back(std::make_shared<Mesh>(pathToObj));
		meshIterator = --meshObjects_.end();
	}

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

	switch(objectType) {
		case GameObjectTypes::PLATFORM:
			return std::make_shared<Platform>(*meshIterator, *shaderIterator, std::vector<double>(20));
		case GameObjectTypes::PLAYER:
			return std::make_shared<Player>(*meshIterator, *shaderIterator, std::vector<double>(20));
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


