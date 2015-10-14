#ifndef EQUALS_H
#define EQUALS_H

#include "Comparison.h"
#include "MathObject.h"
#include "MathContainer.h"

#define EQUALS_STRING "="

class Equals : public Comparison
{

public:

	Equals(const MathObject &lhs, const MathObject &rhs) : Comparison(EQUALS_STRING, lhs, rhs) {}
	Equals() : Comparison() {}

private:

};

#endif /* EQUALS_H */