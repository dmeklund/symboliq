class IMutable
{	
public:
	virtual void set_equal(const MathObject &) throw (OPERATOR_EQUALS_EXCEPTIONS);
};