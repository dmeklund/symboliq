## Process this file with automake to produce Makefile.in

AM_CXXFLAGS = -Iexceptions/ -Iimpl/ -Wall -g

bin_PROGRAMS = test_all
lib_LTLIBRARIES = libsymboliq.la

test_all_SOURCES = test_all.cc
test_all_LDADD = libsymboliq.la

libsymboliq_la_SOURCES = \
	ColVector.cc      ColVector.h           \
	Complex.cc        Complex.h             \
	                  Constant.h            \
	ExtMathContainer.cc ExtMathContainer.h	\
	Integer.cc        Integer.h             \
	MathObject.cc     MathObject.h          \
	Matrix.cc         Matrix.h              \
	Rational.cc       Rational.h            \
	Real.cc           Real.h		\
	RowVector.cc      RowVector.h           \
	SubMatrix.cc      SubMatrix.h           \
	Test.cc           Test.h                \
	MathContainer.cc  MathContainer.h	\
	Operator.h							\
	BinaryOperator.cc BinaryOperator.h	\
	UnaryOperator.cc  UnaryOperator.h	\
	Addition.cc       Addition.h		\
	Subtraction.cc    Subtractiion.h	\
	Multiplication.cc Multiplication.h	\
	Division.cc       Division.h		\
	Negation.cc       Negation.h		\
	NAddition.cc      NAddition.h		\
	Variable.cc       Variable.h		\
	Comparison.cc     Comparison.h		\
	Equals.h							\
	Trig.cc           Trig.h			\
	Power.h								\
	Exponential.h						\
	exceptions/DivideByZero.cc			\
	exceptions/DivideByZero.h			\
	exceptions/IllegalOperation.h		\
	exceptions/InternalError.h			\
	exceptions/UndefException.h			\
	exceptions/UndefException.cc		\
	impl/BinaryAdditionOp.cc			\
	impl/BinaryAdditionOp.h				\
	impl/BinaryDivisionOp.h				\
	impl/BinaryMultiplicationOp.h		\
	impl/BinaryOperations.h				\
	impl/BinarySetEqualOp.h				\
	impl/BinarySubtractionOp.h	
	
## libsymboliq_la_LIBADD = 
libsymboliq_la_LDFLAGS = -version-info 0:0:0

