#include <vector>
#include <cstdarg>
#include <ostream>

#include "Test.h"
#include "NAddition.h"
#include "Addition.h"
#include "Variable.h"

NAddition::NAddition(int N, ...) : Operator(ADDITION_PRECEDENCE)
{
	const MathObject *mo_ptr;
	va_list ap;
	
	int i;

	va_start(ap, N);

	for (i = 0; i < N; ++i)
	{
		mo_ptr = va_arg(ap, const MathObject *);
		append(*mo_ptr);
	}
}

NAddition::NAddition(const Addition &add) : Operator(ADDITION_PRECEDENCE)
{
	const MathObject *arg1, *arg2;
	const NAddition *nadd_ptr;
	const Addition *add_ptr;

	arg1 = &add.get_arg1();
	arg2 = &add.get_arg2();

	// see if first argument is of type addition; if so, simplify
	if (nadd_ptr = dynamic_cast<const NAddition*> (arg1))
		append(*nadd_ptr);
	else if (add_ptr = dynamic_cast<const Addition *> (arg1))
	{
		NAddition tmp(*add_ptr); // recurse, in case we have a nested binary addition structure
		append(tmp);
	}
	else
		append(*arg1);

	// same for second argument
	if (nadd_ptr = dynamic_cast<const NAddition*> (arg2))
		append(*nadd_ptr);
	else if (add_ptr = dynamic_cast<const Addition *> (arg2))
	{
		NAddition tmp(*add_ptr);
		append(tmp);
	}
	else
		append(*arg2);
}

MathContainer
NAddition::simplify() const
{
	return MathContainer(*this);
}

MathContainer
NAddition::solve_for_index(const MathObject &expr, int offset) const
{
	MathContainer negation = this->negate();
	// we know that the negation of an NAddition object is another NAddition object
	NAddition result = static_cast<NAddition&> (negation.var());

	result.na_data.erase(result.na_data.begin() + offset);
	result.append(expr);
	return MathContainer(result);
}

MathContainer
NAddition::negate() const throw ()
{
	NAddition result(*this);
	int N = result.get_length();
	// flip signs
	// TODO: generic?
	for (int i = 0; i < N; ++i)
		result.na_signs[i] *= -1;

	return MathContainer(result);
}

string
NAddition::to_string() const
{
	int N = get_length();

	if (N == 0)
		return "()";
	else
	{
		string result = na_data[0].to_string();
		for (int i = 1; i < N; ++i)
			result += " + " + na_data[i].to_string();
		return result;
	}
}


const MathObject &
NAddition::get_arg(int offset) const
{
	return na_data[offset];
}

int
NAddition::get_length() const
{
	return na_data.size();
}

void
NAddition::append(const MathObject &mo, int sign)
{
	const MathObject *mo_ptr = &mo;
	const Addition *add_ptr;
	const NAddition *nadd_ptr;

	if (add_ptr = dynamic_cast<const Addition*> (mo_ptr))
		append(*add_ptr, sign);
	else if (nadd_ptr = dynamic_cast<const NAddition*> (mo_ptr))
		append(*nadd_ptr, sign);
	else
	{
		na_data.push_back(MathContainer(*mo_ptr));
		na_signs.push_back(sign);
	}
}

void
NAddition::append(const Addition &add, int sign)
{
	NAddition nadd(add); // convert to NAddition (deals with nested structure) and append
	append(nadd, sign);
}

void
NAddition::append(const NAddition &nadd, int sign)
{
	// append all data from arguments na_data vector onto this object's na_data vector
	// TODO: doesn't deal appropriately with sign
	na_data.insert(na_data.end(), nadd.na_data.begin(), nadd.na_data.end());
	na_signs.insert(na_signs.end(), nadd.na_signs.begin(), nadd.na_signs.end());
}

bool
NAddition::test_all(ostream &out)
{
	Test results("NAddition", out);
	Variable x("x"), y("y"), z("z");
	NAddition nadd(3, &x, &y, &z);
	MathContainer mc1, mc2;

	out << "NAddition" << endl;
	mc1 = x + (y + z);
	out << mc1 << endl;
	out << mc1.var().simplify() << endl;
	//out << nadd << endl;

	return results.get_final_result();
}

void
NAddition::set_equal(const NAddition &nadd) throw (OPERATOR_EQUALS_EXCEPTIONS)
{
	na_data = nadd.na_data;
	na_signs = nadd.na_signs;
	Operator::set_equal(nadd);
}