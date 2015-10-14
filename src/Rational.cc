#include <iostream>
#include <sstream>
#include <math.h>

#include "Rational.h"
#include "MathContainer.h"
#include "Test.h"

//#define SIGN(rat) ((rat).r_pos ? +1 : -1)
#define PSIGN(po) (po ? +1 : -1)

#define POS(i) (i >= 0)

Rational::Rational(bool pos, unsigned int whole, unsigned int numer, unsigned int denom, bool simplified)
	throw (DivideByZero)
	: Real(PSIGN(pos) * ((double) whole + (double) numer / denom))
{
	if (denom == 0)
		throw DivideByZero("Rational");
	
	r_pos = pos;
	r_whole = whole + numer / denom; // integer division
	r_numer = numer % denom;
	r_denom = denom;
	
	if (!simplified)
		simplify(r_numer, r_denom);
}

Rational::Rational(short sign, unsigned int whole, unsigned int numer, unsigned int denom)
	throw (invalid_argument, DivideByZero)
	: Real(sign * ((double) whole + (double) numer / denom))
{
	if (abs(sign) != 1)
		throw invalid_argument("sign");
	if (denom == 0)
		throw DivideByZero("Rational");
	
	r_whole = whole + numer / denom; // integer division
	r_numer = numer % denom;
	r_denom = denom;
	
	r_pos = (sign >= 0);
	
	simplify(r_numer, r_denom);
}

Rational::Rational(int whole, unsigned int numer, unsigned int denom)
	throw (DivideByZero)
	: Real((double) whole + (double) numer / denom)
{
	if (denom == 0)
		throw DivideByZero("Rational");
	
	r_pos = (whole >= 0);
	whole = abs(whole);
	
	r_whole = whole + numer / denom; // integer division
	r_numer = numer % denom;
	r_denom = denom;
	
	simplify(r_numer, r_denom);
}

Rational::Rational(int numer, unsigned int denom) throw (DivideByZero)
	: Real((double) numer / denom)
{
	if (denom == 0)
		throw DivideByZero("Rational");
	
	r_pos = (numer > 0);
	numer = abs(numer);
	
	r_whole = numer / denom; // integer division
	r_numer = numer % denom;
	r_denom = denom;
	
	simplify(r_numer, r_denom);
}

Rational::Rational() : Real() {}

unsigned int
Rational::get_whole() const
{
	return r_whole;
}

unsigned int
Rational::get_numer() const
{	
	return r_numer;
}

unsigned int
Rational::get_denom() const
{
	return r_denom;
}

short
Rational::get_sign() const
{
	return SIGN(*this);
}

bool
Rational::get_pos() const
{
	return r_pos;
}


/*
Rational &
Rational::operator=(const Rational &param)
{
	set_equal(param);
	
	return *this;
}

Rational &
Rational::operator=(int param)
{
	r_numer = 0;
	r_denom = 1;
	r_whole = param;
	n_value = param;
	
	return *this;
}

Rational
Rational::operator+(const Rational &param) throw (UndefException)
{
	bool pos;
	unsigned int whole, numer, denom;
	Rational result;
	
	if (!m_defined)
		throw UndefException("Rational");
	
	add(r_pos, r_whole, r_numer, r_denom,
		param.r_pos, param.r_whole, param.r_numer, param.r_denom,
		pos, whole, numer, denom);
		
	result = Rational(pos, whole, numer, denom, true);
	
	return result;
}

Rational 
Rational::operator-(const Rational &param) throw (UndefException)
{
	Rational result;
	bool pos;
	unsigned int whole, numer, denom;
	
	if (!m_defined)
		throw UndefException("Rational");
	
	sub(r_pos, r_whole, r_numer, r_denom,
		param.r_pos, param.r_whole, param.r_numer, param.r_denom,
		pos, whole, numer, denom);
		
	result = Rational(pos, whole, numer, denom, true);
	
	return result;
}

Rational
Rational::operator*(const Rational &param) throw (UndefException)
{
	Rational result;
	bool pos;
	unsigned int whole, numer, denom;
	
	if (!m_defined)
		throw UndefException("Rational");
	
	mult(r_pos, r_whole, r_numer, r_denom,
		 param.r_pos, param.r_whole, param.r_numer, param.r_denom,
		 pos, whole, numer, denom);
	
	result = Rational(pos, whole, numer, denom, true);
	
	return result;
}

Rational
Rational::operator/(const Rational &param) throw (UndefException, DivideByZero)
{
	Rational result;
	bool pos;
	unsigned int whole, numer, denom;
	
	if (!m_defined)
		throw UndefException("Rational");
	if (param == 0)
		throw DivideByZero("Rational");
	
	div(r_pos, r_whole, r_numer, r_denom,
		param.r_pos, param.r_whole, param.r_numer, param.r_denom,
		pos, whole, numer, denom);
		
	result = Rational(pos, whole, numer, denom, true);
	return result;
}

Rational
Rational::operator+(int param) throw (UndefException)
{
	Rational result;
	bool pos;
	unsigned int whole, numer, denom;
	
	if (!m_defined)
		throw UndefException("Rational");
	
	add(r_pos, r_whole, r_numer, r_denom,
		POS(param), param, 0, 1,
		pos, whole, numer, denom);
		
	result = Rational(pos, whole, numer, denom, true);
	return result;
}

Rational
Rational::operator-(int param) throw (UndefException)
{
	Rational result;
	bool pos;
	unsigned int whole, numer, denom;
	
	if (!m_defined)
		throw UndefException("Rational");
	
	sub(r_pos, r_whole, r_numer, r_denom,
		POS(param), param, 0, 1,
		pos, whole, numer, denom);
		
	result = Rational(pos, whole, numer, denom, true);
	return result;
}

Rational
Rational::operator*(int param) throw (UndefException)
{
	Rational result;
	bool pos;
	unsigned int whole, numer, denom;
	
	if (!m_defined)
		throw UndefException("Rational");
	
	mult(r_pos, r_whole, r_numer, r_denom,
		 POS(param), param, 0, 1,
		 pos, whole, numer, denom);
		
	result = Rational(pos, whole, numer, denom, true);
	return result;
}

Rational
Rational::operator/(int param) throw (UndefException, DivideByZero)
{
	Rational result;
	bool pos;
	unsigned int whole, numer, denom;
	
	if (!m_defined)
		throw UndefException("Rational");
	if (param == 0)
		throw DivideByZero("Rational");
	
	div(r_pos, r_whole, r_numer, r_denom,
		POS(param), param, 0, 1,
		pos, whole, numer, denom);
		
	result = Rational(pos, whole, numer, denom, true);
	return result;
}

Rational &
Rational::operator+=(const Rational &param) throw (UndefException)
{
	if (!m_defined)
		throw UndefException("Rational");
	
	add(r_pos, r_whole, r_numer, r_denom,
		param.r_pos, param.r_whole, param.r_numer, param.r_denom,
		r_pos, r_whole, r_numer, r_denom);
	
	return *this;
}

Rational &
Rational::operator-=(const Rational &param) throw (UndefException)
{
	if (!m_defined)
		throw UndefException("Rational");
	
	sub(r_pos, r_whole, r_numer, r_denom,
		param.r_pos, param.r_whole, param.r_numer, param.r_denom,
		r_pos, r_whole, r_numer, r_denom);
	
	return *this;
}

Rational &
Rational::operator*=(const Rational &param) throw (UndefException)
{
	if (!m_defined)
		throw UndefException("Rational");
	
	mult(r_pos, r_whole, r_numer, r_denom,
		 param.r_pos, param.r_whole, param.r_numer, param.r_denom,
		 r_pos, r_whole, r_numer, r_denom);
	
	return *this;
}

Rational &
Rational::operator/=(const Rational &param) throw (UndefException, DivideByZero)
{
	if (!m_defined)
		throw UndefException("Rational");
	if (param == 0)
		throw DivideByZero("Rational");
	
	div(r_pos, r_whole, r_numer, r_denom,
		param.r_pos, param.r_whole, param.r_numer, param.r_denom,
		r_pos, r_whole, r_numer, r_denom);
	
	return *this;
}

Rational &
Rational::operator+=(int param) throw (UndefException)
{
	if (!m_defined)
		throw UndefException("Rational");
	
	add(r_pos, r_whole, r_numer, r_denom,
		POS(param), param, 0, 1,
		r_pos, r_whole, r_numer, r_denom);
	
	return *this;
}
	
Rational &
Rational::operator-=(int param) throw (UndefException)
{
	if (!m_defined)
		throw UndefException("Rational");
	
	sub(r_pos, r_whole, r_numer, r_denom,
		POS(param), param, 0, 1,
		r_pos, r_whole, r_numer, r_denom);
	
	return *this;
}

Rational &
Rational::operator*=(int param) throw (UndefException)
{
	if (!m_defined)
		throw UndefException("Rational");
	
	mult(r_pos, r_whole, r_numer, r_denom,
		 POS(param), param, 0, 1,
		 r_pos, r_whole, r_numer, r_denom);
	
	return *this;
}

Rational &
Rational::operator/=(int param) throw (UndefException, DivideByZero)
{
	if (!m_defined)
		throw UndefException("Rational");
	if (param == 0)
		throw DivideByZero("Rational");
	
	div(r_pos, r_whole, r_numer, r_denom,
		POS(param), param, 0, 1,
		r_pos, r_whole, r_numer, r_denom);
	
	return *this;
}
*/
	
/* class test method */
#ifdef DEBUG

bool
Rational::test_all(ostream &out)
{
	Rational a(-1, 3, 4), b(12, 8), c, f;
	MathContainer d;
	Test results("Rational");
	//unsigned int numer, denom, whole;
	//short sign;
	
	results.check(c, "uninitialized: m_defined", c.is_defined(), false);
	
	results.check(a, "initialization: sign", SIGN(a), (short)-1);
	results.check(a, "initialization: whole", a.r_whole, (unsigned int)1);
	results.check(a, "initialization: numer", a.r_numer, (unsigned int)3);
	results.check(a, "initialization: denom", a.r_denom, (unsigned int)4);
	
	results.check(b, "initialization & simplification: sign", SIGN(b), (short)+1);
	results.check(b, "initialization & simplification: whole", b.r_whole, (unsigned int)1);
	results.check(b, "initialization & simplification: numer", b.r_numer, (unsigned int)1);
	results.check(b, "initialization & simplification: denom", b.r_denom, (unsigned int)2);
	
	//Rational c( (Rational&) (a + b).var() ); // result: -1/4
	c = f = a + b; // also tests double-assignment
	results.check(c, "addition: sign", SIGN(c), (short)-1);
	results.check(c, "addition: whole", c.r_whole, (unsigned int)0);
	results.check(c, "addition: numer", c.r_numer, (unsigned int)1);
	results.check(c, "addition: denom", c.r_denom, (unsigned int)4);
	
	c = a * b; // result: -7/4 * 3/2 = -21/8 = -2 5/8
	
	results.check(c, "multiplication: sign", SIGN(c), (short)-1);
	results.check(c, "multiplication: whole", c.r_whole, (unsigned int)2);
	results.check(c, "multiplication: numer", c.r_numer, (unsigned int)5);
	results.check(c, "multiplication: denom", c.r_denom, (unsigned int)8);
	
	return results.get_final_result();
}

#endif /* DEBUG */

// private methods

void
Rational::write_to_stream(ostream &out) const
{
	if (!is_defined())
		out << "undef";
	else if (r_whole == 0 && r_numer == 0)
		out << "0";
	else
	{
		if (!r_pos)
			out << "-";
		
		if (r_whole != 0)
		{
			out << r_whole;
			if (r_denom != 0)
				out << " ";
		}
		if (r_numer != 0)
			out << r_numer << "/" << r_denom;
	}
}

short
Rational::SIGN()
{
	if (r_pos)
		return +1;
	else
		return -1;
}

short
Rational::SIGN(const Rational &r)
{
	if (r.r_pos)
		return +1;
	else 
		return -1;
}

void
Rational::set_equal(const Rational &param) throw ()
{
	r_pos   = param.r_pos;
	r_whole = param.r_whole;
	r_numer = param.r_numer;
	r_denom = param.r_denom;
	
	Real::set_equal(param);
}

void
Rational::simplify(unsigned int &numer, unsigned int &denom)
{
	unsigned int divisor;
	
	divisor = gcd(numer, denom);
	
	if (divisor != 1)
	{
		numer /= divisor;
		denom /= divisor;
	}
}

void
Rational::update_whole(unsigned int &whole, unsigned int &numer, unsigned int &denom)
{
	if (numer > denom)
	{
		whole += numer / denom; // integer division
		numer  = numer % denom; // remainder
	}
}

void
Rational::add(
	bool a_pos,  unsigned int a_whole,  unsigned int a_numer,  unsigned int a_denom,
    bool b_pos,  unsigned int b_whole,  unsigned int b_numer,  unsigned int b_denom,
	bool &c_pos, unsigned int &c_whole, unsigned int &c_numer, unsigned int &c_denom
	)
{
	// c := a + b
	if (a_pos xor b_pos)
	{
		// a and b are of opposite sign; a lot more trouble
		if (a_whole > b_whole)
			c_pos = a_pos;
		else if (a_whole < b_whole)
			c_pos = b_pos;
		else // a_whole == b_whole
		{
			if (a_numer == b_numer && a_denom == b_denom)
			{
				// c := 0
				c_pos   = true; // arbitrary
				c_whole = 0;
				c_numer = 0;
				c_denom = 1;
				
				return;
			}
			else
			{
				double sum;
				sum = PSIGN(a_pos)*(double)a_numer/a_denom
				      + PSIGN(b_pos)*(double)b_numer/b_denom;
				c_pos = (sum >= 0);
			}
		}
		
		sub(a_whole, a_numer, a_denom,
			b_whole, b_numer, b_denom,
			c_whole, c_numer, c_denom);
	} 
	else
	{
		// a and b are of the same sign
		c_pos = a_pos; // = b_pos
		add(a_whole, a_numer, a_denom,
			b_whole, b_numer, b_denom,
			c_whole, c_numer, c_denom);
	}
}

void
Rational::add(
	unsigned int a_whole,  unsigned int a_numer,  unsigned int a_denom,
	unsigned int b_whole,  unsigned int b_numer,  unsigned int b_denom,
	unsigned int &c_whole, unsigned int &c_numer, unsigned int &c_denom
	)
{
	c_whole = a_whole + b_whole;
	c_denom = a_denom * b_denom;
	c_numer = a_numer*b_denom + b_numer*a_denom;
	
	if (c_numer > c_denom) {
		c_numer -= c_denom;
		++c_whole;
	}
	
	simplify(c_numer, c_denom);
}

inline void
Rational::sub(
	bool a_pos,  unsigned int a_whole,  unsigned int a_numer,  unsigned int a_denom,
	bool b_pos,  unsigned int b_whole,  unsigned int b_numer,  unsigned int b_denom,
	bool &c_pos, unsigned int &c_whole, unsigned int &c_numer, unsigned int &c_denom
)
{
	add( a_pos, a_whole, a_numer, a_denom,
		!b_pos, b_whole, b_numer, b_denom,
		 c_pos, c_whole, c_numer, c_denom);
}

void
Rational::sub(
	unsigned int a_whole,  unsigned int a_numer,  unsigned int a_denom,
    unsigned int b_whole,  unsigned int b_numer,  unsigned int b_denom,
    unsigned int &c_whole, unsigned int &c_numer, unsigned int &c_denom
)
{
	c_denom = b_denom * a_denom;
	if (a_numer >= b_numer)
		c_numer = a_numer - b_numer;
	else
		c_numer = b_numer - a_numer;
	
	if (a_whole >= b_whole)
		c_whole = a_whole - b_whole;
	else
		c_whole = b_whole - a_whole;
	
	simplify(c_numer, c_denom);
}
	

void 
Rational::mult(
	bool a_pos,  unsigned int a_whole,  unsigned int a_numer,  unsigned int a_denom,
	bool b_pos,  unsigned int b_whole,  unsigned int b_numer,  unsigned int b_denom,
	bool &c_pos, unsigned int &c_whole, unsigned int &c_numer, unsigned int &c_denom
)
{
	// c := a*b
	c_pos = !(a_pos xor b_pos);
	c_whole = a_whole * b_whole;
	c_numer = b_whole*a_numer*b_denom + a_whole*b_numer*a_denom + a_numer*b_numer;
	c_denom = a_denom * b_denom;
	
	simplify(c_numer, c_denom);
}

void
Rational::div(
	bool a_pos,  unsigned int a_whole,  unsigned int a_numer,  unsigned int a_denom,
	bool b_pos,  unsigned int b_whole,  unsigned int b_numer,  unsigned int b_denom,
	bool &c_pos, unsigned int &c_whole, unsigned int &c_numer, unsigned int &c_denom
)
{
	// (whole + numer/denom)^-1 = denom/(whole*denom + numer)
	mult(a_pos, a_whole, a_numer, a_denom,
	     b_pos, 0, b_denom, b_whole*b_denom + b_numer,
		 c_pos, c_whole, c_numer, c_denom);
}

// This is the straightforward way to implement GCD: Euclid's algorithm.
// However, there's a more efficient way to do it, implemented after this
// (commented out) function, called the binary GCD algorithm.  We use that
// one instead.
/*unsigned int
Rational::gcd(unsigned int a, unsigned int b)
{
	unsigned int r;
	
	// Euclid's algorithm
	while (b != 0) {
         r = b;
         b = a % b;
         a = r;
	}
	
	return a;
}*/

// code taken from the Wikipedia article "Binary GCD algorithm"
// see: http://en.wikipedia.org/wiki/Binary_GCD_algorithm
unsigned int
Rational::gcd(unsigned int u, unsigned int v) {
	unsigned int k = 0;
	
	while ((u & 1) == 0  &&  (v & 1) == 0) { /* while both u and v are even */
		u >>= 1;   /* shift u right, dividing it by 2 */
		v >>= 1;   /* shift v right, dividing it by 2 */
		k++;       /* add a power of 2 to the final result */
	}
	
	/* At this point either u or v (or both) is odd */
	do {
		if ((u & 1) == 0)      /* if u is even */
			u >>= 1;           /* divide u by 2 */
		else if ((v & 1) == 0) /* else if v is even */
			v >>= 1;           /* divide v by 2 */
		else if (u >= v)       /* u and v are both odd */
			u = (u-v) >> 1;
		else                   /* u and v both odd, v > u */
			v = (v-u) >> 1;
	} while (u > 0);
	
	return v << k;  /* returns v * 2^k */
}

// Non-member functions
/*
ostream &
operator <<(ostream &out, Rational &r)
{
	if (!r.r_pos)
		out << "-";
	
	out << r.r_whole << " " << r.r_numer << "/" << r.r_denom;
	
	return out;
}*/
