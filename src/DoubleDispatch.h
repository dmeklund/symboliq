#ifndef DOUBLE_DISPATCH_H
#define DOUBLE_DISPATCH_H

#include <iostream>
#include "AllClasses.h"
#include "InternalError.h"
#include "ExtMathContainer.h"
#include "UndefException.h"
#include "IllegalOperation.h"

// We reference many classes which we cannot yet #include because they rely on this header
// file, so we need to include forward declarations of them.  See AllClasses.h for
// macros that reference all classes that implement double dispatch (e.g. also the 
// FORALLCLASSES() macro); that file MUST be updated whenever a new class implementing
// double dispatch is added.
ALL_FORWARD_DECLS()

// In a typical double dispatch scenario, this is the first function that will be called.
// The caller knows the instance type of neither argument, and so passes along one as an
// argument to the other's virtual "visit" function.  The callee now knows it's own type
// (since visit is a virtual function declared in all implementing classes), but not the
// other's, so it must call _that_ object's "visit" function, declared below.
#define DEF_BINARY_OP_VISIT_BASE(type) \
	virtual ExtMathContainer visit(BinaryDispatcher &dsp, const MathObject &mo) const	\
	{	ObjectWrapper<type> wrap(this);	\
		return mo.visit(dsp, &wrap);	}

// This will be the function called next.  Now we know the instance types of both arguments
// and can pass them along to the dispatcher, which will execute the operation
// specified in dsp.
#define DEF_BINARY_OP_VISIT_CLASS(type)	\
	virtual ExtMathContainer visit(BinaryDispatcher &dsp, ObjectWrapper<type> *obj) const	\
	{	return dsp.dispatch(this, obj->getObj());	}

// "All classes" in this context refers to all classes which implement double dispatching.
// In practice this refers to all types that can be trivially simplified when acted on by
// most operators with other objects of the same type (e.g., Integer(3) + Integer(5) ->
// Integer(8), or Matrix(m,n) * Matrix(n,l) -> Matrix(m,l)).  In some cases, however,
// interactions between objects of different types are implemented (e.g., scaling a matrix
// by a scalar).
#define DEF_BINARY_OP_VISIT_ALL_CLASSES()  FORALLCLASSES(DEF_BINARY_OP_VISIT_CLASS)
#define DEF_BINARY_OP_VISIT(type)	\
	DEF_BINARY_OP_VISIT_BASE(type)	\
	DEF_BINARY_OP_VISIT_ALL_CLASSES()

// The macros defined below are only used in the implementation of double dispatch as a
// convenience (e.g. in the Binary(...)Op classes).  They should NOT be used in the actual
// MathObject classes (Integer, Matrix, etc.).
#define DEF_BINARY_EXEC_NOT_IMPLEMENTED(type)	\
	virtual ExtMathContainer execute(const type *i1, const type *i2) const throw (InternalError)	\
	{	throw InternalError("Binary operation on type " #type " not implemented!");	}

#define DECL_BINARY_EXEC_DEF(type)	\
	virtual ExtMathContainer execute(const type *t1, const type *t2) const throw (UndefException, InternalError) = 0;
#define DECL_UNARY_EXEC_DEF(type)	\
	virtual ExtMathContainer execute(const type *t) const throw (UndefException, InternalError) = 0;

template <typename T>
class ObjectWrapper
{
	const T *myObj;
	
	public:

	ObjectWrapper(const T *obj) : myObj(obj) {}
	
	const T* getObj()
	{
		return myObj;
	}
};

// All unary operations are derived from this class.  You may wonder what the point of
// implementing a unary operator is in the context of supposed "double" dispatch, and as
// of this writing, I don't actually implement any unary operators this way.  However,
// this is included for completeness.
class UnaryOperation
{
	public:
	
	UnaryOperation() {}
	
	virtual ExtMathContainer execute(const void *ptr) const throw (UndefException, InternalError)
	{
		throw UndefException("Undefined unary operation on MathObject");
	}
	
	FORALLCLASSES(DECL_UNARY_EXEC_DEF)
};

class UnaryDispatcher
{
	const UnaryOperation *operation;
	
	public:
	
	UnaryDispatcher(const UnaryOperation &uo) : operation(&uo) {}
	
	template <class T1>
	ExtMathContainer dispatch(T1 *obj) const
	{
		return operation->execute(obj);
	}
};

class BinaryOperation
{
	public:
	
	BinaryOperation() {}
	
	virtual ExtMathContainer execute(const void *ptr1, const void *ptr2) const throw (UndefException, InternalError, IllegalOperation)
	{
		throw InternalError("Undefined binary operation on two void ptrs: should never reach here");
	}
	
	FORALLCLASSES(DECL_BINARY_EXEC_DEF)
};

class BinaryDispatcher
{
	const BinaryOperation *operation;
	
	public:
	
	BinaryDispatcher(const BinaryOperation &bo) : operation(&bo) {}
	
	template <class T1, class T2>
	ExtMathContainer dispatch(T1 *obj1, T2 *obj2) const throw (UndefException)
	{
		return operation->execute(obj1, obj2);
	}
};

#endif /* DOUBLE_DISPATCH_H */
