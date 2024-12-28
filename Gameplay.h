#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <memory>
#include <array>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Game.h"
#include "IState.h"
#include "Snake.h"

class Gameplay : public IState
{
public:
    Gameplay(std::shared_ptr<Context> &context);
    ~Gameplay();

    void init() override;
    void processInput() override;
    void update(const sf::Time& deltaTime) override;
    void draw() override;

private:
    std::shared_ptr<Context> context;
    sf::Sprite grass;
    sf::Sprite food;
    std::array<sf::Sprite, 4> walls = {
        sf::Sprite(context->sprites->getTexture(WALL)),
        sf::Sprite(context->sprites->getTexture(WALL)),
        sf::Sprite(context->sprites->getTexture(WALL)),
        sf::Sprite(context->sprites->getTexture(WALL))
    };
    Snake snake;

    sf::Vector2f snakeDirection;
    sf::Time elapsedTime;
};



#endif //GAMEPLAY_H
