#ifndef UTILSFUNC_H
#define UTILSFUNC_H

#include "SFML/Graphics.hpp"

bool isIn(sf::RectangleShape&, float, float);
void printSprite(sf::RenderWindow&, sf::Sprite, float x, float y);
void printPlayer(sf::RenderWindow&, std::vector<sf::Sprite>&);
void changeValueOfPlayer(int&, std::pair<float, float>);
bool Used(sf::RectangleShape, int, int);

#endif // UTILSFUNC_H