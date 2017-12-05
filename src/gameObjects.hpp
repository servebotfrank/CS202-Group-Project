#ifndef GAME_OBJECTS_H_P_P
#define GAME_OBJECTS_H_P_P

#define _USE_MATH_DEFINES
#include <cmath>
#include <chrono>
#include <ctime>
#include <memory>
#include <string>
#include <algorithm>

#ifdef __linux__
	#include <GL/glew.h>
	#include <SFML/OpenGL.hpp>
#else
	#include <OpenGL/gl3.h>
#endif

#include <SFML/System.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include "mesh.hpp"
#include "shader.hpp"
#include "dynamic.hpp"
#include <cmath>

enum class GameObjectTypes { PLATFORM, PLAYER, ENEMY };

// The abstract GameObject class
class GameObject {
public:
	GameObject (
		std::shared_ptr<Mesh> mesh,
		std::shared_ptr<Shader> shader,
		const glm::vec3 &initialPosition,
		std::shared_ptr<std::vector<double>> elevations);

	virtual ~GameObject() {}

	virtual void draw(const glm::mat4 &perspective, const glm::mat4 &view, const sf::Time &elapsed) const = 0;
	virtual void updatePhysics() = 0;
	virtual std::string getDescription() const = 0;
	virtual GameObjectTypes getType() const = 0;

	// used by the concrete classes to acess private member of this class
	unsigned int getShaderProgram() const;
	unsigned int getVAO() const;
	size_t getVertexCount() const;
	size_t getIndexCount() const;
	const void* getIndiciesData() const;
	glm::mat4 getModelTransform() const;
	void setUniformMat4(const std::string &name, const glm::mat4 &mat4) const;
	void setUniformVec3(const std::string &name, const glm::vec3 &vec3) const;
	void setModelTransform(const glm::mat4 &transform);
	void translate(const glm::vec3 &difference);

	// get and set the position
	glm::vec3 getPosition() const;
	float getXPosition() const;
	float getYPosition() const;
	float getZPosition() const;
	void setPosition(double xPos, double yPos);
	void setPosition(const glm::vec3 &position);

	// get and set the bounding box width and height
	float getWidth() const;
	void setWidth(float width);
	float getHeight() const;
	void setHeight(float height);

	// determins the orientation of the model - true if faceing right else false
	bool getDirection();

	// sets collidingWith_ to collidingWith
	void setCollisionTarget(const std::shared_ptr<GameObject> &collidingWith);

	// sets _isColliding_ to isColliding
	void setCollision(bool isColliding);

	// returns a shared_ptr to the last GameObject this object was/is colliding with
	std::shared_ptr<GameObject> getCollisionTarget() const;

	// returns isColliding_
	bool getCollisionState() const;

	// flips the GameObject's mesh so that it is faceing the oposite direction
	void faceLeft();
	void faceRight();

	Dynamic_object& getDynamicObject();
private:
	GameObjectTypes type_;
	std::shared_ptr<Mesh> mesh_;
	std::shared_ptr<Shader> shader_;
	glm::mat4 modelTransform_;

	Dynamic_object dynamicObject_;

	float width_;
	float height_;

	bool isColliding_;
	std::shared_ptr<GameObject> collidingWith_;
};


// concrete classes

class Platform : public GameObject {
public:
	Platform(
		std::shared_ptr<Mesh> mesh,
		std::shared_ptr<Shader> shader,
		const glm::vec3 &initialPosition,
		std::shared_ptr<std::vector<double>> elevations);

	// passes gl uniforms to the shaders and calls glDrawElements - a greenish color is used
	virtual void draw(const glm::mat4 &perspective, const glm::mat4 &view, const sf::Time &elapsed) const override;
	// nothing happening here
	virtual void updatePhysics() override;
	// returns a string "Platform"
	virtual std::string getDescription() const override;
	// returns a enum GameObjectTypes::PLATFORM
	virtual GameObjectTypes getType() const override;
private:

};

class Player : public GameObject {
public:
	Player(
		std::shared_ptr<Mesh> mesh,
		std::shared_ptr<Shader> shader,
		const glm::vec3 &initialPosition,
		std::shared_ptr<std::vector<double>> elevations);

	// passes gl uniforms to the shaders and calls glDrawElements - a blue color is used
	virtual void draw(const glm::mat4 &perspective, const glm::mat4 &view, const sf::Time &elapsed) const override;
	// calls physics_objects incrementPosition
	virtual void updatePhysics() override;
	// returns a string "Player"
	virtual std::string getDescription() const override;
	// returns a enum GameObjectTypes::PLAYER
	virtual GameObjectTypes getType() const override;
};

class Enemy : public GameObject {
public:
	Enemy(
		std::shared_ptr<Mesh> mesh,
		std::shared_ptr<Shader> shader,
		const glm::vec3 &initialPosition,
		std::shared_ptr<std::vector<double>> elevations);

	// passes gl uniforms to the shaders and calls glDrawElements - uses time elapsed and a sin function to make the color pulse red and black
	virtual void draw(const glm::mat4 &perspective, const glm::mat4 &view, const sf::Time &elapsed) const override;
	// nothing happening here
	virtual void updatePhysics() override;
	// returns a string "Enemy"
	virtual std::string getDescription() const override;
	// returns a enum GameObjectTypes::ENEMY
	virtual GameObjectTypes getType() const override;
};


#endif
