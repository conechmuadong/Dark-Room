#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "button.h"
class Menu{
private:
    sf::Font font;

    sf::Sprite sprite1;
    sf::Sprite sprite2;
    sf::Texture texture1;
    sf::Texture texture2;

    //Button playButton;
    //Button exitButton;

    sf::Sprite background;
    sf::Texture bgTexture;



    void initVariables();
    void initSprite();
    void initBackground();
public:
    Menu();
    void render(sf::RenderTarget *target);
    int getEvent(sf::RenderTarget *target);
};
