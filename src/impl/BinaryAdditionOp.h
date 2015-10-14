#ifndef IMPL_ADDITION_H
#define IMPL_ADDITION_H

#include "DoubleDispatch.h"
#include "ExtMathContainer.h"
#include "MathObject.h"
#include "Integer.h"
#include "Real.h"
#include "Rational.h"

class BinaryAdditionOp : public BinaryOperation
{
	public:
	
	virtual ExtMathContainer execute(const MathObject *mo1, const MathObject *mo2) const throw (InternalError);
	virtual ExtMathContainer execute(const Integer *i1, const Integer *i2) const throw ();
	virtual ExtMathContainer execute(const Real *f1, const Real *f2) const throw ();
	virtual ExtMathContainer execute(const Rational *r1, const Rational *r2) const throw ();
	virtual ExtMathContainer execute(const ColVector *cv1, const ColVector *cv2) const throw ();
	
	DEF_BINARY_EXEC_NOT_IMPLEMENTED(Complex)
	DEF_BINARY_EXEC_NOT_IMPLEMENTED(Constant)
	DEF_BINARY_EXEC_NOT_IMPLEMENTED(Matrix)
	DEF_BINARY_EXEC_NOT_IMPLEMENTED(RowVector)
	DEF_BINARY_EXEC_NOT_IMPLEMENTED(SubMatrix)
};

#endif /* IMPL_ADDITION_H */
