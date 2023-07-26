#ifndef GAMECLASS_H
#define GAMECLASS_H

#include <SFML/Graphics.hpp>

struct Tile {
	Tile() = delete;

	static constexpr const int BottomRight = 1;
	static constexpr const int Bottom = BottomRight << 1;
	static constexpr const int BottomLeft = Bottom << 1;
	static constexpr const int Right = BottomLeft << 1;
	static constexpr const int Middle = Right << 1;
	static constexpr const int Left = Middle << 1;
	static constexpr const int TopRight = Left << 1;
	static constexpr const int Top = TopRight << 1;
	static constexpr const int TopLeft = Top << 1;
};

struct Pairs {
	Pairs() = delete;

	static constexpr const std::pair<float, float> BottomRight = { 264.f, 264.f };
	static constexpr const std::pair<float, float> Bottom = { 131.f, 264.f };
	static constexpr const std::pair<float, float> BottomLeft = { -2.f, 264.f };
	static constexpr const std::pair<float, float> Right = { 264.f, 131.f };
	static constexpr const std::pair<float, float> Middle = { 131.f, 131.f };
	static constexpr const std::pair<float, float> Left = { -2.f, 131.f };
	static constexpr const std::pair<float, float> TopRight = { 264.f, -2.f };
	static constexpr const std::pair<float, float> Top = { 131.f, -2.f };
	static constexpr const std::pair<float, float> TopLeft = { -2.f, -2.f};
};

class Game {
public:
	Game() {};
	void Init();
	void printBoard(sf::RenderWindow&);
	bool hasWon(int boardPlacements);

public:
	std::vector<sf::RectangleShape> tiles;
};


#endif // GAMECLASS_H