#include "FloatingPoint.h"
#include "Variable.h"

using namespace Math;

FloatingPoint::FloatingPoint() : Number()
{
}

FloatingPoint::FloatingPoint(double param) : Number(param)
{
}

FloatingPoint::FloatingPoint(const Number &param) : Number(param)
{
}

FloatingPoint *
FloatingPoint::copy() const
{
	return new FloatingPoint(*this);
}

void
FloatingPoint::addEq(const MathObject &mo)
throw (invalid_argument, IllegalOperation)
{
	if (dynamic_cast <const Number *> (&mo))
	{
		const Number &n = static_cast <const Number &> (mo);
		addEq(n);
	}
	else
		MathObject::addEq(mo);
}

void
FloatingPoint::subEq(const MathObject &mo)
throw (invalid_argument, IllegalOperation)
{
	if (dynamic_cast <const Number *> (&mo))
	{
		const Number &n = static_cast <const Number &> (mo);
		subEq(n);
	}
	else
		MathObject::subEq(mo);
}

void
FloatingPoint::multEq(const MathObject &mo)
throw (invalid_argument, IllegalOperation)
{
	if (dynamic_cast <const Number *> (&mo))
	{
		const Number &n = static_cast <const Number &> (mo);
		multEq(n);
	}
	else
		MathObject::multEq(mo);
}

void
FloatingPoint::divEq(const MathObject &mo)
throw (invalid_argument, IllegalOperation, DivideByZero)
{
	if (dynamic_cast <const Number *> (&mo))
	{
		const Number &n = static_cast <const Number &> (mo);
		divEq(n);
	}
	else
		MathObject::divEq(mo);
}
	
void
FloatingPoint::addEq(const Number &n)
throw (invalid_argument, IllegalOperation)
{
	n_value += n.to_float();
}

void
FloatingPoint::subEq(const Number &n)
throw (invalid_argument, IllegalOperation)
{
	n_value -= n.to_float();
}

void
FloatingPoint::multEq(const Number &n)
throw (invalid_argument, IllegalOperation)
{
	n_value *= n.to_float();
}

void
FloatingPoint::divEq(const Number &n)
throw (invalid_argument, IllegalOperation, DivideByZero)
{
	n_value /= n.to_float();
}
	
bool
FloatingPoint::is_equal(const MathObject &mo) const
throw ()
{
	bool result;
	
	if (dynamic_cast <const Number *> (&mo))
	{
		const Number &n = static_cast <const Number &> (mo);
		result = (n_value == n.to_float());
	}
	else
		result = false;
	
	return result;
}

void
FloatingPoint::set_equal(const MathObject &mo)
throw (invalid_argument, IllegalOperation)
{
	if (dynamic_cast <const Number *> (&mo))
	{
		const Number &n = static_cast <const Number &> (mo);
		n_value = n.to_float();
	}
	else
		throw invalid_argument("set FloatingPoint to non-numeric argument");
}

