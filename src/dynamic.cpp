#include "dynamic.hpp"
#include "gameObjects.hpp"

Dynamic_object::Dynamic_object(const glm::vec2 &position)
	: _mass{1},
	  _position{position},
	  _velocity(0),
	  _acceleration(0),
	  _timingInterval{1.0/30.0},
	  _accelerationDueToGravity{-9.806}
{}
void Dynamic_object::setMass(double mass)
{
	_mass = mass;
}
void Dynamic_object::setXPosition(double xPosition)
{
	_position[0] = xPosition;
}
void Dynamic_object::setYPosition(double yPosition)
{
	_position[1] = yPosition;
}
void Dynamic_object::setPosition(const glm::vec2 &position)
{
	_position = position;
}
void Dynamic_object::setXVelocity(double xVelocity)
{
	_velocity[0] = xVelocity;
}
void Dynamic_object::setYVelocity(double yVelocity)
{
	_velocity[1] = yVelocity;
}
void Dynamic_object::setVelocity(const glm::vec2 &velocity)
{
	_velocity = velocity;
}
void Dynamic_object::setXAcceleration(double xAcceleration)
{
	_acceleration[0] = xAcceleration;
}
void Dynamic_object::setYAcceleration(double yAcceleration)
{
	_acceleration[1] = yAcceleration;
}
void Dynamic_object::setAcceleration(const glm::vec2 &acceleration)
{
	_acceleration = acceleration;
}

double Dynamic_object::getMass()const
{
	return _mass;
}
glm::vec2 Dynamic_object::getMomentum()const
{
	return _velocity * static_cast<float>(_mass);
}
glm::vec2 Dynamic_object::getForce()const
{
	return _acceleration * static_cast<float>(_mass);
}
double Dynamic_object::getXPosition()const
{
	return _position[0];
}
double Dynamic_object::getYPosition()const
{
	return _position[1];
}
glm::vec2 Dynamic_object::getPosition()const
{
	return _position;
}
double Dynamic_object::getXVelocity()const
{
	return _velocity[0];
}
double Dynamic_object::getYVelocity()const
{
	return _velocity[1];
}
glm::vec2 Dynamic_object::getVelocity()const
{
	return _velocity;
}
double Dynamic_object::getXAcceleration()const
{
	return _acceleration[0];
}
double Dynamic_object::getYAcceleration()const
{
	return _acceleration[1];
}
glm::vec2 Dynamic_object::getAcceleration()const
{
	return _acceleration;
}
double Dynamic_object::getTimingInterval()const
{
	return _timingInterval;
}
double Dynamic_object::getAccelerationDueToGravity()const
{
	return _accelerationDueToGravity;
}

void Dynamic_object::incrementPosition(bool colliding, std::shared_ptr<GameObject> collidingWith)
{
	bool collidingBellow = colliding; // temporary - need some type of checking
	bool collidingAbove = false;
	bool collidingRight = false;
	bool collidingLeft = false;

	if(collidingBellow)
	{
		
	}
	else if(collidingAbove) {
		
	}
	else
	{
		_acceleration[1] += _accelerationDueToGravity;
		_velocity[1] += _acceleration[1] * _timingInterval;
		_position[1] += _velocity[1] * _timingInterval;
	}
	
	if(collidingLeft)
	{
		
	}
	else if(collidingRight)
	{
		
	}
	else
	{
		_position[0] += _velocity[0] * _timingInterval;
	}
}



