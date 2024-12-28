#ifndef GAME_H
#define GAME_H
#include <memory>
#include "SpriteManage.h"
#include "StateManage.h"
#include "SFML/Graphics/RenderWindow.hpp"
enum SpriteID
{
    MAIN_FONT,
    GRASS,
    FOOD,
    WALL,
    SNAKE
};

struct Context
{
    std::unique_ptr<SpriteManage> sprites;
    std::unique_ptr<StateManage> states;
    std::unique_ptr<sf::RenderWindow> window;

    Context()
    {
        sprites = std::make_unique<SpriteManage>();
        states = std::make_unique<StateManage>();
        window = std::make_unique<sf::RenderWindow>();
    }
};


class Game {
public:
    Game();
    ~Game();
    void run();

private:
    std::shared_ptr<Context> context;
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
};



#endif //GAME_H
