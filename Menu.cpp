#include "Menu.h"
#include <SFML/Window/Event.hpp>
#include<SFML/Window/Window.hpp>
#include "Gameplay.h"

Menu::Menu(std::shared_ptr<Context> &context)
    : context(context), ifPlayButtonSelected(true),
      ifPlayButtonPressed(false), ifExitButtonSelected(false),
      ifExitButtonPressed(false), gameTitle(context->sprites->getFont(MAIN_FONT), "Snake Game", 30),
      playButton(context->sprites->getFont(MAIN_FONT), "Play", 20),
      exitButton(context->sprites->getFont(MAIN_FONT), "Exit", 20)
{
}

Menu::~Menu() = default;


void Menu::init()
{
    sf::Vector2f position(gameTitle.getLocalBounds().size.x / 2, gameTitle.getLocalBounds().size.y / 2);
    gameTitle.setOrigin(position);
    sf::Vector2f position2(640/2, 480/2-150.f);
    gameTitle.setPosition(position2);

    sf::Vector2f position3(playButton.getLocalBounds().size.x / 2, playButton.getLocalBounds().size.y / 2);
    playButton.setOrigin(position3);
    sf::Vector2f position4(640/2, 480/2-25.f);
    playButton.setPosition(position4);

    sf::Vector2f position5(exitButton.getLocalBounds().size.x / 2,exitButton.getLocalBounds().size.y / 2);
    exitButton.setOrigin(position5);
    sf::Vector2f position6(640/2, 480/2+25.f);
    exitButton.setPosition(position6);
}

void Menu::processInput()
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
            const auto* keyEvent = event.getIf<sf::Event::KeyPressed>();
            switch (keyEvent->code)
            {
            case sf::Keyboard::Key::Up:
            {
                if (!ifPlayButtonSelected)
                {
                    ifPlayButtonSelected = true;
                    ifExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Key::Down:
            {
                if (!ifExitButtonSelected)
                {
                    ifPlayButtonSelected = false;
                    ifExitButtonSelected = true;
                }
                break;
            }
                case sf::Keyboard::Key::Enter:
            {
                ifPlayButtonPressed = false;
                ifExitButtonPressed = false;

                if (ifPlayButtonSelected)
                {
                    ifPlayButtonPressed = true;
                }
                else
                {
                    ifExitButtonPressed = true;
                }

                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
}

void Menu::update(const sf::Time &deltaTime)
{
    if (ifPlayButtonSelected)
    {
        playButton.setFillColor(sf::Color::Black);
        exitButton.setFillColor(sf::Color::White);
    }
    else
    {
        exitButton.setFillColor(sf::Color::Black);
        playButton.setFillColor(sf::Color::White);
    }

    if (ifPlayButtonPressed)
    {
        context->states->push(std::make_unique<Gameplay>(context), true);
    }
    else if (ifExitButtonPressed)
    {
        context->states->popAll();
    }
}

void Menu::draw()
{
    context->window->clear(sf::Color::Blue);
    context->window->draw(gameTitle);
    context->window->draw(playButton);
    context->window->draw(exitButton);
    context->window->display();
}


