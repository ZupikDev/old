#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <numeric>

#include "entrys.hpp"

bool isPrime(int& x)
{
	for (int i = 2; i < std::sqrt(x); ++i)
	{
		if (x % i == 0)
		{
			return false;
		}
	}
	return true;
}

std::vector<int> findAllPrimes(int& x)
{
	std::vector<int> primes_numbers{};
	if (!isPrime(x))
	{
		for (int i = 2; i != x; ++i)
		{
			if (isPrime(i))
			{
				primes_numbers.push_back(i);
			}
		}
	}
	else
	{
		throw std::runtime_error("Number almost prime");
	}
	return primes_numbers;
	
}

std::vector<int> decompose(int x)
{
	std::vector<int> out{}; int var{ x };

	while ((std::accumulate(std::cbegin(out), std::cend(out), 1, [](int const& left, int const& right) -> int {return left * right; })) != var)
	{
		for (int i = 2; i != var; ++i)
		{
			if (x % i == 0)
				while (x % i == 0)
				{
					out.push_back(i);
					x /= i;
				}
		}
	}

	return out;

}

int main()
{
	while(true) {
		try {
			int val = 0; char again{}; std::string toStr{};

			std::cout << "What number do you want to decompose ? ";
			entry(val, "Une erreur est survenue.");
			auto result = decompose(val);

			for (auto i = 0; i != std::size(result); ++i)
			{
				toStr.append(std::to_string(result[i]));
				if (i == std::size(result) - 1)
				{
					break;
				}
				toStr.append("x");
			}

			std::cout << val << " = " << toStr << std::endl;

			std::cout << "Do you want to continue ? ";
			entry(again, "Enter 'y' or 'n'", [](char& letter) -> bool {return letter == 'y' || letter == 'n'; });
			if (again == 'n')
			{
				break;
			}

		}
		catch (std::runtime_error const& except) {
			std::cout << except.what() << std::endl;
			std::cout << "What number do you want to decompose ? ";
			continue;
		}
	}


	return 0;
}