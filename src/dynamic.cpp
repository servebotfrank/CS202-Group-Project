#include "dynamic.hpp"
#include "gameObjects.hpp"

Dynamic_object::Dynamic_object(const glm::vec2 &position, const std::vector<double> &elevations)
	: _mass{1},
	  _position{position},
	  _velocity(0),
	  _timingInterval{1.0/30.0},
	  _elevations(elevations),
	  _elevationFlags(elevations.size()),
	  _lastX=0
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
double Dynamic_object::getMass()const
{
	return _mass;
}
glm::vec2 Dynamic_object::getMomentum()const
{
	return _velocity * static_cast<float>(_mass);
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
double Dynamic_object::getTimingInterval()const
{
	return _timingInterval;
}

void Dynamic_object::incrementPosition(bool colliding, std::shared_ptr<GameObject> collidingWith)
{
	bool collidingBellow = colliding; // temporary - need some type of checking
	bool collidingAbove = false;
	bool collidingRight = false;
	bool collidingLeft = false;

	auto _tempPos=_position;
	int _tempPosX=_position[0];
	if(_position[1]>_elevations[_tempPosX])
	{
		_elevationFlags[_tempPosX]=1; //flags check if you have been over a terrain point; if you have, then you can land on it
	}

	_position[0]+=_velocity[0]*_timingInterval;
	_position[1]+=_velocity[1]*_timingInterval;

	if(_position[1]<_elevations[_tempPosX])
	{
		if(_elevationFlags[_tempPosX])
		{
			_position[1]=_elevations[_tempPosX];
		}
		else
		{
			_position=_tempPos;
		}
	}
	if(_lastX!=_tempPosX)
	{
		_elevationFlags[_lastX]=0;
	}
	_lastX=_tempPosX;


	// if(collidingBellow)
	// {
		
	// }
	// else if(collidingAbove) {
		
	// }
	// else
	// {
	// 	_velocity[1] += -9.806 * _timingInterval;
	// 	_position[1] += _velocity[1] * _timingInterval;
	// }
	
	// if(collidingLeft)
	// {
		
	// }
	// else if(collidingRight)
	// {
		
	// }
	// else
	// {
	// 	_position[0] += _velocity[0] * _timingInterval;
	// }
}



