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
	x+=_timingIncrement*velocity.getXPosition();
	//add in changes to x and y velocities
}

void Dynamic_object::fixMomentum()
{
	_momentum=velocity.getTotalVelocity()*_mass;
}