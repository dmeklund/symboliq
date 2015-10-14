#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include "MathObject.h"

class Vector : public MathObject
{
	public:
	
	Vector(int n);
	virtual ~Vector();
	
	OVERRIDE_DEFAULT_COPY_OP(Vector)
	DEFAULT_COPY_IMPL(Vector)
	DEF_BINARY_OP_VISIT(Vector)
	CLASS_STRING(Vector)
	
	virtual MathContainer& operator() (int i, int j = 1);
	virtual const MathContainer& operator() (int i, int j = 1) const;
	
	protected:
	
	virtual void set_equal(MathObject &);
	virtual void set_equal(Vector &);
	virtual bool is_equal(MathObject &);
	virtual bool is_equal(Vector &);
	
	private:
	
	void check_args(int i, int j) throw (invalid_argument);
	
	vector<MathContainer> v_data;
};

#endif /* VECTOR_H */
