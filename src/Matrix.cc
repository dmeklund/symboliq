#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "Matrix.h"
#include "SubMatrix.h"
#include "RowVector.h"
#include "ColVector.h"
#include "MathContainer.h"
#include "Constant.h"

#include "Test.h"
#include "Rational.h"
#include "Integer.h"

Matrix::Matrix(unsigned int m, unsigned int n)
	: MathObject(true, 2), m_data(m*n), m_rows(m), m_cols(n)
{
}
/*
Matrix::Matrix(const Matrix &m)
	: MathObject(m), m_data(m.m_data), m_rows(m.m_rows), m_cols(m.m_cols)
{
}
*/
Matrix::Matrix() : MathObject(), m_data(), m_rows(0), m_cols(0)
{
}

Matrix::~Matrix()
{
}
/*
Matrix *
Matrix::copy() const
{
	Matrix *mat;
	int i, j, m, n;

	m = rows();
	n = cols();

	mat = new Matrix(m, n);

	for (i = 1; i <= m; ++i)
		for (j = 1; j <= n; ++j)
			(*mat)(i,j) = (*this)(i,j);

	return mat;
}
*/
Matrix
Matrix::inv() const
{
	throw runtime_error("matrix inversion not implemented!");
}

MathContainer
Matrix::det() const throw (IllegalOperation)
{
	MathContainer result(Math::Zero);
	unsigned int j;
	int sign;
	
	if (m_rows != m_cols)
		throw IllegalOperation("can't calculate determinant of non-square matrix");
	
	if (m_rows == 1)
		result = get_ij(1, 1);
	else
	{
		for (j = 1; j <= m_cols; ++j)
		{
			//const SubMatrix &sm = submatrix(1, j);
			//const MathContainer &var = get_ij(1, j);
			//sign = (j % 2) ? +1 : -1;
			//var.MathObject::operator*(1.0); // * sm.det();
		}
	}
	
	return result;
}

unsigned int
Matrix::rows() const
{
	return m_rows;
}

unsigned int
Matrix::cols() const
{
	return m_cols;
}

RowVector
Matrix::row(unsigned int i) throw (out_of_range)
{
	RowVector result;
	
	if (i > m_rows || i < 1)
		throw out_of_range("no such row in Matrix");
	
	result = RowVector(*this, i);
	
	return result;
}

const RowVector
Matrix::row(unsigned int i) const throw (out_of_range)
{
	RowVector result;
	
	if (i > m_rows || i < 1)
		throw out_of_range("no such row in Matrix");
	
	result = RowVector(*this, i);
	
	return result;
}

ColVector
Matrix::col(unsigned int j) throw (out_of_range)
{
	ColVector result;
	
	if (j > m_cols || j < 1)
		throw out_of_range("no such column in Matrix");
	
	result = ColVector(*this, j);
	
	return result;
}

const ColVector
Matrix::col(unsigned int j) const
	throw (out_of_range)
{
	ColVector result;
	
	if (j > m_cols || j < 1)
		throw out_of_range("no such column in Matrix");
	
	result = ColVector(*this, j);
	
	return result;
}

SubMatrix
Matrix::submatrix(unsigned int i, unsigned int j)
	throw (out_of_range)
{
	return SubMatrix(*this, i, j);
}

const SubMatrix
Matrix::submatrix(unsigned int i, unsigned int j) const
	throw (out_of_range)
{
	return SubMatrix(*this, i, j);
}


SubMatrix
Matrix::submatrix(unsigned int i1, unsigned int j1,
	              unsigned int i2, unsigned int j2)
	throw (out_of_range)
{
	return SubMatrix(*this, i1, j1, i2, j2);
}

const SubMatrix
Matrix::submatrix(unsigned int i1, unsigned int j1,
	              unsigned int i2, unsigned int j2) const
	throw (out_of_range)
{
	return SubMatrix(*this, i1, j1, i2, j2);
}
/*
Matrix &
Matrix::operator=(const Matrix &m)
{
	set_equal_to(m);
	return *this;
}

Matrix &
Matrix::operator=(const MathContainer &v)
{
	const Matrix &var = static_cast<const Matrix &> (v.var());
	set_equal_to(var);
	return *this;
}
*/
MathContainer &
Matrix::operator()(unsigned int i, unsigned int j) throw (out_of_range)
{
	return get_ij(i, j);
	//return m_data[(i-1)*m_rows + (j-1)];
}

const MathContainer &
Matrix::operator()(unsigned int i, unsigned int j) const throw (out_of_range)
{
	return get_ij(i, j);
	//return m_data[(i-1)*m_rows + (j-1)];
}
/*
Matrix 
Matrix::operator+(const Matrix &m) const throw (invalid_argument)
{
	Matrix result(m_rows, m_cols);
	unsigned int i, j;

	if (m.m_rows != m_rows || m.m_cols != m_cols)
		throw invalid_argument("Matrix dimensions don't agree");
	
	for (i = 1; i <= m_rows; ++i)
		for (j = 1; j <= m_cols; ++j)
			result.set_ij(i, j, get_ij(i, j) + m.get_ij(i, j));
	
	return result;
}

Matrix
Matrix::operator-(const Matrix &m) const throw (invalid_argument)
{
	Matrix result(m_rows, m_cols);
	unsigned int i, n;

	if (m.m_rows != m_rows || m.m_cols != m_cols)
		throw invalid_argument("Matrix dimensions don't agree");
	
	n = m_rows*m_cols;
	for (i = 0; i < n; ++i)
		result.m_data[i] = m_data[i] - m.m_data[i];
	
	return result;
}

Matrix
Matrix::operator*(const Matrix &m) const throw (invalid_argument)
{
	Matrix result(m.m_rows, m_cols), temp;
	unsigned int i, j;
	
	if (m.m_cols != m_rows)
		throw invalid_argument("Matrix dimensions don't agree");
	
	for (i = 1; i <= m.m_rows; ++i)
		for (j = 1; j <= m_cols; ++j)
			result(i, j) = row(i) * m.col(j);
	
	return result;
}
			
Matrix
Matrix::operator/(const Matrix &m) const throw (invalid_argument)
{
	Matrix result;
	
	result = *this * m.inv();
	
	return result;
}	

MathContainer
Matrix::operator*(const MathObject &mo) const throw (invalid_argument)
{
	Matrix result(m_rows, m_cols);
	unsigned int i, n;
	
	if (mo.dim() != 1)
		throw invalid_argument("multiply by MathObject of wrong dimension");
	
	n = m_rows * m_cols;
	
	for (i = 0; i < n; ++i)
		result.m_data[i] = m_data[i] * mo;
	
	return MathContainer(result);
}

MathContainer
Matrix::operator/(const MathObject &mo) const throw (invalid_argument)
{
	Matrix result(m_rows, m_cols);
	unsigned int i, n;
	
	if (mo.dim() != 1)
		throw invalid_argument("divide by MathObject of wrong dimension");
	
	n = m_rows * m_cols;
	
	for (i = 0; i < n; ++i)
		result.m_data[i] = m_data[i] / mo;
	
	return MathContainer(result);
}

Matrix &
Matrix::operator+=(const Matrix &m) throw (invalid_argument)
{
	unsigned int i, n;
	
	if (m.m_rows != m_rows || m.m_cols != m_cols)
		throw invalid_argument("Matrix dimensions don't agree");
	
	n = m_rows * m_cols;
	
	for (i = 0; i < n; ++i)
		m_data[i] += m.m_data[i];
	
	return *this;
}
	
Matrix &
Matrix::operator-=(const Matrix &m) throw (invalid_argument)
{
	unsigned int i, n;
	
	if (m.m_rows != m_rows || m.m_cols != m_cols)
		throw invalid_argument("Matrix dimensions don't agree");
	
	n = m_rows * m_cols;
	
	for (i = 0; i < n; ++i)
		m_data[i] -= m.m_data[i];
	
	return *this;
}
	
Matrix &
Matrix::operator*=(const Matrix &m) throw (invalid_argument)
{
	unsigned int i, n;
	
	if (m.m_rows != m_rows || m.m_cols != m_cols)
		throw invalid_argument("Matrix dimensions don't agree");
	
	n = m_rows * m_cols;
	
	for (i = 0; i < n; ++i)
		m_data[i] *= m.m_data[i];
	
	return *this;
}
	
Matrix &
Matrix::operator/=(const Matrix &m) throw (invalid_argument)
{
	unsigned int i, n;
	
	if (m.m_rows != m_rows || m.m_cols != m_cols)
		throw invalid_argument("Matrix dimensions don't agree");
	
	n = m_rows * m_cols;
	
	for (i = 0; i < n; ++i)
		m_data[i] /= m.m_data[i];
	
	return *this;
}

Matrix &
Matrix::operator*=(const MathObject &mo) throw (invalid_argument, IllegalOperation)
{
	unsigned int i, n;
	
	if (mo.dim() != 1)
		throw invalid_argument("multiply by MathObject of wrong dimension");
	
	n = m_rows * m_cols;
	
	for (i = 0; i < n; ++i)
		m_data[i] *= mo;
	
	return *this;
}

Matrix &
Matrix::operator/=(const MathObject &mo) throw (invalid_argument, IllegalOperation)
{
	unsigned int i, n;
	
	if (mo.dim() != 1)
		throw invalid_argument("divide by MathObject of wrong dimension");
	
	n = m_rows * m_cols;
	
	for (i = 0; i < n; ++i)
		m_data[i] /= mo;
	
	return *this;
}
*/
#ifdef DEBUG

bool
Matrix::test_all(ostream &out)
{
	Test result("Matrix", out);
	Matrix a, b, c;
	ColVector colv;
	int i, j;
	a = Matrix(3, 3);
	for (i = 1; i <= 3; ++i)
		for (j = 1; j <= 3; ++j)
			a(i,j) = i*j; //Integer(i*j);
	
	out << a << endl;
	
	/*colv = ColVector(a, 1);
	out << colv << endl;
	colv(3,1) = Rational(12);
	out << colv << endl;
	out << a << endl;*/
	
	Matrix d;
	d = a * a;
	
	out << d << endl;
	out << b << endl;
	
	return result.get_final_result();
}
	
#endif

// protected methods

// dummy matrix: don't actually store any data
Matrix::Matrix(bool dummy, unsigned int m, unsigned int n)
	: m_data(0), m_rows(m), m_cols(n)
{
}


string
Matrix::to_string () const
{
	ostringstream ss;
	unsigned int i, j;
	
	ss << "[";
	for (i = 1; i <= m_rows; ++i) {
		for (j = 1; j <= m_cols; ++j)
		{
			ss << ' ';
			ss << (*this)(i, j);
		}
		
		if (i != m_rows)
			ss << ';';
	}
	ss << ']';
	
	return ss.str();
}


void
Matrix::write_to_stream(ostream &out) const
{
	unsigned int i, j;
	
	out << '[';
	
	for (i = 1; i <= m_rows; ++i) {
		for (j = 1; j <= m_cols; ++j)
			out << ' ' << (*this)(i, j);
		
		if (i != m_rows)
			out << ';';
	}
	out << ']';
}

MathContainer &
Matrix::get_ij(unsigned int i, unsigned int j) throw (out_of_range, invalid_argument, UndefException)
{
	check_bounds(i, j);
	
	return m_data[(i-1)*m_cols + (j-1)];
}

const MathContainer &
Matrix::get_ij(unsigned int i, unsigned int j) const throw (out_of_range, invalid_argument, UndefException)
{
	check_bounds(i, j);
	return m_data[(i-1)*m_cols + (j-1)];
}

void
Matrix::set_ij(unsigned int i, unsigned int j, MathObject &mo) throw (out_of_range, invalid_argument, UndefException)
{
	check_bounds(i, j);

	m_data[(i-1)*m_cols + (j-1)] = mo;
}

void
Matrix::check_bounds(unsigned int i, unsigned int j) const throw (out_of_range)
{
	if (i > m_rows || i < 1)
		throw out_of_range("no such row in Matrix");
	if (j > m_cols || j < 1)
		throw invalid_argument("no such column in Matrix");
}
/*
void
Matrix::set_equal(const MathObject &param) throw (invalid_argument)
{
	const Matrix *m_ptr;
	if (m_ptr = dynamic_cast<const Matrix*> (&param))
	{
		set_equal(*m_ptr);
	}
	else
	{
		ostringstream err;
		err << "attempt to set Matrix equal to object of type " << typeid(param).name();
		throw invalid_argument(err.str());
	}
}
*/
void
Matrix::set_equal(const Matrix &m) throw ()
{
	m_rows = m.m_rows;
	m_cols = m.m_cols;
	m_data = m.m_data;
	MathObject::set_equal(m);
}

