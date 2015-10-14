#ifndef MATH_OBJECT
#define MATH_OBJECT

// don't warn about exception specifications in VC++
#ifdef _MSC_VER
#  pragma warning( disable : 4290 )
#endif // _MSC_VER

#define DEBUG

#include <iostream>
#include <sstream>
#include <string>

#include "IllegalOperation.h"
#include "UndefException.h"
#include "DivideByZero.h"
#include "AllClasses.h"

//ALL_FORWARD_DECLS()

#include "DoubleDispatch.h"

// C++ defines a default copy operator (type& operator=(const type&)) that sets the members
// of *this equal to the passed in argument.  This overwrites the copy operator we want that
// does a double dispatch, so we need a "using" declaration.  We also define our own default
// copy op that returns the correct return type.
#define OVERRIDE_DEFAULT_COPY_OP(type)	\
	using MathObject::operator=;	\
	virtual type& operator= (const type &t) throw (OPERATOR_EQUALS_EXCEPTIONS)	\
	{ set_equal(t);  return *this; }	// correct return type

// this->copy() returns of a newly allocated copy of *this.  Should be able to use this definition
// as long as the copy constructor is implemented correctly (which it better be...)
#define DEFAULT_COPY_IMPL(type)	\
	virtual type* copy() const { return new type(*this); }

// In most all cases, setting equal to a MathObject of unknown type should do as follows here:
// check to see if it's of the same type of this, and if so, cast it and send it along to the
// right function; otherwise, throw an exception.  An implementation of set_equal(const type&)
// better exist or this will infinitely recurse...
#define SETEQUAL_MATHOBJ_IMPL(type) \
	void set_equal(const MathObject &param) throw (invalid_argument) { \
		const type *ptr;	\
		if (ptr = dynamic_cast<const type*> (&param)) set_equal(*ptr);	\
		else {	\
			ostringstream err;	\
			err << "attempt to set " #type " equal to object of type " << typeid(param).name();	\
			throw invalid_argument(err.str());	\
		}	\
	}

// Return the name of whatever class *this is an instance of.  Useful for debugging when RTTI
// isn't available.
#define CLASS_STRING(type)	\
	virtual const char* class_string() const { return #type; }


// For more default #defined functions that appear in many classes, see DoubleDispatch.h


// Define some default exception declarations for the various operators.  TODO: Do we really
// even care enough about declaring thrown exceptions?
#define DEFAULT_OPERATOR_EXCEPTIONS	invalid_argument, UndefException, IllegalOperation, InternalError

#define OPERATOR_PLUS_EXCEPTIONS	DEFAULT_OPERATOR_EXCEPTIONS
#define OPERATOR_MINUS_EXCEPTIONS	DEFAULT_OPERATOR_EXCEPTIONS
#define OPERATOR_TIMES_EXCEPTIONS	DEFAULT_OPERATOR_EXCEPTIONS
#define OPERATOR_DIVIDE_EXCEPTIONS	DEFAULT_OPERATOR_EXCEPTIONS, DivideByZero

#define OPERATOR_EQUALS_EXCEPTIONS	invalid_argument, IllegalOperation
#define OPERATOR_ISEQUAL_EXCEPTIONS

#define DEFAULT_OPERATOR_EQ_EXCEPTIONS	DEFAULT_OPERATOR_EXCEPTIONS
#define OPERATOR_PLUS_EQ_EXCEPTIONS		DEFAULT_OPERATOR_EXCEPTIONS
#define OPERATOR_MINUS_EQ_EXCEPTIONS	DEFAULT_OPERATOR_EXCEPTIONS
#define OPERATOR_TIMES_EQ_EXCEPTIONS	DEFAULT_OPERATOR_EXCEPTIONS
#define OPERATOR_DIVIDE_EQ_EXCEPTIONS	DEFAULT_OPERATOR_EXCEPTIONS, DivideByZero
	
class MathContainer;

class MathObject {
	friend ostream& operator << (ostream &out, const MathObject &o);

	public:
	
	MathObject();
	virtual ~MathObject();
	
	// MathObject, being the base class, will be the class type "determined" for all
	// derived classes that don't implement double dispatching.  The result will be
	// that the Operator type representing the operator used will be returned, e.g.,
	// while "Integer(12) + Real(3.5)" will return Real(15.5), executing
	// "Variable("x") + Variable("y")" will return Addition(x, y), since the Variable
	// class does not explicity support double dispatch.
	DEF_BINARY_OP_VISIT(MathObject)

	// Defines the function 'const char* class_string() const' which returns the name
	// of this class... as a string.  You should include this in all derived types,
	// and this macro should be sufficient unless you want to include extra data
	// (e.g., a Matrix class may want to return "Matrix(3,4)" to show it's a 3x4 Matrix).
	// Note that this is not a static function, and may incorporate instance-specific
	// data
	CLASS_STRING(MathObject)

	// Though now used here, all non-abstract derived types should include the macro
	// OVERRIDE_DEFAULT_COPY_OP(typename).  This will assure that the assignment operator,
	// when used on MathContainer or generic MathObject instances, will do the right
	// thing.  All non-abstract types should also provide a copy() function, which in general
	// can be implemented through DEFAULT_COPY_IMPL(typename).  See below for more
	// functions that should (almost) always be over-rided.
	
	// The number of dimensions this MathObject has.  Numeric types such as Real are
	// 0-dimensional; Vectors 1-dimensional; Matrices 2-dimensional.  Undefined
	// MathObjects return dimension -1.
	int dim() const;
	// Since most MathObject work is done by reference (rather than by dynamically
	// allocated memory), it is often necessary to define a MathObject that isn't...
	// well, defined.  This, along with the dimension, can be set in the protected
	// constructor below
	bool is_defined() const;
	
	virtual void clear();
	virtual MathObject* copy() const;
	virtual string to_string() const;

	virtual int precedence() const { return 0; }
	virtual MathContainer simplify() const;

	virtual MathContainer& operator () (unsigned int i = 1, unsigned int j = 1)
		throw (out_of_range, IllegalOperation);
	virtual const MathContainer& operator () (unsigned int i = 1, unsigned int j = 1) const
		throw (out_of_range, IllegalOperation);

	// function names are capitalized to avoid collision with pre-defined functions
	virtual MathContainer Sqrt() const throw ();
	virtual MathContainer Exp() const throw ();
	virtual MathContainer Log() const throw ();

	virtual MathContainer Pow(const MathObject &) const;
	virtual MathContainer Pow(int) const;
	virtual MathContainer Pow(double) const;

	virtual MathContainer LogBase(const MathObject &) const;
	virtual MathContainer LogBase(int) const;
	virtual MathContainer LogBase(double) const;

	virtual MathContainer Sin() const throw ();
	virtual MathContainer Cos() const throw ();
	virtual MathContainer Tan() const throw ();

	virtual MathContainer Sinh() const throw ();
	virtual MathContainer Cosh() const throw ();
	virtual MathContainer Tanh() const throw ();

	virtual MathContainer ArcSin() const throw (invalid_argument);
	virtual MathContainer ArcCos() const throw (invalid_argument);
	virtual MathContainer ArcTan() const throw (invalid_argument);

	virtual MathContainer ArcSinh() const throw (invalid_argument);
	virtual MathContainer ArcCosh() const throw (invalid_argument);
	virtual MathContainer ArcTanh() const throw (invalid_argument);

	virtual MathObject& operator = (const MathObject &) throw (OPERATOR_EQUALS_EXCEPTIONS);
	virtual MathObject& operator = (const MathContainer &) throw (OPERATOR_EQUALS_EXCEPTIONS);
	virtual MathObject& operator = (int) throw (OPERATOR_EQUALS_EXCEPTIONS);
	virtual MathObject& operator = (double) throw (OPERATOR_EQUALS_EXCEPTIONS);
	
	virtual bool operator == (const MathObject &) const throw (OPERATOR_ISEQUAL_EXCEPTIONS);
	virtual bool operator == (const MathContainer &) const throw (OPERATOR_ISEQUAL_EXCEPTIONS);
	virtual bool operator == (int) const throw (OPERATOR_ISEQUAL_EXCEPTIONS);
	virtual bool operator == (double) const throw (OPERATOR_ISEQUAL_EXCEPTIONS);

	template <class T1>
	bool operator != (T1 obj) const throw (OPERATOR_ISEQUAL_EXCEPTIONS)
	{	return !(*this == obj); }
	
	virtual MathContainer operator + (const MathObject &) const throw (OPERATOR_PLUS_EXCEPTIONS);
	virtual MathContainer operator - (const MathObject &) const throw (OPERATOR_MINUS_EXCEPTIONS);
	virtual MathContainer operator * (const MathObject &) const throw (OPERATOR_TIMES_EXCEPTIONS);
	virtual MathContainer operator / (const MathObject &) const throw (OPERATOR_DIVIDE_EXCEPTIONS);

	virtual MathContainer operator + (const MathContainer &) const throw (OPERATOR_PLUS_EXCEPTIONS);
	virtual MathContainer operator - (const MathContainer &) const throw (OPERATOR_MINUS_EXCEPTIONS);
	virtual MathContainer operator * (const MathContainer &) const throw (OPERATOR_TIMES_EXCEPTIONS);
	virtual MathContainer operator / (const MathContainer &) const throw (OPERATOR_DIVIDE_EXCEPTIONS);
	
	virtual MathContainer operator + (int) const throw (OPERATOR_PLUS_EXCEPTIONS);
	virtual MathContainer operator - (int) const throw (OPERATOR_MINUS_EXCEPTIONS);
	virtual MathContainer operator * (int) const throw (OPERATOR_TIMES_EXCEPTIONS);
	virtual MathContainer operator / (int) const throw (OPERATOR_DIVIDE_EXCEPTIONS);
	
	virtual MathContainer operator + (double) const throw (OPERATOR_PLUS_EXCEPTIONS);
	virtual MathContainer operator - (double) const throw (OPERATOR_MINUS_EXCEPTIONS);
	virtual MathContainer operator * (double) const throw (OPERATOR_TIMES_EXCEPTIONS);
	virtual MathContainer operator / (double) const throw (OPERATOR_DIVIDE_EXCEPTIONS);

	virtual MathContainer operator - () const throw ();

	virtual MathObject& operator += (const MathObject &) throw (OPERATOR_PLUS_EQ_EXCEPTIONS);
	virtual MathObject& operator -= (const MathObject &) throw (OPERATOR_MINUS_EQ_EXCEPTIONS);
	virtual MathObject& operator *= (const MathObject &) throw (OPERATOR_TIMES_EQ_EXCEPTIONS);
	virtual MathObject& operator /= (const MathObject &) throw (OPERATOR_DIVIDE_EQ_EXCEPTIONS);
	
	virtual MathObject& operator += (const MathContainer &) throw (OPERATOR_PLUS_EQ_EXCEPTIONS);
	virtual MathObject& operator -= (const MathContainer &) throw (OPERATOR_MINUS_EQ_EXCEPTIONS);
	virtual MathObject& operator *= (const MathContainer &) throw (OPERATOR_TIMES_EQ_EXCEPTIONS);
	virtual MathObject& operator /= (const MathContainer &) throw (OPERATOR_DIVIDE_EQ_EXCEPTIONS);
	
	virtual MathObject& operator += (double) throw (OPERATOR_PLUS_EQ_EXCEPTIONS);
	virtual MathObject& operator -= (double) throw (OPERATOR_MINUS_EQ_EXCEPTIONS);
	virtual MathObject& operator *= (double) throw (OPERATOR_TIMES_EQ_EXCEPTIONS);
	virtual MathObject& operator /= (double) throw (OPERATOR_DIVIDE_EQ_EXCEPTIONS);
	
	virtual MathObject& operator += (int) throw (OPERATOR_PLUS_EQ_EXCEPTIONS);
	virtual MathObject& operator -= (int) throw (OPERATOR_MINUS_EQ_EXCEPTIONS);
	virtual MathObject& operator *= (int) throw (OPERATOR_TIMES_EQ_EXCEPTIONS);
	virtual MathObject& operator /= (int) throw (OPERATOR_DIVIDE_EQ_EXCEPTIONS);

	protected:
	
	MathObject(bool def, int dim) : m_defined(def), m_dim(dim) {}
	virtual void write_to_stream(ostream &) const;
	
	virtual MathContainer  add(const MathObject &) const throw (OPERATOR_PLUS_EXCEPTIONS);
	virtual MathContainer  sub(const MathObject &) const throw (OPERATOR_MINUS_EXCEPTIONS);
 	virtual MathContainer mult(const MathObject &) const throw (OPERATOR_TIMES_EXCEPTIONS);
	virtual MathContainer  div(const MathObject &) const throw (OPERATOR_DIVIDE_EXCEPTIONS);

	virtual MathContainer negate() const throw ();
	
	virtual void  addEq(const MathObject &) throw (OPERATOR_PLUS_EQ_EXCEPTIONS);
	virtual void  subEq(const MathObject &) throw (OPERATOR_MINUS_EQ_EXCEPTIONS);
 	virtual void multEq(const MathObject &) throw (OPERATOR_TIMES_EQ_EXCEPTIONS);
	virtual void  divEq(const MathObject &) throw (OPERATOR_DIVIDE_EQ_EXCEPTIONS);
	
	virtual bool  is_equal(const MathObject &) const throw ();
	virtual void set_equal(const MathObject &) throw (OPERATOR_EQUALS_EXCEPTIONS);
	
	bool m_defined;
	int m_dim;
	
	private:
	
	MathContainer execute_dispatch(const BinaryOperation &bo, const MathObject &mo) const throw (invalid_argument, IllegalOperation, InternalError);
	static const MathObject & get_inner_object(const MathObject &);
};

MathContainer operator + (int, const MathObject &) throw (OPERATOR_PLUS_EXCEPTIONS);
MathContainer operator - (int, const MathObject &) throw (OPERATOR_MINUS_EXCEPTIONS);
MathContainer operator * (int, const MathObject &) throw (OPERATOR_TIMES_EXCEPTIONS);
MathContainer operator / (int, const MathObject &) throw (OPERATOR_DIVIDE_EXCEPTIONS);

MathContainer operator + (double, const MathObject &) throw (OPERATOR_PLUS_EXCEPTIONS);
MathContainer operator - (double, const MathObject &) throw (OPERATOR_MINUS_EXCEPTIONS);
MathContainer operator * (double, const MathObject &) throw (OPERATOR_TIMES_EXCEPTIONS);
MathContainer operator / (double, const MathObject &) throw (OPERATOR_DIVIDE_EXCEPTIONS);


namespace Math {
	const MathObject UndefMathObject;
}

#endif /* MATH_OBJECT */
