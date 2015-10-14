#ifndef ADDITION_H
#define ADDITION_H

#include "MathObject.h"
#include "BinaryOperator.h"

#define ADDITION_PRECEDENCE 5

class Addition : public BinaryOperator
{

public:

	Addition(const MathObject &mo1, const MathObject &mo2) : BinaryOperator(ADDITION_PRECEDENCE, "+", mo1, mo2) {}
	Addition() : BinaryOperator() {}

	OVERRIDE_DEFAULT_COPY_OP(Addition)
	DEFAULT_COPY_IMPL(Addition)
	CLASS_STRING(Addition)

	virtual MathContainer simplify() const;
	virtual MathContainer solve_for_index(const MathObject &expr, int offset) const;

	virtual bool is_additive() const { return true; }

};

#endif /* ADDITION_H */
