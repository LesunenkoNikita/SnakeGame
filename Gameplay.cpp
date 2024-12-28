#include "Gameplay.h"

#include <SFML/Window/Event.hpp>
#include <stdlib.h>
#include <time.h>

Gameplay::Gameplay(std::shared_ptr<Context> &context)
    : context(context),
      snakeDirection({16.f, 0.f}),
      elapsedTime(sf::Time::Zero),
      grass(context->sprites->getTexture(GRASS)),
      food(context->sprites->getTexture(FOOD)),
      snake(context)
{
    srand(time(nullptr));
}

Gameplay::~Gameplay()
{
}

void Gameplay::init()
{
    grass.setTextureRect(context->window->getViewport(context->window->getDefaultView()));

    for (auto &wall : walls)
    {
        wall.setTexture(context->sprites->getTexture(WALL));
    }

    sf::Vector2<int> position0(0, 0);
    sf::Vector2<int> size0((int)context->window->getSize().x, 16);
    sf::IntRect rect0(position0, size0);
    walls[0].setTextureRect(rect0);

    sf::Vector2<int> position1(0, 0);
    sf::Vector2<int> size1((int)context->window->getSize().x, 16);
    sf::IntRect rect1(position1, size1);
    walls[1].setTextureRect(rect1);
    sf::Vector2f position1f(0.f, (float)(context->window->getSize().y - 16));
    walls[1].setPosition(position1f);

    sf::Vector2<int> position2(0, 0);
    sf::Vector2<int> size2(16, (int)context->window->getSize().y);
    sf::IntRect rect2(position2, size2);
    walls[2].setTextureRect(rect2);

    sf::Vector2<int> position3(0, 0);
    sf::Vector2<int> size3(16, (int)context->window->getSize().y);
    sf::IntRect rect3(position3, size3);
    walls[3].setTextureRect(rect3);
    sf::Vector2f position3f((float)(context->window->getSize().x - 16), 0.f);
    walls[3].setPosition(position3f);

    sf::Vector2f foodPosition((float)(context->window->getSize().x / 2), (float)(context->window->getSize().y / 2));
    food.setPosition(foodPosition);

    snake.init();
}

void Gameplay::processInput()
{
    while (const std::optional<sf::Event> optEvent = context->window->pollEvent())
    {
        const sf::Event& event = *optEvent;
        if (event.is<sf::Event::Closed>())
        {
            context->states->popAll();
        }
        else if (event.is<sf::Event::KeyPressed>())
        {
            sf::Vector2f newDirection = snakeDirection;
            const auto* keyEvent = event.getIf<sf::Event::KeyPressed>();
            switch (keyEvent->code)
            {
            case sf::Keyboard::Key::Up:
                newDirection = {0.f, -16.f};
                break;
            case sf::Keyboard::Key::Down:
                newDirection = {0.f, 16.f};
                break;
            case sf::Keyboard::Key::Left:
                newDirection = {-16.f, 0.f};
                break;
            case sf::Keyboard::Key::Right:
                newDirection = {16.f, 0.f};
                break;
            default:
                break;
            }
            if (std::abs(snakeDirection.x) != std::abs(newDirection.x) ||
                std::abs(snakeDirection.y) != std::abs(newDirection.y))
            {
                snakeDirection = newDirection;
            }
        }
    }
}

void Gameplay::update(const sf::Time &deltaTime)
{
    elapsedTime += deltaTime;
    if (elapsedTime.asSeconds() > 0.1)
    {
        for (auto &wall : walls)
        {
            if (snake.ifOn(wall))
            {
                //context->states->push(std::make_unique<GameOver>(context), true);
                break;
            }
        }
        if (snake.ifOn(food))
        {
            snake.grow(snakeDirection);

            int x = 0, y = 0;
            x = std::clamp<int>(rand() % context->window->getSize().x, 16, context->window->getSize().x - 2 * 16);
            y = std::clamp<int>(rand() % context->window->getSize().y, 16, context->window->getSize().y - 2 * 16);
            sf::Vector2f position(x, y);
            food.setPosition(position);
        }
        else
        {
            snake.move(snakeDirection);
        }

        if (snake.ifSelfIntersecting())
        {
            //context->states->push(std::make_unique<GameOver>(context), true);
        }

        elapsedTime = sf::Time::Zero;
    }
}

void Gameplay::draw()
{
    context->window->clear();
    context->window->draw(grass);

    for (auto &wall : walls)
    {
        context->window->draw(wall);
    }
    context->window->draw(food);
    context->window->draw(snake);

    context->window->display();
}