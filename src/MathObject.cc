#include <stdexcept>
#include <typeinfo>

//#include "stdafx.h"

#include "MathObject.h"

#include "MathContainer.h"
#include "BinaryOperator.h"
#include "IllegalOperation.h"
#include "UndefException.h"
#include "Real.h"
#include "Integer.h"
#include "Trig.h"
#include "Exponential.h"
#include "Power.h"

#include "Negation.h"

#include "DoubleDispatch.h"
#include "BinaryOperations.h"

MathObject::MathObject() : m_defined(false), m_dim(-1)
{
}

MathObject::~MathObject()
{
}

int
MathObject::dim() const
{
	return m_dim;
}

void
MathObject::clear()
{
	m_defined = false;
}

MathObject *
MathObject::copy() const
{
	return new MathObject(*this);
}
	
bool
MathObject::is_defined() const
{
	return m_defined;
}

MathContainer
MathObject::add(const MathObject &mo) const throw (OPERATOR_PLUS_EXCEPTIONS)
{
	BinaryAdditionOp bo;
	return execute_dispatch(bo, mo);
}


MathContainer
MathObject::sub(const MathObject &mo) const throw (OPERATOR_MINUS_EXCEPTIONS)
{
	BinarySubtractionOp bo;
	return execute_dispatch(bo, mo);
}

MathContainer
MathObject::mult(const MathObject &mo) const throw (OPERATOR_TIMES_EXCEPTIONS)
{
	BinaryMultiplicationOp bo;
	return execute_dispatch(bo, mo);
}

MathContainer
MathObject::div(const MathObject &mo) const throw (OPERATOR_DIVIDE_EXCEPTIONS)
{
	BinaryDivisionOp bo;
	return execute_dispatch(bo, mo);
}

MathContainer
MathObject::negate() const throw ()
{
	return Negation(*this);
}

void
MathObject::addEq(const MathObject &mo) throw (OPERATOR_PLUS_EQ_EXCEPTIONS)
{
	throw IllegalOperation("+= on immutable MathObject");
}

void
MathObject::subEq(const MathObject &mo) throw (OPERATOR_MINUS_EQ_EXCEPTIONS)
{
	throw IllegalOperation("-= on immutable MathObject");
}

void
MathObject::multEq(const MathObject &mo) throw (OPERATOR_TIMES_EQ_EXCEPTIONS)
{
	throw IllegalOperation("*= on immutable MathObject");
}

void
MathObject::divEq(const MathObject &mo) throw (OPERATOR_DIVIDE_EQ_EXCEPTIONS)
{
	throw IllegalOperation("/= on immutable MathObject");
}
	
string
MathObject::to_string() const
{
	string result;
	if (m_defined)
		result = "Defined MathObject";
	else
		result = "Undefined MathObject";
	
	return result;
}

MathContainer
MathObject::simplify() const 
{
	return MathContainer(*this);
}

MathContainer &
MathObject::operator () (unsigned int i, unsigned int j) throw (IllegalOperation, out_of_range)
{
	/*if (i == 1 && j == 1)
	{
		return *this;
	}
	else
	{*/
		throw out_of_range("attempt to access index greater than 1 on 0-dimensional MathObject");
	//}
}

const MathContainer &
MathObject::operator () (unsigned int i, unsigned int j) const throw (IllegalOperation, out_of_range)
{
	/*if (i == 1 && j == 1)
	{
		return *this;
	}
	else 
	{*/
		throw out_of_range("attempt to access index greater than 1 on 0-dimensional MathObject");
	//}
}

MathContainer
MathObject::Sqrt() const throw ()
{
	Rational arg(1,2);
	return MathContainer(Power(*this, arg));
}

MathContainer
MathObject::Exp() const throw ()
{
	return MathContainer(Exponential(*this));
}

MathContainer
MathObject::Log() const throw ()
{
	return MathContainer(Logarithm(*this));
}

MathContainer
MathObject::Pow(const MathObject &mo) const
{
	return MathContainer(Power(*this, mo));
}

MathContainer
MathObject::Pow(int i) const
{
	Integer arg(i);
	return MathContainer(Power(*this, arg));
}

MathContainer
MathObject::Pow(double d) const
{
	Real arg(d);
	return MathContainer(Power(*this, arg));
}

MathContainer
MathObject::LogBase(const MathObject &mo) const
{
	return MathContainer(LogarithmBase(*this, mo));
}

MathContainer
MathObject::LogBase(int i) const
{
	Integer arg(i);
	return MathContainer(LogarithmBase(*this, arg));
}

MathContainer
MathObject::LogBase(double d) const
{
	Real arg(d);
	return MathContainer(LogarithmBase(*this, arg));
}


MathContainer
MathObject::Sin() const throw ()
{
	return MathContainer(Sine(*this));
}


MathContainer
MathObject::Cos() const throw ()
{
	return MathContainer(Cosine(*this));
}

MathContainer
MathObject::Tan() const throw ()
{
	return MathContainer(Tangent(*this));
}

MathContainer
MathObject::Sinh() const throw ()
{
	return MathContainer(HypSine(*this));
}

MathContainer
MathObject::Cosh() const throw ()
{
	return MathContainer(HypCosine(*this));
}

MathContainer
MathObject::Tanh() const throw ()
{
	return MathContainer(HypTangent(*this));
}

MathContainer
MathObject::ArcSin() const throw (invalid_argument)
{
	return MathContainer(ArcSine(*this));
}

MathContainer
MathObject::ArcCos() const throw (invalid_argument)
{
	return MathContainer(ArcCosine(*this));
}

MathContainer
MathObject::ArcTan() const throw (invalid_argument)
{
	return MathContainer(ArcTangent(*this));
}

MathContainer
MathObject::ArcSinh() const throw (invalid_argument)
{
	return MathContainer(ArcHypSine(*this));
}

MathContainer
MathObject::ArcCosh() const throw (invalid_argument)
{
	return MathContainer(ArcHypCosine(*this));
}

MathContainer
MathObject::ArcTanh() const throw (invalid_argument)
{
	return MathContainer(ArcHypTangent(*this));
}

MathObject &
MathObject::operator = (const MathObject &mo) throw (OPERATOR_EQUALS_EXCEPTIONS)
{
	//const MathObject &param = get_inner_object(mo);
	set_equal(mo);
	return *this;
}

MathObject &
MathObject::operator = (const MathContainer &v) throw (OPERATOR_EQUALS_EXCEPTIONS)
{
	set_equal(v.var()); //(MathObject&)v;
	return *this;
}

MathObject &
MathObject::operator = (int param) throw (OPERATOR_EQUALS_EXCEPTIONS)
{
	Integer i(param);
	set_equal(i);
	return *this;
}

MathObject &
MathObject::operator = (double param) throw (OPERATOR_EQUALS_EXCEPTIONS)
{
	Real fp(param);
	set_equal(fp);
	return *this;
}

bool
MathObject::operator == (const MathObject &mo) const throw (OPERATOR_ISEQUAL_EXCEPTIONS)
{
	//const MathObject &param = get_inner_object(mo);
	return is_equal(mo);
}

bool
MathObject::operator == (const MathContainer &mc) const throw (OPERATOR_ISEQUAL_EXCEPTIONS)
{
	return is_equal(mc.var());
}

bool
MathObject::operator == (double d) const throw (OPERATOR_ISEQUAL_EXCEPTIONS)
{
	Real fp(d);
	return (*this == fp);
}

bool
MathObject::operator == (int i) const throw (OPERATOR_ISEQUAL_EXCEPTIONS)
{
	Integer intg(i);
	return (*this == intg);
}

bool
MathObject::is_equal(const MathObject &mo) const throw (OPERATOR_ISEQUAL_EXCEPTIONS)
{
	if (!m_defined && !mo.m_defined)
		return true;
	else
		return (m_dim == mo.m_dim);
}


void
MathObject::set_equal(const MathObject &mo) throw (OPERATOR_EQUALS_EXCEPTIONS)
{
	m_defined = mo.is_defined();
	m_dim = mo.m_dim;
}

MathContainer
MathObject::operator + (const MathObject &mo) const throw (OPERATOR_PLUS_EXCEPTIONS)
{
	if (!mo.is_defined() || !m_defined)
		throw UndefException("operator+ on undefined MathObject");
	
	//const MathObject &param = get_inner_object(mo);
	return add(mo);
}
	
MathContainer
MathObject::operator - (const MathObject &mo) const throw (OPERATOR_MINUS_EXCEPTIONS)
{
	if (!mo.is_defined() || !m_defined)
		throw UndefException("operator- on undefined MathObject");
	
	//const MathObject &param = get_inner_object(mo);
	return sub(mo);
}

MathContainer
MathObject::operator * (const MathObject &mo) const throw (OPERATOR_TIMES_EXCEPTIONS)
{
	if (!mo.is_defined() || !m_defined)
		throw UndefException("operator* on undefined MathObject");
	
	//const MathObject &param = get_inner_object(mo);
	return mult(mo);
}


MathContainer
MathObject::operator / (const MathObject &mo) const throw (OPERATOR_DIVIDE_EXCEPTIONS)
{
	if (!mo.is_defined() || !m_defined)
		throw UndefException("operator/ on undefined MathObject");
	
	//const MathObject &param = get_inner_object(mo);
	return div(mo);
}

MathContainer
MathObject::operator+(const MathContainer &mc) const throw (OPERATOR_PLUS_EXCEPTIONS)
{
	return (*this + mc.var());
}

MathContainer
MathObject::operator-(const MathContainer &mc) const throw (OPERATOR_MINUS_EXCEPTIONS)
{
	return (*this - mc.var());
}

MathContainer
MathObject::operator*(const MathContainer &mc) const throw (OPERATOR_TIMES_EXCEPTIONS)
{
	return (*this * mc.var());
}

MathContainer
MathObject::operator/(const MathContainer &mc) const throw (OPERATOR_DIVIDE_EXCEPTIONS)
{
	return (*this / mc.var());
}

MathContainer
MathObject::operator + (int param) const throw (OPERATOR_PLUS_EXCEPTIONS)
{
	if (!m_defined)
		throw UndefException("operator+ on undefined MathObject");
	
	Integer i(param);
	return add(i);
}

MathContainer
MathObject::operator - (int param) const throw (OPERATOR_MINUS_EXCEPTIONS)
{
	if (!m_defined)
		throw UndefException("operator- on undefined MathObject");
	
	Integer i(param);
	return sub(i);
}

MathContainer
MathObject::operator * (int param) const throw (OPERATOR_TIMES_EXCEPTIONS)
{
	if (!m_defined)
		throw UndefException("operator* on undefined MathObject");
	
	Integer i(param);
	return mult(i);
}

MathContainer
MathObject::operator / (int param) const throw (OPERATOR_DIVIDE_EXCEPTIONS)
{
	if (!m_defined)
		throw UndefException("operator/ on undefined MathObject");
	
	Integer i(param);
	return div(i);
}

MathContainer
MathObject::operator + (double param) const throw (OPERATOR_PLUS_EXCEPTIONS)
{
	if (!m_defined)
		throw UndefException("operator+ on undefined MathObject");
	
	Real fp(param);
	return add(fp);
}

MathContainer
MathObject::operator - (double param) const throw (OPERATOR_MINUS_EXCEPTIONS)
{
	if (!m_defined)
		throw UndefException("operator- on undefined MathObject");
	
	Real fp(param);
	return sub(fp);
}

MathContainer
MathObject::operator * (double param) const throw (OPERATOR_TIMES_EXCEPTIONS)
{
	if (!m_defined)
		throw UndefException("operator* on undefined MathObject");
	
	Real fp(param);
	return mult(fp);
}

MathContainer
MathObject::operator / (double param) const throw (OPERATOR_DIVIDE_EXCEPTIONS)
{
	if (!m_defined)
		throw UndefException("operator/ on undefined MathObject");
	
	Real fp(param);
	return div(fp);
}

MathContainer
MathObject::operator - () const throw ()
{
	return negate();
}

MathObject &
MathObject::operator += (const MathObject &mo) throw (OPERATOR_PLUS_EQ_EXCEPTIONS)
{
	if (!mo.is_defined() || !m_defined)
		throw UndefException("operator+= on undefined MathObject");
	
	//const MathObject &param = get_inner_object(mo);
	addEq(mo);
	return *this;
}

MathObject &
MathObject::operator -= (const MathObject &mo) throw (OPERATOR_MINUS_EQ_EXCEPTIONS)
{
	if (!mo.is_defined() || !m_defined)
		throw UndefException("operator-= on undefined MathObject");
	
	//const MathObject &param = get_inner_object(mo);
	subEq(mo);
	return *this;
}

MathObject &
MathObject::operator *= (const MathObject &mo) throw (OPERATOR_TIMES_EQ_EXCEPTIONS)
{
	if (!mo.is_defined() || !m_defined)
		throw UndefException("operator*= on undefined MathObject");
	
	//const MathObject &param = get_inner_object(mo);
	multEq(mo);
	return *this;
}

MathObject &
MathObject::operator /= (const MathObject &mo) throw (OPERATOR_DIVIDE_EQ_EXCEPTIONS)
{
	if (!mo.is_defined() || !m_defined)
		throw UndefException("operator/= on undefined MathObject");
	
	//const MathObject &param = get_inner_object(mo);
	divEq(mo);
	return *this;
}

MathObject &
MathObject::operator += (const MathContainer &mc) throw (OPERATOR_PLUS_EQ_EXCEPTIONS)
{
	return (*this += mc.var());
}

MathObject &
MathObject::operator -= (const MathContainer &mc) throw (OPERATOR_MINUS_EQ_EXCEPTIONS)
{
	return (*this -= mc.var());
}

MathObject &
MathObject::operator *= (const MathContainer &mc) throw (OPERATOR_TIMES_EQ_EXCEPTIONS)
{
	return (*this *= mc.var());
}

MathObject &
MathObject::operator /= (const MathContainer &mc) throw (OPERATOR_DIVIDE_EQ_EXCEPTIONS)
{
	return (*this /= mc.var());
}

MathObject &
MathObject::operator += (int param) throw (OPERATOR_PLUS_EQ_EXCEPTIONS)
{
	if (!m_defined)
		throw UndefException("operator+= on undefined MathObject");
	
	Integer i(param);
	addEq(i);
	return *this;
}

MathObject &
MathObject::operator -= (int param) throw (OPERATOR_MINUS_EQ_EXCEPTIONS)
{
	if (!m_defined)
		throw UndefException("operator-= on undefined MathObject");
	
	Integer i(param);
	subEq(i);
	return *this;
}

MathObject &
MathObject::operator *= (int param) throw (OPERATOR_TIMES_EQ_EXCEPTIONS)
{
	if (!m_defined)
		throw UndefException("operator*= on undefined MathObject");
	
	Integer i(param);
	multEq(i);
	return *this;
}

MathObject &
MathObject::operator /= (int param) throw (OPERATOR_DIVIDE_EQ_EXCEPTIONS)
{
	if (!m_defined)
		throw UndefException("operator/= on undefined MathObject");
	
	Integer i(param);
	divEq(i);
	return *this;
}
            
MathObject &
MathObject::operator += (double param) throw (OPERATOR_PLUS_EQ_EXCEPTIONS)
{
	if (!m_defined)
		throw UndefException("operator+= on undefined MathObject");
	
	Real fp(param);
	addEq(fp);
	return *this;
}

MathObject &
MathObject::operator -= (double param) throw (OPERATOR_MINUS_EQ_EXCEPTIONS)
{
	if (!m_defined)
		throw UndefException("operator-= on undefined MathObject");
	
	Real fp(param);
	subEq(fp);
	return *this;
}

MathObject &
MathObject::operator *= (double param) throw (OPERATOR_TIMES_EQ_EXCEPTIONS)
{
	if (!m_defined)
		throw UndefException("operator*= on undefined MathObject");
	
	Real fp(param);
	multEq(fp);
	return *this;
}

MathObject &
MathObject::operator /= (double param) throw (OPERATOR_DIVIDE_EQ_EXCEPTIONS)
{
	if (!m_defined)
		throw UndefException("operator/= on undefined MathObject");
	
	Real fp(param);
	divEq(fp);
	return *this;
}


ostream& operator << (ostream &out, const MathObject &o)
{
	o.write_to_stream(out);
	return out;
}

void
MathObject::write_to_stream(ostream &out) const
{
	out << to_string();
}

// non-member functions

MathContainer
operator + (int param, const MathObject &mo) throw (OPERATOR_PLUS_EXCEPTIONS)
{
	if (!mo.is_defined())
		throw UndefException("operator+ on undefined MathObject");
	
	Integer i(param);
	return i.operator+(mo);
}

MathContainer
operator - (int param, const MathObject &mo) throw (OPERATOR_MINUS_EXCEPTIONS)
{
	if (!mo.is_defined())
		throw UndefException("operator+ on undefined MathObject");
	
	Integer i(param);
	return i - mo;
}

MathContainer
operator * (int param, const MathObject &mo) throw (OPERATOR_TIMES_EXCEPTIONS)
{
	if (!mo.is_defined())
		throw UndefException("operator+ on undefined MathObject");
	
	Integer i(param);
	return i * mo;
}

MathContainer
operator / (int param, const MathObject &mo) throw (OPERATOR_DIVIDE_EXCEPTIONS)
{
	if (!mo.is_defined())
		throw UndefException("operator+ on undefined MathObject");
	
	Integer i(param);
	return i / mo;
}

         
MathContainer
operator + (double param, const MathObject &mo) throw (OPERATOR_PLUS_EXCEPTIONS)
{
	if (!mo.is_defined())
		throw UndefException("operator+ on undefined MathObject");
	
	Real fp(param);
	return fp + mo;
}

MathContainer
operator - (double param, const MathObject &mo) throw (OPERATOR_MINUS_EXCEPTIONS)
{
	if (!mo.is_defined())
		throw UndefException("operator+ on undefined MathObject");
	
	Real fp(param);
	return fp - mo;
}

MathContainer
operator * (double param, const MathObject &mo) throw (OPERATOR_TIMES_EXCEPTIONS)
{
	if (!mo.is_defined())
		throw UndefException("operator+ on undefined MathObject");
	
	Real fp(param);
	return fp * mo;
}

MathContainer
operator / (double param, const MathObject &mo) throw (OPERATOR_DIVIDE_EXCEPTIONS)
{
	if (!mo.is_defined())
		throw UndefException("operator+ on undefined MathObject");
	
	Real fp(param);
	return fp / mo;
}

// private methods

MathContainer
MathObject::execute_dispatch(const BinaryOperation &bo, const MathObject &mo) const
	throw (invalid_argument, IllegalOperation, InternalError)
{
	ExtMathContainer ext;
	MathObject *value;
	BinaryDispatcher dispatch(bo);
	
	ext = mo.visit(dispatch, *this);
	value = ext.var();
	
	MathContainer result(*value);
	delete value;
	
	return result;
}

const MathObject &
MathObject::get_inner_object(const MathObject &mo)
{
	const MathObject *mo_ptr;
	
	mo_ptr = &mo;
	while (typeid(*mo_ptr) == typeid(MathContainer))
	{
		const MathContainer &v = static_cast <const MathContainer &> (mo);
		mo_ptr = &(v.var());
	}
	
	return *mo_ptr;
}
