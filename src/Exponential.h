#ifndef EXPONENTIAL_H
#define EXPONENTIAL_H

#include "UnaryOperator.h"
#include "MathObject.h"
#include "MathContainer.h"

#define EXP_STR "e^"
#define EXP_PRECEDENCE 2

#define LOG_STR "log"
#define LOG_PRECEDENCE 2

class Exponential : public UnaryOperator
{
public:

	Exponential(const MathObject &mo) : UnaryOperator(EXP_PRECEDENCE, EXP_STR, mo) {}
	Exponential() : UnaryOperator() {}

	virtual MathContainer inverse(const MathObject &expr) const;
	virtual MathContainer simplify() const { return this->arg.simplify().Exp(); }
};

class Logarithm : public UnaryOperator
{
public:

	Logarithm(const MathObject &mo) : UnaryOperator(LOG_PRECEDENCE, LOG_STR, mo) {}
	Logarithm() : UnaryOperator() {}

	virtual MathContainer inverse(const MathObject &expr) const
	{ return MathContainer(Exponential(expr)); }
	virtual MathContainer simplify() const { return this->arg.simplify().Log(); }
};

MathContainer
Exponential::inverse(const MathObject &expr) const
{
	return MathContainer(Logarithm(expr));
}

#endif /* EXPONENTIAL_H */
