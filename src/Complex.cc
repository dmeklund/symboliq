#include <stdexcept>
#include <iostream>
#include <sstream>
#include <math.h>

#include "Complex.h"
#include "UndefException.h"
#include "MathObject.h"
#include "MathContainer.h"

const MathObject &
Complex::get_real() const throw (UndefException)
{
	if (!m_defined)
		throw UndefException("Complex");
	
	return c_real.var();
}

const MathObject &
Complex::get_imag() const throw (UndefException)
{
	if (!m_defined)
		throw UndefException("Complex");
	
	return c_imag.var();
}


void
Complex::set_real(const MathObject &real) throw ()
{
	if (!m_defined)
	{
		m_defined = true;
		c_imag = 0;
	}

	c_real = real;
}

void
Complex::set_real(double real) throw ()
{
	if (!m_defined)
	{
		m_defined = true;
		c_imag = 0;
	}

	c_real = real;
}

void
Complex::set_imag(const MathObject &imag) throw ()
{
	if (!m_defined)
	{
		m_defined = true;
		c_real = 0;
	}
	
	c_imag = imag;
}

void
Complex::set_imag(double imag) throw ()
{
	if (!m_defined)
	{
		m_defined = true;
		c_real = 0;
	}
	
	c_imag = imag;
}

MathContainer
Complex::magnitude2() const throw (UndefException)
{
	if (!m_defined)
		throw UndefException("Complex");
	
	return (c_real*c_real + c_imag*c_imag);
}

MathContainer
Complex::magnitude() const throw (UndefException)
{
	if (!m_defined)
		throw UndefException("Complex");
	
	return magnitude2().Sqrt();
}

Complex
Complex::conjugate() const throw (UndefException)
{
	if (!m_defined)
		throw UndefException("Complex");
	
	return Complex(c_real, -c_imag);
}

MathContainer
Complex::arg() const throw (UndefException)
{
	if (!m_defined)
		throw UndefException("Complex");
	
	return (c_imag/this->magnitude()).ArcSin();
}


string
Complex::to_string() const throw ()
{
	ostringstream ss;

	if (c_real != 0)
	{
		ss << c_real;
		if (c_imag != 0)
			ss << " + (" << c_imag << ") i";

		/*
		if (c_imag > 0)
			ss << " + " << c_imag << 'i';
		else if (c_imag < 0)
			ss << " - " << -c_imag << 'i';
		*/
	}
	else
	{
		ss << c_imag;
	}

	return ss.str();
}
