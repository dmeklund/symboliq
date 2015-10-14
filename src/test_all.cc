#include <iostream>
#include <stdexcept>

#include "Rational.h"
#include "Matrix.h"
#include "DivideByZero.h"
#include "Variable.h"
#include "NAddition.h"

using namespace std;

int
main(int argc, char *argv[])
{
	bool result;
	
	try 
	{
		result = Rational::test_all(cerr);
		result = Matrix::test_all(cerr) && result;
		result = Real::test_all(cerr) && result;
		result = Variable::test_all(cerr) && result;
		result = NAddition::test_all(cerr) && result;
	}
	catch (const exception &err)
	{
		cerr << "Caught exception: " << err.what() << endl;
		result = false;
	}
	catch (...)
	{
		cerr << "Caught unknown exception" << endl;
		result = false;
	}
	
	if (result)
	{
		cout << "All tests were successful." << endl;
	}
	else
	{
		cerr << "Some tests failed!" << endl;
	}
	
	return 0; // (result ? 0 : 1);
}
