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

void Dynamic_object::incrementPosition()
{
	double _tempx=_xPosition, _tempy=_yPosition;
	_xPosition+=_timingInterval*_velocity.getXDirection();
	_yPosition+=_timingInterval*_velocity.getYDirection();
	int _tempPosX=_xPosition;
	if(_yPosition>_elevations[_tempPosX])
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

}

void Dynamic_object::fixMomentum()
{
	_momentum=_velocity.getTotalVelocity()*_mass;
}

Dynamic_object::Dynamic_object(const std::vector<double> & vec)
{
	_mass=_xPosition=_yPosition=_momentum=0;
	_elevations=vec;
	_elevationFlags.resize(_elevations.size());
}

void Dynamic_object::setXYVelocity(double xVelocity, double yVelocity)
{
	int temp=_xPosition;
	if(!(_yPosition>_elevations[temp]))
	{
	_velocity.setYDirection(yVelocity);
	_velocity.setXDirection(xVelocity);
	}
	
}

double Dynamic_object::getXPosition()const
{
	return _xPosition;
}
double Dynamic_object::getYPosition()const
{
	return _yPosition;
}