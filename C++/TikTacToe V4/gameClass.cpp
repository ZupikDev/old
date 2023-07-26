#include "gameClass.h"
#include "entityClass.h"

#include <array>

bool Game::hasWon(int boardPlacements) {
	static const std::array<int, 8> winConditions{
		Tile::TopLeft    + Tile::Top    + Tile::TopRight, 
		Tile::Left       + Tile::Middle + Tile::Right,		
		Tile::BottomLeft + Tile::Bottom + Tile::BottomRight,
		Tile::TopLeft    + Tile::Left   + Tile::BottomLeft,
		Tile::Top        + Tile::Middle + Tile::Bottom,
		Tile::TopRight   + Tile::Right  + Tile::BottomRight,
		Tile::TopLeft    + Tile::Middle + Tile::BottomRight,
		Tile::TopRight   + Tile::Middle + Tile::BottomLeft
	};
	return std::any_of(winConditions.begin(), winConditions.end(),
		[boardPlacements](int condition) {
			return (boardPlacements & condition) == condition;
	});
}

void Game::Init() {

	for (int i = 0 ; i < 9; i++) tiles.emplace_back(sf::RectangleShape(sf::Vector2f(133.f, 133.f)));
	
	int x = 0;
	for (int i = 2; i >= 0; i--) {
		for (int j = 2; j >= 0; j--) {
			tiles[x].setPosition(sf::Vector2f(static_cast<float>(j * 133), static_cast<float>(i * 133)));
			x++;
		}
	}
}

void Game::printBoard(sf::RenderWindow& window) {
	for (auto& tile : tiles) {
		tile.setFillColor(sf::Color(13, 13, 13));
		tile.setOutlineThickness(2.f);
		tile.setOutlineColor(sf::Color::White);
		window.draw(tile);
	}
}