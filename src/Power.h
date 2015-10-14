#ifndef POWER_H
#define POWER_H

#include <stdexcept>

#include "BinaryOperator.h"
#include "MathObject.h"
#include "MathContainer.h"

#define POWER_STR "^"
#define POWER_PRECEDENCE 2

class Power : public BinaryOperator
{
public:
	Power(const MathObject &mo1, const MathObject &mo2)
		: BinaryOperator(POWER_PRECEDENCE, POWER_STR, mo1, mo2) {}
	Power() : BinaryOperator() {}

	virtual MathContainer simplify() const
	{ return this->arg1.simplify().Pow(this->arg2.simplify()); }
	virtual MathContainer solve_for_index(const MathObject &expr, int offset) const;
};

class LogarithmBase : public BinaryOperator
{
public:
	LogarithmBase(const MathObject &arg, const MathObject &base)
		: BinaryOperator(POWER_PRECEDENCE, "", arg, base) {}
	LogarithmBase() : BinaryOperator() {}

	virtual MathContainer simplify() const
	{ return this->arg2.simplify().LogBase(this->arg1.simplify()); }
	virtual MathContainer solve_for_index(const MathObject &expr, int offset) const;

	virtual MathContainer get_arg() const { return this->arg1; }
	virtual MathContainer get_base() const { return this->arg2; }
};

MathContainer
Power::solve_for_index(const MathObject &expr, int offset) const
{
	if (offset == 0)
		return expr.Pow(1/this->arg2);
		// x^y = z <=> x = z^(1/y)
	else if (offset == 1)
		return expr.LogBase(this->arg1);
		// x^y = z <=> y = log_x z
	else
		throw invalid_argument("offset for Power::solve_for_index must be 0 or 1");
}

MathContainer
LogarithmBase::solve_for_index(const MathObject &expr, int offset) const
{
	if (offset == 0)
		return this->get_base().Pow(expr);
		// log_x y = z <=> y = x^z
	else if (offset == 1)
		return this->get_arg().Pow(1/expr);
		// log_x y = z <=> x = y^(1/z)
	else
		throw invalid_argument("offset for LogBase::solve_for_index must be 0 or 1");
}

#endif /* POWER_H */
