#include "mainmenu.h"

void Menu::initVariables()
{
    //this->font.loadFromFile("LP Allema.ttf");
}

void Menu::initSprite()
{
    this->texture1.loadFromFile("data/button/Play.png");
    this->sprite1.setTexture(this->texture1);
    this->texture2.loadFromFile("data/button/Exit.png");
    this->sprite2.setTexture(this->texture2);
    this->sprite1.setScale(sf::Vector2f(0.2,0.2));
    this->sprite2.setScale(sf::Vector2f(0.2,0.2));
    this->sprite1.move(sf::Vector2f(350,250));
    this->sprite2.move(sf::Vector2f(350,350));
}
void Menu::initBackground()
{
    this->bgTexture.loadFromFile("data/bg/menu/background.png");
    this->background.setTexture(this->bgTexture);
}
Menu::Menu()//:
    //playButton("data/button/Play.png"),
    //exitButton("data/button/Exit.png")
{
    this->initVariables();
    //this->initText();
    //this->initShape();
    this->initSprite();
    this->initBackground();
}

int Menu::getEvent(sf::RenderTarget *target)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        return 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        return -1;
}

/*int Menu::getEvent(sf::RenderTarget *target, sf::Event event)
{
    if(this->playButton.isClick(event)) //aka click Play
        {
            return 1;
        }
    if(this->exitButton.isClick(event)) //aka click Exit
        {
           return -1;
        }
}*/
void Menu::render(sf::RenderTarget *target)
{
    target->draw(this->background);
    //this->playButton.render(target);
    //this->exitButton.render(target);
    target->draw(this->sprite1);
    target->draw(this->sprite2);
}
