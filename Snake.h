#ifndef SNAKE_H
#define SNAKE_H

#include <list>
#include "Game.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Snake : public sf::Drawable
{
public:
    Snake(std::shared_ptr<Context> &context);
    ~Snake();
    void init();
    void move(const sf::Vector2f &direction);
    bool ifOn(const sf::Sprite &other) const;
    void grow(const sf::Vector2f &direction);
    bool ifSelfIntersecting() const;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
    std::list<sf::Sprite> body;
    std::list<sf::Sprite>::iterator head;
    std::list<sf::Sprite>::iterator tail;
};

#endif //SNAKE_H
