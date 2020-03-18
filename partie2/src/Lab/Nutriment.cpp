#include "Nutriment.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

Nutriment::Nutriment(const Quantity quantity, const Vec2d& poscenter)
    : CircularBody(poscenter, quantity),
      quantity_(quantity)
{}

Quantity Nutriment::takeQuantity(const Quantity totake)
{
    if (totake <= quantity_)
    {
        quantity_ -= totake;
        return totake;
    }
    double quantite(quantity_);
    quantity_ = 0;
    std::cerr<< quantity_;
    return quantite;


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
        sf::Text const texte = buildText(std::to_string((int)(quantity_)),
                            Vec2d(getPosition().x -5, getPosition().y +  getRadius()+10),
                                         getAppFont(), 15, sf::Color::Black);
        target.draw(texte);
    }
}

j::Value const& Nutriment::getConfig() const
{
    return getAppConfig()["nutriments"];
}

void Nutriment::update(sf::Time dt)
{
    if (cangrow()) //fait les tests avant la croissance et non après... à revoir?
    {
    double speed(getAppConfig()["growth"]["speed"].toDouble());
    auto growth = speed * dt.asSeconds();

    }
}

bool Nutriment::cangrow()
{
    double temperature(getAppEnv().getTemperature());
    if (temperature >= getAppConfig()["growth"]["min temperature"].toDouble() and
            temperature < getAppConfig()["growth"]["max temperature"].toDouble() and
            quantity_ < 2* getAppConfig()["quantity"]["max"].toDouble() and
            getAppEnv().contains(*this))
    {
        return true;
    }
    return false;
}










