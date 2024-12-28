#ifndef SPRITEMANAGE_H
#define SPRITEMANAGE_H
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>
using namespace std;



class SpriteManage {
public:
    SpriteManage();
    ~SpriteManage();
    void addTexture(int id, const string& filePath, bool ifRepeated = false);
    void addFont(int id, const string& filePath);
    const sf::Texture& getTexture(int id) const;
    const sf::Font& getFont(int id) const;
private:
    map<int, sf::Texture> textures;
    map<int, sf::Font> fonts;
};



#endif //SPRITEMANAGE_H
