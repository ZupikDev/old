#include <string>
#include <iostream>

class decimal
{
	int nb;
	std::string last_conversion;
public:
	decimal(int number = 0) { nb = number; }
	void to_binary();
	void print();
};
void decimal::to_binary()
{
	int dividende = nb;
	while (dividende != 0) 
	{
		last_conversion.append(std::to_string(dividende % 2));
		dividende = int(dividende / 2);
	}
	std::reverse(last_conversion.begin(), last_conversion.end());
}
void decimal::print() 
{
	size_t n = 4;
	int precision = n - std::min(n, last_conversion.size());
	std::string solution = std::string(precision, '0').append(last_conversion);
	std::cout << solution;
}

void entry()
{
	int input;
	std::cout << "Enter a decimal number to convert it : ";
	while (!(std::cin >> input))
	{
		std::cout << "Enter a decimal number to convert it : ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	decimal temp(input);
	temp.to_binary();
	temp.print();
}

int main()
{
	while (true)
	{
		std::string i;
		entry();
		std::cout << "\nContinue ? [Y/N] : "; 
		std::cin >> i;
		if (i == "N") { return 0; }
	}
}