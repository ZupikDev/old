#include "Fraction.hpp"

#include <iomanip>
#include <sstream>
#include <algorithm>

Fraction::Fraction(long long int numerator = 1, long long int denominator = 1) {
	num = numerator;
	if (denominator == 0) {
		std::cout << "Error -> Denominator can't be 0.\n";
		std::cout << "The denominator is set to 1 for the fraction : " << this->num << "/0\n";
		denom = 1;
	}
	else {
		denom = denominator;
	}
	this->simplify();
}

Fraction::Fraction(Fraction& f) {
	this->denom = f.denom;
	this->num = f.num;
	this->simplify();
}


Fraction::Fraction(long double d) {
	long double x = d;
	long double r = x - (int)x;
	std::ostringstream strs;
	strs << std::setprecision(10) << r;
	std::string temp = strs.str();
	std::string out = temp.substr(temp.find(".") + 1);
	num = (long long unsigned int)(x * pow(10, out.size()));
	denom = (long long unsigned int)(pow(10, out.size()));
	this->simplify();
}

void Fraction::simplify() {
	long long unsigned n = this->denom;
	if (this->num < this->denom) {
		n = this->num;
	}
	for (long long int i = n; i > 1; i--) {
		if (this->denom % i == 0 && this->num % i == 0) {
			this->denom /= i;
			this->num /= i;
			break;
		}
	}
}

std::ostream& operator<<(std::ostream& o, Fraction& f) {
	o << f.num << "/" << f.denom << " = " << std::setprecision(9) << (double long)f.num / f.denom << "\n";
	return o;
}

Fraction& Fraction::operator/(int x) {
	this->num *= x;
	this->simplify();
	return *this;
}

Fraction& Fraction::operator/(double x) {
	this->operator*(x);
	return *this;
}
Fraction& Fraction::operator/(Fraction& f) {
	this->num *= f.denom;
	this->denom *= f.num;
	this->simplify();
	return *this;
}

