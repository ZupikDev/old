#include <SFML/Graphics.hpp>

class entityClass {
public:
    entityClass(sf::RenderWindow& _Window, sf::Sprite _Sprite, sf::Vector2f _Pos, int _Index) {
        window = &_Window;
        sprite = _Sprite;
        pos = _Pos;
        index = _Index;
    }

private:
    sf::RenderWindow* window;
    sf::Sprite sprite;
    sf::Vector2f pos;
    int index;

public:
    void print_sprite() {
        this->sprite.setPosition(pos.x, pos.y);
        this->window->draw(this->sprite);
    }

    int get_index() { return index; }
};