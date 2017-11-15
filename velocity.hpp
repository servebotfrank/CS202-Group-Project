#ifndef VELOCITY_HPP
#define VELOCITY_HPP

class Velocity
{
private:
	double _xDirection,_yDirection, _total, _angle;
	//need some way to handle direction
public:
	void setXDirection(double xDirection);
	double getXDirection();
	void setYDirection(double yDirection);
	double getYDirection();
	double getTotalDirection();
	double getAngle();
	void squareUpTotalDirection();

};


#endif