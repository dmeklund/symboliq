#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "Integer.h"

#include "Rational.h"
#include "MathContainer.h"
#include "UndefException.h"

Integer::Integer(int value) : Rational(value) {}

Integer::Integer() : Rational() {}

int
Integer::to_int() const
{
	return r_whole;
}

string
Integer::to_string() const
{
	ostringstream ss;
	ss << r_whole;
	return ss.str();
}

void
Integer::write_to_stream(ostream &out) const
{
	out << r_whole;
}
