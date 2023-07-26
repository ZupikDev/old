#include <SFML/Graphics.hpp>

#include "gameClass.h"
#include "utilsFunc.h"

#include <iostream>
#include <vector>
#include <array>

int main() {
	sf::RenderWindow window(sf::VideoMode(400, 400), "Morpion V3", sf::Style::Close);
	sf::Event events;

    //Transparent circle
    sf::Texture Tcircle_image;
    sf::Sprite Tcircle_sprite;
    if (!Tcircle_image.loadFromFile("img/Tcircle.png")) std::cout << "error loading texture";
    Tcircle_sprite.setTexture(Tcircle_image);
    Tcircle_sprite.scale(0.7f, 0.7f);

    //Normal circle
    sf::Sprite circle_sprite;
    sf::Texture circle_texture;
    if (!circle_texture.loadFromFile("img/circle.png")) std::cout << "error loading texture";
    circle_sprite.setTexture(circle_texture);
    circle_sprite.scale(0.7f, 0.7f);

    //Normal cross
    sf::Texture cross_texture;
    if (!cross_texture.loadFromFile("img/cross.png")) std::cout << "error loading texture";
    sf::Sprite cross_sprite;
    cross_sprite.setTexture(cross_texture);
    cross_sprite.scale(0.7f, 0.7f);

    //Transparent cross
    sf::Texture Tcross_texture;
    if (!Tcross_texture.loadFromFile("img/Tcross.png")) std::cout << "error loading texture";
    sf::Sprite Tcross_sprite;
    Tcross_sprite.setTexture(Tcross_texture);
    Tcross_sprite.scale(0.7f, 0.7f);

	int tics{ 0 }, tacs{ 0 }; // player 1, player 2
    bool p1 = true;
    sf::Sprite sprite;
    sf::RectangleShape current;
    bool started = false;
    bool canSwitch = true;

    bool playable = true;

    std::vector<sf::Sprite> circles;
    std::vector<sf::Sprite> crosses;

	Game game;
	game.Init();

	while (window.isOpen()) {

		game.printBoard(window);

		while (window.pollEvent(events) && playable) {
			if (events.type == sf::Event::Closed) window.close();

            if (events.type == sf::Event::MouseMoved) {
                started = true;
                for (auto& tile : game.tiles) {
                    if (isIn(tile, static_cast<float>(events.mouseMove.x), static_cast<float>(events.mouseMove.y))) current = tile;
                }
            }

            if (events.type == sf::Event::MouseButtonPressed) {
                if (Used(current, tics, tacs)) canSwitch = false;
                else canSwitch = true;
                if (p1 && canSwitch) {
                    for (auto& tile : game.tiles) {
                        if (tile.getGlobalBounds() == current.getGlobalBounds()) {
                            std::pair<float, float> coords = { tile.getGlobalBounds().getPosition().x, tile.getGlobalBounds().getPosition().y };

                            int before = tics;
                            changeValueOfPlayer(tics, coords);

                            if (tics != before) {
                                circle_sprite.setPosition(sf::Vector2f(tile.getGlobalBounds().getPosition().x + 18, tile.getGlobalBounds().getPosition().y + 18));
                                circles.push_back(circle_sprite);
                            }

                            break;
                        }
                    }
                }
                else if (!p1 && canSwitch) {
                    for (auto& tile : game.tiles) {
                        if (tile.getGlobalBounds() == current.getGlobalBounds()) {
                            std::pair<float, float> coords = { tile.getGlobalBounds().getPosition().x, tile.getGlobalBounds().getPosition().y };

                            int before = tacs;
                            changeValueOfPlayer(tacs, coords);

                            if (tacs != before) {
                                cross_sprite.setPosition(sf::Vector2f(tile.getGlobalBounds().getPosition().x + 18, tile.getGlobalBounds().getPosition().y + 18));
                                crosses.push_back(cross_sprite);
                            }

                            break;
                        }
                    }
                }

                if (game.hasWon(tics)) {
                    std::cout << "Player A has won";
                    playable = false;
                }
                else if (game.hasWon(tacs)) {
                    std::cout << "Player B has won";
                    playable = false;;
                }
                else if ((tics | tacs) == 0b111111111) {
                    std::cout << "Well played !";
                    playable = false;;
                }

                if (p1 && canSwitch) {
                    sprite = Tcircle_sprite;
                    p1 = false;
                }
                else if (!p1 && canSwitch) {
                    sprite = Tcross_sprite;
                    p1 = true;
                }
            }
		}

        if (p1 && started)
            printSprite(window, Tcircle_sprite, current.getGlobalBounds().getPosition().x + 18, current.getGlobalBounds().getPosition().y + 18);
        else if (!p1 && started) 
            printSprite(window, Tcross_sprite, current.getGlobalBounds().getPosition().x + 18, current.getGlobalBounds().getPosition().y + 18);

        printTics(window, circles);
        printTics(window, crosses);
          
		window.display();
        window.clear();
	}
}