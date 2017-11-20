//mass, velocity, position
#ifndef DYNAMIC_OBJECT_HPP
#define DYNAMIC_OBJECT_HPP
#include <iostream>
#include <vector>
#include "velocity.cpp"

class Dynamic_object
{
private:
	bool _overElevationFlag;
	Velocity velocity;
	double _mass, _momentum, _xPosition, _yPosition;
	const double _timingInterval=1/30;//set to whatever the timing interval is
	std::vector<double> _elevations;
	//Position x and y coords will talk to the graphics processor
public:
	void setMass(double mass);
	double getMass()const;
	double incrementPosition();
	void fixMomentum();
	Dynamic_object(std::ostream & os, const std::vector<double> & vec);
};

#endif