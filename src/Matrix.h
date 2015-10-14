#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <stdexcept>

#include "Real.h"
#include "MathContainer.h"
#include "UndefException.h"
#include "IllegalOperation.h"

class RowVector;
class ColVector;
class SubMatrix;

class Matrix : public MathObject {
	
public:
	
	Matrix(unsigned int m, unsigned int n);
	Matrix();
	virtual ~Matrix();
	
	OVERRIDE_DEFAULT_COPY_OP(Matrix)
	DEFAULT_COPY_IMPL(Matrix)
	DEF_BINARY_OP_VISIT(Matrix)
	CLASS_STRING(Matrix)
	
	virtual Matrix inv() const;
	virtual MathContainer det() const throw (IllegalOperation);
	
	unsigned int rows() const;
	unsigned int cols() const;
	
	virtual RowVector row(unsigned int i) throw (out_of_range);
	virtual const RowVector row(unsigned int i) const throw (out_of_range);
	virtual ColVector col(unsigned int j) throw (out_of_range);
	virtual const ColVector col(unsigned int j) const throw (out_of_range);
	
	virtual SubMatrix submatrix(unsigned int i, unsigned int j) throw (out_of_range);
	virtual const SubMatrix submatrix(unsigned int i, unsigned int j) const throw (out_of_range);

	virtual SubMatrix submatrix(unsigned int i1, unsigned int j1,
	                            unsigned int i2, unsigned int j2) throw (out_of_range);
	virtual const SubMatrix submatrix(unsigned int i1, unsigned int j1,
	                                  unsigned int i2, unsigned int j2) const throw (out_of_range);

	//virtual operator string () const;
	virtual string to_string () const;

	virtual MathContainer& operator()(unsigned int i, unsigned int j) throw (out_of_range);
	virtual const MathContainer& operator() (unsigned int i, unsigned int j) const throw (out_of_range);
	 
#ifdef DEBUG
	static bool test_all(ostream &out = std::cerr);
#endif
	
protected:

	SETEQUAL_MATHOBJ_IMPL(Matrix)
	
	Matrix(bool dummy, unsigned int m, unsigned int n);

	virtual void write_to_stream(ostream &) const;

	virtual MathContainer& get_ij(unsigned int i, unsigned int j) throw (out_of_range, invalid_argument, UndefException);
	virtual const MathContainer& get_ij(unsigned int i, unsigned int j) const throw (out_of_range, invalid_argument, UndefException);
	virtual void set_ij(unsigned int i, unsigned int j, MathObject &) throw (out_of_range, invalid_argument, UndefException);
	
	void check_bounds(unsigned int i, unsigned int j) const throw (out_of_range);
	//void set_equal(const MathObject &param) throw (invalid_argument);
	void set_equal(const Matrix &) throw ();
	
	vector<MathContainer> m_data;
	//auto_ptr<MathObject> m_data;
	unsigned int m_rows, m_cols;
};

#endif
