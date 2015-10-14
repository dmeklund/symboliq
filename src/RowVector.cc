#include "RowVector.h"
#include "ColVector.h"
/*
RowVector &
RowVector::operator = (const RowVector &rv)
{
	c_matrix = rv.c_matrix;
	c_cmatrix = rv.c_cmatrix;
	c_index = rv.c_index;
	
	Matrix::operator=(rv);
	
	return *this;
}

MathContainer
RowVector::operator * (const ColVector &cv) const throw (invalid_argument)
{
	MathContainer result;
	unsigned int i;
	
	if (m_cols != cv.rows())
		throw invalid_argument("vector dimensions don't match");
	
	result = (*this)(1,1) * cv(1,1);
	
	for (i = 2; i <= m_cols; ++i)
		result += (*this)(1, i) * cv(i, 1);
	
	return result;
}
*/

MathContainer &
RowVector::get_ij(unsigned int i, unsigned int j) throw (invalid_argument, out_of_range)
{
	if (c_matrix == NULL && c_cmatrix == NULL)
		return Matrix::get_ij(i, j);
	else
	{
		if (i != 1)
			throw out_of_range("no such column in RowVector");
		if (c_cmatrix == NULL)
			return (*c_matrix)(c_index, j);
		else
			throw invalid_argument("can't return non-const object from const RowVector");
	}
}

const MathContainer &
RowVector::get_ij(unsigned int i, unsigned int j) const throw (invalid_argument, out_of_range)
{
	if (c_matrix == NULL && c_cmatrix == NULL)
		return Matrix::get_ij(i, j);
	else
	{
		if (i != 1)
			throw out_of_range("no such column in RowVector");
		if (c_cmatrix == NULL)
			return (*c_matrix)(c_index, j);
		else
			return (*c_cmatrix)(c_index, j);
	}
}

void
RowVector::set_ij(unsigned int i, unsigned int j, MathObject &mo) throw (invalid_argument, out_of_range)
{
	if (c_matrix == NULL && c_cmatrix == NULL)
		Matrix::set_ij(i, j, mo);
	else
	{
		if (j != 1)
			throw out_of_range("no such column in RowVector");
		
		if (c_cmatrix == NULL)
			(*c_matrix)(c_index, j) = mo;
		else
			throw invalid_argument("can't modify const Matrix");
	}
}
