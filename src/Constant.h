#ifndef CONSTANT_H
#define CONSTANT_H

#include <math.h>
#include "Real.h"

#ifndef PI
#  define PI 3.1415926535897932384626433
#endif /* PI */

class Constant : public Real
{
	public:
	
	Constant(double value) : Real(value) {}
	Constant() : Real() {}
	
	OVERRIDE_DEFAULT_COPY_OP(Constant)
	DEFAULT_COPY_IMPL(Constant)
	DEF_BINARY_OP_VISIT(Constant)
	CLASS_STRING(Constant)
	
	Constant* copy() { return this; }
	
	//void* operator new (size_t) { return this; }
	void operator delete (void *) { } // don't delete anything
	/*
	virtual Real& operator =(const Real &);
	virtual Real& operator =(double);
	
	virtual Real& operator +=(const Real &) throw (UndefException);
	virtual Real& operator -=(const Real &) throw (UndefException);
	virtual Real& operator *=(const Real &) throw (UndefException);
	virtual Real& operator /=(const Real &) throw (UndefException, DivideByZero);
	*/
	private:
	
};

class Pi_ : public Constant
{
	public:
	
	Pi_() : Constant(PI) {}
	
	double Sin() const
	{
		return 0;
	}
	
	double Cos() const
	{
		return -1;
	}
	
	private:
};


class Zero_ : public Constant
{
	public:
	
	Zero_() : Constant(0.0) {}
	/*
	virtual MathObject& operator *(MathObject &n) { return *this; }
	virtual MathObject& operator *(double d) { return *this; }
	
	virtual MathObject& operator +(MathObject &n) { return n; }
	*/
};

namespace Math {
	const Pi_ Pi;
	const Zero_ Zero;
}

#endif /* CONSTANT_H */
