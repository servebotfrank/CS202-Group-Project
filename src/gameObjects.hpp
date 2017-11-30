#ifndef GAME_OBJECTS_H_P_P
#define GAME_OBJECTS_H_P_P

#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>
#include <string>
#include <algorithm>

#ifndef __APPLE__
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#else
#include <OpenGL/gl3.h>
#endif

#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include "mesh.hpp"
#include "shader.hpp"
#include "dynamic.hpp"

class GameObject {
public:
	GameObject (
		std::shared_ptr<Mesh> mesh,
		std::shared_ptr<Shader> shader,
		const glm::vec3 &initialPosition,
		std::shared_ptr<const std::vector<double>> elevations);
	GameObject(
		const std::string &pathToObj,
		const std::string &pathToVertSource,
		const std::string &pathToFragSource,
		const glm::vec3 &initialPosition,
		std::shared_ptr<const std::vector<double>> elevations);

	virtual ~GameObject() {}

	virtual void draw(const glm::mat4 &perspective, const glm::mat4 &view) const = 0;
	virtual void updatePhysics() = 0;
	virtual std::string getDescription() const = 0;

	unsigned int getShaderProgram() const;
	unsigned int getVAO() const;
	size_t getVertexCount() const;
	size_t getIndexCount() const;
	const void* getIndiciesData() const;
	glm::mat4 getModelTransform() const;
	void setUniformMat4(const std::string &name, const glm::mat4 &mat4) const;
	void setModelTransform(const glm::mat4 &transform);
	void translate(const glm::vec3 &difference);

	glm::vec3 getPosition() const;
	float getXPosition() const;
	float getYPosition() const;
	float getZPosition() const;
	void setPosition(double xPos, double yPos);
	void setPosition(const glm::vec3 &position);
	float getWidth() const;
	void setWidth(float width);
	float getHeight() const;
	void setHeight(float height);

	void setCollisionTarget(const std::shared_ptr<GameObject> &collidingWith);
	void setCollision(bool isColliding);
	std::shared_ptr<GameObject> getCollisionTarget() const;
	bool getCollisionState() const;
	void faceLeft();
	void faceRight();

	Dynamic_object& getDynamicObject();
private:
	std::shared_ptr<Mesh> mesh_;
	std::shared_ptr<Shader> shader_;
	glm::mat4 modelTransform_;

	Dynamic_object dynamicObject_;

	float width_;
	float height_;

	bool isColliding_;
	std::shared_ptr<GameObject> collidingWith_;
};

class Platform : public GameObject {
public:
	Platform(
		std::shared_ptr<Mesh> mesh,
		std::shared_ptr<Shader> shader,
		const glm::vec3 &initialPosition,
		std::shared_ptr<const std::vector<double>> elevations);
	Platform(
		const std::string &pathToObj,
		const std::string &pathToVertSource,
		const std::string &pathToFragSource,
		const glm::vec3 &initialPosition,
		std::shared_ptr<const std::vector<double>> elevations);


	virtual void draw(const glm::mat4 &perspective, const glm::mat4 &view) const override;
	virtual void updatePhysics() override;
	virtual std::string getDescription() const override;
private:

};

class Player : public GameObject {
public:
	Player(
		std::shared_ptr<Mesh> mesh,
		std::shared_ptr<Shader> shader,
		const glm::vec3 &initialPosition,
		std::shared_ptr<const std::vector<double>> elevations);
	Player(
		const std::string &pathToObj,
		const std::string &pathToVertSource,
		const std::string &pathToFragSource,
		const glm::vec3 &initialPosition,
		std::shared_ptr<const std::vector<double>> elevations);

	virtual void draw(const glm::mat4 &perspective, const glm::mat4 &view) const override;
	virtual void updatePhysics() override;
	virtual std::string getDescription() const override;
};


#endif
