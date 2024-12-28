#include "Game.h"
#include "Menu.h"

Game::Game() : context(std::make_shared<Context>())
{
    sf::Vector2u vector(640, 480);
    context->window->create(sf::VideoMode(vector), "Snake Game", sf::Style::Close);
    context->sprites->addFont(MAIN_FONT, "/Users/niklesunenko/CLionProjects/SnakeGame/SpritesAndFonts/Movistar-Text-Regular.ttf");
    context->sprites->addTexture(GRASS, "/Users/niklesunenko/CLionProjects/SnakeGame/SpritesAndFonts/grass.png", true);
    context->sprites->addTexture(FOOD, "/Users/niklesunenko/CLionProjects/SnakeGame/SpritesAndFonts/apple.png");
    context->sprites->addTexture(WALL, "/Users/niklesunenko/CLionProjects/SnakeGame/SpritesAndFonts/wall.png", true);
    context->sprites->addTexture(SNAKE, "/Users/niklesunenko/CLionProjects/SnakeGame/SpritesAndFonts/snake.png");
    context->states->push(std::make_unique<Menu>(context));
}

Game::~Game() = default;

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (context->window->isOpen())
    {
        timeSinceLastFrame += clock.restart();

        while (timeSinceLastFrame > TIME_PER_FRAME)
        {
            timeSinceLastFrame -= TIME_PER_FRAME;

            context->states->processChanges();

            if (!context->states->isEmpty())
            {
                context->states->getCur()->processInput();
                context->states->getCur()->update(TIME_PER_FRAME);
                context->states->getCur()->draw();
            }
            else
            {
                context->window->close();
            }
        }
    }
}