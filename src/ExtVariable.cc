#include <iostream>

#include "ExtVariable.h"

ExtVariable::ExtVariable(MathObject *mo)
	: v_var(mo)
{
}

ExtVariable::ExtVariable(const ExtVariable &v)
	: v_var(v.v_var)
{
}

ExtVariable::ExtVariable()
	: v_var(NULL) // unitialized MathObject
{
}

ExtVariable::~ExtVariable()
{
//	delete v_var;
}

MathObject *
ExtVariable::var()
{
	return v_var;
}

const MathObject *
ExtVariable::var() const
{
	return v_var;
}

ExtVariable::operator MathObject* () const
{
	return v_var;
}

MathObject *
ExtVariable::operator=(MathObject *mo) throw ()
{
	v_var =  mo;
	
	return v_var;
}

MathObject *
ExtVariable::operator=(const ExtVariable v) throw ()
{
	v_var = v.v_var;
	
	return v_var;
}
	
#ifdef DEBUG

bool
Variable::test_all(ostream &out = cerr)
{
	Test results("ExtVariable");
	
	return results.get_final_result();
}

#endif /* DEBUG */

