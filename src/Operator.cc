#include <sstream>
#include "Operator.h"

Operator::Operator(int prec, string str)
: MathObject(true, 0), o_precedence(prec), o_str(str)
{
}

string
Operator::to_string() const
{
	ostringstream result;
	if (var1.
}

int
precedence() const
{
	return o_precedence;
}

bool
is_additive() const
{
	return false;
}

bool
is_multiplicative() const
{
	return false;
}