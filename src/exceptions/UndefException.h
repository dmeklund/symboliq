#ifndef UNDEF_EXCEPTION
#define UNDEF_EXCEPTION

#include <stdexcept>

using namespace std;

class UndefException : public runtime_error
{
	public:
	
	UndefException(const char *cls = NULL) throw();
	UndefException(const UndefException &) throw();
	virtual ~UndefException() throw ();
	
	UndefException& operator=(const UndefException&) throw();
	
	virtual const char * what() const throw ();
	
	private:
	
	char *str;
};

#endif /* UNDEF_EXCEPTION */
