#ifndef COMPARISON_H
#define COMPARISON_H

#include <string>

#include "MathObject.h"
#include "MathContainer.h"
#include "BinaryOperator.h"

#define COMPARISON_PRECEDENCE 8

class Comparison : public BinaryOperator
{
	
public:
	
	Comparison(const string str, const MathObject &lhs, const MathObject &rhs)
		: BinaryOperator(COMPARISON_PRECEDENCE, str, lhs, rhs)
	{ /* assert(mo1.m_dim = mo2.m_dim); */ } // TODO: deal with this more appropriately
	Comparison() : BinaryOperator() {}
	
	const MathObject& get_lhs() const { return this->get_arg1(); }
	const MathObject& get_rhs() const { return this->get_arg2(); }

	virtual string to_string() const;
	virtual MathContainer simplify() const;

	virtual MathContainer factory(const MathObject &lhs, const MathObject &rhs) const = 0;

	virtual MathContainer  add(const MathObject &) const throw (OPERATOR_PLUS_EXCEPTIONS);
	virtual MathContainer  sub(const MathObject &) const throw (OPERATOR_MINUS_EXCEPTIONS);
 	virtual MathContainer mult(const MathObject &) const throw (OPERATOR_TIMES_EXCEPTIONS);
	virtual MathContainer  div(const MathObject &) const throw (OPERATOR_DIVIDE_EXCEPTIONS);

	virtual MathContainer negate() const throw ();

private:

};

#endif /* COMPARISON_H */
