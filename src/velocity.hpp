#ifndef VELOCITY_HPP
#define VELOCITY_HPP

#include <cmath>

// not used
// replaced with glm::vec2

class Velocity
{
private:
	double _xDirection,_yDirection, _total, _angle;
	//need some way to handle direction
public:
	Velocity(double xVelocity, double yVelocity);

	void setXDirection(double xDirection);
	double getXDirection()const;
	void setYDirection(double yDirection);
	double getYDirection()const;
	double getTotalDirection()const;
	double getAngle()const;
	void squareUpTotalDirection();
	double getTotalVelocity()const;

};


#endif
