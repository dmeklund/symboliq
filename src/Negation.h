#ifndef NEGATION_h
#define NEGATION_H

#include "MathObject.h"
#include "UnaryOperator.h"

#define NEGATION_PRECEDENCE 2

class Negation : public UnaryOperator
{

public:

	Negation(const MathObject &mo) : UnaryOperator(NEGATION_PRECEDENCE, "-", mo) {}
	Negation() : UnaryOperator() {}

	OVERRIDE_DEFAULT_COPY_OP(Negation)
	DEFAULT_COPY_IMPL(Negation)
	CLASS_STRING(Negation)

	virtual MathContainer simplify() const;
	virtual MathContainer inverse(const MathObject &expr) const;

	virtual bool is_additive() const { return true; }

};

#endif /* NEGATION_H */
