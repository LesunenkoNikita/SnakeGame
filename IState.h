#ifndef ISTATE_H
#define ISTATE_H
#include <SFML/System/Time.hpp>

class IState {
public:
    IState() {}
    virtual ~IState() {}
    virtual void init() = 0;
    virtual void processInput() = 0;
    virtual void update(const sf::Time& deltaTime) = 0;
    virtual void draw() = 0;
};

#endif //ISTATE_H
