#include <iostream>
#include <sstream>
#include <string>

#include "Real.h"

Real::Real() : MathObject() {}
Real::~Real() {}

/* protected constructors */
Real::Real(double value) : MathObject(true), n_value(value) {}
Real::Real(Real &param) : MathObject(param), n_value(param.n_value) {}

double
Real::to_float() const throw (UndefException)
{
	if (!m_defined)
		throw UndefException("Real");
	
	return n_value;
}

string
Real::to_string() const
{
	ostringstream ss;
	ss << n_value;
	return ss.str();
}

Real::operator double() const
throw (UndefException)
{
	if (!m_defined)
		throw UndefException("Real");
	
	return n_value;
}

Real::operator int() const
throw (UndefException)
{
	if (!m_defined)
		throw UndefException("Real");
	
	return (int) n_value;
}


void
Real::write_to_stream(ostream &out) const
{
	out << n_value;
}
