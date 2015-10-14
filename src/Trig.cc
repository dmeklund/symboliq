#include "Trig.h"
#include "MathObject.h"
#include "MathContainer.h"

// Sine
MathContainer
Sine::inverse(const MathObject &expr) const
{
	return expr.ArcSin();
}

MathContainer
Sine::simplify() const
{
	return this->get_arg().simplify().Sin();
}

// Cosine
MathContainer
Cosine::inverse(const MathObject &expr) const
{
	return expr.ArcCos();
}

MathContainer
Cosine::simplify() const
{
	return this->get_arg().simplify().Cos();
}

// Tangent
MathContainer
Tangent::inverse(const MathObject &expr) const
{
	return expr.ArcTan();
}

MathContainer
Tangent::simplify() const
{
	return this->get_arg().simplify().Tan();
}

// ArcSine
MathContainer
ArcSine::inverse(const MathObject &expr) const
{
	return expr.Sin();
}

MathContainer
ArcSine::simplify() const
{
	return this->get_arg().simplify().ArcSin();
}

// ArcCosine
MathContainer
ArcCosine::inverse(const MathObject &expr) const
{
	return expr.Cos();
}

MathContainer
ArcCosine::simplify() const
{
	return this->get_arg().simplify().ArcCos();
}

// ArcTangent
MathContainer
ArcTangent::inverse(const MathObject &expr) const
{
	return expr.Tan();
}

MathContainer
ArcTangent::simplify() const
{
	return this->get_arg().simplify().ArcTan();
}

// HypSine
MathContainer
HypSine::inverse(const MathObject &expr) const
{
	return expr.ArcSinh();
}

MathContainer
HypSine::simplify() const
{
	return this->get_arg().simplify().Sinh();
}


// HypCosine
MathContainer
HypCosine::inverse(const MathObject &expr) const
{
	return expr.ArcCosh();
}

MathContainer
HypCosine::simplify() const
{
	return this->get_arg().simplify().Cosh();
}

// HypTangent
MathContainer
HypTangent::inverse(const MathObject &expr) const
{
	return expr.ArcTanh();
}

MathContainer
HypTangent::simplify() const
{
	return this->get_arg().simplify().Tanh();
}

// ArcHypSine
MathContainer
ArcHypSine::inverse(const MathObject &expr) const
{
	return expr.Sinh();
}

MathContainer
ArcHypSine::simplify() const
{
	return this->get_arg().simplify().ArcSinh();
}

// ArcHypCosine
MathContainer
ArcHypCosine::inverse(const MathObject &expr) const
{
	return expr.Cosh();
}

MathContainer
ArcHypCosine::simplify() const
{
	return this->get_arg().simplify().ArcCosh();
}

// ArcHypTangent
MathContainer
ArcHypTangent::inverse(const MathObject &expr) const
{
	return expr.Tanh();
}

MathContainer
ArcHypTangent::simplify() const
{
	return this->get_arg().simplify().ArcTanh();
}
