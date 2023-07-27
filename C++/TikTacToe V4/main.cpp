#include <SFML/Graphics.hpp>

#include "gameClass.h"
#include "utilsFunc.h"

#include <iostream>
#include <vector>
#include <array>

int main() {
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

    bool p1 = true;
    sf::Sprite Tsprite;
    sf::RectangleShape current;
    bool started = false;
    bool canSwitch = true;

    std::vector<sf::Sprite> circles;
    std::vector<sf::Sprite> crosses;

    sf::RenderWindow gameWindow(sf::VideoMode(400, 400), "Morpion V3", sf::Style::Close);
    sf::Event events;

	Game game;
	game.Init(gameWindow);

    while (game.window->isOpen()) {

		game.printBoard();

		while (game.pollEvents(events)) {

			if (events.type == sf::Event::Closed) gameWindow.close();

            if (events.type == sf::Event::MouseMoved && game.playable) {
                started = true;

                for (auto& tile : game.tiles) {
                    if (isIn(tile, static_cast<float>(events.mouseMove.x), static_cast<float>(events.mouseMove.y))) current = tile;
                }
            }

            if (events.type == sf::Event::MouseButtonPressed && game.playable) {

                if (Used(current, game.tics, game.tacs)) canSwitch = false;
                else canSwitch = true;

                if (p1 && canSwitch) {
                    for (auto& tile : game.tiles) {
                        if (tile.getGlobalBounds() == current.getGlobalBounds()) {

                            std::pair<float, float> coords = { tile.getGlobalBounds().getPosition().x, tile.getGlobalBounds().getPosition().y};
                            game.render(game.tics, circle_sprite, circles, coords);
                           
                            break;
                        }
                    }
                }
                else if (!p1 && canSwitch) {
                    for (auto& tile : game.tiles) {
                        if (tile.getGlobalBounds() == current.getGlobalBounds()) {

                            std::pair<float, float> coords = { tile.getGlobalBounds().getPosition().x, tile.getGlobalBounds().getPosition().y };
                            game.render(game.tacs, cross_sprite, crosses, coords);

                            break;
                        }
                    }
                }

                game.checkIfWon();
               
                if (p1 && canSwitch) { Tsprite = Tcircle_sprite; p1 = false; }
                else if (!p1 && canSwitch) { Tsprite = Tcross_sprite;  p1 = true; }
            }
		}

        
        if (started) {
            if (p1) game.update(Tcircle_sprite, current.getGlobalBounds().getPosition().x + 18, current.getGlobalBounds().getPosition().y + 18, circles, crosses);
            else game.update(Tcross_sprite, current.getGlobalBounds().getPosition().x + 18, current.getGlobalBounds().getPosition().y + 18, circles, crosses);
        }
           
        game.window->display(); // or gameWindow.display()
        game.window->clear();
	}
}