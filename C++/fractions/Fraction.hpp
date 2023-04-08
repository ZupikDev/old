#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <string>
#include <math.h>
#include <iomanip>
#include <sstream>

class Fraction {
	long long int num;
	long long int denom;
public:
	Fraction(long long int, long long int);
	Fraction(Fraction&);
	Fraction(long double);
	void simplify();
	int pgdc(int,int);
	friend std::ostream& operator<<(std::ostream&, Fraction&);

	Fraction& operator/(int);
	Fraction& operator/(double);
	Fraction& operator/(Fraction&);

	template<class T>
	Fraction& operator*=(T v) {
		this->operator*(v);
		this->simplify();
		return *this;
	}
	
	template <class T>
	Fraction& operator*(T v)
	{
		this->num *= v;
		this->simplify();
		return *this;
	}

	template<>
	Fraction& operator*(Fraction v) {
		this->num *= v.num;
		this->simplify();
		return *this;
	}

	template<>
	Fraction& operator*(double v) {
		long double x = (long double)this->num / this->denom * v;
		long double r = x - (int)x;
		std::ostringstream strs;
		strs << std::setprecision(13) << r;
		std::string temp = strs.str();
		std::string out = temp.substr(temp.find(".") + 1);
		this->num = (long long unsigned int)(x * pow(10, out.size()));
		this->denom = (long long unsigned int)(pow(10, out.size()));
		this->simplify();
		return *this;
	}

	template<class X>
	Fraction& operator/=(X x) {
		this->operator/(x);
		return *this;
	}
	
	template<class X>
	Fraction& operator+(X a) {
		this->num += a * this->denom;
		this->simplify();
		return *this;
	}

	template<>
	Fraction& operator+(double a) {
		long double x = (long double)this->num / this->denom + a;
		long double r = x - (int)x;
		std::ostringstream strs;
		strs << std::setprecision(10) << r;
		std::string temp = strs.str();
		std::string out = temp.substr(temp.find(".") + 1);
		this->num = (long long unsigned int)(x * pow(10, out.size()));
		this->denom = (long long unsigned int)(pow(10, out.size()));
		this->simplify();
		return *this;
	}

	template<>
	Fraction& operator+(Fraction a) {
		if (a.denom == this->denom) {
			this->num += a.num;
		}
		else {
			long long int m = this->denom * a.denom;
			this->num = m / this->denom * this->num + (m / a.denom * a.num);
			this->denom = m;
		}

		this->simplify();
		return *this;
	}

	template<class F>
	Fraction& operator+=(F x) {
		this->operator+(x);
		return *this;
	}
};

#endif