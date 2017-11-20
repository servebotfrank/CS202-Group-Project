#include "dynamic.hpp"
void Dynamic_object::setMass(double mass)
{
	_mass=mass;
	fixMomentum();
}

double Dynamic_object::getMass()const
{
	return _mass;
}

double Dynamic_object::incrementPosition()
{
	double _tempx=_xPosition, _tempy=_yPosition;
	_xPosition+=_timingInterval*velocity.getXDirection();


	//add in changes to x and y velocities

}

void Dynamic_object::fixMomentum()
{
	_momentum=velocity.getTotalVelocity()*_mass;
}

Dynamic_object::Dynamic_object(std::ostream & os, std::vector<double> & vec)
{
	_mass=_xPosition=_yPosition=_momentum=0;

}