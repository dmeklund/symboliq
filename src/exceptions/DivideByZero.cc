#include <string.h>
#include <stdlib.h>

#include "DivideByZero.h"

DivideByZero::DivideByZero(const char *cls) throw () 
	: runtime_error("divide by zero")
{
	if (cls == NULL) 
		asprintf(&str, "divide by zero");
	else
		asprintf(&str, "divide by zero: %s", cls);
}

DivideByZero::DivideByZero(const DivideByZero &param) throw()
	: runtime_error(param)
{
	str = strdup(param.str);
}

DivideByZero::~DivideByZero() throw () 
{
	free(str);
}

DivideByZero &
DivideByZero::operator=(const DivideByZero &param) throw()
{
	str = strdup(param.str);
	
	return *this;
}

const char *
DivideByZero::what() const throw () 
{
	return str;
}
