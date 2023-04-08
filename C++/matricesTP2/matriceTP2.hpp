#include <iostream>
#include <vector>

#ifndef MATRICE_HPP
#define MATRICE_HPP

class Matrice
{
public:
	Matrice() = delete;
	Matrice(std::size_t lines, std::size_t rows, int initial_value);
	Matrice(std::size_t lines, std::size_t rows);

	friend std::ostream& operator<<(std::ostream& os, Matrice matrice);
	Matrice& operator=(Matrice const rhs);

	int& operator()(size_t x, size_t y);
	int const operator()(size_t x, size_t y) const;

	int& operator[](int index);
	int operator[](int index) const;

	Matrice& operator*(int const coef);
	Matrice& operator*=(int const coef);
	Matrice operator*(Matrice const matrice);
	Matrice& operator*=(Matrice const matrice);

	Matrice& operator+=(Matrice const matrice);
	Matrice operator+(Matrice const matrice);

	Matrice extractLine(int index) const;
	Matrice extractRow(int index) const;

	int const taille() const;
	int const lines() const;
	int const rows() const;
private:
	std::size_t m_lines;
	std::size_t m_rows;
	std::vector<int> m_nbrs;
};

#endif