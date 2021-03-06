#include "velocity.hpp"

Velocity::Velocity(double xVelocity, double yVelocity) 
	: _xDirection{xVelocity}, _yDirection{yVelocity},
	  _total{0}, _angle{0} {}

void Velocity::setXDirection(double xDirection)
{
	_xDirection=xDirection;
	squareUpTotalDirection();
}

double Velocity::getXDirection() const
{
	return _xDirection;
}
void Velocity::setYDirection(double yDirection)
{
	_yDirection=yDirection;
	squareUpTotalDirection();
}
double Velocity::getYDirection() const
{
	return _yDirection;
}

double Velocity::getTotalDirection() const
{
	return _total;
}

double Velocity::getAngle()const
{
	return _angle;
}

void Velocity::squareUpTotalDirection()
{
	const double pi=3.1415926535897932384626;
	_total=std::sqrt(_xDirection*_xDirection+_yDirection*_yDirection);
	if(_xDirection==0)
	{
		if(_yDirection==0)
		{
			_angle=0;
		}
		else if(_yDirection>0)
		{
			_angle=pi/2;
		}
		else
		{
			_angle=3*pi/2;
		}
	}
	else if(_yDirection==0)
	{
		if(_xDirection>0)
		{
			_angle=0;
		}
		else
		{
			_angle=pi;
		}
	}
	else if(_yDirection>0)
	{
		_angle=std::acos(_xDirection/_total);
	}
	else if(_yDirection<0&&_xDirection>0)
	{
		_angle=std::asin(_yDirection/_total)+2*pi;
	}
	else
	{
		_angle=std::atan(_yDirection/_xDirection)+pi;
	}
}

double Velocity::getTotalVelocity()const
{
	return _total;
}
