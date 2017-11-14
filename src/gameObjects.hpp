#ifndef GAME_OBJECTS_H_P_P
#define GAME_OBJECTS_H_P_P

#include <cmath>
#include <memory>
#include <string>

#include <GL/glew.h>

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
private:
	std::unique_ptr<Mesh> mesh_;
	std::unique_ptr<Shader> shader_;
	glm::mat4 modelTransform_;
};

class Light {
public:
	Light(glm::vec3 position, float intesity, glm::vec3 color);
	void update();
private:
	glm::vec3 position_;
	float intensity_;
	glm::vec3 color_;
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