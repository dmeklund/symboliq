#include "UndefException.h"

#include <string.h>
#include <stdlib.h>

UndefException::UndefException(const char *cls) throw () 
	: runtime_error("illegal operation on undefined object")
{
	if (cls == NULL) 
		asprintf(&str, "illegal operation on undefined object");
	else
		asprintf(&str, "illegal operation on undefined object: %s", cls);
}

UndefException::UndefException(const UndefException &param) throw()
	: runtime_error(param)
{
	str = strdup(param.str);
}

UndefException::~UndefException() throw () 
{
	free(str);
}

UndefException &
UndefException::operator=(const UndefException &param) throw()
{
	str = strdup(param.str);
	
	return *this;
}

const char *
UndefException::what() const throw () 
{
	return str;
}
