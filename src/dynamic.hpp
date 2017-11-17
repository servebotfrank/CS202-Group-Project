//mass, velocity, position, dimensions

class Dynamic_object
{
private:
	Velocity velocity;
	double _mass, _momentum, _xPosition, _yPosition;
	const double _timingInterval=1/30;//set to whatever the timing interval is

	//Position x and y coords will talk to the graphics processor
public:
	void setMass(double mass);
	double getMass()const;
	double incrementPosition();
	void fixMomentum();

	
}