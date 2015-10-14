#ifndef BINARY_SUBTRACTION_OP
#define BINARY_SUBTRACTION_OP

#include "DoubleDispatch.h"
#include "ExtMathContainer.h"
#include "MathObject.h"
#include "Integer.h"
#include "Real.h"
#include "Rational.h"

#include "Subtraction.h"

class BinarySubtractionOp : public BinaryOperation
{
	public:
	
	virtual ExtMathContainer execute(const MathObject *mo1, const MathObject *mo2) const throw (InternalError)
	{
		Subtraction *sub = new Subtraction(*mo1, *mo2);
		return ExtMathContainer(sub);
	}

	virtual ExtMathContainer execute(const Integer *i1, const Integer *i2) const throw ()
	{
		Integer *i3 = new Integer(i1->get_whole() - i2->get_whole());
		return ExtMathContainer(i3);
	}
	
	virtual ExtMathContainer execute(const Real *f1, const Real *f2) const throw ()
	{
		Real *f3 = new Real(f1->to_float() - f2->to_float());
		return ExtMathContainer(f3);
	}
	
	virtual ExtMathContainer execute(const Rational *r1, const Rational *r2) const throw ()
	{
		Rational *r3 = new Rational(r1->get_whole() - r2->get_whole());
		return ExtMathContainer(r3);
	}
	
	DEF_BINARY_EXEC_NOT_IMPLEMENTED(ColVector)
	DEF_BINARY_EXEC_NOT_IMPLEMENTED(Complex)
	DEF_BINARY_EXEC_NOT_IMPLEMENTED(Constant)
	DEF_BINARY_EXEC_NOT_IMPLEMENTED(Matrix)
	DEF_BINARY_EXEC_NOT_IMPLEMENTED(RowVector)
	DEF_BINARY_EXEC_NOT_IMPLEMENTED(SubMatrix)
};

#endif /* IMPL_ADDITION_H */
