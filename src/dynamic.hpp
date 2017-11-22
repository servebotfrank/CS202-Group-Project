//mass, velocity, position
#ifndef DYNAMIC_OBJECT_HPP
#define DYNAMIC_OBJECT_HPP
#include <iostream>
#include <vector>
#include "velocity.hpp"

class Dynamic_object
{
private:
	int _lastX;
	Velocity _velocity;
	double _mass, _momentum, _xPosition, _yPosition;
	const double _timingInterval=1/30;//set to whatever the timing interval is
	std::vector<double> _elevations;
	std::vector <int> _elevationFlags;
	//Position x and y coords will talk to the graphics processor
public:
	void setMass(double mass);
	double getMass()const;
	void incrementPosition();
	void fixMomentum();
	Dynamic_object(const std::vector<double> & vec);
	void setXYVelocity(double xVelocity, double yVelocity);
	double getXPosition()const;
	double getYPosition()const;
};

#endif
