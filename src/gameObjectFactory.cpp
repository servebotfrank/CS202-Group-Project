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

	// checks if the mesh is already loaded
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

	// if the mesh hasn't been loaded then load the mesh by calling its constructor
	if(!foundMesh) {
		meshObjects_.push_back(std::make_shared<Mesh>(pathToObj));
		meshIterator = --meshObjects_.end();
	}

	// check if the shader is laoded
	bool foundShader = false;
	auto shaderIterator = shaderObjects_.begin();
	if(!meshObjects_.empty()) {
		for(; shaderIterator != shaderObjects_.end(); ++shaderIterator) {
			// if a shader uses the same vertex and fragment shader then it is loaded
			if( (*shaderIterator)->getPathToVertexSource() == pathToVertSource
				&& (*shaderIterator)->getPathToFragSource() == pathToFragSource ) {
				foundShader = true;
				break;
			}
		}
	}

	// if the shader isn't loaded then load the shader by calling its constructor
	if(!foundShader) {
		shaderObjects_.push_back(std::make_shared<Shader>(pathToVertSource, pathToFragSource));
		shaderIterator = --shaderObjects_.end();
	}

	// return a shared_ptr to the new game object
	switch(objectType) {
		case GameObjectTypes::PLATFORM:
			return std::make_shared<Platform>(*meshIterator, *shaderIterator, initialPosition, elevations);
		case GameObjectTypes::PLAYER:
			return std::make_shared<Player>(*meshIterator, *shaderIterator, initialPosition, elevations);
		case GameObjectTypes::ENEMY:
			return std::make_shared<Enemy>(*meshIterator, *shaderIterator, initialPosition, elevations);
		default:
			throw std::runtime_error("Error::GameObjectFactory::unreconized enum for game object type");
			break;
	}
}

void GameObjectFactory::cleanUp() {
	// checks if there is only one owner of each shader and mesh if there is only one owner then delete the mesh and shaderIterator
	// because this class is the owner and it is not being used
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


