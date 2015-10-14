#ifndef N_ADDITION_H
#define N_ADDITION_H

#include <vector>
#include <ostream>

#include "Operator.h"
#include "MathObject.h"
#include "MathContainer.h"
#include "Addition.h"

class NAddition : public Operator
{

public:

	NAddition(int N, ...);
	NAddition(const Addition &add);
	NAddition() : Operator(ADDITION_PRECEDENCE) {}

	DEFAULT_COPY_IMPL(NAddition)
	CLASS_STRING(NAddition)

	virtual MathContainer simplify() const;
	virtual MathContainer solve_for_index(const MathObject &expr, int offset) const;
	virtual MathContainer negate() const throw ();

	virtual string to_string() const;

	const MathObject& get_arg(int offset) const;
	int get_length() const;

	void append(const MathObject &mo, int sign=+1);
	void append(const Addition &add, int sign=+1);
	void append(const NAddition &nadd, int sign=+1);

	static bool test_all(ostream &out = cerr);

protected:

	SETEQUAL_MATHOBJ_IMPL(NAddition)
	virtual void set_equal(const NAddition &) throw (OPERATOR_EQUALS_EXCEPTIONS);

private:

	vector<MathContainer> na_data;
	vector<int> na_signs;

};

#endif /* N_ADDITION_H */
