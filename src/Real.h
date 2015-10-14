#ifndef REAL
#define REAL

#include "UndefException.h"
#include "DivideByZero.h"
#include "MathContainer.h"

class Real : public MathObject {

public:
	
	Real();
	Real(double);
	
	OVERRIDE_DEFAULT_COPY_OP(Real)
	DEFAULT_COPY_IMPL(Real)
	DEF_BINARY_OP_VISIT(Real)
	CLASS_STRING(Real)
	
	virtual double to_float() const throw (UndefException);
	virtual string to_string() const;

	operator Complex () const;

//#ifdef DEBUG
	static bool test_all(ostream &out = cerr);
//#endif /* DEBUG */
	
protected:

	virtual bool is_equal(const MathObject &mo) const throw ();
	SETEQUAL_MATHOBJ_IMPL(Real)
	virtual void set_equal(const Real &) throw (invalid_argument, IllegalOperation);
	
private:
	
	double r_value;

};

#endif // REAL
