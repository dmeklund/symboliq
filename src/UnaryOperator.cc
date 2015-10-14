#include <string>
#include <sstream>
#include <stdexcept>

#include "UnaryOperator.h"
#include "MathObject.h"
#include "MathContainer.h"


UnaryOperator::UnaryOperator(int prec, const string str, const MathObject &mo)
: Operator(prec), arg(mo), uo_str(str)
{
}

UnaryOperator::UnaryOperator()
: Operator(-1), arg(), uo_str()
{
}

const MathObject &
UnaryOperator::get_arg() const
{
	return arg.var();
}

string
UnaryOperator::to_string() const
{
	ostringstream ss;

	ss << uo_str;

	if (arg.var().precedence() > precedence())
		ss << "(" << arg << ")";
	else
	{
		if (uo_str.length() > 1)
			ss << " " << arg;
		else
			ss << arg;
	}

	return ss.str();
}

MathContainer
UnaryOperator::solve_for_index(const MathObject &expr, int offset) const
{
	if (offset != 0)
		throw out_of_range("Index to UnaryOperator::solve_index must be 0");
	else
		return this->inverse(expr);
}

void
UnaryOperator::set_equal(const UnaryOperator &uo) throw (OPERATOR_EQUALS_EXCEPTIONS)
{
	uo_str = uo.uo_str;
	arg = uo.arg;
	Operator::set_equal(uo);
}
