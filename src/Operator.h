#ifndef OPERATOR_H
#define OPERATOR_H

#include "MathObject.h"

class Operator : public MathObject
{
	
public:
	
	Operator(int prec) :  MathObject(true, 0), o_precedence(prec) {}
	virtual ~Operator() {}

	virtual MathContainer simplify() const = 0;
	virtual MathContainer solve_for_index(const MathObject &expr, int offset) const = 0;

	virtual int precedence() const { return o_precedence; }

	virtual bool is_additive() const { return false; }
	virtual bool is_multiplicative() const { return false; }

protected:

	int o_precedence;

private:

};

#endif /* OPERATOR_H */
