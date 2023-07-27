#include "utilsFunc.h"

#include "gameClass.h"

#include <iostream>

bool isIn(sf::RectangleShape& r, float x, float y) {
	if (r.getGlobalBounds().contains(x, y)) return true;
	return false;
}

void printSprite(sf::RenderWindow& window, sf::Sprite sprite, float x, float y) {
	sprite.setPosition(x, y); window.draw(sprite);
}

void printPlayer(sf::RenderWindow& window, std::vector<sf::Sprite>& vector) {
	for (auto& vect : vector) {
		window.draw(vect);
	}
}

void changeValueOfPlayer(int& player, std::pair<float, float> coords) {
	if (coords == Pairs::BottomRight) player |= Tile::BottomRight;
	else if (coords == Pairs::Bottom) player |= Tile::Bottom;
	else if (coords == Pairs::BottomLeft) player |= Tile::BottomLeft;
	else if (coords == Pairs::Right) player |= Tile::Right;
	else if (coords == Pairs::Middle) player |= Tile::Middle;
	else if (coords == Pairs::Left) player |= Tile::Left;
	else if (coords == Pairs::TopRight) player |= Tile::TopRight;
	else if (coords == Pairs::Top) player |= Tile::Top;
	else if (coords == Pairs::TopLeft) player |= Tile::TopLeft;
}

bool Used(sf::RectangleShape sprite, int player1, int player2) {
	std::pair<float, float> coords = { sprite.getGlobalBounds().getPosition().x, sprite.getGlobalBounds().getPosition().y };
	int before1 = player1; int before2 = player2;
	changeValueOfPlayer(player1, coords);
	changeValueOfPlayer(player2, coords);
	if (before1 == player1 || before2 == player2) return true;
	else return false;
}