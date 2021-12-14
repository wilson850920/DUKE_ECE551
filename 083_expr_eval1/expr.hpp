#ifndef __EXPR_H___
#define __EXPR_H___
#include<cstdlib>
#include<sstream>
#include<string>
#include<cstdio>

class Expression{
	public:
		Expression() {}
		virtual std::string toString() const = 0;
		virtual ~Expression() {}
};

class NumExpression : public Expression{
	long number;

	public:
		NumExpression(long n) : number(n){}
		virtual std::string toString() const{
		std::stringstream ans;
		ans << number;
		return ans.str();	
		}
	virtual ~NumExpression() {}
};

class PlusExpression : public Expression{
	Expression * l;
	Expression * r;
	
	public:
		PlusExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs){}
		virtual std::string toString() const{
			std::stringstream ans;
			ans << "(" << l->toString() << "+" << r->toString() << ")";
			return ans.str();
		}
		virtual ~PlusExpression() {
			delete l;
			delete r;
		}

};

#endif
