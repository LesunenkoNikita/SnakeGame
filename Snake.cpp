#include "Snake.h"
#include "Game.h"
Snake::Snake(std::shared_ptr<Context> &context) : body(4, sf::Sprite(context->sprites->getTexture(SNAKE)))
{
    head = --body.end();
    tail = body.begin();
}

Snake::~Snake()
{
}

void Snake::init()
{
    float x = 16.f;
    for (auto &piece : body)
    {
        piece.setPosition({x, 16.f});
        x += 16.f;
    }
}

void Snake::move(const sf::Vector2f &direction)
{
    tail->setPosition(head->getPosition() + direction);
    head = tail;
    ++tail;

    if (tail == body.end())
    {
        tail = body.begin();
    }
}

bool Snake::ifOn(const sf::Sprite &other) const
{
    auto intersection = other.getGlobalBounds().findIntersection(head->getGlobalBounds());
    return intersection.has_value();
}


void Snake::grow(const sf::Vector2f &direction)
{
    sf::Sprite newPiece(body.begin()->getTexture());
    newPiece.setPosition(head->getPosition() + direction);
    head = body.insert(++head, newPiece);
}

bool Snake::ifSelfIntersecting() const
{
    bool flag = false;

    for (auto piece = body.begin(); piece != body.end(); ++piece)
    {
        if (head != piece)
        {
            flag = ifOn(*piece);

            if (flag)
            {
                break;
            }
        }
    }

    return flag;
}

void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto &piece : body)
    {
        target.draw(piece);
    }
}