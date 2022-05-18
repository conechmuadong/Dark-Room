#include "button.h"

using namespace std;
Button::Button(string address)
{
    this->initVariable(address);
}
void Button::initVariable(string address)
{
    this->texture.loadFromFile(address);
    this->sprite.setTexture(this->texture);
}
bool Button::isClick(const sf::Event &event) const
{
    return this->sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
}
void Button::render(sf::RenderTarget *target)
{
    target->draw(this->sprite);
}
