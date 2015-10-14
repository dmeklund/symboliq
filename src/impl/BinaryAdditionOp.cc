#include "BinaryAdditionOp.h"
#include "MathObject.h"
#include "Integer.h"
#include "Real.h"
#include "Rational.h"
#include "ColVector.h"
#include "Addition.h"

ExtMathContainer
BinaryAdditionOp::execute(const MathObject *mo1, const MathObject *mo2) const throw (InternalError)
{
	//throw InternalError("Attempted addition on two ill-defined MathObjects");
	// TODO: memory leak?
	//MathObject *m1 = mo1->copy(); // non-const
	//MathObject *m2 = mo2->copy();
	Addition *add = new Addition(*mo1, *mo2);
	return ExtMathContainer(add);
}

ExtMathContainer
BinaryAdditionOp::execute(const Integer *i1, const Integer *i2) const throw ()
{
	if (!i1->is_defined() || !i2->is_defined())
		throw UndefException("addition operation");

	Integer *i3 = new Integer(i1->get_whole() + i2->get_whole());
	return ExtMathContainer(i3);
}

ExtMathContainer
BinaryAdditionOp::execute(const Real *f1, const Real *f2) const throw ()
{
	if (!f1->is_defined() || !f2->is_defined())
		throw UndefException("addition operation");
	
	Real *f3 = new Real(f1->to_float() + f2->to_float());
	return ExtMathContainer(f3);
}

ExtMathContainer
BinaryAdditionOp::execute(const Rational *r1, const Rational *r2) const throw ()
{
	if (!r1->is_defined() || !r2->is_defined())
		throw UndefException("addition operation");
	
	unsigned int whole, numer, denom;
	bool sign, simplified = true;
	
	Rational::add(r1->get_pos(), r1->get_whole(), r1->get_numer(), r1->get_denom(),
				  r2->get_pos(), r2->get_whole(), r2->get_numer(), r2->get_denom(),
				  sign, whole, numer, denom);
				  
	Rational *r3 = new Rational(sign, whole, numer, denom, simplified);
	
	return ExtMathContainer(r3);
}
/*
ExtMathContainer
BinaryAdditionOp::execute(const Angle *a1, const Angle *a2) const throw ()
{
	if (!a1->is_defined() || !a2->is_defined())
		throw UndefException("addition operation");
	
	Angle *a3 = new Angle(a1->in_radians() + a2->in_radians(), Angle::RADIANS);
	return ExtMathContainer(a3);
}
*/
ExtMathContainer
BinaryAdditionOp::execute(const ColVector *cv1, const ColVector *cv2) const throw ()
{
	if (!cv1->is_defined() || !cv2->is_defined())
		throw UndefException("addition operation");
	
	return execute((Vector*) cv1, (Vector*) cv2);
}
