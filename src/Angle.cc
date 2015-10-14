#include <stdexcept>

#include "Angle.h"

Angle::Angle(double value, format a_format)
{
	value = project_to_range(value, a_format);

	if (a_format == RADIANS)
	{
		a_radians = value;
		a_degrees = convert_to_degrees(a_radians);
	} 
	else if (a_format == DEGREES)
	{
		a_degrees = value;
		a_radians = convert_to_radians(a_degrees);
	}
	
}

Angle::Angle(Angle &param)
{
    a_degrees = param.a_degrees;
	a_radians = param.a_radians;
}

double
Angle::in_degrees() const throw (UndefException)
{
	return a_degrees;
}

double
Angle::in_radians() const throw (UndefException)
{
	return a_radians;
}

/*
Angle &
Angle::operator=(Angle &param)
{
	if (param.deg_def == true) {
		degrees = param.degrees;
		deg_def = true;
	} else {
		deg_def = false;
	}
	
	if (param.rad_def == true) {
		radians = param.radians;
		rad_def = true;
	} else {
		rad_def = false;
	}
	
	return *this;
}

Angle
Angle::operator+(Angle &param) throw (UndefException)
{
	Angle *result;
	
	if ((!deg_def && !rad_def) || (!param.deg_def && !param.rad_def))
		throw UndefException("Angle");
	
	if (deg_def && param.deg_def)
	{
		degrees += param.degrees;
		if (rad_def)
		{
			if (param.rad_def)
				radians += param.radians;
			else
				rad_def = false;
		}
		deg_def = true;
	}
	else if (rad_def && param.rad_def)
	{
		radians += param.radians;
		if (deg_def) deg_def = false;
	}
	else
	{
		
	}
}*/

double
Angle::convert_to_degrees(double radians) throw ()
{
	return radians*(360/(2*PI));
}

double
Angle::convert_to_radians(double degrees) throw ()
{
	return degrees*(2*PI/360);
}

double
Angle::project_to_range(double value, format a_format)
{
	int N;
	
	if (a_format == DEGREES)
	{
		if (value > 360)
		{
			N = (int) (value / 360);
			value -= 360*N;
		}
		else if (value < 0)
		{
			N = (int) (value / -360) + 1;
			value += 360*N;
		}
	}
	else 
	{
		if (value > 2*PI)
		{
			N = (int) (value / (2*PI));
			value -= 2*PI*N;
		}
		else if (value < 0)
		{
			N = (int) (value / (-2*PI));
			value += 2*PI*N;
		}
	}

	return value;
}
