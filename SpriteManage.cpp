#include "SpriteManage.h"
using namespace std;
#include <map>

SpriteManage::SpriteManage() = default;

SpriteManage::~SpriteManage() = default;


void SpriteManage::addTexture(int id, const string &filePath, bool ifRepeated) {
    sf::Texture texture;
    if (texture.loadFromFile(filePath)) {
        texture.setRepeated(ifRepeated);
        textures[id] = std::move(texture);
    }
}

void SpriteManage::addFont(int id, const string &filePath) {
    sf::Font font;
    if (font.openFromFile(filePath)) {
        fonts[id] = std::move(font);
    }
}

const sf::Font &SpriteManage::getFont(int id) const {
    return fonts.at(id);
}

const sf::Texture &SpriteManage::getTexture(int id) const {
    return textures.at(id);
}


