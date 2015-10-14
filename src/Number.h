#ifndef NUMBER_H
#define NUMBER_H

#include "MathObject.h"

class Real : public MathObject {
	public:
	
	Real();
	virtual ~Real();
	
	OVERRIDE_DEFAULT_COPY_OP(Real)
	DEF_BINARY_OP_VISIT(Real)
	
	double to_float() const throw (UndefException);
	virtual string to_string() const;
	
	protected:
	
	virtual void write_to_stream(ostream &) const;
	
	Real(double value);
	Real(Real &);
	
	double n_value;
};

#endif
