#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdexcept>
#include <iostream>
#include <string>

#include "UndefException.h"
#include "MathObject.h"
#include "MathContainer.h"
#include "Real.h"

class Complex : public MathObject {

public:
	
	Complex(double real, double imag) throw () : MathObject(true, 0), c_real(Real(real)), c_imag(Real(imag)) {}
	Complex(const MathContainer &real, const MathContainer &imag) throw () : MathObject(true, 0), c_real(real), c_imag(imag) {}
	Complex() throw () : MathObject(false, 0), c_real(), c_imag() {}
	
	OVERRIDE_DEFAULT_COPY_OP(Complex)
	DEFAULT_COPY_IMPL(Complex)
	DEF_BINARY_OP_VISIT(Complex)
	CLASS_STRING(Complex)

	const MathObject& get_real() const throw (UndefException);
	const MathObject& get_imag() const throw (UndefException);
	
	void set_real(const MathObject &) throw ();
	void set_real(double) throw ();
	void set_imag(const MathObject &) throw ();
	void set_imag(double) throw ();
	
	MathContainer magnitude2() const throw (UndefException);
	MathContainer magnitude()  const throw (UndefException);
	
	Complex conjugate() const throw (UndefException);
	MathContainer arg() const throw (UndefException);

	virtual string to_string() const throw ();
	
protected:
	
	SETEQUAL_MATHOBJ_IMPL(Complex)
	virtual void set_equal(const Complex &co) throw ();
	
private:
	
	MathContainer c_real, c_imag;

};

#endif /* COMPLEX_H */
