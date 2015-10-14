#include <sstream>

#include "Real.h"
#include "Rational.h"
#include "MathContainer.h"
#include "Test.h"

using namespace Math;

Real::Real() : MathObject(false, 0)
{
}

Real::Real(double param) : MathObject(true, 0)
{
	r_value = param;
}


double
Real::to_float() const throw (UndefException)
{
	if (!m_defined)
		throw UndefException("Real");
	
	return r_value;
}

string
Real::to_string() const
{
	ostringstream ss;
	ss << to_float();
	return ss.str();
}
/*
void
Real::write_to_stream(ostream &out) const
{
	out << n_value;
}

void
Real::addEq(const MathObject &mo)
throw (invalid_argument, IllegalOperation)
{
	if (dynamic_cast <const Real *> (&mo))
	{
		const Real &n = static_cast <const Real &> (mo);
		addEq(n);
	}
	else
		MathObject::addEq(mo);
}

void
Real::subEq(const MathObject &mo)
throw (invalid_argument, IllegalOperation)
{
	if (dynamic_cast <const Real *> (&mo))
	{
		const Real &n = static_cast <const Real &> (mo);
		subEq(n);
	}
	else
		MathObject::subEq(mo);
}

void
Real::multEq(const MathObject &mo)
throw (invalid_argument, IllegalOperation)
{
	if (dynamic_cast <const Real *> (&mo))
	{
		const Real &n = static_cast <const Real &> (mo);
		multEq(n);
	}
	else
		MathObject::multEq(mo);
}

void
Real::divEq(const MathObject &mo)
throw (invalid_argument, IllegalOperation, DivideByZero)
{
	if (dynamic_cast <const Real *> (&mo))
	{
		const Real &n = static_cast <const Real &> (mo);
		divEq(n);
	}
	else
		MathObject::divEq(mo);
}
	
void
Real::addEq(const Real &n)
throw (invalid_argument, IllegalOperation)
{
	n_value += n.to_float();
}

void
Real::subEq(const Real &n)
throw (invalid_argument, IllegalOperation)
{
	n_value -= n.to_float();
}

void
Real::multEq(const Real &n)
throw (invalid_argument, IllegalOperation)
{
	n_value *= n.to_float();
}

void
Real::divEq(const Real &n)
throw (invalid_argument, IllegalOperation, DivideByZero)
{
	n_value /= n.to_float();
}
*/
	
bool
Real::is_equal(const MathObject &mo) const
throw ()
{
	bool result;
	
	if (dynamic_cast <const Real *> (&mo))
	{
		const Real &n = static_cast <const Real &> (mo);
		result = (to_float() == n.to_float());
	}
	else
		result = false;
	
	return result;
}

void
Real::set_equal(const Real &re)
throw (invalid_argument, IllegalOperation)
{
	r_value = re.to_float();
	MathObject::set_equal(re);
}


bool
Real::test_all(ostream &out)
{
	Real a(2.3), b(5.7), c;
	Rational d(4,3);
	Test results("Real");

	c = a + b;
	results.check(c, "addition", c.to_float(), 8.0);

	c = a + d;
	out << a << " + " << d << " = " << c << endl;

	return results.get_final_result();
}

