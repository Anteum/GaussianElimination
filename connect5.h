#ifndef CONNECT_H
#define CONNECT_H
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

//declare classes

class ReallyLong//like really long int (using vector)
{
	public:
		std::vector<short> reallyLongInt;//one's place is first
		bool neg;
		ReallyLong(std::vector<short> rli = std::vector<short>(1,0), bool n = false);
		ReallyLong(long long num);
		int Length() const;
		short operator[](int) const;//one's place is last
		void Display() const;
		ReallyLong& Negation();// *= -1
		ReallyLong Abs() const;
		friend bool operator==(const ReallyLong, const ReallyLong);
		friend bool operator!=(const ReallyLong, const ReallyLong);
		friend bool operator<(const ReallyLong, const ReallyLong);
		friend bool operator>(const ReallyLong, const ReallyLong);
		ReallyLong& operator+=(const ReallyLong&);
		friend ReallyLong operator+(ReallyLong, const ReallyLong&);
		ReallyLong& operator-=(const ReallyLong&);
		friend ReallyLong operator-(ReallyLong, const ReallyLong&);
		ReallyLong& operator*=(const ReallyLong&);
		friend ReallyLong operator*(ReallyLong, const ReallyLong&);
		ReallyLong& operator/=(const ReallyLong&);
		friend ReallyLong operator/(ReallyLong, const ReallyLong&);
		//ReallyLong& operator%=(const ReallyLong&);
		//friend ReallyLong operator%(ReallyLong, const ReallyLong&);		

};

class Rational //class for ReallyLong rationals
{
	public:
		ReallyLong numer, denom;
		Rational(ReallyLong n = ReallyLong(0), ReallyLong d = ReallyLong(1));
		void Display();
		void Reduce();
		Rational& Negation();// *= -1
		friend bool operator==(const Rational, const Rational);
		Rational& operator+=(const Rational&);
		friend Rational operator+(Rational, const Rational&);
		Rational& operator-=(const Rational&);
		friend Rational operator-(Rational, const Rational&);
		Rational& operator*=(const Rational&);
		friend Rational operator*(Rational, const Rational&);
		Rational& operator/=(const Rational&);		
		friend Rational operator/(Rational, const Rational&);
		//Rational& operator%=(const Rational&);
		//friend Rational operator%(Rational, const Rational&);
		
};
/*
class Rational//rational number class with numer and denom vectors
{
	public:
		std::vector<short> numer, denom;
		Rational(std::vector<short> n = std::vector<short>(1,0), std::vector<short> d = std::vector<short>(1,1));
		void Display();
		void Reduce();
		Rational& operator+=(const Rational&);
		friend Rational operator+(Rational, const Rational&);
		Rational& operator*=(const Rational&);
		friend Rational operator*(Rational, const Rational&);
		Rational& operator%=(const Rational&);
	  	friend Rational operator%(Rational, const Rational&);
};
//*/
//declare functions here
int LongLength(long long);
ReallyLong intExp(int, int);
ReallyLong ninesComp(const ReallyLong&);
ReallyLong Euclidean(ReallyLong, ReallyLong);
//ReallyLong Euclidean(std::vector<short>, std::vector<short>);
void RREF(std::vector<std::vector<Rational>>&);//rref of matrix of rationals
std::vector<Rational> LinSysSolve(std::vector<std::vector<ReallyLong>>);


int ohdone();
int ohdtwo();
//int ohdthr();
int ohdfor();
//int ohdfiv();



#endif