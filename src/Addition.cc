#include <sstream>
#include <string>
#include <iostream>

#include "Addition.h"
#include "MathObject.h"
#include "MathContainer.h"
#include "NAddition.h"

MathContainer
Addition::simplify() const
{
	const Operator *o;
	bool can_simplify = false;

	if (o = dynamic_cast <const Operator*> (&arg1.var()))
	{
		if (o->is_additive())
			can_simplify = true;
	}
	if (!can_simplify && (o = dynamic_cast <const Operator*>(&arg2.var())))
	{
		if (o->is_additive())
			can_simplify = true;
	}

	if (can_simplify)
	{
		NAddition result(2, &arg1.var(), &arg2.var());
		return MathContainer(result);
	}
	else
		return MathContainer(*this);
}

MathContainer
Addition::solve_for_index(const MathObject &expr, int offset) const
{
	MathContainer result;

	if (offset == 0)
	{
		result = expr - arg2;
	}
	else if (offset == 1)
	{
		result = expr - arg1;
	}
	else
	{
		throw invalid_argument("Addition::solve_for_index: offset invalid: must be either 0 or 1");
	}

	return result;
}

