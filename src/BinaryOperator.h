#ifndef BINARY_OPERATOR_H
#define BINARY_OPERATOR_H

#include "MathObject.h"
#include "Operator.h"
#include "MathContainer.h"

class BinaryOperator : public Operator {

public:
	
	BinaryOperator(int prec, const string str, const MathObject &m1, const MathObject &m2);
	BinaryOperator();

	OVERRIDE_DEFAULT_COPY_OP(BinaryOperator)

	const MathObject& get_arg1() const;
	const MathObject& get_arg2() const;

	virtual string to_string() const;

protected:
/*
	SETEQUAL_MATHOBJ_IMPL(BinaryOperator)
	virtual void set_equal(const BinaryOperator &) throw (OPERATOR_EQUALS_EXCEPTIONS);
*/
	MathContainer arg1, arg2;
	string bo_str;
	
private:
	
};


#endif /* BINARY_OPERATOR_H */
