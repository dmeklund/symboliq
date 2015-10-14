#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <iostream>

#include "MathObject.h"
#include "UndefException.h"
#include "DivideByZero.h"

class Variable : public MathObject
{

public:

	Variable(const string name);
	Variable(const char* name);

	OVERRIDE_DEFAULT_COPY_OP(Variable)
	DEFAULT_COPY_IMPL(Variable)
	CLASS_STRING(Variable)

	virtual string to_string() const;

	static bool test_all(ostream &out = cerr);

private:

	string v_name;

};



#endif /* VARIABLE_H */
