#ifndef ANGLE_H
#define ANGLE_H

#include <math.h>
#include <stdexcept>

#include "UndefException.h"
#include "MathObject.h"

#ifndef PI
#  define PI 3.1415926535897932384626433
#endif /* PI */

using namespace std;

class Angle : public MathObject {
	public:
	
	typedef enum {RADIANS, DEGREES} format;
	Angle(double value, format a_format=RADIANS);
	Angle(Angle &);
	Angle();
	
	OVERRIDE_DEFAULT_COPY_OP(Angle)
	DEF_BINARY_OP_VISIT(Angle)
	
	double in_radians() const throw (UndefException);
	double in_degrees() const throw (UndefException);
	
	static double convert_to_degrees(double radians) throw ();
	static double convert_to_radians(double degrees) throw ();
	static double project_to_range(double value, format a_format=RADIANS);
	
	double a_radians, a_degrees;
};

class NPi : public Angle {
	public:
	
	NPi(double mult);
	NPi(NPi &);
	
	double in_radians();
	double in_degrees();
	
	NPi& operator=(NPi &);
	NPi operator+(NPi &);
	Angle operator+(Angle &);
	
	private:
	
	double p_mult;
};


#endif /* ANGLE_H */
