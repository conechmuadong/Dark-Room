#pragma once

#include<SFML/Graphics.hpp>
#include<string>

using namespace std;
class Button
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    void initVariable(string address);
public:
    Button(string address);
    bool isClick(const sf::Event & event) const;
    void render(sf::RenderTarget *target);
};
