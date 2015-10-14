#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "MathObject.h"
#include "BinaryOperator.h"

#define MULTIPLICATION_PRECEDENCE 4

class Multiplication : public BinaryOperator
{

public:

	Multiplication(const MathObject &mo1, const MathObject &mo2) : BinaryOperator(MULTIPLICATION_PRECEDENCE, "*", mo1, mo2) {}
	Multiplication(const Multiplication &mult) : BinaryOperator(MULTIPLICATION_PRECEDENCE, "*", mult.arg1, mult.arg2) {}
	Multiplication() : BinaryOperator() {}

	OVERRIDE_DEFAULT_COPY_OP(Multiplication)
	DEFAULT_COPY_IMPL(Multiplication)
	CLASS_STRING(Multiplication)

	virtual MathContainer simplify() const;
	virtual MathContainer solve_for_index(const MathObject &expr, int offset) const;

	virtual bool is_multiplicative() const { return true; }

};

#endif /* MULTIPLICATION_H */
