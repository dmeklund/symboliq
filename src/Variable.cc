#include <string>
#include <iostream>

#include "MathContainer.h"
#include "Addition.h"
#include "Variable.h"
#include "Test.h"

Variable::Variable(const char *name)
: MathObject(true, 1), v_name(name)
{
}

Variable::Variable(const string name)
: MathObject(true, 1), v_name(name)
{
}

string
Variable::to_string() const
{
	return v_name;
}

bool
Variable::test_all(ostream &out)
{
	Variable x("x"), y("y");
	MathContainer mc = -(2.4+x) + (-y) * (3 + x);
	out << mc << endl;
	return true;
}
