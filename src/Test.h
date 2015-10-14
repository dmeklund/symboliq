#ifndef TEST_H
#define TEST_H

#include <iostream>

#include "MathObject.h"

class Test {
	public:
	
	Test(const char * = NULL, std::ostream & = cerr);
	
	template <class T>
	bool check(MathObject &obj, const char *str_test, T result, T expected)
	{
		bool success = true;
		
		if (result != expected) 
		{
			if (t_class_str == NULL)
			{
				t_out << "test '" << str_test << "' on " << t_class_str << " object '"
					  << obj << "' failed: got " << result << ", expected "
					  << expected << endl;
			}
			else
			{
				t_out << "test " << str_test << " on object '"  << obj
					  << "' failed: got " << result << ", expected " << expected
					  << endl;
			}
			
			success = false;
			t_final_result = false;
		}
		else
		{
			t_out << "test '" << str_test << "' succeeded" << endl;
		}
		
		return success;
	};
	
	bool get_final_result();
	
	private:
	
	const char *t_class_str;
	std::ostream &t_out;
	bool t_final_result;
};

#endif
