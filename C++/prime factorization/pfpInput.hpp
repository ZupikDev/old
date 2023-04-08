#ifndef ENTRYS
#define ENTRYS

#include <string>
#include <iostream>
#include <limits>

template <typename T1, typename Predicat>
void entry(T1& input, std::string const message, Predicat const predicat)
{
	while (!(std::cin >> input) || !predicat(input))
	{
		std::cout << message << " Try again : ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

template <typename T1>
void entry(T1& input, std::string const message)
{
	while (!(std::cin >> input))
	{
		std::cout << message << " Try again : ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

#endif