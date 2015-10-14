#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "MathObject.h"
#include "BinaryOperator.h"

#define SUBTRACTION_PRECEDENCE 5

class Subtraction : public BinaryOperator
{

public:

	Subtraction(const MathObject &mo1, const MathObject &mo2) : BinaryOperator(SUBTRACTION_PRECEDENCE, "-", mo1, mo2) {}
	Subtraction() : BinaryOperator() {}

	OVERRIDE_DEFAULT_COPY_OP(Subtraction)
	DEFAULT_COPY_IMPL(Subtraction)
	CLASS_STRING(Subtraction)

	virtual MathContainer simplify() const;
	virtual MathContainer solve_for_index(const MathObject &expr, int offset) const;

	virtual bool is_additive() const { return true; }

};

#endif /* SUBTRACTION_H */
