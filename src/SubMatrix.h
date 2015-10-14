#ifndef SUBMATRIX_H
#define SUBMATRIX_H

#include <stdexcept>

#include "Matrix.h"
#include "MathContainer.h"
#include "UndefException.h"

using namespace std;

class SubMatrix : public Matrix
{
	public:
	
	SubMatrix(Matrix &, unsigned int i1, unsigned int j1, unsigned int i2, unsigned int j2) throw (out_of_range);
	SubMatrix(const Matrix &, unsigned int i1, unsigned int j1, unsigned int i2, unsigned int j2) throw (out_of_range);
	SubMatrix(Matrix &, unsigned int exclude_i, unsigned int exclude_j) throw (out_of_range);
	SubMatrix(const Matrix &, unsigned int exclude_i, unsigned int exclude_j) throw (out_of_range);
	SubMatrix(Matrix &);
	SubMatrix(const Matrix &);
	
	SubMatrix(const SubMatrix &);
	SubMatrix();
	
	OVERRIDE_DEFAULT_COPY_OP(SubMatrix)
	DEFAULT_COPY_IMPL(SubMatrix)
	DEF_BINARY_OP_VISIT(SubMatrix)
	CLASS_STRING(SubMatrix)
	
	protected:
	
	virtual MathContainer& get_ij(unsigned int i, unsigned int j)
		throw (UndefException, invalid_argument, out_of_range);
	virtual const MathContainer& get_ij(unsigned int i, unsigned int j) const
		throw (UndefException, invalid_argument, out_of_range);
	virtual void set_ij(unsigned int i, unsigned int j, MathObject &)
		throw (UndefException, invalid_argument, out_of_range);
		
	private:
	
	void fix_indices(unsigned int &i, unsigned int &j) const throw (out_of_range);

	Matrix *sm_matrix;
	const Matrix *sm_c_matrix;
	unsigned int sm_i1, sm_j1, sm_i2, sm_j2;
	unsigned int sm_exclude_i, sm_exclude_j;
};

#endif /* SUBMATRIX_H */
