#ifndef DIVIDE_BY_ZERO
#define DIVIDE_BY_ZERO

#include <stdexcept>

using namespace std;

class DivideByZero : public runtime_error {
	public:
	
	DivideByZero(const char *cls = NULL) throw ();
	DivideByZero(const DivideByZero &) throw ();
	virtual ~DivideByZero() throw ();
	
	DivideByZero& operator=(const DivideByZero&) throw ();
	
	virtual const char * what() const throw ();
	
	private:
	
	char *str;
};

#endif /* DIVIDE_BY_ZERO */
