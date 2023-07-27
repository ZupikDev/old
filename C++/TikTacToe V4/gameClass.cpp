#include "gameClass.h"
#include "entityClass.h"
#include "utilsFunc.h"

#include <iostream>

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

void Game::Init(sf::RenderWindow& w) {

	for (int i = 0 ; i < 9; i++) tiles.emplace_back(sf::RectangleShape(sf::Vector2f(133.f, 133.f)));
	
	int x = 0;
	for (int i = 2; i >= 0; i--) {
		for (int j = 2; j >= 0; j--) {
			tiles[x].setPosition(sf::Vector2f(static_cast<float>(j * 133), static_cast<float>(i * 133)));
			x++;
		}
	}

	for (auto& tile : tiles) {
		tile.setFillColor(sf::Color(13, 13, 13));
		tile.setOutlineThickness(2.f);
		tile.setOutlineColor(sf::Color::White);
	}

	window = &w;

}

void Game::printBoard() {
	for (auto& tile : tiles) {
		window->draw(tile);
	}
}

bool Game::pollEvents(sf::Event& events) {
	return window->pollEvent(events);
}

void Game::render(int& player, sf::Sprite what, std::vector<sf::Sprite>& whereToAdd, std::pair<float, float> coords) {
	int before = player; 
	changeValueOfPlayer(player, coords);

	if (player != before) {
		what.setPosition(sf::Vector2f(coords.first + 18, coords.second + 18));
		whereToAdd.push_back(what);
	}
}

void Game::checkIfWon() {
	if (hasWon(tics)) {
		std::cout << "Player A has won";
		playable = false;
	}
	else if (hasWon(tacs)) {
		std::cout << "Player B has won";
		playable = false;
	}
	else if ((tics | tacs) == 0b111111111) {
		std::cout << "Well played !";
		playable = false;
	}
}

void Game::update(sf::Sprite Tsprite, float Tx, float Ty, std::vector<sf::Sprite>& playerA, std::vector<sf::Sprite>& playerB) {
	printSprite(*window, Tsprite, Tx, Ty);
	printPlayer(*window, playerA);
	printPlayer(*window, playerB);
}