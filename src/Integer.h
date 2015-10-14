#ifndef INTEGER_H
#define INTEGER_H

#include <iostream>
#include "Rational.h"

class Integer : public Rational
{
	public:
	
	Integer(int);
	Integer();
	
	OVERRIDE_DEFAULT_COPY_OP(Integer)
	DEFAULT_COPY_IMPL(Integer)
	DEF_BINARY_OP_VISIT(Integer)
	CLASS_STRING(Integer)
	
	virtual int to_int() const;
	virtual string to_string() const;
	
	protected:
	
	virtual void write_to_stream(ostream &) const;
};

#endif /* INTEGER_H */
