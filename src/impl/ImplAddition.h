#ifndef IMPL_ADDITION_H
#define IMPL_ADDITION_H

#include "DoubleDispatch.h"
#include "ExtVariable.h"
#include "MathObject.h"
#include "Integer.h"
#include "Real.h"
#include "Rational.h"

class BinaryAdditionOp : public BinaryOperation
{
	public:
	
	virtual ExtVariable execute(const MathObject *mo1, const MathObject *mo2) throw (InternalError)
	{
		throw InternalError("Attempted addition on two ill-defined MathObjects");
	}

	virtual ExtVariable execute(const Integer *i1, const Integer *i2) throw ()
	{
		Integer *i3 = new Integer(i1->get_whole() + i2->get_whole());
		return ExtVariable(i3);
	}
	
	virtual ExtVariable execute(const Real *f1, const Real *f2) throw ()
	{
		Real *f3 = new Real(f1->to_float() + f2->to_float());
		return ExtVariable(f3);
	}
	
	virtual ExtVariable execute(const Rational *r1, const Rational *r2) throw ()
	{
		Rational *r3 = new Rational(r1->get_whole() + r2->get_whole());
		return ExtVariable(r3);
	}
};

#endif /* IMPL_ADDITION_H */
