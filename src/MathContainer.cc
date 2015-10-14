#include <iostream>

#include "MathContainer.h"
#include "Integer.h"
#include "Real.h"
#include "Test.h"

ostream& operator << (ostream &out, const MathContainer &v)
{
	out << v.to_string();
	return out;
}

MathContainer::MathContainer(int i)
	: v_var(new Integer(i))
{
}

MathContainer::MathContainer(double d)
	: v_var(new Real(d))
{
}

MathContainer::~MathContainer()
{
	delete v_var;
}

MathObject *
MathContainer::copy() const
{
	return v_var->copy();
}

string
MathContainer::to_string() const
{
	return v_var->to_string();
}

MathObject &
MathContainer::var()
{
	return *v_var;
}

const MathObject &
MathContainer::var() const
{
	return *v_var;
}

MathContainer::operator MathObject& () const
{
	return *v_var;
}

MathContainer &
MathContainer::operator () (unsigned int i, unsigned int j) throw (IllegalOperation)
{
	return (*v_var)(i, j);
}

const MathContainer &
MathContainer::operator () (unsigned int i, unsigned int j) const throw (IllegalOperation)
{
	return (*v_var)(i, j);
}

MathContainer
MathContainer::simplify() const
{
	return v_var->simplify();
}

MathContainer
MathContainer::Sqrt() const throw ()
{
	return v_var->Sqrt();
}

MathContainer
MathContainer::Exp() const throw ()
{
	return v_var->Exp();
}

MathContainer
MathContainer::Log() const throw ()
{
	return v_var->Log();
}

MathContainer
MathContainer::Pow(const MathObject &mo) const
{
	return v_var->Pow(mo);
}

MathContainer
MathContainer::Pow(int i) const
{
	return v_var->Pow(i);
}

MathContainer
MathContainer::Pow(double d) const
{
	return v_var->Pow(d);
}

MathContainer
MathContainer::LogBase(const MathObject &mo) const
{
	return v_var->LogBase(mo);
}

MathContainer
MathContainer::LogBase(int i) const
{
	return v_var->LogBase(i);
}

MathContainer
MathContainer::LogBase(double d) const
{
	return v_var->Pow(d);
}


MathContainer
MathContainer::Sin() const throw ()
{
	return v_var->Sin();
}


MathContainer
MathContainer::Cos() const throw ()
{
	return v_var->Cos();
}

MathContainer
MathContainer::Tan() const throw ()
{
	return v_var->Tan();
}

MathContainer
MathContainer::Sinh() const throw ()
{
	return v_var->Sinh();
}

MathContainer
MathContainer::Cosh() const throw ()
{
	return v_var->Cosh();
}

MathContainer
MathContainer::Tanh() const throw ()
{
	return v_var->Tanh();
}

MathContainer
MathContainer::ArcSin() const throw (invalid_argument)
{
	return v_var->ArcSin();
}

MathContainer
MathContainer::ArcCos() const throw (invalid_argument)
{
	return v_var->ArcCos();
}

MathContainer
MathContainer::ArcTan() const throw (invalid_argument)
{
	return v_var->ArcTan();
}

MathContainer
MathContainer::ArcSinh() const throw (invalid_argument)
{
	return v_var->ArcSinh();
}

MathContainer
MathContainer::ArcCosh() const throw (invalid_argument)
{
	return v_var->ArcCosh();
}

MathContainer
MathContainer::ArcTanh() const throw (invalid_argument)
{
	return v_var->ArcTanh();
}

MathObject &
MathContainer::operator=(const MathObject &mo) throw ()
{
	delete v_var;
	
	v_var =  mo.copy();
	
	return *v_var;
}

MathObject &
MathContainer::operator=(const MathContainer &v) throw ()
{
	delete v_var;
	
	v_var = v.v_var->copy();
	
	return *v_var;
}

MathObject &
MathContainer::operator = (int param) throw (OPERATOR_EQUALS_EXCEPTIONS)
{
	delete v_var;
	v_var = new Integer(param);
	return *v_var;
}

MathObject &
MathContainer::operator = (double param) throw (OPERATOR_EQUALS_EXCEPTIONS)
{
	delete v_var;
	v_var = new Real(param);
	return *v_var;
}
	
bool
MathContainer::operator == (const MathObject &mo) const throw (OPERATOR_ISEQUAL_EXCEPTIONS)
{
	return (*v_var == mo);
}

bool
MathContainer::operator == (int param) const throw (OPERATOR_ISEQUAL_EXCEPTIONS)
{
	return (*v_var == Integer(param));
}

bool
MathContainer::operator == (double param) const throw (OPERATOR_ISEQUAL_EXCEPTIONS)
{
	return (*v_var == Real(param));
}


MathContainer
MathContainer::operator+(const MathObject &mo) const throw (OPERATOR_PLUS_EXCEPTIONS)
{
	MathContainer result;
	
	result = *v_var + mo;
	
	return result;
}

MathContainer
MathContainer::operator-(const MathObject &mo) const throw (OPERATOR_MINUS_EXCEPTIONS)
{
	MathContainer result;
	
	result = *v_var - mo;
	
	return result;
}

MathContainer
MathContainer::operator*(const MathObject &mo) const throw (OPERATOR_TIMES_EXCEPTIONS)
{
	MathContainer result;
	
	result = *v_var * mo;
	
	return result;
}

MathContainer
MathContainer::operator/(const MathObject &mo) const throw (OPERATOR_DIVIDE_EXCEPTIONS)
{
	MathContainer result;
	
	result = *v_var / mo;
	
	return result;
}


MathContainer
MathContainer::operator+(const MathContainer &v) const throw (OPERATOR_PLUS_EXCEPTIONS)
{
	MathContainer result;
	
	result = *v_var + *v.v_var;
	
	return result;
}

MathContainer
MathContainer::operator-(const MathContainer &v) const throw (OPERATOR_MINUS_EXCEPTIONS)
{
	MathContainer result;
	
	result = *v_var - *v.v_var;
	
	return result;
}

MathContainer
MathContainer::operator*(const MathContainer &v) const throw (OPERATOR_TIMES_EXCEPTIONS)
{
	MathContainer result;
	
	result = *v_var * *v.v_var;
	
	return result;
}

MathContainer
MathContainer::operator/(const MathContainer &v) const throw (OPERATOR_DIVIDE_EXCEPTIONS)
{
	MathContainer result;
	
	result = *v_var / *v.v_var;
	
	return result;
}

MathContainer
MathContainer::operator + (int param) const throw (OPERATOR_PLUS_EXCEPTIONS)
{
	return (*v_var + Integer(param));
}

MathContainer
MathContainer::operator - (int param) const throw (OPERATOR_MINUS_EXCEPTIONS)
{
	return (*v_var - Integer(param));
}

MathContainer
MathContainer::operator * (int param) const throw (OPERATOR_TIMES_EXCEPTIONS)
{
	return (*v_var * Integer(param));
}

MathContainer
MathContainer::operator / (int param) const throw (OPERATOR_DIVIDE_EXCEPTIONS)
{
	return (*v_var / Integer(param));
}

MathContainer
MathContainer::operator + (double param) const throw (OPERATOR_PLUS_EXCEPTIONS)
{
	return (*v_var + Real(param));
}

MathContainer
MathContainer::operator - (double param) const throw (OPERATOR_MINUS_EXCEPTIONS)
{
	return (*v_var - Real(param));
}

MathContainer
MathContainer::operator * (double param) const throw (OPERATOR_TIMES_EXCEPTIONS)
{
	return (*v_var * Real(param));
}

MathContainer
MathContainer::operator / (double param) const throw (OPERATOR_DIVIDE_EXCEPTIONS)
{
	return (*v_var / Real(param));
}


MathContainer
MathContainer::operator - () const throw ()
{
	return -(*v_var);
}

MathObject &
MathContainer::operator+=(const MathObject &mo) throw (UndefException)
{
	//*v_var += mo;
	
	MathObject *result = (*v_var + mo).copy();
	
	delete v_var;
	
	v_var = result; //.copy();
	
	return *v_var;
}

MathObject &
MathContainer::operator-=(const MathObject &mo) throw (UndefException)
{
	//*v_var -= mo;
	MathObject &result = *v_var + mo;
	
	delete v_var;
	
	v_var = result.copy();
	
	return *v_var;
}

MathObject &
MathContainer::operator*=(const MathObject &mo) throw (UndefException)
{
	//*v_var *= mo;
	MathObject &result = *v_var + mo;
	
	delete v_var;
	
	v_var = result.copy();
	
	return *v_var;
}

MathObject &
MathContainer::operator/=(const MathObject &mo) throw (UndefException, DivideByZero)
{
	//*v_var /= mo;
	MathObject &result = *v_var + mo;
	
	delete v_var;
	
	v_var = result.copy();
	
	return *v_var;
}

MathObject &
MathContainer::operator+=(const MathContainer &v) throw (UndefException, IllegalOperation)
{
	//*v_var += *v.v_var;
	MathContainer result(*v_var + *v.v_var);
	
	*this = result;
	
	return *v_var;
}

MathObject &
MathContainer::operator-=(const MathContainer &v) throw (UndefException)
{
	//*v_var -= *v.v_var;
	MathObject &result = *v_var + *v.v_var;
	
	delete v_var;
	
	v_var = result.copy();
	
	return *v_var;
}

MathObject &
MathContainer::operator*=(const MathContainer &v) throw (UndefException)
{
	//*v_var *= *v.v_var;
	MathObject &result = *v_var + *v.v_var;
	
	delete v_var;
	
	v_var = result.copy();
	
	return *v_var;
}

MathObject &
MathContainer::operator/=(const MathContainer &v) throw (UndefException, DivideByZero)
{
	//*v_var /= *v.v_var;
	MathObject &result = *v_var + *v.v_var;
	
	delete v_var;
	
	v_var = result.copy();
	
	return *v_var;
}

	
#ifdef DEBUG

bool
MathContainer::test_all(ostream &out)
{
	Test results("MathContainer");
	
	return results.get_final_result();
}

#endif /* DEBUG */

// non-methods

MathContainer
operator + (int param, const MathContainer &mc) throw (OPERATOR_PLUS_EXCEPTIONS)
{
	return (Integer(param) + mc.var());
}

MathContainer
operator - (int param, const MathContainer &mc) throw (OPERATOR_MINUS_EXCEPTIONS)
{
	return (Integer(param) - mc.var());
}

MathContainer
operator * (int param, const MathContainer &mc) throw (OPERATOR_TIMES_EXCEPTIONS)
{
	return (Integer(param) * mc.var());
}

MathContainer
operator / (int param, const MathContainer &mc) throw (OPERATOR_DIVIDE_EXCEPTIONS)
{
	return (Integer(param) / mc.var());
}

MathContainer
operator + (double param, const MathContainer &mc) throw (OPERATOR_PLUS_EXCEPTIONS)
{
	return (Real(param) + mc.var());
}

MathContainer
operator - (double param, const MathContainer &mc) throw (OPERATOR_MINUS_EXCEPTIONS)
{
	return (Real(param) - mc.var());
}

MathContainer
operator * (double param, const MathContainer &mc) throw (OPERATOR_TIMES_EXCEPTIONS)
{
	return (Real(param) * mc.var());
}

MathContainer
operator / (double param, const MathContainer &mc) throw (OPERATOR_DIVIDE_EXCEPTIONS)
{
	return (Real(param) / mc.var());
}

















