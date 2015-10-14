#include "Test.h"

#include <iostream>

Test::Test(const char *class_str, std::ostream &out)
	: t_class_str(strdup(class_str)), t_out(out), t_final_result(true)
{
}

bool
Test::get_final_result()
{
	return t_final_result;
}
