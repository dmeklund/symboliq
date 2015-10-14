#ifndef DIVISION_H
#define DIVISION_H

#include "MathObject.h"
#include "BinaryOperator.h"

#define DIVISION_PRECEDENCE 4

class Division : public BinaryOperator
{

public:

	Division(const MathObject &mo1, const MathObject &mo2) : BinaryOperator(DIVISION_PRECEDENCE, "/", mo1, mo2) {}
	Division() : BinaryOperator() {}

	OVERRIDE_DEFAULT_COPY_OP(Division)
	DEFAULT_COPY_IMPL(Division)
	CLASS_STRING(Division)

	virtual MathContainer simplify() const;
	virtual MathContainer solve_for_index(const MathObject &expr, int offset) const;

	virtual bool is_multiplicative() const { return true; }

};

#endif /* DIVISION_H */
