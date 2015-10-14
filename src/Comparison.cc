#include <string>

#include "Comparison.h"
#include "MathContainer.h"
#include "MathObject.h"

string
Comparison::to_string() const
{
	return (this->arg1.to_string() + " " + this->bo_str + " " + this->arg2.to_string());
}

MathContainer
Comparison::simplify() const {
	if (get_rhs() != 0)
		return (*this - get_rhs());
	else
		return MathContainer(*this);
}

MathContainer
Comparison::add(const MathObject &mo) const throw (OPERATOR_PLUS_EXCEPTIONS)
{
	return this->factory(get_lhs() + mo, get_rhs() + mo);
}

MathContainer
Comparison::sub(const MathObject &mo) const throw (OPERATOR_MINUS_EXCEPTIONS)
{
	return this->factory(get_lhs() - mo, get_rhs() - mo);
}

MathContainer
Comparison::mult(const MathObject &mo) const throw (OPERATOR_TIMES_EXCEPTIONS)
{
	return this->factory(get_lhs() * mo, get_rhs() * mo);
}

MathContainer
Comparison::div(const MathObject &mo) const throw (OPERATOR_DIVIDE_EXCEPTIONS)
{
	return this->factory(get_lhs() / mo, get_rhs() / mo);
}

MathContainer
Comparison::negate() const throw ()
{
	return this->factory(-get_lhs(), -get_rhs());
}

