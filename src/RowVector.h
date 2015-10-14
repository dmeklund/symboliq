#ifndef ROW_VECTOR_H
#define ROW_VECTOR_H

#include <stdexcept>

#include "Matrix.h"

class RowVector : public Matrix {
	public:
	
	RowVector(unsigned int n)
		: Matrix(1, n), c_matrix(NULL), c_cmatrix(NULL), c_index(0) {}
	RowVector(Matrix &m, unsigned int i)
		: Matrix(true, 1, m.cols()), c_matrix(&m), c_cmatrix(NULL), c_index(i) {}
	RowVector(const Matrix &m, unsigned int i)
		: Matrix(true, 1, m.cols()), c_matrix(NULL), c_cmatrix(&m), c_index(i) {}
	RowVector() : Matrix () {}
	
	OVERRIDE_DEFAULT_COPY_OP(RowVector)
	DEFAULT_COPY_IMPL(RowVector)
	DEF_BINARY_OP_VISIT(RowVector)
	CLASS_STRING(RowVector)
	
	protected:
	
	virtual MathContainer& get_ij(unsigned int i, unsigned int j) throw (invalid_argument, out_of_range);
	virtual const MathContainer& get_ij(unsigned int i, unsigned int j) const throw (invalid_argument, out_of_range);
	virtual void set_ij(unsigned int i, unsigned int j, MathObject &) throw (invalid_argument, out_of_range);
	
	Matrix *c_matrix;
	const Matrix *c_cmatrix;
	unsigned int c_index;	
};

#endif /* ROW_VECTOR_H */
