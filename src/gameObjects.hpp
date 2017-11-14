#ifndef GAME_OBJECTS_H_P_P
#define GAME_OBJECTS_H_P_P

#include <cmath>
#include <memory>
#include <string>

#ifdef __APPLE__
#include <OpenGL/glew.h>
#else
#include <GL/glew.h>
#endif

#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "mesh.hpp"
#include "shader.hpp"

class GameObject {
public:
	GameObject(
		const std::string &pathToObj,
		const std::string &pathToVertSource,
		const std::string &pathToFragSource);
	virtual ~GameObject() {}

	virtual void draw(const glm::mat4 &perspective, const glm::mat4 &view) const = 0;
	virtual void updatePhysics() = 0;

	unsigned int getShaderProgram() const;
	unsigned int getVAO() const;
	size_t getVertexCount() const;
	size_t getIndexCount() const;
	void* getIndiciesData() const;
	glm::mat4 getModelTransform() const;
	void setUniformMat4(const std::string &name, const glm::mat4 &mat4) const;
	void setModelTransform(const glm::mat4 &transform);

	// gets the center of the mesh, the first three elements in the last colume
	// of the modelTransform matrix
	glm::vec3 getPosition() const;
private:
	std::unique_ptr<Mesh> mesh_;
	std::unique_ptr<Shader> shader_;
	glm::mat4 modelTransform_;
};

class Platform : public GameObject {
public:
	Platform(
		const std::string &pathToObj,
		const std::string &pathToVertSource,
		const std::string &pathToFragSource);

	virtual void draw(const glm::mat4 &perspective, const glm::mat4 &view) const override;
	virtual void updatePhysics() override;
private:

};

enum class GameObjectTypes { PLATFORM };

std::unique_ptr<GameObject> gameObjectFactory(GameObjectTypes type);

#endif
