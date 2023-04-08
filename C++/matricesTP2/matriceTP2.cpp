#include "matrice.hpp"

#include <cassert>

Matrice::Matrice(std::size_t lines, std::size_t rows, int initial_value)
	: m_lines(lines), m_rows(rows), m_nbrs(lines*rows, initial_value)
{
	assert(m_lines >= 1 && "nombre de ligne < 1 !");
	assert(m_rows >= 1 && "nombre de colonnes < 1 !");
}

Matrice::Matrice(std::size_t lines, std::size_t rows)
	: m_lines(lines), m_rows(rows), m_nbrs(rows* lines)
{
	assert(m_lines >= 1 && "nombre de ligne < 1 !");
	assert(m_rows >= 1 && "nombre de colonnes < 1 !");
}

std::ostream& operator<<(std::ostream& os, const Matrice matrice)
{
	for (int x = 0; x < matrice.m_lines; ++x)
	{
		for (int y = 0; y < matrice.m_rows; ++y)
		{
			os << matrice(x,y) << " ";
		}
		os << "\n"; 
		
	}
	return os;
}


Matrice& Matrice::operator=(Matrice const rhs)
{
	this->m_nbrs.clear();
	this->m_lines = rhs.m_lines;
	this->m_rows = rhs.m_rows;

	for (int x : rhs.m_nbrs) { this->m_nbrs.push_back(x); }

	return *this;
}

int& Matrice::operator()(size_t x, size_t y)
{
	return this->m_nbrs[y * this->m_lines + x];
}

int const Matrice::operator()(size_t x, size_t y) const
{
	return this->m_nbrs[y * this->m_lines + x];
}

int const Matrice::taille() const
{
	return static_cast<int>(std::size(this->m_nbrs));
}

Matrice Matrice::extractLine(int index) const
{
	assert(index > 0 && "Il faut entrer une ligne existante.");
	assert(index <= this->m_lines && "L'index est trop élevé !");

	Matrice out(1,this->m_rows,0);
	for (int i = 0; i < this->m_rows; ++i)
	{
		out[i] = this->m_nbrs[this->m_lines * i + (index - 1)];
	}
	return out;
}

Matrice Matrice::extractRow(int index) const
{
	assert(index > 0 && "Il faut entrer une colonne existante.");
	assert(index <= this->m_rows && "L'index est trop élevé");

	Matrice out(this->m_lines, 1, 0);
	for (int i = 0; i < this->m_lines; ++i)
	{
		out[i] = this->m_nbrs[this->m_lines * (index-1) + i];
	}
	return out;
}

int const Matrice::lines() const
{
	return static_cast<int>(this->m_lines);
}

int const Matrice::rows() const
{
	return static_cast<int>(this->m_rows);
}

int& Matrice::operator[](int index)
{
	return this->m_nbrs[index];
}

int Matrice::operator[](int index) const
{
	return this->m_nbrs[index];
}

Matrice& Matrice::operator*(int const coef)
{
	return *this *= coef;
}

Matrice& Matrice::operator*=(int const coef)
{
	for (int &nb : this->m_nbrs) { nb *= coef;}
	return *this;
}


int sumL(Matrice line, Matrice row)
{
	int sum = 0;
	for (int lineIndex = 0; lineIndex < line.rows(); ++lineIndex)
	{
		sum += line[lineIndex] * row[lineIndex];
	}
	return sum;
}

Matrice& Matrice::operator*=(Matrice const matrice)
{
	assert(this->m_rows == matrice.m_lines && "Le nombre de colonnes de la première matrice doit correspondre au nombre de lignes de la deuxième matrice.");
	Matrice out(this->m_lines, matrice.m_rows);
	for (int l = 1; l <= this->m_lines; ++l)
	{
		for (int r = 1; r <= matrice.m_rows; ++r)
		{
			out(l-1, r-1) = sumL(this->extractLine(l), matrice.extractRow(r));
		}
	}
	*this = out;
	return *this;
}

Matrice Matrice::operator*(Matrice const matrice)
{
	return *this *= matrice;
}

Matrice& Matrice::operator+=(Matrice const matrice)
{
	assert(this->taille() == matrice.taille() && "Les matrices doivent faire la même taille");
	for (int index = 0; index < matrice.taille(); ++index)
	{
		this->m_nbrs[index] += matrice.m_nbrs[index];
	}
	return *this;
}

Matrice Matrice::operator+(Matrice const matrice)
{
	return *this+=matrice;
}
