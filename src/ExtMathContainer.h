#ifndef EXT_VARIABLE_H
#define EXT_VARIABLE_H

#include <iostream>

class MathObject;

class ExtMathContainer
{
	public:
	
	ExtMathContainer(MathObject *);
	ExtMathContainer(const ExtMathContainer &);
	ExtMathContainer();
	
	virtual ~ExtMathContainer();

	MathObject* var();
	const MathObject* var() const;
	
	operator MathObject* () const;
	
	MathObject* operator=(MathObject *) throw ();
	MathObject* operator=(const ExtMathContainer) throw ();
	
#ifdef DEBUG
	static bool test_all(ostream &out = cerr);
#endif /* DEBUG */

	private:

	MathObject *v_var;
};



#endif /* VARIABLE_H */
