#ifndef ENTITYCLASS_H
#define ENTITYCLASS_H

#include <SFML/Graphics.hpp>

template <typename Sprite>
class entityClass {
public:
	entityClass(Sprite _Sprite, sf::Vector2f _Pos) {
		sprite = _Sprite;
		pos = _Pos;
	}

private:
	Sprite sprite;
	sf::Vector2f pos;
};

#endif // ENTITYCLASS_H
