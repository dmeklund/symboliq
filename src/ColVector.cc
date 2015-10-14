#include "ColVector.h"

/*
ColVector &
ColVector::operator = (const ColVector &cv)
{
	c_matrix = cv.c_matrix;
	c_cmatrix = cv.c_cmatrix;
	c_index = cv.c_index;
	
	Matrix::operator=(cv);
	
	return *this;
}
*/
MathContainer &
ColVector::get_ij(unsigned int i, unsigned int j) throw (out_of_range, invalid_argument)
{
	if (c_matrix == NULL && c_cmatrix == NULL)
		return Matrix::get_ij(i, j);
	else
	{
		if (j != 1)
			throw out_of_range("no such column in ColVector");
		if (c_cmatrix == NULL)
			return (*c_matrix)(i, c_index);
		else
			throw invalid_argument("can't return non-const object from const ColVector");
	}
}

const MathContainer &
ColVector::get_ij(unsigned int i, unsigned int j) const throw (out_of_range, invalid_argument)
{
	if (c_matrix == NULL && c_cmatrix == NULL)
		return Matrix::get_ij(i, j);
	else
	{
		if (j != 1)
			throw out_of_range("no such column in ColVector");
		if (c_cmatrix == NULL)
			return (*c_matrix)(i, c_index);
		else
			return (*c_cmatrix)(i, c_index);
	}
}

void
ColVector::set_ij(unsigned int i, unsigned int j, MathObject &mo) throw (out_of_range, invalid_argument)
{
	if (c_matrix == NULL && c_cmatrix == NULL)
		Matrix::set_ij(i, j, mo);
	else
	{
		if (j != 1)
			throw out_of_range("no such column in ColVector");
		
		if (c_cmatrix == NULL)
			(*c_matrix)(i, c_index) = mo;
		else
			throw invalid_argument("can't modify const Matrix");
	}
}
