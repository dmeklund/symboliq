#include <string>
#include <sstream>

#include "BinaryOperator.h"
#include "MathObject.h"
#include "MathContainer.h"


BinaryOperator::BinaryOperator(int prec, const string str, const MathObject &m1, const MathObject &m2)
: Operator(prec), arg1(m1), arg2(m2), bo_str(str)
{
}

BinaryOperator::BinaryOperator()
: Operator(-1), arg1(), arg2(), bo_str()
{
}

const MathObject &
BinaryOperator::get_arg1() const
{
	return arg1.var();
}

const MathObject &
BinaryOperator::get_arg2() const
{
	return arg2.var();
}

string
BinaryOperator::to_string() const
{
	ostringstream ss;

	if (arg1.var().precedence() > precedence())
		ss << "(" << arg1 << ")";
	else
		ss << arg1;

	ss << " " << bo_str << " ";

	if (arg2.var().precedence() > precedence())
		ss << "(" << arg2 << ")";
	else
		ss << arg2;

	return ss.str();
}
/*
void
BinaryOperator::set_equal(const BinaryOperator &bo) throw (OPERATOR_EQUALS_EXCEPTIONS)
{
	bo_str = bo.bo_str;
	arg1 = bo.arg1;
	arg2 = bo.arg2;
	Operator::set_equal(bo);
}
*/