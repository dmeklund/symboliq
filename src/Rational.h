#ifndef RATIONAL_H
#define RATIONAL_H

#include <stdexcept>
#include <iostream>

#include "UndefException.h"
#include "DivideByZero.h"
#include "Real.h"
#include "DoubleDispatch.h"
#include "MathObject.h"

class Rational : public Real {

public:
	
	Rational(bool pos, unsigned int whole, unsigned int numer, unsigned int denom, bool simplified)
		throw (DivideByZero);
	Rational(short sign, unsigned int whole, unsigned int numer, unsigned int denom)
		throw (invalid_argument, DivideByZero);
	Rational(int whole, unsigned int numer, unsigned int denom)
		throw (DivideByZero);
	Rational(int numer, unsigned int denom=1) throw (DivideByZero);
	Rational();
	
	OVERRIDE_DEFAULT_COPY_OP(Rational)
	DEFAULT_COPY_IMPL(Rational)
	DEF_BINARY_OP_VISIT(Rational)
	CLASS_STRING(Rational)
	
	unsigned int get_whole() const;
	unsigned int get_numer() const;
	unsigned int get_denom() const;
	short get_sign() const;
	bool get_pos() const;

	static void add(bool a_pos,  unsigned int a_whole,  unsigned int a_numer,  unsigned int a_denom,
	         bool b_pos,  unsigned int b_whole,  unsigned int b_numer,  unsigned int b_denom,
	         bool &c_pos, unsigned int &c_whole, unsigned int &c_numer, unsigned int &c_denom);
			 
	static void add(unsigned int a_whole,  unsigned int a_numer,  unsigned int a_denom,
             unsigned int b_whole,  unsigned int b_numer,  unsigned int b_denom,
             unsigned int &c_whole, unsigned int &c_numer, unsigned int &c_denom);

	static inline void sub(
		bool a_pos,  unsigned int a_whole,  unsigned int a_numer,  unsigned int a_denom,
	    bool b_pos,  unsigned int b_whole,  unsigned int b_numer,  unsigned int b_denom,
	    bool &c_pos, unsigned int &c_whole, unsigned int &c_numer, unsigned int &c_denom
	);
			 
	static void sub(unsigned int a_whole,  unsigned int a_numer,  unsigned int a_denom,
             unsigned int b_whole,  unsigned int b_numer,  unsigned int b_denom,
             unsigned int &c_whole, unsigned int &c_numer, unsigned int &c_denom);
	
	static void mult(bool a_pos,  unsigned int a_whole,  unsigned int a_numer,  unsigned int a_denom,
	          bool b_pos,  unsigned int b_whole,  unsigned int b_numer,  unsigned int b_denom,
			  bool &c_pos, unsigned int &c_whole, unsigned int &c_numer, unsigned int &c_denom);
	
	static void div(bool a_pos,  unsigned int a_whole,  unsigned int a_numer,  unsigned int a_denom,
			 bool b_pos,  unsigned int b_whole,  unsigned int b_numer,  unsigned int b_denom,
			 bool &c_pos, unsigned int &c_whole, unsigned int &c_numer, unsigned int &c_denom);

#ifdef DEBUG
	static bool test_all(ostream &out = cerr);
#endif /* DEBUG */

	
protected:
	
	virtual void write_to_stream(ostream &out) const;
	
	short SIGN();
	static short SIGN(const Rational &);
	
	SETEQUAL_MATHOBJ_IMPL(Rational)
	virtual void set_equal(const Rational &) throw ();
	
	static void simplify(unsigned int &numer, unsigned int &denom);
	static void update_whole(unsigned int &whole, unsigned int &numer, unsigned int &denom);
	
	static unsigned int gcd(unsigned int u, unsigned int v);

	
	unsigned int r_whole, r_numer, r_denom;
	bool r_pos;
};

#endif
