#ifndef BINARY_MULTIPLICATION_OP_H
#define BINARY_MULTIPLICATION_OP_H

#include "DoubleDispatch.h"
#include "ExtMathContainer.h"
#include "MathObject.h"
#include "Integer.h"
#include "Real.h"
#include "Rational.h"
#include "Matrix.h"
#include "IllegalOperation.h"

#include "Multiplication.h"

class BinaryMultiplicationOp : public BinaryOperation
{
	public:
	
	virtual ExtMathContainer execute(const MathObject *mo1, const MathObject *mo2) const throw (InternalError)
	{
		Multiplication *mult = new Multiplication(*mo1, *mo2);
		return ExtMathContainer(mult);
	}

	virtual ExtMathContainer execute(const Integer *i1, const Integer *i2) const throw ()
	{
		Integer *i3 = new Integer(i1->get_whole() * i2->get_whole());
		return ExtMathContainer(i3);
	}
	
	virtual ExtMathContainer execute(const Real *f1, const Real *f2) const throw ()
	{
		Real *f3 = new Real(f1->to_float() * f2->to_float());
		return ExtMathContainer(f3);
	}
	
	virtual ExtMathContainer execute(const Rational *r1, const Rational *r2) const throw ()
	{
		unsigned int whole, numer, denom;
		bool sign, simplified = true;
		
		Rational::mult(r1->get_pos(), r1->get_whole(), r1->get_numer(), r1->get_denom(),
		     r2->get_pos(), r2->get_whole(), r2->get_numer(), r2->get_denom(),
			 sign, whole, numer, denom);

		Rational *r3 = new Rational(sign, whole, numer, denom, simplified);
		
		return ExtMathContainer(r3);
	}

	virtual ExtMathContainer execute(const Matrix *m1, const Matrix *m2) const throw (IllegalOperation)
	{
		Matrix *result;
		unsigned int i, j, k, m, n;

		m = m1->rows();
		n = m2->cols();

		result = new Matrix(m, n);

		if (n != m2->rows())
			throw IllegalOperation("Cannot multiply matrices: not conformable");

		for (i = 1; i <= m; ++i)
		{
			for (j = 1; j <= n; ++j)
			{
				(*result)(i, j) = (*m1)(i,1) * (*m2)(1,j);
				for (k = 2; k <= n; ++k)
					(*result)(i,j) = (*result)(i,j) + (*m1)(i,k) * (*m2)(k,j);
			}
		}

		return ExtMathContainer(result);
	}
	
	DEF_BINARY_EXEC_NOT_IMPLEMENTED(ColVector)
	DEF_BINARY_EXEC_NOT_IMPLEMENTED(Complex)
	DEF_BINARY_EXEC_NOT_IMPLEMENTED(Constant)
	DEF_BINARY_EXEC_NOT_IMPLEMENTED(RowVector)
	DEF_BINARY_EXEC_NOT_IMPLEMENTED(SubMatrix)
};

#endif /* BINARY_MULTIPLICATION_OP_H */
