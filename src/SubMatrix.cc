#include "SubMatrix.h"

#define NROWS(i1, i2, rows) ((i2 >= i1) ? (i2-i1+1) : (i1-i2+rows+1))
#define NCOLS(j1, j2, cols) NROWS(j1, j2, cols)

SubMatrix::SubMatrix(Matrix &m, unsigned int i1, unsigned int j1,
                                unsigned int i2, unsigned int j2)
	throw (out_of_range)
	: Matrix(true, NROWS(i1, i2, m.rows()), NCOLS(j1, j2, m.rows())),
	  sm_matrix(&m), sm_c_matrix(NULL),
	  sm_i1(i1), sm_j1(j1), sm_i2(i2), sm_j2(j2)
{
	if (   i1 > m.rows() || i2 > m.rows() || i1 < 1 || i2 < 1
		|| j1 > m.cols() || j2 > m.cols() || j1 < 1 || j2 < 1 )
	{
		throw out_of_range("SubMatrix::SubMatrix (Matrix &, unsigned int, unsigned int, unsigned int, unsigned int)");
	}
}

SubMatrix::SubMatrix(const Matrix &m, unsigned int i1, unsigned int j1,
                                      unsigned int i2, unsigned int j2)
	throw (out_of_range)
	: Matrix(true, NROWS(i1, i2, m.rows()), NCOLS(j1, j2, m.rows())),
	  sm_matrix(NULL), sm_c_matrix(&m),
	  sm_i1(i1), sm_j1(j1), sm_i2(i2), sm_j2(j2),
	  sm_exclude_i(0), sm_exclude_j(0)
{
	if (   i1 > m.rows() || i2 > m.rows() || i1 < 1 || i2 < 1
		|| j1 > m.cols() || j2 > m.cols() || j1 < 1 || j2 < 1 )
	{
		throw out_of_range("SubMatrix::SubMatrix (Matrix &, unsigned int, unsigned int, unsigned int, unsigned int)");
	}
}


SubMatrix::SubMatrix(Matrix &m, unsigned int exclude_i, unsigned int exclude_j)
	throw (out_of_range)
	: Matrix(true, m.rows()-1, m.cols()-1), sm_matrix(&m), sm_c_matrix(NULL),
	  sm_i1(0), sm_j1(0), sm_i2(0), sm_j2(0),
	  sm_exclude_i(exclude_i), sm_exclude_j(exclude_j)
{
	if (exclude_i > m.rows() || exclude_j > m.rows() || exclude_i < 1 || exclude_j < 1)
	{
		throw out_of_range("SubMatrix::SubMatrix (Matrix &, unsigned int, unsigned int)");
	}
}

SubMatrix::SubMatrix(const Matrix &m, unsigned int exclude_i, unsigned int exclude_j)
	throw (out_of_range)
	: Matrix(true, m.rows()-1, m.cols()-1), sm_matrix(NULL), sm_c_matrix(&m),
	  sm_i1(0), sm_j1(0), sm_i2(0), sm_j2(0),
	  sm_exclude_i(exclude_i), sm_exclude_j(exclude_j)
{
	if (exclude_i > m.rows() || exclude_j > m.rows() || exclude_i < 1 || exclude_j < 1)
	{
		throw out_of_range("SubMatrix::SubMatrix (Matrix &, unsigned int, unsigned int)");
	}
}

SubMatrix::SubMatrix(const SubMatrix &sm)
	: Matrix(true, sm.rows(), sm.cols()), sm_matrix(sm.sm_matrix), sm_c_matrix(sm.sm_c_matrix),
	  sm_i1(sm.sm_i1), sm_j1(sm.sm_j1), sm_i2(sm.sm_i2), sm_j2(sm.sm_j2),
	  sm_exclude_i(sm.sm_exclude_i), sm_exclude_j(sm.sm_exclude_j)
{
}

SubMatrix::SubMatrix(Matrix &m)
	: Matrix(true, m.rows(), m.cols()), sm_matrix(&m), sm_c_matrix(NULL),
	  sm_i1(1), sm_j1(1), sm_i2(m.rows()), sm_j2(m.cols()),
	  sm_exclude_i(0), sm_exclude_j(0)
{
}

SubMatrix::SubMatrix(const Matrix &m)
	: Matrix(true, m.rows(), m.cols()), sm_matrix(NULL), sm_c_matrix(&m),
	  sm_i1(1), sm_j1(1), sm_i2(m.rows()), sm_j2(m.cols()),
	  sm_exclude_i(0), sm_exclude_j(0)
{
}

SubMatrix::SubMatrix() : Matrix()
{
}

// protected methods

MathContainer &
SubMatrix::get_ij(unsigned int i, unsigned int j) throw (UndefException, invalid_argument, out_of_range)
{
	fix_indices(i, j);
	
	if (sm_matrix != NULL)
		return (*sm_matrix)(i, j);
	else if (sm_c_matrix != NULL)
		throw invalid_argument("can't return non-const MathContainer from const SubMatrix");
	else
		throw UndefException("SubMatrix");
}
		
const MathContainer &
SubMatrix::get_ij(unsigned int i, unsigned int j) const throw (UndefException, invalid_argument, out_of_range)
{
	fix_indices(i, j);
	
	if (sm_matrix != NULL)
		return (*sm_matrix)(i, j);
	else if (sm_c_matrix != NULL)
		return (*sm_matrix)(i, j);
	else
		throw UndefException("SubMatrix");
}

void
SubMatrix::set_ij(unsigned int i, unsigned int j, MathObject &mo)
	throw (UndefException, invalid_argument, out_of_range)
{
	fix_indices(i, j);
	
	if (sm_matrix != NULL)
		(*sm_matrix)(i, j) = mo;
	else if (sm_c_matrix != NULL)
		throw invalid_argument("can't modify contents of const SubMatrix");
	else
		throw UndefException("SubMatrix");
}

// private methods

void
SubMatrix::fix_indices(unsigned int &i, unsigned int &j) const throw (out_of_range)
{
	check_bounds(i, j);
	
	if (sm_exclude_i == 0)
	{
		i += sm_i1 - 1;
		j += sm_j1 - 1;
		
		if (i > m_rows)
			i -= m_rows;
		if (j > m_cols)
			j -= m_cols;
	}
	else
	{
		if (i >= sm_exclude_i)
			++i;
		if (j >= sm_exclude_j)
			++j;
	}
}
