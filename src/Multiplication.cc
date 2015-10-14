#include <sstream>
#include <string>
#include <iostream>

#include "Multiplication.h"
#include "MathObject.h"
#include "MathContainer.h"

MathContainer
Multiplication::simplify() const
{
	bool can_simplify = false;

	if (dynamic_cast <const Operator*> (&arg1.var()))
	{
		const Operator *o = static_cast<const Operator*> (&arg1.var());
		if (o->is_multiplicative())
			can_simplify = true;
	}
	if (!can_simplify && dynamic_cast <const Operator*>(&arg2.var()))
	{
		const Operator *o = static_cast<const Operator*> (&arg2.var());
		if (o->is_multiplicative())
			can_simplify = true;
	}

//	if (can_simplify)
//		return MathContainer(NMultiplication(arg1, arg2));
//	else
		return MathContainer(*this);
}

MathContainer
Multiplication::solve_for_index(const MathObject &expr, int offset) const
{
	MathContainer result;

	if (offset == 0)
	{
		result = expr / arg2;
	}
	else if (offset == 1)
	{
		result = expr / arg1;
	}
	else
	{
		throw invalid_argument("Multiplication::solve_for_index: offset invalid: must be either 0 or 1");
	}

	return result;
}

