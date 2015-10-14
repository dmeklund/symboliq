#ifndef ALL_CLASSES_H
#define ALL_CLASSES_H

// These next two definition use a nifty feature of the preprocessor that
// essentially allows a macro to be passed in as the argument of another macro.
// This works because of the way in which the macros are expanded, and may
// not be supported by all preprocessors.
#define FORALLCLASSES_EXCEPT_MATHOBJECT(macro)	\
	macro(ColVector)	\
	macro(Complex)	\
	macro(Constant)	\
	macro(Real)	\
	macro(Integer)	\
	macro(Matrix)	\
	macro(Rational)	\
	macro(RowVector)	\
	macro(SubMatrix)

#define FORALLCLASSES(macro)	\
	macro(MathObject)	\
	macro(ColVector)	\
	macro(Complex)	\
	macro(Constant)	\
	macro(Real)	\
	macro(Integer)	\
	macro(Matrix)	\
	macro(Rational)	\
	macro(RowVector)	\
	macro(SubMatrix)

#define ALL_FORWARD_DECLS()	\
	class MathObject;	\
	class ColVector;	\
	class Complex;	\
	class Constant;	\
	class Real;	\
	class Integer;	\
	class Matrix;	\
	class Rational;	\
	class RowVector;	\
	class SubMatrix;

#endif /* ALL_CLASSES_H */
