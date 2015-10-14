#include <sstream>
#include <string>
#include <iostream>

#include "Negation.h"
#include "MathObject.h"
#include "MathContainer.h"

MathContainer
Negation::simplify() const
{
	bool can_simplify = false;

//	this->arg = this->arg.simplify();

	if (dynamic_cast <const Operator*> (&arg.var()))
	{
		const Operator *o = static_cast<const Operator*> (&arg.var());
		if (o->is_multiplicative())
			can_simplify = true;
	}

//	if (can_simplify)
//		return MathContainer(NNegation(var1, var2));
//	else
		return MathContainer(*this);
}

MathContainer
Negation::inverse(const MathObject &expr) const
{
	return -expr;
}

