#include "Nutriment.hpp"
#include <Application.hpp>
#include <Utility/Utility.hpp>

//Constructeur:
Nutriment::Nutriment(const Quantity quantity, const Vec2d& poscenter)
    : CircularBody(poscenter, quantity),
      quantity_(quantity)
{}

//Getters et setter:
j::Value const& Nutriment::getConfig() const
{
    return getAppConfig()["nutriments"];
}

Quantity Nutriment::getQuantity() const
{
    return quantity_;
}

void Nutriment::setQuantity(Quantity newquantity)
{
    if (newquantity >= 0) {
        quantity_= newquantity;
    } else {
        quantity_ = 0;
    }

    setRadius(quantity_);
}

//Autres méthodes:
Quantity Nutriment::takeQuantity(const Quantity totake)
{
    double taken(quantity_);

    if (totake <= quantity_) {
        taken = totake;
    }

    quantity_ -= taken;
    setRadius(quantity_);
    return taken;
}

void Nutriment::drawOn(sf::RenderTarget& target) const
{
    int taille_graphique(6);
    auto const& texture = getAppTexture(getConfig()["texture"].toString());
    auto nutrimentSprite = buildSprite(getPosition(), taille_graphique, texture);
    // adapte la taille du Sprite au rayon du nutriment:
    nutrimentSprite.setScale(2 * getRadius() / texture.getSize().x, 2 * getRadius() / texture.getSize().y);
    target.draw(nutrimentSprite);

    if (isDebugOn()) { //mode debug
        sf::Text const texte = buildText(std::to_string((int)(quantity_)),
                                         Vec2d(getPosition().x -5, getPosition().y +  getRadius()+10),
                                         getAppFont(), 15, sf::Color::Black);
        target.draw(texte);
    }
}

void Nutriment::update(sf::Time dt)
{
    if (canGrow()) {
        double speed(getConfig()["growth"]["speed"].toDouble());
        auto growth = speed * dt.asSeconds();
        quantity_ += growth;
        setRadius(quantity_);
    }
}

bool Nutriment::depleted() const
{
    return (int(quantity_) <=0); // <=pour éviter que les nutriments aient
    //tendance à grandir alors qu'ils devraient disparaître
}

//Méthode privée:
bool Nutriment::canGrow() const
{
    double temperature(getAppEnv().getTemperature());
    return (temperature >= getConfig()["growth"]["min temperature"].toDouble() and
            temperature < getConfig()["growth"]["max temperature"].toDouble() and
            quantity_ < 2* getConfig()["quantity"]["max"].toDouble() and
            getAppEnv().contains(*this));
}







