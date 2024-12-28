#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics/Text.hpp>
#include "IState.h"
#include "Game.h"
#include <memory>

class Menu : public IState
{
private:
    std::shared_ptr<Context> context;
    sf::Text gameTitle;
    sf::Text playButton;
    sf::Text exitButton;

    bool ifPlayButtonSelected;
    bool ifPlayButtonPressed;

    bool ifExitButtonSelected;
    bool ifExitButtonPressed;

public:
    Menu(std::shared_ptr<Context>& context);
    ~Menu();

    void init() override;
    void processInput() override;
    void update(const sf::Time& deltaTime) override;
    void draw() override;
};



#endif //MENU_H
