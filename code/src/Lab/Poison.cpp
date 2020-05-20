#include "Poison.hpp"
#include "Bacterium.hpp"
#include "SimpleBacterium.hpp"
#include "SwarmBacterium.hpp"
#include "TwitchingBacterium.hpp"
#include "MadBacterium.hpp"
#include "PoisonousBacterium.hpp"
#include <Application.hpp>
#include <Utility/Utility.hpp>

//Static member's initialization
int Poison::compteur_ = 0;

//Constructeurs et destructeur:
Poison::Poison(const Vec2d& poscenter)
    :CircularBody(poscenter, getConfig()["quantity"].toDouble()/getConfig()["factor size division"].toDouble()),
     color_(getConfig()["color"]), quantity_(getConfig()["quantity"].toDouble())
{
    compteur_+= 1;
}

Poison::~Poison()
{
    compteur_-=1;
}

Poison::Poison(const Poison& other)
    :CircularBody (other.getPosition(), other.getRadius()),
     color_(other.color_), quantity_(other.quantity_)
{
    compteur_ += 1;
}

//Getters et setter:
j::Value& Poison::getConfig() const
{
    return getAppConfig()["poison"];
}

Quantity Poison::getQuantity() const
{
    return quantity_;
}

void Poison::eatPoison()
{
    quantity_ = 0;
    setRadius(quantity_);
}

bool Poison::iseaten()
{
    return quantity_<= 0;
}

int Poison::getCompteur()
{
    return compteur_;
}

void Poison::drawOn(sf::RenderTarget& target) const
{
    auto const circle = buildCircle(getPosition(), getRadius(), color_.get());
    target.draw(circle);

    if (isDebugOn()) {
        sf::Text const texte = buildText(std::to_string((int)(quantity_)),
                                         Vec2d(getPosition().x -5, getPosition().y +  getRadius()+10),
                                         getAppFont(), 15, sf::Color::Black);
        target.draw(texte);
    }
}

Quantity Poison::eatenBy(Bacterium& bact)
{
    Quantity quantity(quantity_ * bact.eatablePoison(*this));
    if  (quantity >0) {
        eatPoison();
    }
    return (quantity);
}

Quantity Poison::eatenBy(SimpleBacterium& bact)
{
    return bact.getPoisoneffects();
}

Quantity Poison::eatenBy(TwitchingBacterium& bact)
{
    return bact.getPoisoneffects();
}

Quantity Poison::eatenBy(SwarmBacterium& bact)
{
    return bact.getPoisoneffects();
}

Quantity Poison::eatenBy(PoisonousBacterium& bact)
{
    return bact.getPoisoneffects();
}

Quantity Poison::eatenBy(MadBacterium& bact)
{
    return bact.getPoisoneffects();
}
