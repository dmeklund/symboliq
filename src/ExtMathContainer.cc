#include <iostream>

#include "ExtMathContainer.h"

ExtMathContainer::ExtMathContainer(MathObject *mo)
	: v_var(mo)
{
}

ExtMathContainer::ExtMathContainer(const ExtMathContainer &v)
	: v_var(v.v_var)
{
}

ExtMathContainer::ExtMathContainer()
	: v_var(NULL) // unitialized MathObject
{
}

ExtMathContainer::~ExtMathContainer()
{
//	delete v_var;
}

MathObject *
ExtMathContainer::var()
{
	return v_var;
}

const MathObject *
ExtMathContainer::var() const
{
	return v_var;
}

ExtMathContainer::operator MathObject* () const
{
	return v_var;
}

MathObject *
ExtMathContainer::operator=(MathObject *mo) throw ()
{
	v_var =  mo;
	
	return v_var;
}

MathObject *
ExtMathContainer::operator=(const ExtMathContainer v) throw ()
{
	v_var = v.v_var;
	
	return v_var;
}
	
#ifdef DEBUG

bool
MathContainer::test_all(ostream &out = cerr)
{
	Test results("ExtMathContainer");
	
	return results.get_final_result();
}

#endif /* DEBUG */

