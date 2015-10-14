#ifndef TRIG_H
#define TRIG_H

#include "UnaryOperator.h"
#include "MathObject.h"

#define TRIG_PRECEDENCE 1

class Sine : public UnaryOperator
{
public:
	Sine(const MathObject &mo) : UnaryOperator(TRIG_PRECEDENCE, "sin", mo) {}
	Sine() : UnaryOperator() {}
	virtual MathContainer inverse(const MathObject &expr) const;
	virtual MathContainer simplify() const;
};

class Cosine : public UnaryOperator
{
public:
	Cosine(const MathObject &mo) : UnaryOperator(TRIG_PRECEDENCE, "cos", mo) {}
	Cosine() : UnaryOperator() {}
	virtual MathContainer inverse(const MathObject &expr) const;
	virtual MathContainer simplify() const;
};

class Tangent : public UnaryOperator
{
public:
	Tangent(const MathObject &mo) : UnaryOperator(TRIG_PRECEDENCE, "tan", mo) {}
	Tangent() : UnaryOperator() {}
	virtual MathContainer inverse(const MathObject &expr) const;
	virtual MathContainer simplify() const;
};

class ArcSine : public UnaryOperator
{
public:
	ArcSine(const MathObject &mo) : UnaryOperator(TRIG_PRECEDENCE, "arcsin", mo) {}
	ArcSine() : UnaryOperator() {}
	virtual MathContainer inverse(const MathObject &expr) const;
	virtual MathContainer simplify() const;
};

class ArcCosine : public UnaryOperator
{
public:
	ArcCosine(const MathObject &mo) : UnaryOperator(TRIG_PRECEDENCE, "arccos", mo) {}
	ArcCosine() : UnaryOperator() {}
	virtual MathContainer inverse(const MathObject &expr) const;
	virtual MathContainer simplify() const;
};

class ArcTangent : public UnaryOperator
{
public:
	ArcTangent(const MathObject &mo) : UnaryOperator(TRIG_PRECEDENCE, "arctan", mo) {}
	ArcTangent() : UnaryOperator() {}
	virtual MathContainer inverse(const MathObject &expr) const;
	virtual MathContainer simplify() const;
};

class HypSine : public UnaryOperator
{
public:
	HypSine(const MathObject &mo) : UnaryOperator(TRIG_PRECEDENCE, "sinh", mo) {}
	HypSine() : UnaryOperator() {}
	virtual MathContainer inverse(const MathObject &expr) const;
	virtual MathContainer simplify() const;
};

class HypCosine : public UnaryOperator
{
public:
	HypCosine(const MathObject &mo) : UnaryOperator(TRIG_PRECEDENCE, "cosh", mo) {}
	HypCosine() : UnaryOperator() {}
	virtual MathContainer inverse(const MathObject &expr) const;
	virtual MathContainer simplify() const;
};

class HypTangent : public UnaryOperator
{
public:
	HypTangent(const MathObject &mo) : UnaryOperator(TRIG_PRECEDENCE, "tanh", mo) {}
	HypTangent() : UnaryOperator() {}
	virtual MathContainer inverse(const MathObject &expr) const;
	virtual MathContainer simplify() const;
};

class ArcHypSine : public UnaryOperator
{
public:
	ArcHypSine(const MathObject &mo) : UnaryOperator(TRIG_PRECEDENCE, "arcsinh", mo) {}
	ArcHypSine() : UnaryOperator() {}
	virtual MathContainer inverse(const MathObject &expr) const;
	virtual MathContainer simplify() const;
};

class ArcHypCosine : public UnaryOperator
{
public:
	ArcHypCosine(const MathObject &mo) : UnaryOperator(TRIG_PRECEDENCE, "arccosh", mo) {}
	ArcHypCosine() : UnaryOperator() {}
	virtual MathContainer inverse(const MathObject &expr) const;
	virtual MathContainer simplify() const;
};

class ArcHypTangent : public UnaryOperator
{
public:
	ArcHypTangent(const MathObject &mo) : UnaryOperator(TRIG_PRECEDENCE, "arctanh", mo) {}
	ArcHypTangent() : UnaryOperator() {}
	virtual MathContainer inverse(const MathObject &expr) const;
	virtual MathContainer simplify() const;
};

#endif /* TRIG_H */
