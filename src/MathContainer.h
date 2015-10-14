#ifndef MATHCONTAINER_H
#define MATHCONTAINER_H

#include <iostream>
#include <string>

#include "MathObject.h"
#include "UndefException.h"
#include "DivideByZero.h"

// This class essentially acts as a kind of smart pointer designed
// specifically for MathObjects.  It can be used in (almost) any place a
// MathObject can, the result being that the MathObject this MathContainer
// wraps will be passed along instead (the only exception is in the rare
// places where a pointer, rather than a reference, to a MathObject is 
// needed; see, e.g., NAddition(int N, ...)).  In fact, it was originally
// designed to _inherit_ from MathObject, with the idea that this container
// object could be supplanted into, for example, an Addition operator;
// the user could then modify the contents of the MathContainer, indirectly
// modifying the contents of the Addition operator.  This was scrapped
// in preference to keeping "copies" of objects _true_ copies (i.e., avoiding
// keeping and sharing or changing pointers to objects) due to issues of
// unneeded complexity. Now it acts mostly as a container for a MathObject
// of unknown instance type; e.g., instead of this:
//
// Variable x("x"), y("y"), z("z");
// Addition add = x + y + z;
// add = add.simplify(); // WRONG!  this is now an NAddition object
// NAddition nadd = add.simplify(); // Correct
//
// The user does not need to know the implementation details, and can instead
// say,
//
// Variable x("x"), y("y"), z("z");
// MathContainer mc = x + y + z;
// mc = mc.simplify();
//
class MathContainer
{
	friend ostream& operator << (ostream &out, const MathContainer &v);

public:
	
	MathContainer(const MathObject &mo) : v_var(mo.copy()) {}
	MathContainer(const MathContainer &mc) : v_var(mc.v_var->copy()) {}
	MathContainer() : v_var(new MathObject()) {}

	MathContainer(int i);
	MathContainer(double d);
	
	~MathContainer();

	string class_string() const { return "MathContainer"; }

	MathObject* copy() const;
	string to_string() const;
	
	MathObject& var();
	const MathObject& var() const;
	
	MathContainer& operator () (unsigned int i, unsigned int j) throw (IllegalOperation);
	const MathContainer& operator () (unsigned int i, unsigned int j) const throw (IllegalOperation);

	MathContainer simplify() const;

	MathContainer Sqrt() const throw ();
	MathContainer Exp() const throw ();
	MathContainer Log() const throw ();

	MathContainer Pow(const MathObject &) const;
	MathContainer Pow(int) const;
	MathContainer Pow(double) const;
	
	MathContainer LogBase(const MathObject &) const;
	MathContainer LogBase(int) const;
	MathContainer LogBase(double) const;

	MathContainer Sin() const throw ();
	MathContainer Cos() const throw ();
	MathContainer Tan() const throw ();

	MathContainer Sinh() const throw ();
	MathContainer Cosh() const throw ();
	MathContainer Tanh() const throw ();

	MathContainer ArcSin() const throw (invalid_argument);
	MathContainer ArcCos() const throw (invalid_argument);
	MathContainer ArcTan() const throw (invalid_argument);

	MathContainer ArcSinh() const throw (invalid_argument);
	MathContainer ArcCosh() const throw (invalid_argument);
	MathContainer ArcTanh() const throw (invalid_argument);
	
	MathObject& operator = (const MathObject &) throw ();
	MathObject& operator = (const MathContainer &) throw ();
	MathObject& operator = (int) throw (OPERATOR_EQUALS_EXCEPTIONS);
	MathObject& operator = (double) throw (OPERATOR_EQUALS_EXCEPTIONS);
	
	bool operator == (const MathObject &) const throw (OPERATOR_ISEQUAL_EXCEPTIONS);
	bool operator == (int) const throw (OPERATOR_ISEQUAL_EXCEPTIONS);
	bool operator == (double) const throw (OPERATOR_ISEQUAL_EXCEPTIONS);

	template <class T>
	bool operator != (T obj) const throw (OPERATOR_ISEQUAL_EXCEPTIONS)
	{ return !(*this == obj); }
	
	MathContainer operator+(const MathObject &) const throw (OPERATOR_PLUS_EXCEPTIONS);
	MathContainer operator-(const MathObject &) const throw (OPERATOR_MINUS_EXCEPTIONS);
	MathContainer operator*(const MathObject &) const throw (OPERATOR_TIMES_EXCEPTIONS);
	MathContainer operator/(const MathObject &) const throw (OPERATOR_DIVIDE_EXCEPTIONS);
	
	MathContainer operator+(const MathContainer &) const throw (OPERATOR_PLUS_EXCEPTIONS);
	MathContainer operator-(const MathContainer &) const throw (OPERATOR_MINUS_EXCEPTIONS);
	MathContainer operator*(const MathContainer &) const throw (OPERATOR_TIMES_EXCEPTIONS);
	MathContainer operator/(const MathContainer &) const throw (OPERATOR_DIVIDE_EXCEPTIONS);

	MathContainer operator-() const throw ();

	MathContainer operator + (int) const throw (OPERATOR_PLUS_EXCEPTIONS);
	MathContainer operator - (int) const throw (OPERATOR_MINUS_EXCEPTIONS);
	MathContainer operator * (int) const throw (OPERATOR_TIMES_EXCEPTIONS);
	MathContainer operator / (int) const throw (OPERATOR_DIVIDE_EXCEPTIONS);
	
	MathContainer operator + (double) const throw (OPERATOR_PLUS_EXCEPTIONS);
	MathContainer operator - (double) const throw (OPERATOR_MINUS_EXCEPTIONS);
	MathContainer operator * (double) const throw (OPERATOR_TIMES_EXCEPTIONS);
	MathContainer operator / (double) const throw (OPERATOR_DIVIDE_EXCEPTIONS);
	
	MathObject& operator+=(const MathObject &) throw (UndefException);
	MathObject& operator-=(const MathObject &) throw (UndefException);
	MathObject& operator*=(const MathObject &) throw (UndefException);
	MathObject& operator/=(const MathObject &) throw (UndefException, DivideByZero);
	
	MathObject& operator+=(const MathContainer &) throw (UndefException,IllegalOperation);
	MathObject& operator-=(const MathContainer &) throw (UndefException);
	MathObject& operator*=(const MathContainer &) throw (UndefException);
	MathObject& operator/=(const MathContainer &) throw (UndefException, DivideByZero);

	operator MathObject& () const;
	
#ifdef DEBUG
	static bool test_all(ostream &out = cerr);
#endif /* DEBUG */

protected:
	          
private:

	MathObject *v_var;

};

MathContainer operator + (int, const MathContainer &) throw (OPERATOR_PLUS_EXCEPTIONS);
MathContainer operator - (int, const MathContainer &) throw (OPERATOR_MINUS_EXCEPTIONS);
MathContainer operator * (int, const MathContainer &) throw (OPERATOR_TIMES_EXCEPTIONS);
MathContainer operator / (int, const MathContainer &) throw (OPERATOR_DIVIDE_EXCEPTIONS);

MathContainer operator + (double, const MathContainer &) throw (OPERATOR_PLUS_EXCEPTIONS);
MathContainer operator - (double, const MathContainer &) throw (OPERATOR_MINUS_EXCEPTIONS);
MathContainer operator * (double, const MathContainer &) throw (OPERATOR_TIMES_EXCEPTIONS);
MathContainer operator / (double, const MathContainer &) throw (OPERATOR_DIVIDE_EXCEPTIONS);


#endif /* MATHCONTAINER_H */
