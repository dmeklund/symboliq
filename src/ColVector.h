#ifndef COLVECTOR_H
#define COLVECTOR_H

#include <stdexcept>

#include "Matrix.h"

class ColVector : public Matrix
{
	public:
	
	ColVector(unsigned int m)
		: Matrix(m, 1), c_matrix(NULL), c_cmatrix(NULL), c_index(0) {}
	ColVector(Matrix &m, unsigned int i)
		: Matrix(true, m.rows(), 1), c_matrix(&m), c_cmatrix(NULL), c_index(i) {}
	ColVector(const Matrix &m, unsigned int i)
		: Matrix(true, m.rows(), 1), c_matrix(NULL), c_cmatrix(&m), c_index(i) {}
	ColVector() : Matrix () {}
	
	OVERRIDE_DEFAULT_COPY_OP(ColVector)
	DEFAULT_COPY_IMPL(ColVector)
	DEF_BINARY_OP_VISIT(ColVector)
	CLASS_STRING(ColVector)
	
	protected:
	
	virtual MathContainer& get_ij(unsigned int i, unsigned int j) throw (out_of_range, invalid_argument);
	virtual const MathContainer& get_ij(unsigned int i, unsigned int j) const throw (out_of_range, invalid_argument);
	virtual void set_ij(unsigned int i, unsigned int j, MathObject &) throw (out_of_range, invalid_argument);
	
	Matrix *c_matrix;
	const Matrix *c_cmatrix;
	unsigned int c_index;
};

//typedef ColVector Vector;

#endif /* COLVECTOR_H */
