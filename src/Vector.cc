#include "Vector.h"

// public methods

Vector::Vector(int n) throw () : v_data(n)
{
}

Vector::~Vector() throw ()
{
}

int
Vector::size() throw ()
{
	return v_data.size();
}

MathContainer &
Vector::operator() (int i, int j = 1) throw (invalid_argument)
{
	check_args(i, j);
	
	return v_data[i-1];
}

const MathContainer &
Vector::operator() (int i, int j = 1) const throw (invalid_argument)
{
	check_args(i, j);
	
	return v_data[i-1];
}
	
// protected methods
	
void
Vector::set_equal(const MathObject &mo) throw (invalid_argument)
{
	if (dynamic_cast<Vector*> (&mo))
	{
		set_equal(static_cast<Vector&> (mo));
	}
	else if (mo.dim == 1)
	{
		int size = v_data.size();
		for (int i = 0; i < size; ++i)
		{
			v_data[i] = mo;
		}
	}
	else
	{
		throw invalid_argument("Can't assign 2+ dimensional object to Vector");
	}
}

void
Vector::set_equal(Vector &v) throw (invalid_argument)
{
	int size = v_data.size();
	
	if (v.size() != size)
	{
		throw invalid_argument("Vector lengths don't agree");
	}
	else
	{
		int size = v_data.size();
		for (i = 0; i < size; ++i)
		{
			v_data[i] = v(i);
		}
	}
}

bool
Vector::is_equal(MathObject &mo) throw ()
{
	if (dynamic_cast<Vector*> (&mo))
	{
		return is_equal(static_cast<Vector&> (mo));
	}
	else
	{
		return false;
	}
}

bool
Vector::is_equal(Vector &v)
{
	int size = v_data.size();
	
	for (i = 0; i < size; ++i)
	{
		if (v_data[i] != v(i+1))
			return false;
	}
	
	return true;
}

// private methods

void
Vector::check_args(int i, int j) throw (invalid_argument)
{
	if (i < 1 || j < 1)
	{
		throw invalid_argument("Vector index must be >= 1");
	}
	else if (i > v_data.size())
	{
		throw invalid_argument("Vector index must be <= size of Vector");
	}
	else if (j != 1)
	{	
		throw invalid_argument("2nd index to one-dimensional object must be 1");
	}
}
