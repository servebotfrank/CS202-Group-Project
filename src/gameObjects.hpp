#ifndef GAME_OBJECTS_H_P_P
#define GAME_OBJECTS_H_P_P

#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>
#include <string>
#include <algorithm>

#ifdef Xcode
#include <OpenGL/glew.h>
#else
#include <GL/glew.h>
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
		std::vector<double> elevation);
	GameObject(
		const std::string &pathToObj,
		const std::string &pathToVertSource,
		const std::string &pathToFragSource,
		std::vector<double> elevation);

	virtual ~GameObject() {}

	virtual void draw(const glm::mat4 &perspective, const glm::mat4 &view) const = 0;
	virtual void updatePhysics() = 0;

	unsigned int getShaderProgram() const;
	unsigned int getVAO() const;
	size_t getVertexCount() const;
	size_t getIndexCount() const;
	const void* getIndiciesData() const;
	glm::mat4 getModelTransform() const;
	void setUniformMat4(const std::string &name, const glm::mat4 &mat4) const;
	void setModelTransform(const glm::mat4 &transform);

	glm::vec3 getPosition() const;
	void setPosition(double xPos, double yPos);
	void translate(const glm::vec3 &difference);

	void faceLeft();
	void faceRight();

	Dynamic_object& getDynamicObject();
private:
	std::shared_ptr<Mesh> mesh_;
	std::shared_ptr<Shader> shader_;
	glm::mat4 modelTransform_;

	Dynamic_object dynamicObject_;
};

class Platform : public GameObject {
public:
	Platform(
		std::shared_ptr<Mesh> mesh,
		std::shared_ptr<Shader> shader,
		std::vector<double> elevation);
	Platform(
		const std::string &pathToObj,
		const std::string &pathToVertSource,
		const std::string &pathToFragSource,
		std::vector<double> elevation);


	virtual void draw(const glm::mat4 &perspective, const glm::mat4 &view) const override;
	virtual void updatePhysics() override;
private:

};

class Player : public GameObject {
public:
	Player(
		std::shared_ptr<Mesh> mesh,
		std::shared_ptr<Shader> shader,
		std::vector<double> elevation);
	Player(
		const std::string &pathToObj,
		const std::string &pathToVertSource,
		const std::string &pathToFragSource,
		std::vector<double> elevation);

	virtual void draw(const glm::mat4 &perspective, const glm::mat4 &view) const override;
	virtual void updatePhysics() override;
	//virtual void updatePhysics(char &direction);

};


#endif
