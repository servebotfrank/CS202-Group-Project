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

void Dynamic_object::incrementPosition() //discrete simulation of continuous movement, frame by frame
{
	double _tempx=_xPosition, _tempy=_yPosition;
	_xPosition+=_timingInterval*_velocity.getXDirection(); //timing interval is set to 1/30, since we're target 30 fps
	_yPosition+=_timingInterval*_velocity.getYDirection();
	int _tempPosX=_xPosition;
	if(_yPosition>_elevations[_tempPosX]) //elevation checks uses X positions as an indices. 
	{
		_elevationFlags[_tempPosX]=1;
	}
	if(_yPosition<_elevations[_tempPosX])
	{
		if(_elevationFlags[_tempPosX])
		{
			_yPosition=_elevations[_tempPosX];
			_velocity.setYDirection(0);
		}
		_xPosition=_tempx;
		_yPosition=_tempy;
		_velocity.setXDirection(0);
	}
	if(_yPosition>_elevations[_tempPosX])
	{
		_velocity.setYDirection(_velocity.getYDirection()-9.806*_timingInterval);
	}
	if(_lastX!=_tempPosX)
	{
		_elevationFlags[_lastX]=0;
	}

	_lastX=_tempPosX;
	std::cout<<"incrementing position x= "<<_xPosition<<" y = "<<_y<<std::endl;

}

void Dynamic_object::fixMomentum()
{
	_momentum=_velocity.getTotalVelocity()*_mass;
}

Dynamic_object::Dynamic_object(const std::vector<double> & vec)
{
	_velocity.setYDirection(0);
	_velocity.setXDirection(0);
	_mass=_xPosition=_yPosition=_momentum=0;
	_elevations=vec;
	_elevationFlags.resize(_elevations.size());
}

void Dynamic_object::setXYVelocity(double xVelocity, double yVelocity) //input goes here
{
	int temp=_xPosition;
	if(_yPosition==_elevations[temp]) //Throws out user input if player is in air. Means player has NO AIR CONTROL, as intended.
	{
	_velocity.setYDirection(yVelocity);
	_velocity.setXDirection(xVelocity);
	}
	std::cout<<"x velocity = " << _velocity.getXDirection()<<" y velocity = "<<_velocity.getYDirection()<<std::endl;
}

double Dynamic_object::getXPosition()const
{
	std::cout<<"retrieving x coordinate"<<std::endl;
	return _xPosition;

}
double Dynamic_object::getYPosition()const
{
	std::cout<<"retrieving y position"<<std::endl;
	return _yPosition;
}