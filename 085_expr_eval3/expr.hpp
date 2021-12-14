#ifndef __EXPR_H___
#define __EXPR_H___
#include<cstdlib>
#include<sstream>
#include<string>
#include<cstdio>

class Expression{
	public:
		Expression() {}
		virtual long evaluate() const = 0;
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
		virtual long evaluate() const { return number; }
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
		virtual long evaluate() const {
			long ans;
			ans = l->evaluate() + r->evaluate();
			return ans;
		}
		virtual ~PlusExpression() {
			delete l;
			delete r;
		}

};

class MinusExpression : public Expression{
	Expression * l;
	Expression * r;

	public:
		MinusExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs){}
		virtual std::string toString() const{
			std::stringstream ans;
			ans << "(" << l->toString() << "-" << r->toString() << ")";
			return ans.str();
		}
		virtual long evaluate() const {
			long ans;
			ans = l->evaluate() - r->evaluate();
			return ans;
		}
		virtual ~MinusExpression(){
			delete l;
			delete r;
		}
};

class TimesExpression : public Expression{
	Expression * l;
	Expression * r;

	public:
		TimesExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs){}
		virtual std::string toString() const{
			std::stringstream ans;
			ans << "(" << l->toString() << " * " << r->toString() << ")";
			return ans.str();
		}
		virtual long evaluate() const{
			long ans;
			ans = l->evaluate() * r->evaluate();
			return ans;
		}
		virtual ~TimesExpression(){
			delete l;
			delete r;
		}
};

class DivExpression : public Expression{
	Expression * l;
	Expression * r;

	public:
		DivExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs){}
		virtual std::string toString() const{
			std::stringstream ans;
			ans << "(" << l->toString() << " / " << r->toString() << ")";
			return ans.str();
		}
		virtual long evaluate() const {
			long ans;
			ans = l->evaluate() / r->evaluate();
		       return ans;
		}	       
		virtual ~DivExpression(){
			delete l;
			delete r;
		}
};

#endif
