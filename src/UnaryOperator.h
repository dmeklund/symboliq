#ifndef UNARY_OPERATOR_H
#define UNARY_OPERATOR_H

#include "MathObject.h"
#include "Operator.h"
#include "MathContainer.h"

class UnaryOperator : public Operator {

public:
	
	UnaryOperator(int prec, const string str, const MathObject &mo);
	UnaryOperator();

	OVERRIDE_DEFAULT_COPY_OP(UnaryOperator)

	const MathObject& get_arg() const;
	virtual string to_string() const;
	virtual MathContainer solve_for_index(const MathObject &expr, int offset) const;

	virtual MathContainer inverse(const MathObject &expr) const = 0;
	virtual MathContainer simplify() const { return MathContainer(*this); }

protected:

	SETEQUAL_MATHOBJ_IMPL(UnaryOperator)
	virtual void set_equal(const UnaryOperator &) throw (OPERATOR_EQUALS_EXCEPTIONS);

	MathContainer arg;
	
private:

	string uo_str;
	
};


#endif /* Unary_OPERATOR_H */
