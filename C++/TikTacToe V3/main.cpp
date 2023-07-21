#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "entityClass.cpp"

std::vector<sf::RectangleShape> print_map(sf::RenderWindow& window) {
    std::vector<sf::RectangleShape> out;

    sf::RectangleShape r1(sf::Vector2f(400 / 3 - 3, 400 / 3 - 3));
    r1.setPosition(0, 0);
    out.push_back(r1);

    sf::RectangleShape r2(sf::Vector2f(400 / 3 - 3, 400 / 3 - 3));
    r2.setPosition(400 / 3, 0);
    out.push_back(r2);

    sf::RectangleShape r3(sf::Vector2f(400 / 3, 400 / 3 - 3));
    r3.setPosition(400 / 3 * 2, 0);
    out.push_back(r3);

    sf::RectangleShape r4(sf::Vector2f(400 / 3 - 3, 400 / 3 - 3));
    r4.setPosition(0, 400 / 3);
    out.push_back(r4);

    sf::RectangleShape r5(sf::Vector2f(400 / 3 - 3, 400 / 3 - 3));
    r5.setPosition(400 / 3, 400 / 3);
    out.push_back(r5);

    sf::RectangleShape r6(sf::Vector2f(400 / 3, 400 / 3 - 3));
    r6.setPosition(400 / 3 * 2, 400 / 3);
    out.push_back(r6);

    sf::RectangleShape r7(sf::Vector2f(400 / 3 - 3, 400 / 3));
    r7.setPosition(0, 400 / 3 * 2);
    out.push_back(r7);

    sf::RectangleShape r8(sf::Vector2f(400 / 3 - 3, 400 / 3));
    r8.setPosition(400 / 3, 400 / 3 * 2);
    out.push_back(r8);

    sf::RectangleShape r9(sf::Vector2f(400 / 3, 400 / 3));
    r9.setPosition(400 / 3 * 2, 400 / 3 * 2);
    out.push_back(r9);

    for (auto & square : out) {
        square.setFillColor(sf::Color(13, 13, 13));
        square.setOutlineThickness(3.f);
        square.setOutlineColor(sf::Color::White);
        window.draw(square);
    }

    return out;

}

int check_if_playable(int map[9]) {
    /* Returns 1 if playable 
       Returns -1 if toe
       Returns 0 if somebody won
    */

    // row
    for (int i = 0; i < 3; i++) {
        if ((map[i * 3] == map[i * 3 + 1] && map[i * 3 + 1] == map[i * 3 + 2])
            && map[i * 3] != 0) {
            return 0;
        }
    }

    //colums
    for (int i = 0; i < 3; i++) {
        if ((map[i] == map[i + 3] && map[i + 3] == map[i + 6])
            && map[i] != 0) {
            return 0;
        }
    }

    //diag
    if (((map[0] == map[4] && map[4] == map[8]) || (map[2] == map[4] && map[4] == map[6]))
        && map[4] != 0) {
        return 0;
    }

    // empty case ?
    for (int i = 0; i < 9; i++) {
        if (map[i] == 0) return 1;
    }

    return -1;
}

bool isIn(int x, int y, sf::RectangleShape rectangle) {
    if (rectangle.getGlobalBounds().contains(x, y)) return true;
    return false;
}

bool check_if_empty(std::vector<entityClass> cases, int index_of_case) {
    /*checks if the case which corresponds to the case number index_of_case is empty*/
    for (auto& entity_circle : cases) {
        if (entity_circle.get_index() == index_of_case)
            return false;
    }
    return true;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "Morpion V3", sf::Style::Close);
    window.setFramerateLimit(400);

    std::vector<sf::RectangleShape> world;
    std::vector<std::pair<sf::RectangleShape, sf::Sprite>> _Where_mouse_is;
    bool pressed = false;
    int _index_of_current_square = 0;

    sf::Sprite temp;

    std::vector<entityClass> circles;
    std::vector<entityClass> crosses;
    int map[9] = { 0,0,0,0,0,0,0,0,0 };

    // Transparent circle
    sf::Texture Tcircle_image;
    if (!Tcircle_image.loadFromFile("img/Tcircle.png")) std::cout << "(TC) error";
    sf::Sprite Tcircle_sprite;
    Tcircle_sprite.setTexture(Tcircle_image);
    Tcircle_sprite.scale(0.7,0.7);

    //Normal circle
    sf::Sprite circle_sprite;
    sf::Texture texture;
    if (!texture.loadFromFile("img/circle.png")) std::cout << "an error occured";
    circle_sprite.setTexture(texture);
    circle_sprite.scale(0.7, 0.7);

    //cross
    sf::Texture cross_texture;
    if (!cross_texture.loadFromFile("img/cross.png")) std::cout << "cross error";
    sf::Sprite cross_sprite;
    cross_sprite.setTexture(cross_texture);
    cross_sprite.scale(0.7, 0.7);

    //transparent cross
    sf::Texture Tcross_texture;
    if (!Tcross_texture.loadFromFile("img/Tcross.png")) std::cout << "cross error";
    sf::Sprite Tcross_sprite;
    Tcross_sprite.setTexture(Tcross_texture);
    Tcross_sprite.scale(0.7, 0.7);

    int player = 1;
    bool canSwitch = false;
    bool playable = true;

    while (window.isOpen()) {
        sf::Event event;

        world = print_map(window);

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseMoved && playable) {

                player == 1 ? temp = Tcircle_sprite : temp = Tcross_sprite;

                for (auto& square : world) {
                    if (isIn(event.mouseMove.x, event.mouseMove.y, square) ) {
                        temp.setPosition(sf::Vector2f(square.getGlobalBounds().getPosition().x + 18, square.getGlobalBounds().getPosition().y + 18));
                        std::pair<sf::RectangleShape, sf::Sprite> _where{ square, temp };
                        _Where_mouse_is.push_back(_where);
                        _index_of_current_square = 0;
                        
                    }
                    _index_of_current_square++;
                }

                if (!_Where_mouse_is.empty() && !isIn(event.mouseMove.x, event.mouseMove.y, _Where_mouse_is[0].first)) {
                    _index_of_current_square = 0;
                    _Where_mouse_is.clear();      
                }
            }

            else if (event.type == sf::Event::MouseButtonPressed && playable) {
                if (!_Where_mouse_is.empty()) {
                    bool empty_case = true;
                    if (player == 1) {
                        if (!circles.empty()) {
                            empty_case = check_if_empty(circles, 9 - _index_of_current_square);
                        }

                        if (empty_case && check_if_empty(crosses, 9 - _index_of_current_square)) {
                            entityClass circle(window,
                                circle_sprite,
                                { _Where_mouse_is[0].first.getGlobalBounds().getPosition().x + 18,  _Where_mouse_is[0].first.getGlobalBounds().getPosition().y + 18 },
                                9 - _index_of_current_square);

                            circles.push_back(circle);
                            map[9 - _index_of_current_square] = 1;
                            canSwitch = true;
                        }
                    }
                    else if(player == 2) {
                        bool empty_case = true;

                        if (!crosses.empty()) {
                            empty_case = check_if_empty(crosses, 9 - _index_of_current_square);
                        }

                        if (empty_case && check_if_empty(circles, 9 - _index_of_current_square)) {
                            entityClass cross(window,
                                cross_sprite,
                                { _Where_mouse_is[0].first.getGlobalBounds().getPosition().x + 18,  _Where_mouse_is[0].first.getGlobalBounds().getPosition().y + 18 },
                                9 - _index_of_current_square);

                            crosses.push_back(cross);
                            map[9 - _index_of_current_square] = 2;
                            canSwitch = true;
                        }
                    }

                    if (check_if_playable(map) == 0) {
                        if (player == 1) std::cout << "Player 1 won";
                        else if (player == 2) std::cout << "Player 2 won";
                        playable = false;
                    }
                    else if (check_if_playable(map) == -1) {
                        std::cout << "Toe";
                        playable = false;
                    }

                    if (player == 1 && canSwitch) {
                        player = 2;
                    }
                    else if (player == 2 && canSwitch) {
                        player = 1;
                    }

                    canSwitch = false;
                }
            }
        }
         
        if (!_Where_mouse_is.empty()) window.draw(_Where_mouse_is[0].second);

        for (auto& circle : circles) {
             circle.print_sprite();
        }

        for (auto& cross : crosses) {
            cross.print_sprite();
        }

        window.display();
        window.clear(sf::Color::Black);

    }
    return 0;
}