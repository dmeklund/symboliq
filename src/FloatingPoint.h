#ifndef FLOATING_POINT
#define FLOATING_POINT

#include "Number.h"

#include "UndefException.h"
#include "DivideByZero.h"
#include "Variable.h"

class FloatingPoint : public Number {
	public:
	
	FloatingPoint();
	FloatingPoint(double);
	FloatingPoint(const Number &);
	
	OVERRIDE_DEFAULT_COPY_OP(FloatingPoint)
	DEF_BINARY_OP_VISIT(FloatingPoint)
	
	virtual FloatingPoint* copy() const;
	
	virtual bool  is_equal(const MathObject &) const throw ();
	virtual void set_equal(const MathObject &) throw (invalid_argument, IllegalOperation);
	
	private:
	
};

#endif
