#include "Nutriment.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

Nutriment::Nutriment(const Quantity quantity, const Vec2d& poscenter)
    : CircularBody(poscenter, quantity),
      quantity_(quantity)
{}

Quantity Nutriment::takeQuantity(const Quantity totake)
{
    if (totake >= quantity_)
    {
        quantity_ -= totake;
    }
}

void Nutriment::setQuantity(Quantity newquantity)
{
    if (newquantity >= 0)
    {
        quantity_= newquantity;
    }
    else
    {
        quantity_ = 0;
    }
    setRadius(quantity_);
}

void Nutriment::drawOn(sf::RenderTarget& target) const
{

    int taille_graphique(6);
    auto const& texture = getAppTexture(getConfig()["texture"].toString());
    auto nutrimentSprite = buildSprite(getPosition(), taille_graphique, texture);
    // adapte la taille du Sprite au rayon du nutriment:
    nutrimentSprite.setScale(2 * getRadius() / texture.getSize().x, 2 * getRadius() / texture.getSize().y);
    target.draw(nutrimentSprite);

    if (isDebugOn()) //mode debug
    {
        //std::string chaine(std::to_string(quantity_));
        sf::Text const texte = buildText(std::to_string(quantity_),
                            Vec2d(20,20),getAppFont(), 15, sf::Color::Black);
        target.draw(texte);
    }
}

j::Value const& Nutriment::getConfig() const
{
    return getAppConfig()["nutriments"];
}

