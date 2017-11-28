//mass, velocity, position
#ifndef DYNAMIC_OBJECT_HPP
#define DYNAMIC_OBJECT_HPP

#include "velocity.hpp"
#include <vector>
#include <iostream>
#include <memory> // shared_ptr
#include <glm/glm.hpp>
// forward declaration
class GameObject;
// used in incrementPosition for collision resolution
// GameObject.hpp included in dynamic.cpp to prevent circular dependancy

class Dynamic_object
{
private:
	double _mass;
	glm::vec2 _position;
	glm::vec2 _velocity;
	glm::vec2 _acceleration;

	const double _timingInterval; // set to whatever the timing interval is in the initializer list
	const double _accelerationDueToGravity;
public:
	Dynamic_object(const glm::vec2 &position);

	// mutators
	void setMass(double mass);

	void setXPosition(double xPosition);
	void setYPosition(double yPosition);
	void setPosition(const glm::vec2 &position);

	void setXVelocity(double xVelocity);
	void setYVelocity(double yVelocity);
	void setVelocity(const glm::vec2 &velocity);

	void setXAcceleration(double xAcceleration);
	void setYAcceleration(double yAcceleration);
	void setAcceleration(const glm::vec2 &acceleration);

	// accessors
	double getMass()const;
	glm::vec2 getMomentum()const;
	glm::vec2 getForce()const;

	double getXPosition()const;
	double getYPosition()const;
	glm::vec2 getPosition()const;

	double getXVelocity()const;
	double getYVelocity()const;
	glm::vec2 getVelocity()const;

	double getXAcceleration()const;
	double getYAcceleration()const;
	glm::vec2 getAcceleration()const;

	double getTimingInterval()const;
	double getAccelerationDueToGravity()const;


	void incrementPosition(bool colliding, std::shared_ptr<GameObject> collidingWith);
};

#endif
